/*-m-aplap-----------------------------------------------------------
 *
 * Module Name: aplap.h
 *
 * Descriptive Name: SVP interfaces for Auxiliary Processors
 *
 * Copyright:   5724-B74 Workstation APL2 Version 2.0
 *              Licensed Materials - Property of IBM
 *              © Copyright IBM Corporation 1994, 2015
 *              All Rights Reserved.
 *              US Government Users Restricted Rights - Use,
 *              duplication or disclosure restricted by GSA ADP
 *              Schedule Contract with IBM Corp.
 *
 * Function: Provide structures and constants for Auxiliary Processors
 *           to interface with the SVP
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

#ifndef _aplap_h
#define _aplap_h

/*******************************************************************/
/* Extended ID Structure                                           */
/*******************************************************************/
struct xid {                 /* Extended ID structure               */
    unsigned long pparent;   /*  Parent's Parent ID                 */
    unsigned long parent;    /*  Parent ID                          */
    unsigned long procid;    /*  Processor ID                       */
    unsigned long hostid;    /*  Host ID (TCP/IP address)           */
    unsigned long res1;      /*  Reserved                           */
    unsigned long res2;      /*  Reserved                           */
    char userid[8];          /*  User ID                            */
    char surrid[8];          /*  Surrogate ID                       */
    };

struct flags {
    unsigned int b1:1;
    unsigned int b2:1;
    unsigned int b3:1;
    unsigned int b4:1;
    unsigned int b5:1;
    unsigned int b6:1;
    unsigned int b7:1;
    unsigned int b8:1;
    unsigned int b9:1;
    unsigned int b10:1;
    unsigned int b11:1;
    unsigned int b12:1;
    unsigned int b13:1;
    unsigned int b14:1;
    unsigned int b15:1;
    unsigned int b16:1;
    unsigned int b17:1;
    unsigned int b18:1;
    unsigned int b19:1;
    unsigned int b20:1;
    unsigned int b21:1;
    unsigned int b22:1;
    unsigned int b23:1;
    unsigned int b24:1;
    unsigned int b25:1;
    unsigned int b26:1;
    unsigned int b27:1;
    unsigned int b28:1;
    unsigned int b29:1;
    unsigned int b30:1;
    unsigned int b31:1;
    unsigned int b32:1;
    };

/*******************************************************************/
/* Processor Request Block                                         */
/*******************************************************************/
struct prb {
    short req;                 /*  Request code              */
    short rc;                  /*  Return code               */
    short reason;              /*  Reason code               */
    short res1;                /*  Reserved                  */
    struct xid xid;            /*  Extended ID               */
    void *user;                /*  User field                */
    unsigned long emask;       /*  Event mask                */
    unsigned long ntoken;      /*  Notification token        */
    unsigned long pcbx;        /*  PCB index                 */
    unsigned long socket;      /*  Socket number             */
    unsigned long socksem;     /*  Socket semaphore          */
    char ** argv;              /*  Command line args ptr     */
    int argc;                  /*  Count of args             */
    void *res2;                /*  Reserved                  */
    struct flags prbflags;     /*  Processor flags           */
    char socksemname[20];      /*  Socket semaphore name     */
    char reserved[12];         /*  Reserved                  */
    };

#define PRBFOFFS  prbflags.b1  /*  Offers outstanding        */
#define PRBFNPOST prbflags.b3  /*  Don't post                */
#define PRBFNOTRC prbflags.b4  /*  Don't trace               */

/*******************************************************************/
/* Share Request Block                                             */
/*******************************************************************/
struct srb {
    short req;                 /*  Request code              */
    short rc;                  /*  Return code               */
    short reason;              /*  Reason code               */
    short res1;                /*  Reserved                  */
    void *user;                /*  User field                */
    unsigned long ntoken;      /*  Notification token        */
    unsigned long pcbx;        /*  PCB index                 */
    unsigned long scbx;        /*  SCB index                 */
    struct xid pxid;           /*  Extended Partner ID       */
    long osn;                  /*  Offer sequence number     */
    long vlen;                 /*  Length of value           */
    void *value;               /*  Pointer to value          */
    unsigned long pvrba;       /*  Reserved                  */
    unsigned short acv;        /*  Access control            */
    unsigned short state;      /*  State                     */
    unsigned short coupling;   /*  Coupling                  */
    unsigned short res2;       /*  Reserved                  */
    struct flags srbflags;     /*  Flags                     */
    unsigned long socket;      /*  socket number             */
    unsigned long socksem;     /*  socket send sem-id        */
    char socksemname[20];      /*  Socket semaphore name     */
    char reserved[12];         /*  Reserved                  */
    char name[256];            /*  Variable name             */
    };

#define SRBFIGNV  srbflags.b1  /*  Ignore value waiting      */
#define SRBFNEWQ  srbflags.b2  /*  Request new event queue   */
#define SRBFNPOST srbflags.b4  /*  Don't post                */
#define SRBFNOFFR srbflags.b5  /*  No offer back on retract  */

/*******************************************************************/
/* Wait Request Block                                              */
/*******************************************************************/
struct wrb {
   short req;                  /* Request code               */
   short rc;                   /* Return code                */
   short reason;               /* Reason code                */
   short res1;                 /* Reserved                   */
   void *user;                 /* User field                 */
   unsigned long ntoken;       /* Notification token         */
   unsigned long pcbx;         /* PCB index                  */
   unsigned long scbx;         /* SCB index                  */
   unsigned long osn;          /* offer sequence number      */
   long timeout;               /* Timeout value              */
   unsigned long event;        /* Event code                 */
   struct flags wrbflags;      /* Flags                      */
   char reserved[16];          /* Reserved                   */
   };

#define WRBFFLUSH wrbflags.b1  /*  Flush event queue         */

/*******************************************************************/
/* SVP requests                                                    */
/*******************************************************************/
#define SVINIT         0
#define SVSIGNON       1
#define SVSIGNOFF      2
#define SVSCAN         3
#define SVSHARE        4
#define SVSEEACV       5
#define SVSETACV       6
#define SVREF          7
#define SVSPEC         8
#define SVRELEASE      11
#define SVRETRACT      12
#define SVSTATE        13
#define SVQUERY        14
#define SVPREREF       15
#define SVPRESPEC      16
#define SVEVENT        17
#define SVPOST         18
#define SVGETTOKEN     19


/*******************************************************************/
/* SVP return codes                                                */
/*******************************************************************/
#define SVP_ERROR_SYSTEM  - 3     /* System Error                  */
#define SVP_SMNOSPACE     - 2     /* No space for object           */
#define SVP_INTERLOCK     - 1     /* variable interlocked          */
#define SVP_OK              0     /* A-OK                          */
#define SVP_UNAVAILABLE     1     /* SVP is unavailable            */
#define SVP_ERROR_PROTEXCP  2     /* Protection exception          */
#define SVP_ERROR_NSO       3     /* Not signed on                 */
#define SVP_ERROR_ASO       4     /* Already signed on             */
#define SVP_ERROR_PUSED     5     /* Processor in use              */
#define SVP_ERROR_SHRSELF   8     /* Share with self               */
#define SVP_ERROR_VTL       10    /* Value too large               */
#define SVP_ERROR_NOVALUE   11    /* No value                      */
#define SVP_ERROR_NOOFFER   12    /* No offer found                */
#define SVP_ERROR_INVREQ    13    /* Invalid request               */
#define SVP_ERROR_VOS       14    /* Unread value exists           */
#define SVP_ERROR_INVARG    15    /* Invalid argument              */
#define SVP_ERROR_NOEVENT   16    /* No event found                */
#define SVP_ERROR_TIMEOUT   17    /* Timeout on SVEVENT            */
#define SVP_ERROR_INTERRUPT 18    /* Interrupt on wait             */

/*******************************************************************/
/* SVP reason codes                                                */
/*******************************************************************/
#define SVP_ERRSYS_GETNMEM   100   /* Error getting named sh mem    */
#define SVP_ERRSYS_FREEMEM   101   /* Error freeing sh mem          */
#define SVP_ERRSYS_SUBFREE   102   /* Error freeing pcb/scb space   */
#define SVP_ERRSYS_NOPCBS    103   /* Limit on processors exceeded  */
#define SVP_ERRSYS_NOSCBS    104   /* Limit on variables exceeded   */
#define SVP_ERRSYS_GETESEM   105   /* Error creating event sem      */
#define SVP_ERRSYS_POSTQUEUE 106   /* Error on post of queue        */
#define SVP_ERRSYS_WAITESEM  107   /* Error on wait for semaphore   */
#define SVP_ERRSYS_RESETESEM 108   /* Reset semaphore error         */
#define SVP_ERRSYS_OPENSEM   109   /* Error opening a semaphore     */
#define SVP_ERRSYS_REQSEM    110   /* Error requesting sm semaphore */
#define SVP_ERRSYS_RELSEM    111   /* Error releasing sm semaphore  */
#define SVP_ERRSYS_CREATESEM 112   /* Error creating sm semaphore   */
#define SVP_ERRSYS_GETXID    113   /* Error in side file lookup     */
#define SVP_ERRSYS_GETQUEUE  114   /* Error creating msg queue      */
#define SVP_ERRSYS_FREESEM   115   /* Error freeing semaphore       */
#define SVP_ERRSYS_FREEQUEUE 116   /* Error freeing queue           */
#define SVP_ERRSYS_WAITQUEUE 117   /* Error waiting on queue        */
#define SVP_ERRSYS_PEEKQUEUE 118   /* Error peeking queue           */
#define SVP_ERRSYS_OPENFAIL  119   /* Error opening file            */
#define SVP_ERRSYS_QEMPTY    120   /* Error queue is empty          */
#define SVP_ERRSYS_PURGEQUE  121   /* Error purging queue           */
#define SVP_ERRSYS_VARLOCK   122   /* Error acquiring variable lock */

#define SVP_ERRPRF_FNF       201   /* Profile not found             */
#define SVP_ERRPRF_SNF       202   /* Svopid not found              */
#define SVP_ERRPRF_INVF      203   /* Invalid file                  */
#define SVP_ERRPRF_IOERR     204   /* I/O Error                     */
#define SVP_ERRPRF_INVWC     205   /* Invalid wild card             */
#define SVP_ERRPRF_NOAUTH    206   /* Authorization failed          */
#define SVP_ERRPRF_CRYPT     207   /* Could not load crypt routine  */

#define SVP_ARGERR_INVPCBX   301   /* Invalid PCB Index             */
#define SVP_ARGERR_INVSCBX   302   /* Invalid SCB Index             */
#define SVP_ARGERR_INVNAME   303   /* Invalid Variable name         */
#define SVP_ARGERR_NOLOCK    304   /* Lock not held on post-op      */
#define SVP_ARGERR_INVTOKEN  305   /* Invalid token on SVEVENT      */
#define SVP_ARGERR_INVPARENT 306   /* Parent not signed on          */
#define SVP_ARGERR_INVOSN    307   /* Invalid Offer Sequence Number */
#define SVP_ARGERR_INVSPI    308   /* Invalid Process Number        */

/*******************************************************************/
/* SVP event codes                                                 */
/*******************************************************************/
#define SVP_EVENT_OFFEREX     0x01     /* Offer extended           */
#define SVP_EVENT_OFFERAC     0x02     /* Offer accepted           */
#define SVP_EVENT_SMAVAIL     0x04     /* Shared Memory Available  */
#define SVP_EVENT_PRETRACT    0x08     /* Partner retracted        */
#define SVP_EVENT_PSETACV     0x10     /* Partner set ACV          */
#define SVP_EVENT_PSPEC       0x20     /* Partner specified        */
#define SVP_EVENT_PREF        0x40     /* Partner referenced       */
#define SVP_EVENT_FSPEC       0x80     /* Partner failed spec      */
#define SVP_EVENT_FREF        0x100    /* Partner failed ref       */
#define SVP_EVENT_SHUTDOWN    0x200    /* SVP shutdown             */
#define SVP_EVENT_PRELEASE    0x400    /* Partner released var     */


/*******************************************************************/
/* Linkage Convention                                              */
/* We attempt to address the major compilers but user modification */
/* may be necessary.                                               */
/*******************************************************************/

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
 /* Note: this may need to be extended for other compilers */
 #ifndef _System
    #define _System
 #endif
#endif

/*******************************************************************/
/* Function Prototypes                                             */
/*******************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

int _System svpp(struct prb *);
int _System svps(struct srb *);
int _System svpe(struct wrb *);
void _System svsleep(unsigned long);
unsigned long _System aplobjsize(char, char, unsigned long);
void * _System APV2Integer(void *);
void * _System Boolean2Integer(void *);
void * _System Matrix2VectorOfVectors(void *, int);
int _System Nested2Simple(void *);
int _System CompareCdrs(void *, void *);
char * _System GetEnvOpt(char *, int, char **);
char * _System GetEnvLib(int);
char * _System GetSvpOpt(char *);
char * _System GetLibraryStrings(void);
int _System msgs_to_qets(long, long, long *, long *);

#ifdef __cplusplus
}
#endif

/*******************************************************************/
/* Access Control Constants                                        */
/*******************************************************************/

/* sv state    */
#define INITSTATE      0x03
#define PARTSPEC       0x05
#define USERSPEC       0x0A

/* sv coupling */
#define ISSHARED       0x02
#define ISOFFER        0x01
#define ISNTSHAR       0x00

/* sv acv      */
#define ACVMYSET       0x08
#define ACVPARTSET     0x04
#define ACVMYUSE       0x02
#define ACVPARTUSE     0x01

#endif
