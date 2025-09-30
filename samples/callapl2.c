/*-p-callapl2.c---------------------------------------------------*/
/*                                                                */
/* Module Name: callapl2.c                                        */
/*                                                                */
/* Descriptive Name: Sample C program to call APL2                */
/*                                                                */
/* Copyright:   5724-B74 Workstation APL2 Version 2.0             */
/*              Licensed Materials - Property of IBM              */
/*              © Copyright IBM Corporation 2004, 2007            */
/*              All Rights Reserved.                              */
/*              US Government Users Restricted Rights - Use,      */
/*              duplication or disclosure restricted by GSA ADP   */
/*              Schedule Contract with IBM Corp.                  */
/*                                                                */
/* Function: Demonstrate using apl2pi to call APL2 from C         */
/*                                                                */
/* Module Type: Stand-alone executable                            */
/*                                                                */
/*    Processor: C                                                */
/*                                                                */
/*----------------------------------------------------------------*/
/*                                                                */
/* Entry-point: main                                              */
/*                                                                */
/*    Purpose: Sample C program to call APL2                      */
/*                                                                */
/*    Linkage: Standard C main entry point                        */
/*                                                                */
/* External References:                                           */
/*                                                                */
/*    Routines:                                                   */
/*                                                                */
/*       apl2pi                                                   */
/*                                                                */
/*    Control Blocks:                                             */
/*                                                                */
/*       CALL                                                     */
/*       APLOBJ                                                   */
/*                                                                */
/* Change Activity:                                               */
/*                                                                */
/*----------------------------------------------------------------*/

/*----------------------------------------------------------------*/
/* C runtime include files                                        */
/*----------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*----------------------------------------------------------------*/
/* APL2 include files                                             */
/*----------------------------------------------------------------*/
#include "aplfun.h"
#include "aplobj.h"

/*----------------------------------------------------------------*/
/*                                                                */
/* Entry point: main                                              */
/*                                                                */
/* Purpose:  Demonstrate using apl2pi to call APL2 from C.        */
/*                                                                */
/*----------------------------------------------------------------*/
int main(int argc,char ** argv)
{
CALL     Call       ; /* apl2pi interface control block          */
int      RcApl2     ; /* apl2pi return code                      */
long     TokenApl2  ; /* APL2 interpreter token                  */
long     Reloc      ; /* Relocation count                        */
long     LtQuadTS   ; /* Locator token for QuadTS array          */
APLOBJ * CdrQuadTS  ; /* Address of QuadTS array                 */
long     DataQuadTS ; /* Address of data section of QuadTS array */
long     LtResult   ; /* Locator token of result of EXECUTE_APL  */
APLOBJ * CdrResult  ; /* Address of result array                 */
long     DataResult ; /* Address of data section of result array */
long   * Date       ; /* Pointer to date-time stamp elements     */

/* Initialize apl2pi CALL structure */
memset(&Call,0x00,sizeof(CALL)) ;

/* Start an APL2 interpreter */
Call.request = APL2PI_INIT ;
Call.parm1   = 0 ;
Call.parm2   = argc ;
Call.parm3   = (long)argv ;
RcApl2 = apl2pi(&Call) ;
if(RcApl2 != MSG_OK) printf("APL2PI_INIT request failed.  Rc: %li Reason: %li\n",RcApl2,Call.reason) ;
else
   {
   TokenApl2 = Call.token ; /* Save the token for this interpreter */

   /* Allocate space in the workspace to hold 3 characters */
   Call.token   = TokenApl2 ;  /* APL2 interpreter token */
   Call.request = ARRAYSPACE ; /* Request code           */
   Call.parm1   = 3 ;          /* Number of elements     */
   Call.parm2   = 1 ;          /* Rank                   */
   Call.parm3   = CDWRTC ;     /* Type                   */
   RcApl2 = apl2pi(&Call) ;
   if(RcApl2 != MSG_OK) printf("ARRAYSPACE request failed.  Rc: %li Reason: %li\n",RcApl2,Call.reason) ;
   else
      {
      LtQuadTS   = Call.parm1 ;           /* Locator token for array   */
      CdrQuadTS  = (APLOBJ *)Call.parm2 ; /* Address of start of array */
      DataQuadTS = Call.parm3 ;           /* Address of data section   */
      Reloc      = Call.reloc_count ;     /* Save relocation count     */

      /* Copy QuadTS into array's data area */
      memcpy((void *)DataQuadTS,"\x90TS",3) ;

      /* Execute the array containing QuadTS */
      Call.token   = TokenApl2 ;   /* APL2 interpreter token                       */
      Call.request = EXECUTE_APL ; /* Request code                                 */
      Call.parm1   = LtQuadTS ;    /* Locator token of expression or function name */
      Call.parm2   = 0 ;           /* Locator token of right argument              */
      Call.parm3   = 0 ;           /* Locator token of left argument               */
      RcApl2 = apl2pi(&Call) ;
      if(RcApl2 != MSG_OK) printf("EXECUTE_APL request failed.  Rc: %li Reason: %li\n",RcApl2,Call.reason) ;
      else
         {
         LtResult   = Call.parm1 ;           /* Locator token of result                    */
         CdrResult  = (APLOBJ *)Call.parm2 ; /* Address of the result array                */
         DataResult = Call.parm3 ;           /* Address of the result array's data section */

         /* If relocation count has changed, previously allocated arrays may have moved */
         /* and our array addresses are no longer reliable.  Refresh them if necessary. */
         /* Note: This code is not necessary for this program,                          */
         /*       because it will not be using the QuadTS array again.                  */
         /*       It is only provided to demonstrate how to handle the relocation count */
         /*       and use the TOKEN_TO_ADDRESS request.                                 */
         if(Reloc != Call.reloc_count)
            {
            Reloc = Call.reloc_count ; /* Save new relocation count */

            /* Retrieve the new address of the QuadTS array */
            Call.token   = TokenApl2 ;        /* APL2 interpreter token     */
            Call.request = TOKEN_TO_ADDRESS ; /* Request code               */
            Call.parm1   = LtQuadTS ;         /* Locator token of the array */
            RcApl2 = apl2pi(&Call) ;
            if(RcApl2 != MSG_OK) printf("TOKEN_TO_ADDRESS request failed.  Rc: %li Reason: %li\n",RcApl2,Call.reason) ;
            else
               {
               CdrQuadTS  = (APLOBJ *)Call.parm2 ; /* Address of start of array */
               DataQuadTS = Call.parm3 ;           /* Address of data section   */
               }
            }

         /* Check the result of EXECUTE_APL */
         if(CdrResult->type != CDWRTI) printf("EXECUTE_APL returned unexpected type result\n") ;
         else
            {
            Date = (long *)DataResult ;
            printf("Time stamp: %li-%li-%li %li:%li:%li:%li\n",
               Date[0], Date[1], Date[2], Date[3], Date[4], Date[5], Date[6]) ;
            }

         /* Free the array containing result */
         Call.token   = TokenApl2 ; /* APL2 interpreter token             */
         Call.request = FREESPACE ; /* Request code                       */
         Call.parm1   = LtResult ;  /* Locator token of array to be freed */
         RcApl2 = apl2pi(&Call) ;
         if(RcApl2 != MSG_OK) printf("FREESPACE request failed.  Rc: %li Reason: %li\n",RcApl2,Call.reason) ;
         }

      /* Free the array containing QuadTS */
      Call.token   = TokenApl2 ; /* APL2 interpreter token             */
      Call.request = FREESPACE ; /* Request code                       */
      Call.parm1   = LtQuadTS ;  /* Locator token of array to be freed */
      RcApl2 = apl2pi(&Call) ;
      if(RcApl2 != MSG_OK) printf("FREESPACE request failed.  Rc: %li Reason: %li\n",RcApl2,Call.reason) ;
      }

   /* Shutdown the interpreter */
   Call.token   = TokenApl2 ;   /* APL2 interpreter token */
   Call.request = APL2PI_TERM ; /* Request code          */
   RcApl2 = apl2pi(&Call) ;
   if(RcApl2 != MSG_OK) printf("APL2PI_TERM request failed.  Rc: %li Reason: %li\n",RcApl2,Call.reason) ;
   }

return 0 ;
}
