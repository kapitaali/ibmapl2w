/*-p-ap999-----------------------------------------------------------
 *
 * Module Name: ap999.c
 *
 * Descriptive Name: Auxiliary Processor 999
 *
 *
 * Copyright:   Workstation APL2        Version 2.0
 *              Licensed Materials - Property of IBM
 *              (c) Copyright IBM Corp. 1994, 2002
 *
 * Function: Sample Auxiliary Processor implementing client-server
 *           protocol.  For hard working programmers with deadlines,
 *           this sample server will "catch some ZZZZZZ's" for a
 *           client who has no time to sleep for himself.
 *
 *
 * Notes:
 *
 *    Dependencies: None
 *
 *    Restrictions: None
 *
 * Module Type: C
 *
 * Change Activity:
 *
 *-Z----------------------------------------------------------------*/

#include <stdlib.h>
#include <string.h>
#include "aplobj.h"
#include "apserver.h"

#define INVALID_REQ  -1                 /* catch-all rc for unfriendly AP   */
#define SYSTEM_LIMIT -2                 /* requested space is unavailable   */

int _System sleep_init(void *);         /* AP Server "init" callback fn     */
int _System sleep_server(void *);       /* AP Server "process" callback fn  */
int _System sleep_exit(void *);         /* AP Server "exit" callback fn     */

static int error_code(void *, int);     /* error handler                    */

/*-F-main---------------------------------------------------------------------
 *
 * Purpose:    Auxiliary Processor 999 - main routine runs the general
 *             AP Server with standard callback to one or more of the 4
 *             AP Server callback routines identified in the parameter list.
 *             The 4 callback routines are named in parms 3-6 of apserver, and
 *             provide the following function:
 *                1. AP initialization, prior to accepting the client share
 *                2. multiple event wait and non-SVP event handling
 *                3. process a client request (passed in shared variable)
 *                4. AP exit cleanup on retraction of the share
 *             (Note: if a callback function is not provided, set parm to NULL)
 *
 * Arguments:  int      argc        Number of elements in argv
 *             char **  argv        Argument pointer array
 *             char **  envp        Environment pointer array
 *
 * Results:    int                  Exit Return Code
 *
 *--------------------------------------------------------------------------*/

int main(int argc, char **argv, char **envp) {

   return(apserver(argc, argv, sleep_init, NULL, sleep_server, sleep_exit));
/*                             init        wait  process       exit        */
}



/*-F-sleep_init---------------------------------------------------------------
 *
 * Purpose:    Server initialization callback - called by the AP Server prior
 *             to accepting the share to fully couple with the client.  The
 *             typical things done by an AP here are to open files, allocate
 *             global storage, initialize a global data structure and store
 *             its address in the user token field of the srvtoken, etc...
 *             Via SRVPXID and SRVNAME, the AP can examine the client's
 *             fully-qualified SVP identification and the name of the share.
 *             If the AP decides not to accept the share, it returns from
 *             this init routine with return code SRV_REJECT_SHARE.
 *
 * Arguments:  void * srvtoken       pointer to AP Server token
 *
 *             SRVUTOK(srvtoken)     macro returns user token (AP defined)
 *             SRVNAME(srvtoken)     macro returns shared variable name
 *             SRVPXID(srvtoken)     macro returns partner's extended ID
 *             SRVSRBP(srvtoken)     macro returns SVP share request block ptr
 *
 * Results:    int      Return Code
 *                      0 = success
 *                      SRV_REJECT_SHARE = AP Server just quietly ends thread
 *                      other = error condition (Server message & end thread)
 *
 *--------------------------------------------------------------------------*/

int _System sleep_init(void * srvtoken) {

   SRVUTOK(srvtoken) = malloc(8);       /* fake control block as an example */
   if (SRVUTOK(srvtoken) == NULL)
      return(SRV_REJECT_SHARE);         /* reject share if malloc failed    */

   memset(SRVUTOK(srvtoken),'Z',8);     /* initialize fake control block    */
   return(0);
}



/*-F-sleep_server-------------------------------------------------------------
 *
 * Purpose:    Auxiliary processor 999 is a sample server AP which
 *             uses the general AP Server interface (apserver.c) to
 *             implement a client-server type protocol through the
 *             Shared Variable Processor.  It uses a single shared
 *             variable interface, with no name restrictions, and
 *             runs each share request stream asynchronously under
 *             a separate process (Unix) or thread (OS/2, Windows).
 *
 *             AP999 accepts 2 element integer vectors, where the first
 *             value is the number of milliseconds to sleep, and the second
 *             element is the size of the resulting character vector to
 *             return.  To demonstrate the handling of short versus long
 *             requests, AP999 uses a fast path through the SVP for a
 *             sleep of 1 second or less (holding the shared variable
 *             lock from pre-ref until post-spec), while releasing the
 *             lock (via srv_free call) for longer requests.
 *
 * Arguments:  void * srvtoken      pointer to AP Server token
 *
 *             SRVBUF(srvtoken)     macro returns ptr to shared var buffer
 *             SRVBUFL(srvtoken)    macro returns shared var buffer length
 *             SRVUTOK(srvtoken)    macro returns user token (AP defined)
 *             SRVNAME(srvtoken)    macro returns shared variable name
 *             SRVPXID(srvtoken)    macro returns partner's extended ID
 *             SRVSRBP(srvtoken)    macro returns SVP share request block ptr
 *
 * Results:    int            Return Code
 *                            0 = success
 *                        other = error condition (Server retracts & exits)
 *
 *             On return, the AP stores the result of the client's request
 *             in the shared variable buffer, enlarging it if necessary (or
 *             reallocating it if freed with srv_free) using the srv_alloc
 *             callback to the AP Server.  Note that srv_alloc will NOT
 *             preserve the previous contents of the buffer, and SRVBUF
 *             must be used to get addressability to the buffer after the
 *             call to srv_alloc.
 *
 *--------------------------------------------------------------------------*/

int _System sleep_server(void * srvtoken) {

   int rc = 0;
   APLOBJ *obj = (APLOBJ *) SRVBUF(srvtoken);  /* request is an APL2 object */
   int objsize;
   int msecs = obj->dim[1];             /* 1st item of request is sleep time*/
   int shape = obj->dim[2];             /* 2nd is shape of char array result*/

   if ((obj->type != INTEGER && obj->type != BOOLEAN) ||
        obj->rank != VECTOR || obj->dim[0] != 2) {
      rc = error_code(srvtoken, INVALID_REQ);  /* generate error return code*/
      return rc;
      }

   if (obj->type == BOOLEAN) {          /* if boolean, convert to integer   */
      msecs = ((unsigned long)obj->dim[1]) >> ((8*sizeof(long))-1);
      shape = (((unsigned long)obj->dim[1]) << 1) >> ((8*sizeof(long))-1);
      }

   if (msecs <= 1000) {                 /* short wait - OK to hold the lock */
      if (msecs > 0) {
         svsleep(msecs);
         }
      }
   else {                               /* long wait                        */
      srv_free(srvtoken);               /* AP Server releases space, unlocks*/
      obj = NULL;                       /* no longer have addressability    */
      if (msecs <= 60000) {             /* bypass sleep if more than 60     */
         svsleep(msecs);                /*    seconds in this sample AP     */
         }
      }

   objsize = aplobjsize(CHARACTER, VECTOR, shape);          /* result size? */
   obj = (APLOBJ *) SRVBUF(srv_alloc(srvtoken, objsize));   /* ask for space*/
   if (obj == NULL) {                              /* if allocation failed, */
      rc = error_code(srvtoken, SYSTEM_LIMIT);     /* set error return code */
      return rc;
      }

   obj->ptr = CDRID;                    /* build the CDR header for result  */
   obj->nb = objsize;
   obj->nelm = shape;
   obj->type = CHARACTER;
   obj->rank = VECTOR;
   obj->dim[0] = shape;

   memset(&obj->dim[1], 'Z', shape);    /* return some Z's for sleepy client*/

   return rc;
}



/*-F-error_code---------------------------------------------------------------
 *
 * Purpose:    Return an error return code to client for this request
 *
 * Arguments:  void * srvtoken       pointer to AP Server token
 *             int        rc         AP return code
 *
 * Results:    int            Return Code (from this function)
 *                            0 = success
 *                           -1 = error condition (srv_alloc failed)
 *
 *--------------------------------------------------------------------------*/

int error_code(void * srvtoken, int rc) {

   APLOBJ *obj;                         /* ptr to APL2 object in CDR format */
   int objsize;

   objsize = aplobjsize(INTEGER, SCALAR, 1);                /* result size? */
   obj = (APLOBJ *) SRVBUF(srv_alloc(srvtoken, objsize));   /* ask for space*/
   if (obj == NULL) {                           /* we're in trouble if we   */
      return (-1);                              /* can't get 32 bytes - die!*/
      }

   obj->ptr = CDRID;                            /* construct result header  */
   obj->nb = objsize;
   obj->nelm = 1;
   obj->type = INTEGER;
   obj->rank = SCALAR;
   obj->dim[0] = rc;

   return (0);
}




/*-F-sleep_exit---------------------------------------------------------------
 *
 * Purpose:    Server exit callback - called by the AP Server prior to
 *             shared variable retraction and termination of this process
 *             thread.  Typical use by the AP is for freeing any dynamic
 *             storage it allocated, closing files and pipes, etc.
 *
 * Arguments:  void * srvtoken       pointer to AP Server token
 *
 *             SRVUTOK(srvtoken)     macro returns user token (AP defined)
 *
 * Results:    int             Return Code
 *                             0 = success
 *                         other = error condition (Server prints error msg)
 *
 *--------------------------------------------------------------------------*/

int _System sleep_exit(void * srvtoken) {

   free(SRVUTOK(srvtoken));             /* free the fake control block      */

   return(0);
}



/*==========================================================================*/
/*   The following wait callback routine is not used in this sample AP, but */
/*   is provided for documentation purposes.                                */
/*==========================================================================*/


/*-F-multi_wait---------------------------------------------------------------
 *
 * Purpose:    Server callback to allow wait on multiple file descriptors,
 *             semaphores, or message queues, including the shared variable
 *             event queue.
 *
 *             Return from this function allows the AP Server to handle
 *             shared variable (SVP) events.  Typically an AP will wait on the
 *             notification token along with window, file, or pipe descriptors.
 *             The AP handles non-SVP events, and simply returns from this
 *             function when it wants the AP Server to process SVP events
 *             (which normally result in a call-back to the AP "process" exit
 *             function to handle the client request).
 *
 * Arguments:  void * srvtoken       pointer to AP Server token
 *
 *             SRVNTOK(srvtoken)     macro returns shared variable event
 *                                   notification token (system dependent)
 *             SRVUTOK(srvtoken)     macro returns user token (AP defined)
 *
 * Results:    int             Return Code
 *                             0 = success
 *                         other = error condition (Server retracts & ends)
 *
 *--------------------------------------------------------------------------*/

int _System multi_wait(void * srvtoken) {

/* Get message queue id (Unix) or semaphore handle (OS/2, Windows)          */
   unsigned long wait_token = SRVNTOK(srvtoken);

/* AP typically does poll/select (Unix) or wait (OS/2, Windows)             */
/* and continues processing non-SVP events in a while loop until the only   */
/* event outstanding is an SVP event, at which time it will simply return   */
/* to the AP Server to read the share event queue and handle the event.     */

   return(0);
}

