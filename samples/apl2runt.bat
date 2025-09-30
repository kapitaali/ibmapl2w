@echo off
rem
rem  Module Name: APL2RUNT.BAT
rem
rem  Descriptive Name: Sample .BAT file for APL2 Runtime
rem
rem  Copyright:   5724-B74 Workstation APL2 Version 2.0
rem               Licensed Materials - Property of IBM
rem               © Copyright IBM Corporation 2002, 2007 All Rights Reserved.
rem               US Government Users Restricted Rights - Use, duplication or
rem               disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
rem
rem  Function: Provide sample of a .BAT file to invoke  APL2 Runtime
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
rem         SET APL207FL=..\FONTS
rem     would be changed to
rem         SET APL207FL=C:\PROGRA~1\IBMAPL2W\FONTS
rem     (assuming the default directory has been chosen during installation)
rem
rem  3. Define any invocation parameters you would like to have in
rem     effect every time APL2 is invoked.
rem     For example:
rem        SET APLWS=8M
rem
rem  4. You must add the information required to start your application.
rem     Use one of the following methods:
rem       -run invocation option or set APLRUN environment variable
rem        to start a packaged workspace in a DLL
rem       -rns or set APLRNS to start a namespace
rem       -input or set APLINPUT to provide APL statements directly
rem       -sm piped or set APLSM=PIPED to take input from a file
rem
SET APL207FL=..\FONTS
SET APLP11=..\BIN\APLNM011.NAM
SET CLASSPATH=%CLASSPATH%;..\APL2.JAR
APL2RUN.EXE %1 %2 %3 %4 %5 %6 %7 %8 %9
