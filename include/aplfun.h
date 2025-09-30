/*-m-aplfun----------------------------------------------------------
 *
 * Module Name: aplfun.h
 *
 * Descriptive Name: Header file for external functions and Calls to APL2
 *
 * Copyright:   5724-B74 Workstation APL2 Version 2.0
 *              Licensed Materials - Property of IBM
 *              © Copyright IBM Corporation 1997, 2012
 *              All Rights Reserved.
 *              US Government Users Restricted Rights - Use,
 *              duplication or disclosure restricted by GSA ADP
 *              Schedule Contract with IBM Corp.
 *
 * Function: Provide typedefs and constants for writing external
 *           routines using :link.FUNCTION protocol and calling
 *           APL2 using the APL2 Program Interface (apl2pi)
 *
 * Notes:
 *
 *    Dependencies: None
 *
 *    Restrictions: None
 *
 * Module Type: Header
 *
 * Change Activity:    Added EXECUTE_APL_ESTACK
 *
 *-Z----------------------------------------------------------------*/

#ifndef APLFUN_DEF
#define APLFUN_DEF

/*-----------------------------------------------------------------*/
/* Linkage Conventions                                             */
/* We attempt to address the major compilers but user modification */
/* may be necessary.                                               */
/*-----------------------------------------------------------------*/

#ifdef __IBMC__
 #ifndef __OS2__
  #ifndef __WINDOWS__
    #define _System
  #endif
 #endif
#else
 #ifdef _MSC_VER
    #define _System __stdcall
 #elif defined(__BORLANDC__)
  #ifdef _Windows
    #define _System __stdcall
  #endif
 #endif
 #ifndef _System
    #define _System
 #endif
#endif

/* This section must follow the above so _System is properly defined */
#ifndef __OS2_H__
   typedef long ( _System _PFN) (void *);
   typedef _PFN    *PFN;
#endif

/*-----------------------------------------------------------------*/
/*                                                                 */
/*  CALL structure                                                 */
/*                                                                 */
/*  Control block for communication between Processor 11 and       */
/*  external routines written in :link.FUNCTION protocol and       */
/*  communication between callers of APL2 and the APL2 PI          */
/*                                                                 */
/*-----------------------------------------------------------------*/

typedef struct _call {
        short request;       /* request code on entry             */
                             /* return code on return             */
        short reason;        /* reason code if applicable         */
        PFN  service;        /* pointer to Service Routine        */
        long parm1;          /* service parameter 1               */
        long parm2;          /* service parameter 2               */
        long token;          /* routine token (user word)         */
        void *result;        /* address of result                 */
        long result_token;   /* result object locator token       */
        void *left_arg;      /* address of left arg               */
        long left_arg_token; /* left arg locator token            */
        long left_fn;        /* reserved for future use           */
        long operator_token; /* reserved for future use           */
        long right_fn;       /* reserved for future use           */
        long right_arg_token;/* right arg locator token           */
        void *right_arg;     /* address of right arg              */
        long reloc_count;    /* relocation count                  */
        long parm3;          /* service parameter 3               */
    } CALL   ;


/*-----------------------------------------------------------------*/
/*                                                                 */
/* External Routine Entry Conventions                              */
/*                                                                 */
/* The prototype for a :link.FUNCTION routine must be:             */
/*     int _System RoutineName(CALL *call)                         */
/*                                                                 */
/* The routine is entered with call->request set to:               */
/*                                                                 */
/*     FUNCTION_INIT  when the name is resolved (associated)       */
/*                    ->service is the only CALL field valid       */
/*                                                                 */
/*                    routine can set ->token to point to its own  */
/*                    anchor block or any desired resource.  The   */
/*                    value in ->token will be retained across     */
/*                    calls.  The routine must exit with:          */
/*                    ->request set to an error message code or 0  */
/*                    ->reason set to a QuadET subcode or 0        */
/*                    if ->request is not 0 on exit Processor 11   */
/*                    will stop the association from completing.   */
/*                                                                 */
/*     FUNCTION_CALL  each time the name is called                 */
/*                    ->service is the callback service routine    */
/*                    ->token is the routine token from INIT       */
/*                    ->left_arg_token is the left arg locator     */
/*                    ->left_arg is the address of the left arg    */
/*                    ->right_arg_token is the right arg locator   */
/*                    ->right_arg is the address of the right arg  */
/*                    ->reloc_count is the relocation count        */
/*                                                                 */
/*                    after completing its processing, routine     */
/*                    should return with the following set:        */
/*                    ->request is the error message code or 0     */
/*                    ->reason is the QuadET subcode or 0          */
/*                    ->result_token is the locator of the result  */
/*                    (if ->request is 0)                          */
/*                                                                 */
/*     FUNCTION_TERM  when the name is expunged                    */
/*                    ->service is the only CALL field valid       */
/*                    ->token is the routine token from INIT       */
/*                                                                 */
/*                    routine should free any resources associated */
/*                    with ->token and clear it.                   */
/*                                                                 */
/*-----------------------------------------------------------------*/
#define FUNCTION_INIT   (1)
#define FUNCTION_CALL   (0)
#define FUNCTION_TERM   (-1)

/*-----------------------------------------------------------------*/
/* Codes for Callback Services                                     */
/*                                                                 */
/* The callback service routine is called as follows:              */
/*    rc = (call->service)(call)                                   */
/*                                                                 */
/* On error, rc is set by the service routine to one of the        */
/* MSG_ error codes (see below).  The same code is set in          */
/* call->request.  A reason code is set in call->reason if         */
/* applicable for the error code.                                  */
/*                                                                 */
/* The routine can call the service routine with                   */
/* call->request set to the following service codes:               */
/*                                                                 */
/*     ARRAYSPACE   to allocate an array in the workspace          */
/*          Parameters:                                            */
/*             ->parm1  is the number of elements                  */
/*             ->parm2  is the rank                                */
/*             ->parm3  is the type (from aplobj.h)                */
/*          Results:                                               */
/*             ->parm1  is the locator token of the array          */
/*             ->parm2  is the address of the descriptor section   */
/*             ->parm3  is the address of the data section         */
/*             ->left_arg, ->right_arg, and ->result are also      */
/*             refreshed (due to possible garbage collection)      */
/*                                                                 */
/*     ARRAYRESIZE to change the number of elements in an array    */
/*                  previously allocated with ARRAYSPACE           */
/*          Parameters:                                            */
/*             ->parm1  is the locator token of the array          */
/*             ->parm2  is the new number of elements              */
/*             ->parm3  is the new rank                            */
/*          Results:                                               */
/*             ->parm2  is the address of the descriptor section   */
/*             ->parm3  is the address of the data section         */
/*             ->left_arg, ->right_arg, and ->result are also      */
/*             refreshed (due to possible garbage collection)      */
/*                                                                 */
/*     ARRAYREF     to increase the usage count of an array        */
/*          Parameters:                                            */
/*             ->parm1  is the locator token of the array          */
/*                                                                 */
/*     ARRAYCONVERT to convert an array to a new type              */
/*          Parameters:                                            */
/*             ->parm1  is the locator token of the array          */
/*             ->parm2  is the new type                            */
/*          Results:                                               */
/*             ->parm1  is the locator token of the new array      */
/*             ->parm2  is the address of the descriptor section   */
/*             ->parm3  is the address of the data section         */
/*             ->left_arg, ->right_arg, and ->result are also      */
/*             refreshed (due to possible garbage collection)      */
/*                                                                 */
/*     FREESPACE    to free an array previously allocated with     */
/*                  ARRAYSPACE or ARRAYREF                         */
/*          Parameters:                                            */
/*             ->parm1  is the locator token of the array          */
/*                                                                 */
/*     EXECUTE_APL to execute an apl expression or function        */
/*     EXECUTE_APL_ESTACK to execute an apl expression or function */
/*          and return the stack on error                          */
/*          Parameters:                                            */
/*             ->parm1  is the locator token of the expression or  */
/*                      function name                              */
/*             ->parm2  is the locator token of the right argument */
/*                      or 0 if none                               */
/*             ->parm3  is the locator token of the left argument  */
/*                      or 0 if none                               */
/*          Results:                                               */
/*             ->parm1  is the locator token of the result or      */
/*                      the locator token of the error message     */
/*                      if ->request is MSG_APLERROR               */
/*                      or 0 if none                               */
/*             ->parm2  is the address of the result or            */
/*                      the APL error class (First of QuadET)      */
/*                      if ->request is MSG_APLERROR               */
/*                      or 0 if none                               */
/*             ->parm3  is the address of the result data area or  */
/*                      the APL error type  (Second of QuadET)     */
/*                      if ->request is MSG_APLERROR               */
/*                      or 0 if none                               */
/*                                                                 */
/*     TOKEN_TO_ADDRESS to convert an array locator token to an    */
/*                      address                                    */
/*          Parameters:                                            */
/*             ->parm1  is the locator token of the array          */
/*          Results:                                               */
/*             ->parm2  is the address of the descriptor section   */
/*             ->parm3  is the address of the data section         */
/*                                                                 */
/*     QUAD_CT          to get the current value of QuadCT         */
/*          Results:                                               */
/*             ->parm1  is the address of the current value of     */
/*                      QuadCT if valid                            */
/*                                                                 */
/*     QUAD_IO          to get the current value of QuadIO         */
/*          Results:                                               */
/*             ->parm1  is the current value of QuadIO if valid    */
/*                                                                 */
/*     LCDR_TO_ARRAY    to convert a linear CDR to an array        */
/*          Parameters:                                            */
/*             ->parm2  is the address of the CDR                  */
/*          Results:                                               */
/*             ->parm1  is the locator token of the array          */
/*                                                                 */
/*     ARRAY_TO_LCDR    to convert an array to a linear CDR        */
/*          Parameters:                                            */
/*             ->parm1  is the locator token of the array          */
/*             ->parm2  is the address of a user-provided buffer   */
/*             ->*parm2 is the length of the buffer                */
/*          Results:                                               */
/*             ->parm2 is the actual length of the CDR             */
/*             CDR is placed in the buffer immediately following   */
/*             the length word, if the buffer was long enough.     */
/*                                                                 */
/*     DOAP1EVENTS      Allow AP 1 to handle pending events        */
/*          Parameters:                                            */
/*             None                                                */
/*          Results:                                               */
/*             None                                                */
/*                                                                 */
/*     GETSIGNALS       Query and/or clear the signal state        */
/*          Parameters:                                            */
/*             ->parm1  indicates whether to clear interrupt       */
/*                      0 - do not clear interrupt                 */
/*                      1 - clear interrupt if pending             */
/*          Results:                                               */
/*             ->parm1  is the signal state                        */
/*                      0 - no signals                             */
/*                      1 - reserved for attention                 */
/*                      2 - interrupt pending                      */
/*                                                                 */
/*-----------------------------------------------------------------*/
#define ARRAYSPACE       21   /* Allocate array in the workspace   */
#define ARRAYRESIZE      22   /* Change size of allocated array    */
#define ARRAYREF         23   /* Increase use count of array       */
#define ARRAYCONVERT     24   /* Convert array to new type         */
#define FREESPACE         2   /* Return space                      */
#define EXECUTE_APL       5   /* Execute an apl expression         */
#define EXECUTE_APL_ESTACK 38 /* Execute apl, full stack on error  */
#define TOKEN_TO_ADDRESS 11   /* Convert locator token to address  */
#define QUAD_CT          40   /* get value of current QuadCT       */
#define QUAD_IO          15   /* get value of current QuadIO       */
#define LCDR_TO_ARRAY    18   /* Convert linear CDR to an array    */
#define ARRAY_TO_LCDR    19   /* Convert array to a linear CDR     */
#define DOAP1EVENTS      35   /* Do AP 1 events                    */
#define GETSIGNALS       32   /* Get signal state                  */

/*-----------------------------------------------------------------*/
/* APL2 Program Interface                                          */
/*                                                                 */
/* APL2 is called as follows:                                      */
/*    rc = apl2pi(call)                                            */
/*                                                                 */
/* On error, rc is set by the apl2pi routine to one of the         */
/* MSG_ error codes (see below).  The same code is set in          */
/* call->request.  A reason code is set in call->reason if         */
/* applicable for the error code.                                  */
/*                                                                 */
/*-----------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

int _System apl2pi(CALL *);

#ifdef __cplusplus
   }
#endif

/*-----------------------------------------------------------------*/
/* A program can call apl2pi with call->request set to the         */
/* following service codes:                                        */
/*                                                                 */
/*     APL2PI_INIT to start an APL2 session                        */
/*          Parameters:                                            */
/*             ->parm1  is the caller anchor word                  */
/*             ->parm2  is the apl2 invocation parameter count     */
/*                      (Corresponds to the standard C "argc")     */
/*             ->parm3  is the apl2 invocation parameter array     */
/*                      (Corresponds to the standard C "argv")     */
/*                      Any APL2 invocation parameters may be      */
/*                      passed, as defined in the APL2 User's      */
/*                      Guide chapter "Invoking APL2".  However,   */
/*                      these parameters will be ignored if        */
/*                      specified:                                 */
/*                          -hostwin                               */
/*                          -input                                 */
/*                          -lx  (is always OFF)                   */
/*                          -quiet (is always ON)                  */
/*                          -run                                   */
/*                          -rns                                   */
/*                          -sm (is always OFF)                    */
/*          Results:                                               */
/*             ->token  is the interpreter instance identifier     */
/*                      This identifier must be passed in the      */
/*                      ->token field on all subsequent calls      */
/*                      to apl2pi for this instance                */
/*                                                                 */
/*     APL2PI_TERM to terminate an APL2 session                    */
/*          Parameters:                                            */
/*             ->token  is the interpreter instance identifier     */
/*                                                                 */
/*     ARRAYSPACE   to allocate an array in the workspace          */
/*     ARRAYRESIZE  to change the number of elements in an array   */
/*                  previously allocated with ARRAYSPACE           */
/*     ARRAYREF     to increase the usage count of an array        */
/*     ARRAYCONVERT to convert an array to a new type              */
/*     FREESPACE    to free an array previously allocated with     */
/*                  ARRAYSPACE or ARRAYREF                         */
/*     EXECUTE_APL  to execute an apl expression or function       */
/*     EXECUTE_APL_ESTACK to execute an apl expression or function */
/*          and return the stack on error                          */
/*     TOKEN_TO_ADDRESS to convert an array locator token to an    */
/*                      address                                    */
/*     QUAD_IO          to get the current value of QuadIO         */
/*     LCDR_TO_ARRAY    to convert a linear CDR to an array        */
/*     ARRAY_TO_LCDR    to convert an array to a linear CDR        */
/*                                                                 */
/*     Parameters and results for these services are as defined    */
/*     above for external functions, with the addition of the      */
/*     following parameter on each call:                           */
/*         ->token  is the interpreter instance identifier         */
/*                                                                 */
/*-----------------------------------------------------------------*/

#define APL2PI_INIT   0
#define APL2PI_TERM   255

/*-----------------------------------------------------------------*/
/*                                                                 */
/* Message Codes                                                   */
/*                                                                 */
/*    MSG_  codes to be set in call->request on exit.              */
/*    ET_ codes to be set in call->reason (if applicable).         */
/*                                                                 */
/*-----------------------------------------------------------------*/
#define MSG_OK              (0)
#define MSG_INTERRUPT       (1)
#define MSG_SYSTEMERROR     (2)
#define MSG_WSFULL          (3)
#define MSG_SYSTEMLIMIT     (4)
   #define ET_SYMBOLTABLE        (4)
   #define ET_INTERFACENA        (5)
   #define ET_INTERFACEQUOTA     (6)
   #define ET_INTERFACECAPACITY  (7)
   #define ET_ARRAYRANK          (8)
   #define ET_ARRAYSIZE          (9)
   #define ET_ARRAYDEPTH         (10)
   #define ET_PROMPTLENGTH       (11)
   #define ET_INTERFACEREP       (12)
   #define ET_IMPLEMENTATION     (13)
#define MSG_SYNTAXERROR     (5)
   #define ET_OMITTED            (1)
   #define ET_ILLFORMED          (2)
   #define ET_NAMECLASS          (3)
   #define ET_CONTEXT            (4)
   #define ET_COMPATIBILITY      (5)
#define MSG_VALUEERROR      (6)
   #define ET_NOVALUE            (1)
   #define ET_NORESULT           (2)
#define MSG_QUADERROR       (7)
   #define ET_PP                 (1)
   #define ET_IO                 (2)
   #define ET_CT                 (3)
   #define ET_FC                 (4)
   #define ET_RL                 (5)
   #define ET_PR                 (7)
#define MSG_VALENCEERROR    (8)
#define MSG_RANKERROR       (9)
#define MSG_LENGTHERROR     (10)
#define MSG_DOMAINERROR     (11)
#define MSG_INDEXERROR      (12)
#define MSG_AXISERROR       (13)
#define MSG_APLERROR        (99)

#endif
