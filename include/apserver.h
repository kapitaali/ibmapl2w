/*-m-apserver--------------------------------------------------------
 *
 * Module Name: apserver.h
 *
 * Descriptive Name: Auxiliary Processor Server
 *
 * Copyright:   5724-B74 Workstation APL2 Version 2.0
 *              Licensed Materials - Property of IBM
 *              © Copyright IBM Corporation 1994, 2007
 *              All Rights Reserved.
 *              US Government Users Restricted Rights - Use,
 *              duplication or disclosure restricted by GSA ADP
 *              Schedule Contract with IBM Corp.
 *
 * Function: Provide prototypes, typedefs and constants for
 *           C auxiliary processor server
 *
 * Notes:
 *
 *    Dependencies: None
 *
 *    Restrictions: None
 *
 * Module Type: Header
 *
 * Change Activity:
 *
 *-Z----------------------------------------------------------------*/

#include "aplap.h"

/*---------------------- AP Server SRVTOKEN structure -------------------*/

typedef struct srvtoken {
   struct srb * srbp;                   /* ptr to AP share request block */
   void * srvbuf;                       /* ptr to shared variable buffer */
   unsigned long srvbufl;               /* shared variable buffer length */
   void * srvutok;                      /* user token (saved for AP use) */
   int * jmpbuf;                        /* setjmp ptr for error recovery */
   } SRVTOKEN;

/*---------------------- AP Server function prototypes ------------------*/

#ifdef __cplusplus
extern "C" {
#endif

int  _System apserver( int,  char **, int (_System * initfn)(void *),
              int (_System * waitfn)(void *),
              int (_System * procfn)(void *),
              int (_System * exitfn)(void *));
void *  _System  srv_alloc(void *, unsigned long);
void    _System  srv_free(void *);

#ifdef __cplusplus
}
#endif

/*---------------------- AP Server macro definitions --------------------*/

#define SRVBUF(x) (((SRVTOKEN *)(x))->srvbuf)
#define SRVBUFL(x) (((SRVTOKEN *)(x))->srvbufl)
#define SRVUTOK(x) (((SRVTOKEN *)(x))->srvutok)
#define SRVNTOK(x) (((SRVTOKEN *)(x))->srbp->ntoken)
#define SRVPXID(x) (((SRVTOKEN *)(x))->srbp->pxid)
#define SRVNAME(x) (((SRVTOKEN *)(x))->srbp->name)
#define SRVSRBP(x) (((SRVTOKEN *)(x))->srbp)

/*---------------------- AP Server init exit return code ----------------*/

#define SRV_REJECT_SHARE -31415927
