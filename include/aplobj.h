/*-m-aplobj----------------------------------------------------------
 *
 * Module Name: aplobj.h
 *
 * Descriptive Name: Workstation CDR Formats
 *
 * Copyright:   Workstation APL2        Version 2.0
 *              Licensed Materials - Property of IBM
 *              (c) Copyright IBM Corp. 1994, 2002
 *
 * Function: Provide typedefs and constants for workstation CDRs
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

#ifndef APLOBJ_DEF
#define APLOBJ_DEF
/*-------------------------------------------------------------------*/
/*    Basic Structure                                                */
/*                                                                   */
/*    Note: Each array is a self-contained item, consisting of the   */
/*          APLOBJ structure, followed by the data, and then extra   */
/*          bytes to round up to an even multiple of 16 bytes.       */
/*                                                                   */
/*-------------------------------------------------------------------*/
typedef struct aplobj {
   unsigned long  ptr      ;           /* Platform Identifier        */
   unsigned long  nb       ;           /* Total bytes in this array  */
   unsigned long  nelm     ;           /* Number of elements (xrho)  */
   unsigned char  type     ;           /* Data type                  */
   unsigned char  rank     ;           /* Rank (number of dimensions)*/
   unsigned char  fill[2]  ;           /* Reserved                   */
   unsigned long  dim[1]   ;           /* Items in a dimension       */
                                       /* (# dim elements = rank)    */
} APLOBJ ;

/*-------------------------------------------------------------------*/
/*    Alternate Structure                                            */
/*                                                                   */
/*    This structure refers to the first four bytes as 2 short. It   */
/*    allows references to the pertinent parts of the platform       */
/*    identifier to be made in a way independant of byte-reversal    */
/*                                                                   */
/*-------------------------------------------------------------------*/
typedef struct cdw  {
   unsigned short id       ;           /* Platform Identifier        */
   unsigned short uuzero   ;           /* Unused (Must be zero)      */
   unsigned long  nb       ;           /* Total bytes in this array  */
   unsigned long  nelm     ;           /* Number of elements (xrho)  */
   unsigned char  type     ;           /* Data type                  */
   unsigned char  rank     ;           /* Rank (number of dimensions)*/
   unsigned char  fill[2]  ;           /* Reserved                   */
   unsigned long  dim[1]   ;           /* Items in a dimension       */
                                       /* (# dim elements = rank)    */
} CDW ;

/*-------------------------------------------------------------------*/
/*    Mappings for Data Section                                      */
/*                                                                   */
/*    Note: For scalar integers, since there will be 0 elements in   */
/*          "dim", dim[0] is often used to address the data value.   */
/*                                                                   */
/*    Other mappings could be added for each of the other types,     */
/*    but these seem to be the most useful.                          */
/*                                                                   */
/*-------------------------------------------------------------------*/

 typedef struct objgen {
    unsigned long offset[1] ;          /* Offsets to sub-items       */
 } OBJGEN ;

 typedef struct objapv {
    signed long start   ;              /* Progression start value    */
    signed long inc  ;                 /* And increment              */
 } OBJAPV ;

/*-------------------------------------------------------------------*/
/*    Valid values for the ->ptr field  (APLOBJ)                     */
/*    Note:  The value CDRID denotes the correct id for the          */
/*           the running system.  Can be used to store into          */
/*           the ptr field when creating CDR's for the running       */
/*           system.  Beware of byte reversal when using these.      */
/*                                                                   */
/*    If your compiler is not from IBM, you may need to edit the     */
/*    conditions for using the byte-reversed defintion.              */
/*-------------------------------------------------------------------*/

#define CDRid6000 0x40400000
#define CDRidOS2  0x00002020

#if defined(__OS2__)  || defined(__WINDOWS__) || defined(WIN32) || defined(LINUX)
   #define CDRID 0x00002020
#else
   #define CDRID 0x40400000
#endif

/*-------------------------------------------------------------------*/
/*    Valid values for the ->id  field  (CDW)                        */
/*    Note: If using these to create CDRs be sure to also zero the   */
/*          uuzero field                                             */
/*                                                                   */
/*    If your compiler is not from IBM, you may need to edit the     */
/*    conditions for using the byte-reversed defintion.              */
/*-------------------------------------------------------------------*/

#define CDWid6000    0x4040
#define CDWidOS2     0x2020

#if defined(__OS2__)  || defined(__WINDOWS__) || defined(WIN32) || defined(LINUX)
   #define CDWID 0x2020
#else
   #define CDWID 0x4040
#endif

/*-------------------------------------------------------------------*/
/*    Valid values for the ->type field                              */
/*-------------------------------------------------------------------*/

 #define CDWRTB    0                   /* Boolean                    */
 #define BOOLEAN   CDWRTB
 #define CDWRTI    1                   /* Integer                    */
 #define INTEGER   CDWRTI
 #define CDWRTR    2                   /* Real                       */
 #define FLOAT     CDWRTR
 #define CDWRTJ    3                   /* Complex                    */
 #define COMPLEX   CDWRTJ
 #define CDWRTC    4                   /* Character                  */
 #define CHARACTER CDWRTC
 #define CDWRTD    5                   /* Character long (dbcs)      */
 #define CHARLONG  CDWRTD
 #define CDWRTA    6                   /* Integer Progression vector */
 #define APV       CDWRTA
 #define CDWRTG    7                   /* General array              */
 #define NESTED    CDWRTG

/*-------------------------------------------------------------------*/
/*    Length in bytes for each of the valid types                    */
/*-------------------------------------------------------------------*/

 #define CDWRLB  1                     /* Boolean                    */
 #define CDWRLI  4                     /* Integer                    */
 #define CDWRLR  8                     /* Real                       */
 #define CDWRLJ  16                    /* Complex                    */
 #define CDWRLC  1                     /* Character                  */
 #define CDWRLD  4                     /* Character long (dbcs)      */
 #define CDWRLA  8                     /* Integer Progression vector */
 #define CDWRLG  4                     /* General array              */

/*-------------------------------------------------------------------*/
/*    Some valid values for the ->rank field                         */
/*-------------------------------------------------------------------*/

 #define CDWRRS  0                    /* Scalar                      */
 #define SCALAR  CDWRRS
 #define CDWRRV  1                    /* Vector                      */
 #define VECTOR  CDWRRV
 #define CDWRRM  2                    /* Matrix                      */
 #define MATRIX  CDWRRM

/*-------------------------------------------------------------------*/
/*    Miscellaneous Equates                                          */
/*-------------------------------------------------------------------*/

#define CDWSDLEN      (sizeof(CDW) - sizeof(long))
#define ObjHeadSize   CDWSDLEN
#define ObjSize(Rank) (CDWSDLEN + (sizeof(long)*Rank))

#endif
