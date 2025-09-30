@echo off
rem
rem  Module Name: APL2.BAT
rem
rem  Descriptive Name: Sample APL2.BAT
rem
rem  Copyright:   5724-B74 Workstation APL2 Version 2.0
rem               Licensed Materials - Property of IBM
rem               © Copyright IBM Corporation 1997, 2008 All Rights Reserved.
rem               US Government Users Restricted Rights - Use, duplication or
rem               disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
rem
rem  Function: Provide sample of a .BAT file to invoke  APL2
rem
rem  Notes:
rem
rem  1. To use this sample, copy it to the APL2 \BIN directory
rem     and modify as desired.  Only the copy in \SAMPLES will be
rem     replaced by future product installs and/or maintenance.
rem
rem  2. This .BAT file is written to run from the APL2 \BIN directory.
rem     If you wish to invoke it from other working directories the
rem     paths should be made complete to avoid ambiguity.
rem     For example:
rem         SET APL00001=..\WSLIB1
rem     would be changed to
rem         SET APL00001=C:\PROGRA~1\IBMAPL2W\WSLIB1
rem     (assuming the default directory has been chosen during installation)
rem
rem  3. Change the location of APL01001 if you want your private
rem     workspaces to be saved in their own separate directory.
rem
rem  4. Define any additional library numbers you wish to have.
rem     For example:
rem        SET APL00011=A:
rem        SET APL00019=D:\AGSS
rem
rem  5. Define any invocation parameters you would like to have in
rem     effect every time APL2 is invoked.
rem     For example:
rem        SET APLWS=8M
rem
SET APL00001=..\WSLIB1
SET APL00002=..\WSLIB2
SET APL01001=.\
SET APL207FL=..\FONTS
SET APLP11=..\BIN\APLNM011.NAM
SET CLASSPATH=%CLASSPATH%;..\bin\apl2.jar
APL2WIN.EXE %1 %2 %3 %4 %5 %6 %7 %8 %9
