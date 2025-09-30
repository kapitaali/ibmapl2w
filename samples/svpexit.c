/*-p-svpexit.c----------------------------------------------------*/
/*                                                                */
/* Module Name: svpexit.c                                         */
/*                                                                */
/* Descriptive Name: Sample encryption exit                       */
/*                                                                */
/*                                                                */
/* Copyright:   Workstation APL2        Version 2.0               */
/*              Licensed Materials - Property of IBM              */
/*              (c) Copyright IBM Corp. 1997, 2002                */
/*                                                                */
/* Function: Sample excryption exit routine for APL2              */
/*           Shared Variables.                                    */
/*                                                                */
/* Prototype:                                                     */
/*                                                                */
/*  long _System cryptrtn(long encdecflag,                        */
/*                        char * data,                            */
/*                        long datalen,                           */
/*                        char * buffer,                          */
/*                        long * bufflenp)                        */
/*                                                                */
/* Parameters:                                                    */
/*                                                                */
/*    encdecflag - flag indicating processing mode                */
/*                 1 = encryption                                 */
/*                 0 = decryption                                 */
/*                                                                */
/*    data       - pointer to data to be processed                */
/*                                                                */
/*    datalen    - length of data to be processed                 */
/*                                                                */
/*    buffer     - pointer to area for processed data             */
/*                 (original data must not be modified)           */
/*                                                                */
/*    bufflenp   - pointer to area for length of processed        */
/*                 data.                                          */
/*                                                                */
/*                 On entry, this area will contain the length of */
/*                 the output buffer.  The routine must be        */
/*                 prepared for the case where the buffer is not  */
/*                 long enough for the processed data, or is of   */
/*                 length 0.  APL2 may call this routine with a   */
/*                 length of 0 to determine the amount of storage */
/*                 required by the routine for its result.  This  */
/*                 length should always be checked before         */
/*                 accessing the storage pointed to by "buffer".  */
/*                                                                */
/*                 On exit, the routine must ensure that the      */
/*                 length area is set to actual length required   */
/*                 for the processed data.                        */
/*                                                                */
/*                 If a 1 is returned to APL2 from this routine,  */
/*                 APL2 will allocate the amount specified and    */
/*                 re-call the routine.                           */
/*                                                                */
/*                 After encryption, the length will be used      */
/*                 to determine how many bytes to send across     */
/*                 the network.                                   */
/*                                                                */
/*                 After decryption, it will be used to validate  */
/*                 that the data has been restored to its         */
/*                 original length before encryption.             */
/*                                                                */
/* Results:                                                       */
/*                                                                */
/*    0 =     Success                                             */
/*    1 =     Insufficient Storage for Result                     */
/*                                                                */
/* Testing:                                                       */
/*                                                                */
/*    Since this routine follows the same linkage conventions     */
/*    as functions called by Processor 11, it can be tested       */
/*    using Processor 11.  The names file entry for the routine   */
/*    when calling via Processor 11 is:                           */
/*                                                                */
/*       :nick.CRYPT     :link.SYSTEM                             */
/*           :lib.svpexit   :proc.cryptrtn                        */
/*           :valence.1 1 0                                       */
/*           :rslt.(I4 0)                                         */
/*           :rarg.(5 G0 1 5)(I4 0)(G4 0)(C1 1 *)                 */
/*                 (I4 0)(G4 0)(>C1 1 *)(G4 0)(>I4 0)             */
/*                                                                */
/*    and a sample call from APL2 for this routine is:            */
/*                                                                */
/*       IN½'ABCDE'                                               */
/*       INLEN½5                                                  */
/*       OUT½5æ' '                                                */
/*       OUTLEN½5                                                 */
/*       CRYPT (1 (âIN) INLEN (â'OUT') (â'OUTLEN'))               */
/*       OUT                                                      */
/*    EDCBA                                                       */
/*                                                                */
/*----------------------------------------------------------------*/

/*----------------------------------------------------------------*/
/* Include of "aplap.h" is for proper resolution of _System       */
/* on Unix and non-IBM compilers                                  */
/*----------------------------------------------------------------*/
#include "aplap.h"

long _System
cryptrtn(long encdecflag,char * data, long datalen, char * buffer, long * bufflenp)  /* EXPORT */
{
   int i,j;

   /*-------------------------------------------------------------*/
   /* Make sure the buffer is large enough for what we want to do */
   /* If not, tell the caller how much we need.                   */
   /*-------------------------------------------------------------*/
   if (datalen > *bufflenp) {
      *bufflenp = datalen;
      return 1;
   }  /* buffer too short */

   if (encdecflag == 1) {
   /*-------------------------------------------------------------*/
   /* Encrypt data - sample is simple reversal                    */
   /*-------------------------------------------------------------*/
      for (i = 0, j = datalen - 1; i < datalen; i++,j--) {
         buffer[i] = data[j];
      }
   }  /* encrypt */

   else {
   /*-------------------------------------------------------------*/
   /* Decrypt data - sample is simple reversal                    */
   /*-------------------------------------------------------------*/
      for (i = 0, j = datalen - 1; i < datalen; i++,j--) {
         buffer[i] = data[j];
      }
   }  /* decrypt */

   /*-------------------------------------------------------------*/
   /* Set correct length for caller.                              */
   /*-------------------------------------------------------------*/
   *bufflenp = datalen;
   return 0;
}
