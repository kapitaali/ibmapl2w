========================================================================
 5724-B74 IBM* Workstation APL2* Version 2.0
 README for Windows**  (README.TXT)

 Licensed Materials - Property of IBM
 © Copyright IBM Corporation 1997, 2008 All Rights Reserved.
 US Government Users Restricted Rights - Use, duplication or disclosure
 restricted by GSA ADP Schedule Contract with IBM Corp.

 Installation of this product implies acceptance of the license
 statement in the LICENSE INFORMATION section of this README file.
========================================================================

========================================================================
 Required Software
========================================================================

The following software is the minimum required to run APL2:
 -  Windows 7, Windows 8 or Windows 10

Some features of APL2 have additional requirements:
 -  Adobe** Acrobat** Reader to view the on-line documentation
 -  IBM DATABASE 2 (DB2*) for AP 127
 -  An ODBC Driver Manager that supports the ODBC 3.0 level of
    Application Programming Interfaces for AP 227
 -  TCP/IP for AP 119 and cross-system shared variables
 -  IBM Object Rexx or Open Object Rexx for calling Rexx routines with
    Processor 10
 -  TCL and TK 8.1 or later for the TCL external function
 -  Java** 2 Version 1.4 or later for Processor 14 or to call APL2 from Java

========================================================================
 If you have a previous level of APL2 installed...
========================================================================

 - If you have modified any parts supplied with APL2, you should back
   up your modified versions before installing this new level.
   Installing the new level will replace all the product parts from the
   old level.  Note, however, that apl2.bat, apl2.ini, apl2svp.prm and
   apl2svp.prf are replaced only in the \samples directory.
   If you have copies in the \bin directory that you have modified,
   these will be retained.

 - You may either delete the old level (see "Removing APL2" below for
   instructions) or install over it.

   If you elect to install over the old level, the re-installation
   process must be performed from the same userid that performed the
   original product installation.


========================================================================
 Installing APL2
========================================================================

  Installing from CD-ROM:
     Insert the CD-ROM.  If the installation does not start
     automatically, follow the 5 steps below.

  Installing by download:
     Download the installation file to the target machine in binary mode.
     Follow the 5 steps.

  1) Click the "Start" button, point to "Settings", and then click
     "Control Panel".
  2) Double-click "Add/Remove Programs".
  3) Click "Install".
  4) Click "Next".
  5) On CD-ROM, the installation program is "x:\windows\setup.exe",
     where "x" represents the letter of the CD-ROM drive.
     For download, the installation program is the downloaded file.
     Click "Finish".

  Follow the instructions on your screen.

 Notes:

  - On some versions of Windows, if the installation process is performed
    from a userid that is a member of the administrator group, you may be
    prompted to choose whether the installation will be for the current
    user or all users.

  - By default, the installation tool chooses the TCP/IP enabled
    version of the shared variable processor (apl2svp.dll).

    If you are not going to use cross-system shared variables, you can
    install the TCP/IP disabled version. Select the desired dll as follows:

    1. Change into the APL2 \ibmapl2w\bin directory.

    2. To select the dll which uses TCP/IP, (and enables cross-system
       shared variables), issue:

        copy apl2svpt.dll apl2svp.dll

    3. To select the dll which does not use TCP/IP, issue:

        copy apl2svpn.dll apl2svp.dll

========================================================================
 Methods of Starting APL2
========================================================================

By default, one APL2 invocation icon ("APL2win") is installed into
the APL2 folder.  The "APL2win" icon starts APL2 directly from an
.EXE file.  It assumes the environment variables it needs for public
library definitions have already been set.

If you use the default icon as installed, and you want to set up your
own library definitions or invocation options with environment variables,
you can add the environment variables you need in the "Environment"
table of the "System" option in "Control Panel".

If you prefer to use a .BAT file, an APL2.BAT sample file is
shipped in \ibmapl2w\samples.  You can copy this file to \ibmapl2w\bin,
modify as desired to customize your environment, and create an icon in
the APL2 folder or on the desktop which invokes it.

========================================================================
 APL2 Folder and Icon Customization
========================================================================

 After installation is complete, you will have a new folder in "Programs"
 called "IBM APL2".  Click on the "Read Me" icon for information relating
 to this version.  The folder also contains documentation objects and
 program objects to start APL2, the APL file editor, and the SVP monitor.
 The program objects should be considered templates to be customized by
 the user.  For more details on customizing the program objects, see the
 section on "Installing and Customizing APL2" in the APL2 User's Guide.

=========================================================================
 Removing APL2
========================================================================

  1) Click the "Start" button, point to "Settings", and then click
     "Control Panel".
  2) Double-click "Add/Remove Programs".
  3) Select "IBM APL2" from the list of installed programs, and then
     click "Add/Remove".
  4) Confirm "Yes" that you want the product removed.

 If you receive a message that "Some elements could not be removed" when
 APL2 was removed, the elements are probably workspaces, session logs,
 or other files created since APL2 was installed.

  1) Click the "Start" button, point to "Find", and then click
     "Files or Folders...".
  2) Use "Find" to search for a folder named "ibmapl2w".
  3) To check the contents of any folder, double-click on it.
  4) To delete any unwanted file or folder, right-click on it,
     point to "delete", and left-click.

 Note:

  - The removal process must be performed from the same userid that
    performed the original product installation.


========================================================================
Restrictions/Special Notes
========================================================================

 - TCP/IP and the APL2 Shared Variable Processor

   There are two versions of the APL2SVP DLL, for systems with TCP/IP
   (APL2SVPT.DLL) and without TCP/IP (APL2SVPN.DLL).
   If TCP/IP is present on the system, but not configured or not running,
   it appears that TCP/IP does not return a return code to it's caller,
   but merely hangs.  If you experience hangs on APL2 startup, you may
   need to boot your machine to restart TCP/IP, or switch to the
   APL2SVPN.DLL (by copying over APL2SVP.DLL) so that APL2 does not
   attempt to connect to TCP/IP on startup.

 - Termination of Auxiliary Processors written in APL2

   Auxiliary processors written in APL2 may not be terminated cleanly.
   If any APL2 tasks remain active after termination of such an AP, the
   interpreter session for that AP will not be signed off properly from
   the SVP, and it will not be allowed to sign on again.  To bypass the
   problem, all active APL2 tasks must be terminated to reset the SVP.

 - DDESHARE and Excel

   There is a bug in Excel which causes Excel to terminate abnormally.
   If you create a DDE DATA object linked to Excel, and if Excel is
   charting the linked cells, and you specify a value to a variable
   shared with the object's DATA property, Excel will terminate.
   For example, if you copied some data to the clipboard in Excel
   and pasted them into APL2 like this:

         HDATA½PASTE_SPECIAL 'DATA'

   and then assigned a value to the shared variable like this:

         DATA½'3.145' '345' '654' '5432'

   If Excel were charting the cells, it would terminate.

   Microsoft is aware of the problem and suggests the following two
   work-arounds:

   1) Change the Active Sheet

      This problem does not occur if the active sheet is a worksheet.
      To change the active sheet to a worksheet, use a DDE COMMAND object
      to send the Workbook.Activate command to change the active sheet.
      For example, the following macro sends the string "ABCD" to cell
      A1 of Sheet1 in the workbook Book1.

         ä Create a DDE DATA object
         HDATA½'Excel' '[Book1]Sheet1' 'R1C1' APL2_DDE_CONNECT 'DATA'

         ä Create a DDE COMMAND object
         HCMD½'Excel' '[Book1]Sheet1' APL2_DDE_CONNECT 'COMMAND' 'DDE COMMAND'

         ä Change the active sheet.
         COMMAND½'[Workbook.Activate("Sheet2")]'

         ä Change the data on the inactive sheet.
         DATA½'ABCD'

      You must know a sheet name to switch to.

   2) Use a DDE COMMAND object to send the data

      Use a DDE COMMAND object with the Formula function instead of using
      a DDE DATA object. For example, the following macro sends the string
      "3.145" to cell A1 of Sheet1 in the workbook Book1.

         ä Create a DDE COMMAND object
         HCMD½'Excel' '[Book1]Sheet1' APL2_DDE_CONNECT 'COMMAND' 'DDE COMMAND'

         ä Use the formula formula to send the data
         COMMAND½'[Formula("3.145","''Sheet1''!R1C1")]'

   The application, topic, and item names can be retrieved from the
   clipboard if you have copied data to the clipboard from Excel.
   For example:

         'CLIPBOARD LINK' SHAREWINDOW 1 'LINK'
         (APPNAME TOPIC ITEM)½LINK
         DISPLAY (APPNAME TOPIC ITEM)
   Ú¸ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
   ³ Ú¸ÄÄÄÄ¿ Ú¸ÄÄÄÄÄÄÄÄÄÄÄÄ¿ Ú¸ÄÄÄ¿ ³
   ³ ³Excel³ ³[Book1]Sheet1³ ³R1C1³ ³
   ³ ÀÄÄÄÄÄÙ ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÙ ÀÄÄÄÄÙ ³
   ÀîÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ

   For further information, you can contact Microsoft Technical Support
   at http://www.microsoft.com/support or write mshelp@microsoft.com.
   Request article:
      Q176783 "Error using DDEPoke When Chart Is The Active Sheet"


========================================================================
 Support
========================================================================

 We'd like to hear from you!

 Please report any comments, suggestions, or problems through one of the
 following channels:

   RETAIN:      Queue CAPL2W

   Web:         www.ibm.com/software/awdtools/apl

   Email:       apl2@vnet.ibm.com

   Phone:       1-408-463-APL2  (1-408-463-2752)

   Mail:        APL Products & Services
                IBM Silicon Valley Laboratory, 53NA/E2
                555 Bailey Ave.
                San Jose, CA 95141


========================================================================
 Trademarks
========================================================================

 The following terms are trademarks of the IBM Corporation.  They are
 denoted by an asterisk (*) when they first appear in the text.

     APL2
     DB2
     IBM

 The following terms are trademarks of other corporations.  They are
 denoted by a double asterisk (**) when they first appear in the text.

     Adobe               Adobe Systems, Inc.
     Acrobat             Adobe Systems, Inc.
     Java                Sun Microsystems, Inc.
     Windows             Microsoft Corporation

================================================================================
LICENSE INFORMATION
================================================================================

The Programs listed below are licensed under the following terms and conditions
in addition to those of the International Program License Agreement.

Program Name: IBM Workstation APL2 for Multiplatforms V2.0
Program Number: 5724-B74
Authorization for Use on Home/Portable Computer: You may not copy and use this
Program on another computer without paying additional license fees.

Limited Use Rights for Other IBM Programs

If You acquired this Program as part of another IBM Program ("Principal
Program") that lists this Program under "Other IBM Programs", You received this
Program only in support of the Principal Program, and Your rights to use this
Program will be limited by the license of the Principal Program. Please contact
Your IBM Sales Representative if You wish to acquire a separate license to this
Program not limited by the Principal Program's license terms.

Excluded Components

The provisions of this paragraph do not apply to the extent they are held to be
invalid or unenforceable under the law that governs this license. The components
listed below are "Excluded Components." Notwithstanding any of the terms in the
Agreement or any other agreement You may have with IBM:

(a) the third party suppliers of such Excluded Components ("Suppliers") provide
    the components WITHOUT WARRANTIES OF ANY KIND and, such Suppliers DISCLAIM
    ANY AND ALL EXPRESS AND IMPLIED WARRANTIES AND CONDITIONS INCLUDING, BUT NOT
    LIMITED TO, THE WARRANTY OF TITLE, NON-INFRINGEMENT OR INTERFERENCE AND THE
    IMPLIED WARRANTIES AND CONDITIONS OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE, WITH RESPECT TO THE EXCLUDED COMPONENTS;

(b) in no event are the Suppliers liable for any direct, indirect, incidental,
    special, exemplary, punitive or consequential damages, including but not
    limited to lost data, lost savings, and lost profits, with respect to the
    Excluded Components; and,

(c) IBM and the Suppliers are not liable to You, and will not defend, indemnify,
    or hold You harmless for any claims arising from or related to the Excluded
    Components.

Notwithstanding these exclusions, in Germany and Austria, IBM's warranty and
liability for the Excluded Components is governed only by the respective terms
applicable for Germany and Austria in the IBM license agreements.

Notices and important information that IBM is required to provide to You with
respect to the Excluded Components, including instructions for obtaining source
code for certain Excluded Components, may be found in the NOTICES file(s) that
accompanies the Program.

Your use of the Excluded Components is governed by the terms of the Agreement
and not by any terms that may be contained in the NOTICES file(s). The terms
contained in the Agreement are offered by IBM and not by any other party. Future
Program updates or fixpacks may contain additional Excluded Components. Such
additional Excluded Components, and related notices and information, if any,
will be listed in another NOTICES file that accompanies the Program update or
fixpack.

The following are Excluded Components:

Independent JPEG Group JPEG routines version 6b
Microsoft Visual Studio 2003 .Net Runtime Library msvcp71.dll version 7.10.3077.0
Microsoft Visual Studio 2003 .Net Runtime Library msvcr71.dll version 7.10.3052.4
RSA Data Security, Inc., MD5 message-digest algorithm
RSA MD5 (April 1992 Version - original IETF RFC 1321 sample implementation)
Unicode Transformation Format routines

Redistribution Information

If You have developed an application that is dependent upon the files or modules
listed below or located in the directory named below, You may distribute these
files or modules, subject to the following terms:

1) The files or modules must be in object code.
2) You will indemnify IBM or third parties that provide IBM products ("Third
   Parties") from and against any third party claim arising out of the use or
   distribution of Your application.
3) You may not use the same path name as the original files/modules.
4) You may not use IBM's or Third Parties' names or trademarks in connection
   with the marketing of Your applications without IBM's or Third Parties' prior
   written consent.
5) IBM or Third Parties provide copies of these files or modules "AS IS," i.e.,
   You are responsible for all technical assistance for Your application.
6) In Your license agreement with the recipient, You will notify the recipient
   that these files or modules may not be 1) used for any purpose other than to
   enable the application, 2) copied (except for backup purposes), 3) further
   distributed, or 4) reverse assembled, reverse compiled, or otherwise
   translated.

apl2ar20.installp
apl2lr20
apl2lr20.tgz
apl2sr20
apl2sr20.tarz
apl2wr20.exe

Your application containing a copy of the above referenced files/modules must be
labeled as follows:

"CONTAINS Runtime Modules of IBM Workstation APL2 for Multiplatforms V2.0
(c) Copyright IBM Corporation 1991-2008 All Rights Reserved"

Specified Operating Environment

The Program's specifications and specified operating environment information may
be found in documentation accompanying the Program, if available, such as a
read-me file, or other information published by IBM, such as an announcement
letter. You agree that such documentation and other Program content may be
supplied only in the English language.

D/N:  L-DLIG-7DJSH9
P/N:  L-DLIG-7DJSH9
