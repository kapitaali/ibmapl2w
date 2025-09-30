/*-p-aplfun.c-----------------------------------------------------*/
/*                                                                */
/* Module Name: aplfun.c                                          */
/*                                                                */
/* Descriptive Name: Sample :link.FUNCTION routines               */
/*                                                                */
/* Copyright:   5724-B74 Workstation APL2 Version 2.0             */
/*              Licensed Materials - Property of IBM              */
/*              © Copyright IBM Corporation 1997, 2007            */
/*              All Rights Reserved.                              */
/*              US Government Users Restricted Rights - Use,      */
/*              duplication or disclosure restricted by GSA ADP   */
/*              Schedule Contract with IBM Corp.                  */
/*                                                                */
/* Function: Sample functions written in :link.FUNCTION protocol  */
/*                                                                */
/*                                                                */
/*----------------------------------------------------------------*/

/*----------------------------------------------------------------*/
/* Include files                                                  */
/*----------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "aplfun.h"
#include "aplobj.h"

/*----------------------------------------------------------------*/
/*                                                                */
/* Function: funsample1                                           */
/*                                                                */
/* Routine descriptor:                                            */
/*                                                                */
/*       :nick.NEST      :link.FUNCTION                           */
/*           :lib.aplfun    :proc.funsample1                      */
/*           :valence.1 2 0                                       */
/*                                                                */
/* Purpose:  This routine simply returns a nested array whose     */
/*           elements are copies of the left and right argument.  */
/*           Demonstrates ARRAYSPACE, ARRAYREF.                   */
/*                                                                */
/*----------------------------------------------------------------*/
int _System
funsample1(CALL * call)      /* EXPORT */
{
   long * dataobj;

   /*----------------------------------------------------------------*/
   /* Handle INIT and TERM cases                                     */
   /*----------------------------------------------------------------*/
   switch (call->request) {
      case FUNCTION_INIT:
         call->request = MSG_OK;
         call->reason = MSG_OK;
         return 0;
      case FUNCTION_CALL:
         break;
      case FUNCTION_TERM:
         call->request = MSG_OK;
         call->reason = MSG_OK;
         return 0;
      default:
         call->request = MSG_SYSTEMERROR;
         call->reason = MSG_OK;
         return 0;
   }

   /*----------------------------------------------------------------*/
   /* FUNCTION_CALL - main logic for function                        */
   /*----------------------------------------------------------------*/

   /*----------------------------------------------------------------*/
   /* Make sure there are both left and right arguments              */
   /*----------------------------------------------------------------*/
   if ((call->left_arg_token == 0) || (call->right_arg_token == 0)) {
      call->request = MSG_VALENCEERROR;
      call->reason = 0;
      return 0;
   }

   /*----------------------------------------------------------------*/
   /* Allocate a nested array for the result                         */
   /*----------------------------------------------------------------*/
   call->request = ARRAYSPACE;
   call->parm1 = 2;
   call->parm2 = VECTOR;
   call->parm3 = NESTED;
   if ((call->service)(call)) return 0;

   call->result_token = call->parm1;
   call->result = (void *) call->parm2;

   /*----------------------------------------------------------------*/
   /* Set the array data to the tokens for the left and right arg    */
   /*----------------------------------------------------------------*/
   dataobj = (long *) call->parm3;
   dataobj[0] = call->left_arg_token;
   dataobj[1] = call->right_arg_token;

   /*----------------------------------------------------------------*/
   /* Reference the left and right arg                               */
   /*----------------------------------------------------------------*/
   call->request = ARRAYREF;
   call->parm1 = call->left_arg_token;
   ((call->service)(call));

   call->request = ARRAYREF;
   call->parm1 = call->right_arg_token;
   ((call->service)(call));

   call->request = MSG_OK;
   call->reason = MSG_OK;
   return 0;
}

/*----------------------------------------------------------------*/
/*                                                                */
/* Function: funsample2                                           */
/*                                                                */
/* Routine descriptor:                                            */
/*                                                                */
/*       :nick.REMOVEFROM    :link.FUNCTION                       */
/*           :lib.aplfun    :proc.funsample2                      */
/*           :valence.1 2 0                                       */
/*                                                                */
/* Purpose:  This routine removes the left argument items         */
/*           from the right.                                      */
/*           Demonstrates ARRAYSPACE, ARRAYRESIZE.                */
/*                                                                */
/*----------------------------------------------------------------*/
int _System
funsample2(CALL * call)     /* EXPORT */
{
   APLOBJ *objleft, *objright, *objres;
   char *dataleft, *dataright, *datares;
   int left, right, res;

   /*----------------------------------------------------------------*/
   /* Handle INIT and TERM cases                                     */
   /*----------------------------------------------------------------*/
   switch (call->request) {
      case FUNCTION_INIT:
         call->request = MSG_OK;
         call->reason = MSG_OK;
         return 0;
      case FUNCTION_CALL:
         break;
      case FUNCTION_TERM:
         call->request = MSG_OK;
         call->reason = MSG_OK;
         return 0;
      default:
         call->request = MSG_SYSTEMERROR;
         call->reason = MSG_OK;
         return 0;
   }

   /*----------------------------------------------------------------*/
   /* FUNCTION_CALL - main logic for function                        */
   /*----------------------------------------------------------------*/

   /*----------------------------------------------------------------*/
   /* Make sure there are both left and right arguments              */
   /*----------------------------------------------------------------*/
   if ((call->left_arg_token == 0) || (call->right_arg_token == 0)) {
      call->request = MSG_VALENCEERROR;
      call->reason = 0;
      return 0;
   }

   /*----------------------------------------------------------------*/
   /* Make sure the left argument is what we need                    */
   /*----------------------------------------------------------------*/
   objleft = (APLOBJ *) call->left_arg;

   if (objleft->type != CHARACTER) {
      call->request = MSG_DOMAINERROR;
      call->reason = 0;
      return 0;
   }

   if (objleft->rank > VECTOR) {
      call->request = MSG_RANKERROR;
      call->reason = 0;
      return 0;
   }

   /*----------------------------------------------------------------*/
   /* Make sure the right argument is what we need                   */
   /*----------------------------------------------------------------*/
   objright = (APLOBJ *) call->right_arg;

   if (objright->type != CHARACTER) {
      call->request = MSG_DOMAINERROR;
      call->reason = 0;
      return 0;
   }

   if (objright->rank > VECTOR) {
      call->request = MSG_RANKERROR;
      call->reason = 0;
      return 0;
   }

   /*----------------------------------------------------------------*/
   /* Allocate an array for the result. Assume nothing will be       */
   /* removed.                                                       */
   /*----------------------------------------------------------------*/
   call->request = ARRAYSPACE;
   call->parm1 = objright->nelm;
   call->parm2 = VECTOR;
   call->parm3 = CHARACTER;
   if ((call->service)(call)) return 0;

   call->result_token = call->parm1;
   objres = (APLOBJ *) call->parm2;
   datares = (char *) call->parm3;

   /*----------------------------------------------------------------*/
   /* Refresh the left and right arg addresses in case they moved    */
   /* during the call to ARRAYSPACE.                                 */
   /*----------------------------------------------------------------*/
   objleft = call->left_arg;
   objright = call->right_arg;

   dataleft = (char *) &objleft->dim[objleft->rank];
   dataright = (char *) &objright->dim[objright->rank];

   /*----------------------------------------------------------------*/
   /* Copy the data (first pass is into the result from the right)   */
   /*----------------------------------------------------------------*/
   for (right=0, res = 0; right < (int)objright->nelm; right++) {
      if (dataright[right] != dataleft[0]) {
         datares[res] = dataright[right];
         res++;
      }
    }
    objres->nelm = res;

   /*----------------------------------------------------------------*/
   /* For rest of left, do it in place  (use res as right)           */
   /*----------------------------------------------------------------*/
   objright = objres;
   dataright = datares;

   for (left = 1; left <(int)objleft->nelm; left++) {
      for (right=0, res = 0; right < (int)objright->nelm; right++) {
         if (dataright[right] != dataleft[left]) {
            datares[res] = dataright[right];
            res++;
         }
       }
       objres->nelm = res;
   }

   /*----------------------------------------------------------------*/
   /* Shorten the result to its actual size                          */
   /* Return ->request and ->reason as set by ARRAYRESIZE            */
   /* Chance of error is minimal since we are shortening             */
   /*----------------------------------------------------------------*/
   call->request = ARRAYRESIZE;
   call->parm1 = call->result_token;
   call->parm2 = res;
   call->parm3 = VECTOR;
   (call->service)(call);

   return 0;
}

/*----------------------------------------------------------------*/
/*                                                                */
/* Function: funsample3                                           */
/*                                                                */
/* Routine descriptor:                                            */
/*                                                                */
/*       :nick.TYPE      :link.FUNCTION                           */
/*           :lib.aplfun    :proc.funsample3                      */
/*           :valence.1 1 0                                       */
/*                                                                */
/* Purpose:  This routine returns the type of the argument.       */
/*           (If simple, returns type, If nested, returns type    */
/*            if each subitem). Builds array in workspace.        */
/*           Demonstrates ARRAYSPACE, TOKEN_TO_ADDRESS,           */
/*           FREESPACE.                                           */
/*                                                                */
/*----------------------------------------------------------------*/
int _System
funsample3(CALL * call)     /* EXPORT */
{
   APLOBJ *input, *subinput, *result;
   long *restok, *inptok;
   char *typestr;
   int i;
   long reloc_count;

   /*----------------------------------------------------------------*/
   /* Handle INIT and TERM cases                                     */
   /*----------------------------------------------------------------*/
   switch (call->request) {
      case FUNCTION_INIT:
         call->request = MSG_OK;
         call->reason = MSG_OK;
         return 0;
      case FUNCTION_CALL:
         break;
      case FUNCTION_TERM:
         call->request = MSG_OK;
         call->reason = MSG_OK;
         return 0;
      default:
         call->request = MSG_SYSTEMERROR;
         call->reason = MSG_OK;
         return 0;
   }

   /*----------------------------------------------------------------*/
   /* FUNCTION_CALL - main logic for function                        */
   /*----------------------------------------------------------------*/

   /*----------------------------------------------------------------*/
   /* Make sure there is not a left argument and is a right argument */
   /*----------------------------------------------------------------*/
   if ((call->left_arg_token != 0) || (call->right_arg_token == 0)) {
      call->request = MSG_VALENCEERROR;
      call->reason = 0;
      return 0;
   }

   /*----------------------------------------------------------------*/
   /* Make sure the right argument meets criteria                    */
   /*----------------------------------------------------------------*/
   input = (APLOBJ *) call->right_arg;

   if (input->rank > VECTOR) {
      call->request = MSG_RANKERROR;
      call->reason = 0;
      return 0;
   }

   if (input->nelm == 0) {
      call->request = MSG_LENGTHERROR;
      call->reason = 0;
      return 0;
   }

   /*----------------------------------------------------------------*/
   /* Allocate the top-level result array                            */
   /*----------------------------------------------------------------*/
   call->request = ARRAYSPACE;
   if (input->type == NESTED)
      call->parm1 = input->nelm;
   else
      call->parm1 = 1;
   call->parm2 = VECTOR;
   call->parm3 = NESTED;
   if ((call->service)(call)) return 0;

   call->result_token = call->parm1;
   call->result = (void *) call->parm2;
   result = (APLOBJ *) call->parm2;
   restok = (long *) call->parm3;

   /*----------------------------------------------------------------*/
   /* Recopy right arg pointer in case it moved during ARRAYSPACE    */
   /*----------------------------------------------------------------*/
   input = (APLOBJ *) call->right_arg;
   inptok = (long *) &input->dim[input->rank];

   /*----------------------------------------------------------------*/
   /* Initialize the token pointers to 0                             */
   /*----------------------------------------------------------------*/
   for (i = 0; i < (int)result->nelm; i++)  restok[i] = 0;

   /*----------------------------------------------------------------*/
   /* For each item in the input, allocate an array subitem          */
   /*----------------------------------------------------------------*/
   reloc_count = call->reloc_count;

   for (i = 0; i < (int)result->nelm; i++)  {
      if (input->type == NESTED) {
         call->request = TOKEN_TO_ADDRESS;
         call->parm1 = inptok[i];
         if ((call->service)(call)) break;
         subinput = (APLOBJ *) call->parm2;
      }
      else {
         subinput = input;
      }
      switch (subinput->type) {
         case BOOLEAN:
            typestr = "BOOLEAN";
            break;
         case INTEGER:
            typestr = "INTEGER";
            break;
         case FLOAT:
            typestr = "FLOAT";
            break;
         case COMPLEX:
            typestr = "COMPLEX";
            break;
         case CHARACTER:
            typestr = "CHARACTER";
            break;
         case CHARLONG:
            typestr = "LONG CHARACTER";
            break;
         case APV:
            typestr = "PROGRESSION";
            break;
         case NESTED:
            typestr = "NESTED";
            break;
         default:
            typestr = "UNKNOWN";
            break;
      }


      call->request = ARRAYSPACE;
      call->parm1 = strlen(typestr);
      call->parm2 = VECTOR;
      call->parm3 = CHARACTER;
      if ((call->service)(call)) break;

      /*-------------------------------------------------------------*/
      /* Recopy right arg and result addresses if needed             */
      /*-------------------------------------------------------------*/
      if (call->reloc_count != reloc_count) {
         input = (APLOBJ *) call->right_arg;
         inptok = (long *) &input->dim[input->rank];
         result = (APLOBJ *) call->result;
         restok = (long *) &result->dim[result->rank];
         reloc_count = call->reloc_count;
      }

      /*-------------------------------------------------------------*/
      /* Set the data sections of the main array and subarray        */
      /*-------------------------------------------------------------*/
      restok[i] = call->parm1;
      memcpy((char *)call->parm3, typestr, strlen(typestr));

   }

   /*----------------------------------------------------------------*/
   /* If anything failed, back it all out                            */
   /*----------------------------------------------------------------*/
   if (i < (int)result->nelm) {
      int rc = call->request;       /* Save rc and reason for return */
      int reas = call->reason;

      for (i = 0; i < (int)result->nelm; i++) {      /* Free each subitem */
         if (restok[i] != 0) {
            call->request = FREESPACE;
            call->parm1 = restok[i];
            (call->service)(call);
         }
      }
      call->request = FREESPACE;               /* Free main array    */
      call->parm1 = call->result_token;
      (call->service)(call);
      call->result_token = 0;

      call->request = rc;
      call->reason = reas;

   }

   return 0;
}

/*----------------------------------------------------------------*/
/*                                                                */
/* Function: funsample4                                           */
/*                                                                */
/* Routine descriptor:                                            */
/*                                                                */
/*       :nick.TABLE     :link.FUNCTION                           */
/*           :lib.aplfun    :proc.funsample4                      */
/*           :valence.1 1 0                                       */
/*                                                                */
/* Purpose:  This routine returns a table of data.                */
/*           The argument is the number of rows to return.        */
/*           It builds the array in routine storage.              */
/*           Demonstrates ARRAYCONVERT, LCDR_TO_ARRAY, and        */
/*           the use of call->token.                              */
/*                                                                */
/*----------------------------------------------------------------*/
int _System
funsample4(CALL * call)     /* EXPORT */
{
   APLOBJ *right;
   long rows;
   APLOBJ *result, *subitem;
   long *datanest;
   long *dataint;
   char *datachar;
   double *datareal;
   int i;

   char *names[5] = {"Doug Aiton",
                     "Roy Bei",
                     "David Liebtag",
                     "Ed Oddo",
                     "Nancy Wheeler"};

   double extension[5] = {3.3590,3.4632,3.2739,3.4167,3.4031};

   /*----------------------------------------------------------------*/
   /* Handle INIT and TERM cases                                     */
   /*----------------------------------------------------------------*/
   switch (call->request) {
      case FUNCTION_INIT:
         call->token = (long) malloc(4096);
         if (call->token == 0) {
            call->request = MSG_SYSTEMLIMIT;
            call->reason = ET_INTERFACECAPACITY;
         }
         else {
            call->request = MSG_OK;
            call->reason = MSG_OK;
         }
         return 0;
      case FUNCTION_CALL:
         break;
      case FUNCTION_TERM:
         free((void *)call->token);
         call->request = MSG_OK;
         call->reason = MSG_OK;
         return 0;
      default:
         call->request = MSG_SYSTEMERROR;
         call->reason = MSG_OK;
         return 0;
   }

   /*----------------------------------------------------------------*/
   /* FUNCTION_CALL - main logic for function                        */
   /*----------------------------------------------------------------*/

   /*----------------------------------------------------------------*/
   /* Make sure there is not a left argument and is a right argument */
   /*----------------------------------------------------------------*/
   if ((call->left_arg_token != 0) || (call->right_arg_token == 0)) {
      call->request = MSG_VALENCEERROR;
      call->reason = 0;
      return 0;
   }

   /*----------------------------------------------------------------*/
   /* Process the right argument                                     */
   /*----------------------------------------------------------------*/
   right = (APLOBJ *) call->right_arg;

   if (right->rank > VECTOR) {
      call->request = MSG_RANKERROR;
      call->reason = 0;
      return 0;
   }

   if (right->nelm != 1) {
      call->request = MSG_LENGTHERROR;
      call->reason = 0;
      return 0;
   }

   if (right->type == INTEGER)  {      /* Already have what we want */
      rows = right->dim[right->rank];
   }
   else {                              /* Try to get it to integer   */
      call->request = ARRAYCONVERT;
      call->parm1 = call->right_arg_token;
      call->parm2 = INTEGER;
      if ((call->service)(call)) {     /* conversion impossible      */
         return 0;  /* ->request and ->reason set by ARRAYCONVERT    */
      }
      rows = *((long *)call->parm3);   /* copy the data we want      */
      call->request = FREESPACE;       /* and now we can free it     */
      (call->service)(call);           /* ->parm1 already set        */
   }
   if (rows < 0) rows = 0;
   if (rows > 5) rows = 5;

   /*----------------------------------------------------------------*/
   /* Create the APL array in the buffer                             */
   /*----------------------------------------------------------------*/
   result = (APLOBJ *) call->token;
   result->ptr = CDRID;
   result->nb = ObjSize(VECTOR) +           /* Descriptor            */
                (4 * sizeof(long));         /* Data                  */
   result->nb = ((result->nb+15)>>4)<<4;    /* Round to 16 bytes     */
   result->nelm = 4;
   result->type = NESTED;
   result->rank = VECTOR;
   result->fill[0] = 0x0;
   result->fill[1] = 0x0;
   result->dim[0] = 4;

   datanest = (long *) &result->dim[result->rank];

   /*----------------------------------------------------------------*/
   /* Create the first subitem                                       */
   /*----------------------------------------------------------------*/
   datanest[0] = result->nb;                /* Offset to this item   */
   subitem = (APLOBJ *) (result->nb + (char *)result); /* This item  */

   subitem->ptr = CDRID;
   subitem->nb = ObjSize(MATRIX) +          /* Descriptor            */
                (rows * sizeof(long));      /* Data                  */
   subitem->nb = ((subitem->nb+15)>>4)<<4;  /* Round to 16 bytes     */
   subitem->nelm = rows;
   subitem->type = INTEGER;
   subitem->rank = MATRIX;
   subitem->fill[0] = 0x0;
   subitem->fill[1] = 0x0;
   subitem->dim[0] = rows;
   subitem->dim[1] = 1;

   dataint = (long *) &subitem->dim[subitem->rank];
   for (i = 0; i < rows; i++) {
      dataint[i] = i + 1;
   }

   result->nb += subitem->nb;               /* Update total size     */

   /*----------------------------------------------------------------*/
   /* Create the second subitem                                      */
   /*----------------------------------------------------------------*/
   datanest[1] = result->nb;                /* Offset to this item   */
   subitem = (APLOBJ *) (result->nb + (char *)result); /* This item  */

   subitem->ptr = CDRID;
   subitem->nb = ObjSize(MATRIX) +          /* Descriptor            */
                 (rows * 4);                /* Data                  */
   subitem->nb = ((subitem->nb+15)>>4)<<4;  /* Round to 16 bytes     */
   subitem->nelm = rows * 4;
   subitem->type = CHARACTER;
   subitem->rank = MATRIX;
   subitem->fill[0] = 0x0;
   subitem->fill[1] = 0x0;
   subitem->dim[0] = rows;
   subitem->dim[1] = 4;

   datachar = (char *) &subitem->dim[subitem->rank];
   memcpy(datachar,"D122D132D121F326D127", rows*4);

   result->nb += subitem->nb;               /* Update total size     */

   /*----------------------------------------------------------------*/
   /* Create the third subitem                                       */
   /*----------------------------------------------------------------*/
   datanest[2] = result->nb;                /* Offset to this item   */
   subitem = (APLOBJ *) (result->nb + (char *)result); /* This item  */

   subitem->ptr = CDRID;
   subitem->nb = ObjSize(MATRIX) +          /* Descriptor            */
                 (rows * sizeof(double));   /* Data                  */
   subitem->nb = ((subitem->nb+15)>>4)<<4;  /* Round to 16 bytes     */
   subitem->nelm = rows;
   subitem->type = FLOAT;
   subitem->rank = MATRIX;
   subitem->fill[0] = 0x0;
   subitem->fill[1] = 0x0;
   subitem->dim[0] = rows;
   subitem->dim[1] = 1;

   datareal = (double *) &subitem->dim[subitem->rank];
   for (i = 0; i < rows; i++) {
      datareal[i] = extension[i];
   }

   result->nb += subitem->nb;               /* Update total size     */

   /*----------------------------------------------------------------*/
   /* Create the fourth subitem                                      */
   /*----------------------------------------------------------------*/
   datanest[3] = result->nb;                /* Offset to this item   */
   subitem = (APLOBJ *) (result->nb + (char *)result); /* This item  */

   subitem->ptr = CDRID;
   subitem->nb = ObjSize(MATRIX) +          /* Descriptor            */
                 (rows * 20);               /* Data                  */
   subitem->nb = ((subitem->nb+15)>>4)<<4;  /* Round to 16 bytes     */
   subitem->nelm = rows * 20;
   subitem->type = CHARACTER;
   subitem->rank = MATRIX;
   subitem->fill[0] = 0x0;
   subitem->fill[1] = 0x0;
   subitem->dim[0] = rows;
   subitem->dim[1] = 20;

   datachar = (char *) &subitem->dim[subitem->rank];
   memset(datachar,' ', rows*20);
   for (i = 0; i < rows; i++) {
      memcpy(datachar,names[i],strlen(names[i]));
      datachar += 20;
   }

   result->nb += subitem->nb;               /* Update total size     */


   /*----------------------------------------------------------------*/
   /* Put the result in the workspace                                */
   /* If it fails call->parm1 will be 0, return codes already set    */
   /*----------------------------------------------------------------*/
   call->request = LCDR_TO_ARRAY;
   call->parm2 = (long) result;
   (call->service)(call);
   call->result_token = call->parm1;

   return 0;
}

