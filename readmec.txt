================================================================================
 5724-B74 IBM* Workstation APL2* Version 2.0
 Corrective Service Information for Windows**  (READMEC.TXT)

 Licensed Materials - Property of IBM
 © Copyright IBM Corporation 1997, 2008 All Rights Reserved.
 US Government Users Restricted Rights - Use, duplication or disclosure
 restricted by GSA ADP Schedule Contract with IBM Corp.

================================================================================

================================================================================
 APL2 for Windows -- Version 2.0  -- Service Level 26 - May 2019
================================================================================

 To install service to APL2 for Windows:

  1. Shut down all running parts of APL2
  2. Download the service .EXE file in binary mode.
  3. Click the "Start" button, point to "Settings", and then click
     "Control Panel".
  4. Double-click "Add/Remove Programs".
  5. Click "Install".
  6. Click "Next".
  7. The installation program is the downloaded .EXE file.
     Click "Finish".

  Follow the instructions on your screen.

 Notes:

  - The service process must be performed from the same userid that
    performed the original product installation.

  - By default, the installation tool chooses the TCP/IP enabled
    version of the shared variable proceessor (apl2svp.dll).
    See the User's Guide or product README for information on
    switching if this is not the desired version.

  - After installing downloaded service, the service .EXE file may be deleted.

  - As of Service Level 13, in order to support objects that contain characters
    that are not in the APL2 atomic vector, the Library Manager and WSCOMP write
    Unicode files when using an external compare program. As a result of this
    change, you must select a compare program that supports Unicode, and you
    must configure it to use a font that contains Unicode APL2 characters (such
    as Courier APL2 Unicode).

 -  As of Service Level 12, AP 127 has been re-written to use the CLI
    interface to DB2*.  This interface does not use bind files.  The
    bind process, and the apldb2.bat file, are no longer required.
    The rewrite should generally be transparent to users, however, the
    following behavior changes may be noted:

    1. Implicit connection to the database via the DB2DBDFT environment
       variable is not supported.  CONNECT must be issued explicitly.
    2. In error conditions the SQLCODE reported may be different.
    3. Errors may not be given for certain type mismatch conditions
       (for example, passing a numeric value in a WHERE clause where
       to column type is character.) Instead, the value is simply
       treated as "not found".
    4. Character columns declared with binary attributes (such as BLOB
       and with the FOR BIT DATA clause) will accept only data that is
       passed to DB2 using binary types.  To force AP 127 to use binary
       types, use the :B form of the value indicator. For example, given
          INSERT INTO TABLE VALUES(:1, :B2, :3, :B4)
       AP 127 will use binary character datatypes to pass the data in
       the second and fourth positions.

  - Starting with Service Level 7, the APL2 system has been generated using
    the Microsoft Visual Studio** compiler instead of the IBM VisualAge*
    compiler.  This change will for the most part be transparent to
    APL2 users. However, please note the following:

    1. The online help for the session manager, editors and SVP monitor
       is in a new format.

    2. Environment variable HELP is no longer used to locate the online
       help.  Standard Windows search order and the PATH environment
       variable are used.

    3. Environment variable TZ is no longer required to determine the
       time zone.  If set, it will be used, but if not set, Windows
       operating system services will be used to determine the time
       zone.  Since the operating system services will more accurately
       reflect the latest policies on dates for changing to and from
       daylight saving time, we recommend that TZ not be set.

    4. Changes have been made to apserver.h so that it can be used
       with the new compiler, and the .lib files shipped with APL2
       (apl2svp.lib and apl2lib.lib) have been generated with the new
       compiler.  If you have C user-written AP's or use the Calls to APL2
       interface from C and have had to make special adjustments to your
       C code in order to use these files with a C compiler other than
       IBM VisualAge, the adjustments may no longer be necessary.

================================================================================
 Support for Windows 98 and Windows Me
================================================================================

 Support for Windows 98 and Windows Me was withdrawn in July 2006.
 Service Level 8 was the last APL2 service level that was tested on
 those systems.  Users still running Windows 98 and Windows Me should
 not install APL2 service beyond Service Level 8.

================================================================================
 Support for Windows 2000
================================================================================

 Support for Windows 2000 was withdrawn in July 2010.
 Service Level 16 was the last APL2 service level to be tested on that
 system.  Users still running Windows 2000 should not install APL2
 service beyond Service Level 16.

================================================================================
 Support for Windows XP
================================================================================

 Support for Windows XP was withdrawn on April 8, 2014.
 Service Level 21 was the last APL2 service level to be tested on
 that system.  Users still running Windows XP should not install APL2
 service beyond Service Level 21.

================================================================================
 Support for Windows Vista**
================================================================================

 Support for Windows Vista was withdrawn on April 11, 2017.
 Service Level 23 was the last APL2 service level to be supported
 that system. Users still running Windows Vista should not install APL2
 service beyond Service Level 23.

================================================================================
 Support for Windows 7
================================================================================

 Support for Windows 7 will be withdrawn in January 2020.
 Service Level 26 is the last APL2 service level to be tested and supported on
 that system.  Users still running Windows 7 should not install APL2
 service beyond Service Level 26.

================================================================================
 Support for Windows 8
================================================================================

 APL2 has been tested by customers on Windows 8.  No new problems
 have been reported, however all the notes below pertaining to Windows 10
 also apply to Windows 8.

 In addition, since Windows 8 does not have a Start menu, we
 recommend that when asked whether you wish an icon to be created on
 the desktop during the installation process, that you reply "yes".
 Otherwise navigation to the APL2 folder to start APL2 may be
 cumbersome.

================================================================================
 Support for Windows 10
================================================================================

 APL2 has been tested on Windows 10.  One new problem has been reported, with
 display of the APL2 Image font.  A workaround removing internal usage of APL2
 Image was shipped in Service Level 25.

 Notes:

  - In Windows 10, certain system directories are protected from write access.
    One of these is "C:\Program Files (x86)", the default installation
    directory for APL2.  If you install APL2 into that directory, you will
    not be able to use DOS commands via AP 100 or )HOST to access files there.
    APL2 library commands like )LIB and )SAVE and direct file access through
    other auxiliary and associated processors (AP 210, AP 211, P12) will still
    work, however file writes may be silently rerouted from the protected
    directories to directories in C:\Users.  This can cause confusion if
    you attempt to find or use files saved within APL2 from another program,
    as they may not be in the directory where you expect to find them.
    The Windows search facility may be used to find their location.

  - APL2 remains a 32-bit program.  It runs on 64-bit systems, but does not
    exploit them.  In addition, you cannot call 64-bit programs from APL2
    using Processor 11 or AP 145, and you cannot interface to 64-bit versions
    of programs when APL2 loads their DLL's to communicate with them.  For
    example, to call Rexx programs using Processor 10, the 32-bit version of
    Rexx must be used.


================================================================================
 Changes in Service Level 26
================================================================================

 Interpreter
    KOC2266  Refcount too high after )RESET via AP 101
    KOC2272  Support larger print width
    KOC2276  Unnecessary garbage collections during grade of integers

 Session Manager
    KOC2270  Memory leak after attempting insert into longest SM line
    KOC2271  No beep/message when insert into SM line reaches limit
    KOC2273  Memory leak when AP 101 string longer than max of PW


================================================================================
 Enhancements Added in Previous Version 2.0 Levels
================================================================================

 Namespaces
    The interpreter and Processor 11 have been enhanced to support
    encapsulation of APL2 workspaces into namespaces. Namespaces
    reside outside the active workspace, and objects in them are
    accessed using the QuadNA system function.

 Runtime Library
    The APL2 Runtime Library is now included with APL2 and may be
    re-distributed with user applications.

 Calls to APL2
  - The APL2 interpreter has been re-packaged into a shared library which
    is callable by other programs.  Specific support and documentation
    is provided for calling APL2 from the C and Java** environments.
  - Visual Basic** is added to the list of languages and programs that are
    supported by the APL2 Program Interface.  A set of subroutines is
    provided that can be called by Visual Basic as external procedures
    to start, manage and stop an APL2 session.
  - A new sample C program demonstrates using the APL2 Programming
    Interface to call APL2 from C.
  - APL2 is added to the list of languages and programs that are
    supported by the APL2 Program Interface.  An external function,
    APL2PIA, provides a synchronous call interface for managing APL2
    sessions. An auxiliary processor, AP 200, provides an asynchronous
    shared variable interface to the same facility.
  - On error, the execution stack is now available to the calling program.
    From APL2, the stack is always returned in the error result.
    From C, use the EXECUTE_APL_ESTACK callback service to enable
    this facility.
    From Java, examine the Stack field of the APL2exception class.
    From Visual Basic, use the GetStack function.

 Invocation
  - Support has been added for the use of a configuration file (.ini)
    to specify APL2 options and settings.
  - A new GUI tool has been added to configure APL2 using the .INI file.
  - New invocation options -p11 and -207fl correspond to the
    environment variables APLP11 and APL207FL.
  - A negative value may be passed to the -id parameter, indicating that
    the first available id number starting with the specified value
    should be used.
  - APL2 will load its fonts automatically on invocation if they are
    not installed in Windows.
  - The -pw invocation option allows specification of the default value
    for the print width.

 Documentation
  - The APL2 on-line manuals, including the APL2 Language Reference,
    are now provided in Adobe PDF format.
  - A new book, "APL2 Programming: GUI Application Development", has been
    added to the APL2 library.  This book includes step-by-step instructions
    for building typical GUI applications.  In addition, it contains
    complete reference information about APL2's GUI programming facilities
    for Windows.
  - A new on-line document has been added to Workstation APL2.
    "APL2 Programming: Using APL2 with WebSphere*" gives step-by-step
    instructions, with examples, for creating a WebSphere application
    that uses APL2.
  - A new section has been added to the User's Guide COM documentation,
    to demonstrate transferring Visual Basic macros between APL2 and
    the Microsoft Office environment.

 Interpreter
  - The following deviations from the APL2 Language Reference
    have been removed:
    - QuadPW is now a session variable
    - The maximum rank of an array has been increased from 63 to 64
    - Comments are now allowed after system commands
    - When displaying nested arrays (default display and monadic format),
      in columns with both numeric and character data, the character data
      is right-justified.  In columns with only non-numeric data,
      character data is left-justified.
    - When results of disclose, expand, replicate and take require the
      use of fill items, the added items will use the prototypes
      for the first element of the correct dimension rather than always
      using the prototype of the first element of the array.
    - The results from partition when one or both arguments are null
      are the correct depth and shape as defined by the language.
    - The depth of the result of monadic format of nested arrays is at
      most two, instead of taking the depth of the argument.
    - Enlist supported in selective specification
    - Fill functions for Each and Outer Product
    - Identity functions for Reduce
    - Allow localization of system function names
    - Factorial, Binomal for complex arguments
    - Domino for complex arguments
    - Support identity items with defined operators
    - Do not display insignificant parts of complex numbers
  - 4-byte characters are now allowed in function and operator
    definitions, in both comments and character constants, and will
    be correctly handled by 2 QuadTF, QuadFX, QuadCR, )IN and )OUT.
    4-byte characters are useful in countries such as Japan, that
    have extended character sets.
  - The limit on the number of names on the left of the assignment
    arrow when using vector specification has been lifted.
  - Function line length limit increases to 32767
  - Execute Controlled system function (QuadEC) returns full stack
    information on error
  - Maximum length of simple workspace name increased from 8 to 64
  - Retain 4-byte characters in QuadEM and QuadEC error results
  - Improve performance of encode and decode
  - Add special cases to Compress/Replicate/Expand for performance
  - The performance of the Find primitive is improved for
    right arguments of rank 2 or higher.
  - Performance of the index of, member and without primitives is
    improved for vectors of integer vectors
  - Unicode option for )EDITOR name
  - Performance of monadic Grade on matrices improved
  - Special case for TAKE/DROP on APVs improves performance

 Session Manager/Object Editor
  - A new "Recent Objects" selection has been added to the "Edit" menu,
    allowing users to select from the most recently edited objects.
  - Windows shortcut keys are supported in the "Find" dialog.
  - The cursor position is changed after insert according to standard
    Windows conventions.
  - The Object Editor now supports matrices containing numeric scalars,
    character scalars, and character vectors.
  - A Mark All choice has been added to the Edit menu.
  - A Marked Lines Only checkbox has been added to the Find dialog
  - A Sort Header choice has been added to the Edit menu for programs.
  - Localized names in programs are now color coded.
  - Format and Check now checks for localized labels in programs.
  - The Open Object dialog has been made resizeable.
  - The Unicode Clipboard system option enables the use of Unicode
    characters during clipboard operations.
  - Editing of objects containing 4-byte characters is allowed, but
    the 4-byte characters are converted to omegas.
  - Operator arguments, operator operands, and labels are
    color coded when editing. Operator arguments and operands are
    classed as local names.  Labels are a new class.
  - Two new buttons have been added to the Session Manager, Object Editor
    and File Editor toolbars, to allow control of the "Partial Line Marking"
    and "APL" settings.
  - The "Lines From/To" option is enabled in the Print dialog for the
    session maanger and editors.  This option allows specification of
    a range of lines to be printed.  If no lines are marked, the default
    range for the session manager is set to the last 150 lines.
    The default for the editors is set to all lines.
  - New system option "Objects Inherit Background Color" can be selected
    to request that editor sessions take the same background color as the
    session manger window from which they were started.
  - The message "Definition changed" will appear in the editors' status
    area when changes have been made and not saved.
  - The follwing session manager options will be enabled by default:
      "Windows Shortcut Keys"
      "Confirm Session Close"
      "Partial Line Marking"
      "Save Continue"
      "Objects on Task Bar"
      "Scroll"
  - A new option, Display, is added to the Session Manager Popup Object Menu.
    Selecting this option when positioned over a variable opens a window
    with the output from the APL2 DISPLAY function for the variable.
  - The "Find" dialog has been redesigned. It is now an integral part of
    the session manager and editor windows and supports highlighting all
    occurances of the find text.
  - "Localize all" and "Unlocalize all" actions have been added to the
    Object Editor's popup menu when editing a function or operator.
    These actions localize or unlocalize all the names on a line.
  - Unicode fonts may be selected for use in the APL2 Session Manager
    and editor windows.
  - Windows themes will be recognized and used in all APL2 GUI windows.
  - File Editor, Library Manager, and SVP Monitor buttons have been added
    to the toolbar.
  - URLs in comments in the Object Editor are underlined.  Double clicking
    on an URL or pressing Ctrl+O when the caret is on a URL opens the URL.
  - New "Always on Top" option available in the Object Editor.
  - The object editor and file editor support display and entry of
    characters that are not in the APL2 Atomic Vector.
  - Proportional fonts are supported in the Session Manager and editors.
  - The find dialog is available in the grid editor
  - DISPLAY popup windows appear on the taskbar, subject to the
    "Objects on Task Bar" system option.
  - The session manager supports user-defined tool bar buttons.
    Entries in the new apl2.ini file define the button text, picture,
    and command.
  - An optional ruler can be displayed in object editor and AplEdit
  - New system option "Underline URLs" controls whether URLs in
    function comments are highlighted and active.
  - New "Find" choice is available in the popup menu
  - The object editor syntax check searches for additional errors,
    including ill-formed names and numeric constants, un-localizable
    system names, and invalid characters.
  - The "APL Assist" is a new optional toolbar containing all the APL2
    special characters.  APL characters can be placed into the session
    manager or editor window at the current cursor position by clicking
    on them in the toolbar, regardless of the APL keyboard setting.
  - Files (.apl or .atf) can now be dropped on the session manager window.
    The user is given a choice of )LOAD, )COPY or )IN as appropriate.
  - The new "Refresh" menu choice and toolbar button in the editors
    re-opens the object using the latest saved definition.
  - The "Open Object" dialog is changed to be non-modal (it will not
    suspend the window that invoked it).
  - Invalid characters in the editor windows will be displayed in
    reverse video.
  - Improved font handling in the dialog editor.
  - Session manager cursor change to hourglass while status is running
  - Allow customization of the characters in the APL Assist toolbar
  - Accelerator key combinations to open the Recent Objects list and
    Open Object dialog
  - Optional set APL divide and times on numeric keypad slash and asterisk
  - Execution properties displayed and settable from object editor
  - Ctrl+Up and Ctrl+Down move caret to previous and next label
  - Unicode characters may be entered using the numeric keypad
  - Popup documentation for APL characters on the APL Assist toolbar
  - Copy To... choice on Log pull-down menu
  - Execute Line executes current line and displays result in separate window
  - Trace All Labels and Stop All Labels choices in Breakpoints menu
  - Close Popups toolbar button and pull-down menu choice
  - Custom toolbar buttons can execute APL expressions
  - Find dialog input fields are wider
  - Active workspace name displayed in Session Manager titlebar
  - File menu in Session Manager menubar
  - Undo facility in Object Editor
  - Remove Unused Locals facility in Object Editor
  - Font size change using Ctrl+MouseWheel or Ctrl+Keypad +-
  - Reverse video supported by the APL2 Colors dialog
  - New object editor output classes for Syntax Error and URL
  - Preserve color and font as data is copied to the clipboard
  - Use single global custom colors array
  - Use I beam cursor for input area
  - Paste File into Object Editor
  - Windows shortcut key combinations are shown in menus if the Windows
    Shortcut Keys option is on.
  - Redo capability after Undo
  - Comment / Decomment Marked Areas
  - Debugging Facilities
    - Session Manager Debug Menu
      - Set debugging options
      - Set stops and traces on all functions
    - Stop and Trace All affects only non-blank non-comment lines
    - Set multiple break points by swiping mouse
    - Popup menu for line number area of Object Editor
    - Shift+Pause key combination for Resume
    - Visual cue for line on which execution is suspended
    - Breakpoint choices in Popup menu
    - Watch windows
    - Stack window
  - AP 120 program interface to object editor
  - Assist bar online help windows show key combination
  - Shift+Escape to edit line in wrapped mode
  - Alt+PageDown moves current line to top of window
  - Trace and stop this line on line number popup menu
  - Ctrl+Double Click marks token
  - Ctrl+Shift+Double Click localizes/unlocalizes name
  - Watch workspace size system option
  - Add access keys (mnemonics) to menus
  - Shift+F10 displays the popup menu
  - Add Save As, Open Object and Recent Files to Object Menu
  - Support Drag and drop marked text
  - Stack and Watch always on top options
  - Unlocalize/Unlocalize all in popup object menu
  - Programmable interface for watch windows
  - Color coding of global names in object editor
  - User-controllable character cell size in grid editor
  - A new session manager option supports automatically setting
    print width based on window size.

 File Editor
  - UTF8 and UCS4 data support in AplEdit and GUITOOLS Unicode file
    editing functions
  - Start line numbers with 1

 Keyboard Handler
  - Support Unicode characters in keyboard layouts

 Library Manager
  - This new tool allows the user to explore the active APL2 workspace
    and APL2 workspaces, transfer files and namespaces saved on disk.
    Features include workspace-to-workspace comparison, object-to-object
    comparison, and clipboard operations to transfer objects to the
    active workspace.
  - Support is added for files with non-standard extensions; APL2 file
    type will be determined by examination of the contents.
  - The new "Compare Timestamps" option specifies whether timestampes
    are considered when comparing function and operator definitions.
  - The new "Sort using DCS" option allows for an alternate sorting
    algorithm based on the DCS variable from 1 EXAMPLES.
  - Compare objects containing Unicode data

 SVP Monitor
  - The information from the SVP parameter file (apl2svp.prm) is added
    to the SVP Monitor "Info"->"Statistics" display.
  - The variable information panel has been enhanced to show two numbers
    for variable space usage - amount allocated and amount in use.

 AP 119
    The 'SOCKET' command has been enhanced to accept the 'DGRAM' type
    keyword, which allows the use of datagram sockets.

 AP 124
    When a font is selected via the AP 124 menubar, that font
    setting will be retained across APL2 sessions.

 AP 127/AP 227
  - A new invocation option, -isol, has been added for AP 127 and AP 227.
    This invocation option sets the default isolation level for the
    APL2 session.  Note: isolation level can also be changed dynamically
    using the AP command 'ISOL'.
  - Two new commands have been added to AP 227:
    - ODBC retrieves information about available datasources or drivers.
    - ODBCOPEN sets up an SQL table containing information about
      the tables or supported datatypes of the current database.
  - Support is added for an indicator to be used with value list indices to
    request processing of data with the BLOB (Binary Large Object) SQL type.
    In the following SQL statement
          INSERT INTO TABLE (CHARCOL, BLOBCOL) VALUES (:1, :B2)
    the use of the letter B (:B2) indicates that AP 127 should use
    the BLOB type when passing the associated data to DB2
  - AP 127's restrictions on the length of the id and password parameters
    to CONNECT have been lifted.  (The database system may still impose
    its own restrictions).
  - AP 127 and AP 227 will recognize and fetch the XML column datatype.
    'X' is returned as the datatype indicator in DESCRIBE output.
  - AP 127 and AP 227 are enhanced to allow calls to Stored
    Procedures, including support for output parameters and
    result set fetching.  The SQL workspace is also updated to
    handle these calls, through the SQL function and with a new
    high-level function PROCEDURE.
  - Support for DECFLOAT datatype

 Dialog Editor/AP 145/DEMO145/GUITOOLS
  - a new Grid Control has been added
  - the MLE "wordwrap" style is now supported
  - The Grid control has been enhanced to support numeric data.
  - Dynamic Control Creation
    Controls can now be created dynamically without using the dialog
    editor or dialog templates.  The CREATEDLG function accepts a
    character vector containing a list of dialog styles. The new
    CREATECTL function is used to create controls.
  - Positioning and Sizing Aids
    New Properties:
       CLIENT POSITION positions control relative to parent's client area.
       CLIENT SIZE resizes a dialog to produce a specified client area size.
       MAXIMUM SIZE, MINIMUM SIZE specify a dialog's resizing limits.
       OFFSET indicates how controls should be resized as dialogs are resized.
       SPLIT positions a dialog split bar.
       STATE MINMAX minimizes, maximizes and restores dialogs.
    New Functions:
       SIZETOTEXT resizes a control to fit its data.
       CENTER_CHILD centers a control within its parent's client area.
  - Printing Facilities
    PRINT_PROPERTY function used to get and set print job properties
    Properties supported:
       ORIENTATION indicates portrait or landscape paper orientation
       PAPER SIZE returns size of paper
       POSITION indicates position on page of next output
       MINIMUM MARGINS returns minimum margins supported by printer
       MARGINS indicates margins used in print job
  - STATE APL property enables APL keyboard input
  - PICTURE property sets dialog icon
  - Listbox and Combobox Sort style maintains data in alphabetical order
  - 3state Check Boxes supported
  - GETPARENT, GETCHILDREN functions return handles of parents and children
  - The BORDER style is now supported for Frames and Rectangles.
  - New PATH, PATH SELECTION, and PATH STYLE properties enable
    the inclusion of file and directory information in dialogs.
  - Support has been added for dialog scroll bar events.
  - New STATE LIST VISIBLE property controls whether the list portion
    of combo boxes is visible.
  - New PRINTERS, PRINTER and FILENAME properties for print objects
    enable applications to query the available printers, query or set
    the current printer, and query or set the output filename, all
    under program control.
  - New CLIENT ORIGIN property makes it possible to easily position
    controls relative to group boxes.
  - Event handlers can now contain Unicode characters
  - The following new demos have been added:
    - DEMO_EXPLORE demonstrates using dialogs in a split dialog.
    - DEMO_GDI demonstrates using Microsoft Gdi API's through AP 145.
    - DEMO_MODE demonstrates modal and modeless dialogs.
    - DEMO_PATH demonstrates displaying file and directory information.
    - DEMO_PROPERTIES demonstrates building a properties dialog dynamically.
  - The following new tools have been added:
    - ALIGN, RESIZE and SPACE make it easy to arrange controls.
    - FILEDLG displays a standard Open or Save As file dialog.
    - FONTDLG displays a standard font dialog.
    - MSGBOX supports new flags to control display of icons and buttons.
    - POPUPMENU displays a popup menu.
    - UNIEDIT supports editing arrays containing Unicode characters.
  - Buttons produce new "Button down" and "Button up" events.
  - The BORDER style is supported for text controls.
  - New command AplShowContextHelp and function CONTEXTHELP display
    the context help associated with a control or menu item.
  - The EDIT and UNIEDIT sample functions have been enhanced to
    support numeric matrices, using a grid control.
  - "Set Focus" and "Kill Focus" events added for graphic windows
  - New custom control class enables programmers to build controls in APL2.
  - CLASS and STYLE properties return the data used to create windows.
  - GET_PROFILE and SET_PROFILE in GUITOOLS allow applications to store
    and retrieve information in the Windows registry.
  - LOADAPI, CALLAPI, and FREEAPI in GUITOOLS make it easier for applications
    to manage calls to routines in dynamic link libraries (DLLs).
  - DEMO_SHEET in DEMO145 demonstrates how to build a spreadsheet interface
    combining an entry field and grid controls.
  - New property TEMPLATE allows direct reference of the definition
    template for a dialog.
  - New property ID allows reference and specification of the id
    associated with a control in a dialog.
  - New function PRINTER_PROPERTIES in workspace GUITOOLS displays
    the printer properties dialog
  - Support is added for changing the number of rows and columns in
    a Grid control by specifying the CONTROL DATA property.
  - Support is added for specification and reference of the UNICODE DATA
    property of a Listview control
  - Treeview control
  - "Resizable" style for Grid controls
  - "NAME" property
  - "FOCUS" property for Listview controls
  - "Context menu" event
  - "Kill focus" and "Set focus" events for Listview controls
  - "Start Menu" event for dialogs
  - Grid property CELL FORMAT and event "Format Change" allow for
    program control of the format of the cell (numeric vs. character).
  - Event handlers can now be arbitrary arrays including labels.  This
    makes it easier to write self-contained and more efficient GUI programs.
  - The new WAIT_EVENT function supports arbitrary array event handlers and
    waiting for events until a timeout.
  - The new FOLDERDLG function prompts the user for a folder.
  - The new COLORDLG function lets the user change window colors.
  - The POPUPMENU function has been enhanced to support submenus.
  - The picture properties now support more types of images including
    JPEGs and GIFs.  Images can be in image files, DLLs, or in the workspace.
  - The file and folder dialogs are sizeable and include places buttons.
  - The FILEDLG function supports an optional title argument.
  - Listview controls now support the UNICODE HEADINGS property.
  - Windows themes will be recognized and used in AP 145 windows.
  - Unicode support is enhanced, including support for Unicode data in
    menus, status areas and tab controls, the addition of Unicode
    versions of the FILEDLG, FOLDERDLG and POPUPMENU functions, and
    extension of the UNIMSGBOX function to support styles.
  - Drag and drop of files onto dialogs, listviews, MLEs,
    treeviews, and custom controls.
  - All controls support the 'Hover' event.
  - Listview controls support the 'Check state change' event.
  - Listview labels may be edited.
  - Pictures may be specified for menu items
    Note: To support some forms of pictures, including those used
          in the new DEMO_MENU function in DEMO145, AP 145 uses GDI+,
          a library of graphics routines that is included in all current
          levels of Windows. For older versions of Windows, GDI+ is
          available for download from Microsoft. If GDI+ is not installed,
          AP 145 will display a message box with further instructions.
  - SIZETOTEXT supports controls with the PICTURE property set.
  - The CURSOR property supports arrow, hand, and question mark cursors.
  - LOADAPI allows specification of argument and result types.
  - New service AplStrLen is added.
  - Scroll bar support is added to the custom control
  - Dialogs support scroll bar thumb tracking
  - The profile tools (GET_PROFILE and SET_PROFILE) are enhanced to support
    INI files, listing profile values, and deletion of profile values.
  - DEMO_TOOLBAR in DEMO145 shows how to create a toolbar using AP 145.
  - Progress bar controls
  - Mouse wheel support
  - Horizontal split bar for dialogs
  - Horizontal scroll bars for Combobox and Listbox controls
  - STATE ENABLE property for static controls
  - Multiple values in GET_PROPERTY and SET_PROPERTY arguments
  - ActiveX** controls may be used in dialogs
  - New dialog styles NoIcon and NoIgnore
  - Built-in picture support for menu items
  - Address support in LOADAPI and CALLAPI
  - Multiple lines of initial data for MLE and text controls
  - STATE RESIZING property
  - Add UNIDeltaFM  (Unicode version of DeltaFM)
  - 'COLLAPSED ...' properties for drop-down combo boxes

 AP 207
  - A new command, 'MENU', allows an application to use the commands
    available on the AP 207 windows' menubar
  - A new keyword, 'ORIENTATION', is accepted for the 'PRINTER SETUP'
    item of the 'MENU' command.  This keyword allows you to set and
    reference the printer orientation under program control.
  - The new PRINTERS and PRINTER options for the MENU command allow
    applications to query the available printers and query or set the
    current printer under program control.
  - The 'CURSOR' command has been enhanced to support eleven additional
    cursor images.
  - Options 'OUTPUT' and 'FILENAME' are added to the 'MENU' command.
    'OUTPUT' sets the output destination to 'PRINTER' or 'FILE'
    'FILENAME' sets the file name to be used when 'OUTPUT' is 'FILE'
  - An additional cursor image, the hand, is supported by the CURSOR
    command as cursor number 13.
  - All use of temporary disk files is removed from the GRDATA command
  - Unicode window mode is now supported by the AP 207 'OPEN' command.

 AP 210
    Improved performance accessing linefeed-delimited files

 EXECUTE_APL Callback Service
    A new callback service is provided for external functions written
    to the :link.FUNCTION protocol.  EXECUTE_APL allows external
    functions to request execution of APL expressions and functions.

 Processor 10
    Performance of the built-in file functions is improved

 Processor 11
  - Support is added for searching more than one names file for an
    external routine's descriptor.  Where a single file name was
    previously provided, multiple file names separated by ; (semi-colon)
    may now be provided.
  - Null-terminated strings of two-byte characters are supported in
    patterns specified for ATR, RTA, Procssor 15, and arguments to
    non-APL external routines.

 Processor 12
  - A new pattern, 'C1 1 *', is supported when associating a name with a
    text file (type 'F').  This pattern specifies that the view of the
    file in APL2 will be a simple character vector (byte stream).
  - Five new pattern types (C2, C4, I4, E8 and J16) are supported
    by Processor 12 when viewing a file as a simple vector.
  - Performance of association to lf-delimited files is improved.
  - The amount of temporary storage required for write operations to
    APL files is reduced by half.

 Processor 14/Java Interfaces
  - A new associated processor, Processor 14, provides the ability
    to call Java from APL2.
  - A new invocation option to APL2, -javaxmx, allows control of the
    size of the memory heap used by the Java Virtual Machine started by
    the APL2 Java interfaces.
  - Java objects may now be passed directly to APL2, instead of being
    converted to APL2 objects.
  - Return Java exception through P14

 Processor 15
  - This new associated processor provides access to storage outside
    the APL2 workspace using variable names in the workspace. The
    storage is formatted into APL2 data structures by Processor 15
    based on a user-provided pattern.
  - Arbitrary arrays are supported with the '' pattern
  - Variable monitor expressions can be established

 Visual Basic Interface
  - "Assign" has been added the set of functions provided for calling APL2
    from Visual Basic.  It allows you to directly assign a name to an object.
  - Support is added for passing parameters by reference ("ByRef")

 Supplied External Routines
  - A new external function provides access to Microsoft Component Object
    Model (COM) objects from APL2.  COM is an object-oriented protocol
    that is supported by many Windows programs, including the Microsoft
    Office suite of products.
  - A new set of external functions provides workspace compression
    facilities.  The ZIP and UNZIP functions operate on individual APL
    arrays, and the ZIPWS and UNZIPWS functions operate on the entire
    workspace.  Note: these functions use the APL2 Java interfaces.
  - A new external function, TCL, provides an interface to the Tcl/Tk
    language.
  - The TIME function from 1 TIME and the DISPLAY, DISPLAYC and DISPLAYG
    functions from 1 DISPLAY have been placed in a new namespace shipped
    with APL2.  You can access these functions via name association:
       3 11 êNA 'TIME'
       3 11 êNA 'DISPLAY'
  - The ATR and RTA external functions have been extended to support a
    monadic syntax.  If ATR is called without a left argument, it uses
    Common Data Representation (CDR) format to create its result.  If RTA
    is called without a left argument, it will treat its right argument
    as a CDR.  RTA will support the CDR format of both workstation and
    mainframe APL2.
 -  The follow new external functions have been added:
    CHECK_ERROR gets the text associated with a system error number.
                This function is a replacement for the APL function
                in the AIX, LINUX and SOLARIS workspaces, and is
                available for all platforms. An association to this
                function has been added to the WINDOWS workspace.
    OPTION      queries and sets APL2 invocation and session options.
    PRINTWSG    is a version of PRINTWS with a GUI user interface.
 -  The following functions from the supplied workspaces have been
    moved into namespaces and are available as external functions.
    The namespace versions of the functions are platform-independent:
    From WINDOWS:
      DIR         Return a directory listing
      ERASE       Erase a file
      HOST        Execute a operating system command
      LIBS        Return the list of defined APL2 workspace libraries
      MKDIR       Make a directory
      PIPE        Redirect input and output to a command
      RENAME      Rename a file
      RMDIR       Remove a directory
    From EDIT:
      EDITOR_2    Mainframe )EDITOR 2 equivalent editor
    From IDIOMS:
      IDIOMS      Display commonly used APL2 phrases
    From WSCOMP:
      WSCOMP      Workspace comparison tool
      WSCOMP_ANALYZE
  - Three new external routines provide program access to the
    functionality of the APL2 system commands )COPY, )PCOPY and )LIB.
    The COPY, PCOPY and LIB functions are accessed via Processor 11
    and take a character string argument with the same syntax as their
    corresponding system commands.
  - Four new namespaces contain the contents of the public library 2
    workspaces FILE, GRAPHPAK, MATHFNS and SQL.  The namespaces
    are an alternative way to use the objects in these workspaces
    without making local copies of them and without name conflicts.
  - Support for events is added to the COM external function. You can
    query the available events for a COM object, request notification
    when events occur, and wait for notification of events.
  - When passed a null right argument, the OPTION external function
    will return the APL2 command line.
  - Unicode filenames are accepted by  FILE and FSTAT
  - Output parameters are supported by COM
  - TIME 4 queries the current state of timing
  - New external function REPLACEX is a high-performance routine to
    replace instances of a string or strings in a character vector.
  - Namespace versions of the GUITOOLS and GUIVARS workspaces
    are shipped with the APL2 product.
  - New DATATYPE function returns information about the internal type
    of data objects in the APL2 workspace.  It is compatible with
    the new mainframe APL2 function of the same name.
  - New PEACHP and PEACHT operators allow automatic distribution of
    computation across multiple processors.
  - ROUNDC external function provides high-performance commercial rounding
  - Configure APL2 supports browsing for path and file names
  - IDIOMSG provides a GUI interface to the APL2 Idioms Library.
  - FDELETE deletes an operating system file.
    On Windows, the deleted file will be sent to the recycle bin.
  - LEXP is a lexical parsing facility that analyzes a
    character vector using the APL2 syntax rules.
  - SI and SIS provide program access to the APL2 stack
  - The RF external function is extended to handle nested matrices
    whose subitems are all character and/or integer arrays of any rank.
  - The SCANDIR function gets directory listings without use of an
    operating system shell.
  - GMTSTAMP function allows setting function timestamps under program control

 Workspaces
  DEMOJAVA
  - JAVAMAIL_SEND function to send emails
  - XML2APL and APL2XML tools parse and create XML
  - JAVA_PRINT prints APL objects using Java faclities
  - XML2APL adds support for DTD addresses
  GRAPHPAK
  - New function OPENGP145 supports opening the graphics window within
    an AP 145 dialog.
  WSCOMP
  - The Windows GUI interface of the WSCOMP workspace has been enhanced
    to allow specification of a user-selected compare program.
  - Compare objects containing Unicode data
  - Use summary window status area for warning messages
  - Copy name to clipboard on summary screen

 Installation
  - On NT-based Windows systems, administrator authority will not be
    required to install APL2 for a single user.
  - The option to add an APL2 program icon on the desktop will be offered.
  - The default install directory path will be obtained by querying
    the system, allowing for national language differences.


================================================================================
 Problems Fixed by Previous Version 2.0 Levels
================================================================================

 Interpreter
    KOA0105  Transfer form accepts period after object name
    KOA0128  QuadFX will not accept empty numeric
    KOA0133  QuadFX behavior does not match host
    KOA0145  Reduce with axis fuzz problem
    KOA0274  System fuzz not working for booleans
    KOA0353  No prompt for 1st input with -sm off -quiet on
    KOA0387  Reduce 0-wise (from slash) w/scalar dyadic fns
    KOA0445  Inner product documentation discrepancy
    KOA0484  QuadES with Each does not result in DOMAIN ERROR
    KOA0489  Called functions do not inherit "Ignore attention" property
    KOB0033  Enclose along axis of empty does not reduce rank
    KOB0111  QuadPR inserted in reply to empty QuoteQuad prompt
    KOB0155  QuoteQuad input reprompts with 6 blanks after ENTRY ERROR
    KOB0349  Domino is not interruptible
    KOB0392  Interpreter should discard stack on Interrupt
    KOB0470  1 QuadTF ignores non-blank extra characters
    KOB0543  Behaviour of wrapping on error lines
    KOB0548  AP1 does not send system variables always
    KOB0657  Quad or quote-quad as labels handled incorrectly
    KOB0869  AXIS ERROR from some cases of inner/outer product with axis
    KOB0957  Tolerate trailing slash on library envronment vars
    KOB1064  Clueless NOT SAVED message
    KOB1140  )EDITOR xxx cannot be qualified name
    KOB1329  Prohibit nested expressions in vector specification
    KOB1700  Inconsistancy in scalar extension with nulls
    KOB1887  Selective spec works on APL2/PC, fails on new APL2
    KOB1962  Quad Input not allowed under QuadEC
    KOB2291  4 QuadAT of shared variable returns 0 0
    KOB2332  Improve interruptibility of nested array operations
    KOB2379  Selective specification leads to Ws Full and/Or System Error
    KOB2472  Checkws errors or hang interrupting output of large array
    KOB2485  2 QuadTF of a shared variable returns ''
    KOB2486  QuadTF will not replace P12 var with normal var
    KOB2487  Problems replacing existing external objects with QuadTF
    KOB2618  Prompt replacement does not work
    KOB2646  )IN cannot find lowercase Quad name in transfer file
    KOB2663  Interpreter does not sign off SVP on Ctrl-Break
    KOB2739  Bad format of array with positive and negative floating point
    KOB2790  Workspace does not expand enough during )COPY
    KOB2808  Handle 4-byte character arguments to Quad functions
    KOC0039  Wrong error when function result shared or not a variable
    KOC0046  QuadES does not accept 4 byte characters
    KOC0064  Cannot fix operator with leading spaces in header
    KOC0071  Increase default wssize
    KOC0126  Recovery when external function returns error
    KOC0137  Cannot start APL with corrupted CONTINUE.apl
    KOC0154  Branch in Execute Alternate before Diamond Bug
    KOC0157  Incomplete external name cleanup on clear
    KOC0176  Garbage in result of expand with arg in parentheses
    KOC0179  -ws invocation parameter interprets large sizes incorrectly
    KOC0205  Diamond formatted with blanks
    KOC0206  AP 1 does not handle requests after )HOST
    KOC0217  System Error in Selective Spec
    KOC0218  Cannot open object when interpreter runs app
    KOC0229  Checkws message after )RESET 1
    KOC0256  )COPY changes current directory
    KOC0268  Invalid SYNTAX ERROR doing outer product each
    KOC0287  EXP while running under an EXP doesn't work
    KOC0301  System Error using QuadEC under EXP
    KOC0302  Interpreter terminates using QuadCR under EXP
    KOC0306  )LOADing PRML workspace crashes interpreter
    KOC0307  QuadEC and QuadEA problems under EXP
    KOC0309  Checkws messages on )SAVE
    KOC0310  Problems in vector specification with external name
    KOC0311  Overbar invalid in )VARS, )FNS, )OPS, )NMS
    KOC0319  Cleanup of external names incomplete on )CLEAR
    KOC0328  APL2 terminates on repeat QuadNA from namespace
    KOC0329  SYSTEM ERROR copying workspace with external name
    KOC0330  SYSTEM ERROR, selective spec of Boolean into float
    KOC0331  Incorrect output from 0 2 format
    KOC0332  Cannot use nameclass to access object in namespace
    KOC0333  Wrong error from QuadES under EXP with numeric event
    KOC0334  QuadET incorrect after reference inside function
    KOC0337  AP 1 reports )SAVEd association to namespace is class 0
    KOC0353  Residue wrong on maximum left arg
    KOC0356  Checkws messages after failed association
    KOC0357  Circle Left Argument fuzz problem
    KOC0358  Interpreter crashs if error in long input
    KOC0360  Checkws messages after PFA of depth 182 array
    KOC0361  Interpreter abends with invalid CONTINUE
    KOC0362  )COPY from a Version 2 workspace corrupts ws
    KOC0363  Checkws messages after MOD1165 test case 365
    KOC0365  Checkws msg after WS FULL doing +/[2]...
    KOC0367  DOMAIN ERROR from decode, residue
    KOC0368  Catenate allows creation of high-rank objects
    KOC0369  Editor 1 Function Display Problems
    KOC0372  Garbage in replicate fill items
    KOC0373  Bad answer, magnitude of largest negative integer
    KOC0374  DOMAIN ERROR from exponential on certain negative arguments.
    KOC0386  Checkws messages after using namespace
    KOC0387  Segmentation fault (SIGSEGV) assigning long name
    KOC0401  Interpreter error msgs not wrapped at QuadPW
    KOC0407  QuadET incorrect after reference via EXP
    KOC0427  Shared variable system function edge conditions
    KOC0428  Garbage in QuadEM after execute with DBCS
    KOC0433  Left operand to expand not fuzzed to Boolean
    KOC0434  System fuzz not used for monadic grade
    KOC0435  QuadDL right argument not fuzzed to float
    KOC0463  AP 101 crashes interpreter
    KOC0480  Disclose with empty object leads to System Error
    KOC0485  SYSTEM ERROR after using namespaces
    KOC0508  QuadEC returns 4 byte error messages
    KOC0518  QuoteQuad input uses old prompt after ENTRY ERROR
    KOC0519  Output wrapping logic does not consider previous QQ output
    KOC0524  CHECKWS after catenation of large matrices
    KOC0533  SYSTEM ERROR after WS FULL replacing column of mixed matrix
    KOC0552  NOT COPIED: message from )IN
    KOC0555  QuadTF fails to fix function missing trailing quote
    KOC0562  System Error accessing QuadTF in namespace
    KOC0565  Stop and trace vectors can be set on namespace function
    KOC0567  System Error using object in namespace
    KOC0574  DOMAIN ERROR from Dyadic Format
    KOC0575  RANK ERROR from reduce of empty
    KOC0581  Error behavior wrong in operand across namespace boundary
    KOC0590  Abend after error in defined function
    KOC0592  Abend opening a locked function
    KOC0595  DOMAIN ERROR multiplying float by null
    KOC0604  Assignment to Quad fails under EXP
    KOC0609  Abend after re-association of namespace value
    KOC0610  Abend using TIME inside namespace
    KOC0611  QuadEC of namespace function produces wrong QuadEM
    KOC0612  Bad answer from or-scan of integer argument
    KOC0627  Function display loses data when QuadPW is exceeded
    KOC0643  SYSTEM ERROR trying to display namespace function
    KOC0648  )NMS wrong on QuadNA'ed object in namespace
    KOC0654  EXP allows assignment to primitive functions
    KOC0656  GETENV in namespace causes system error
    KOC0665  Checkws msg after )LOAD w/namespace suspended
    KOC0687  SYSTEM ERROR from 2 QuadAT of function in namespace
    KOC0689  QuadTS returns '' in rare cases
    KOC0693  "Namespace modified" message after )COPY of external object
    KOC0701  Double-click edit of external abends the interpreter
    KOC0707  Prompt written for Quad input under runtime
    KOC0712  QuadES should accept nested vectors of integer scalars
    KOC0726  System Error using external variable on left of compress
    KOC0729  CHECKWS msgs after member/index on Unicode data
    KOC0736  Nested array of scalars not accepted on left of compress
    KOC0737  Handle external variables as arguments to external functions
    KOC0742  Back off KOC0575 fix until KOC0650 fix is available
    KOC0753  )OUT external with long name abends interpreter
    KOC0760  )IN with namelist fails on P12 variable with no surrogate
    KOC0773  QuadNA allows Quadname surrogates
    KOC0782  No INDEX ERROR when index is invalid APV
    KOC0791  Bad data, checkws messages after error during P12 catenate
    KOC0795  Incorrect data for external var indexed assignment
    KOC0799  2 (5 5) return from 2-take-QuadEC
    KOC0806  SYSTEM ERROR modifying copy of simple external var
    KOC0807  Last input line lost if no trailing LF on file
    KOC0808  Inaccurate result from binomial
    KOC0813  Wrong item replaced, selective spec with pick of squad
    KOC0814  Inaccurate result from complex logarithm
    KOC0817  Abend during )IN of mainfame apltf with DBCS
    KOC0824  Storage overwritten during error recovery
    KOC0830  Branch to bracket indexed assignment fails
    KOC0838  apl2pi should not set handlers for asynchronous signals
    KOC0839  Stops not honored by QuadEA
    KOC0843  Dyadic grade with DCS on left does not sort correctly
    KOC0858  QuadNLT reference returns garbage after CSD 4
    KOC0864  -input "''" causes initialization error
    KOC0868  QuadCR on locked function in namespace yields System Error
    KOC0877  No DOMAIN ERROR on power overflow
    KOC0879  SYNTAX ERROR, selective spec with redundant parentheses
    KOC0880  Result of catenate to null matrix has wrong prototype
    KOC0881  Wrong type produced by enlist of null
    KOC0885  Incorrect DOMAIN ERROR executing primitive function via apl2pi
    KOC0889  No message after APL error in callback
    KOC0894  Extra spaces in format of nested arrays
    KOC0898  Matrix inverse returns result for singular matrix
    KOC0900  Null result from '' + 'A' has wrong type
    KOC0901  Wrong error with negative left argument to reshape
    KOC0902  Wrong error code from take left arg greater than max rank
    KOC0903  Wrong error from invalid vector specification
    KOC0906  Improve error checking in dyadic format
    KOC0907  Wrong error from pick with numeric left arg
    KOC0919  SAVED ... message not in national language message files
    KOC0926  Wrong message and/or abend after error inside namespace
    KOC0930  SYSTEM ERROR, selective spec of empty with pick
    KOC0932  Demo version accumulates CPU time when doing nothing
    KOC0935  Fraction lost in result of factorial and binomial
    KOC0937  Dyadic Grade result bad after KOB0033
    KOC0947  APL2 crash on Windows 2003 with Service Pack 1
    KOC0948  System Error after Divide by 0 with Axis
    KOC0952  Incorrect answers from edge cases of floor with fuzz
    KOC0953  Type of result from encode/decode should be reduced
    KOC0954  Match mainframe behavior on Tdelta, Sdelta assigment
    KOC0956  QuadTF accepts large left argument
    KOC0964  SIGSEGV on fpreset() after floating point excecption handled
    KOC0965  Some system variables not allowed in vector specification
    KOC0967  VALUE ERROR referencing QuadNLT after localization
    KOC0968  Cannot associate to session quads
    KOC0969  Cannot ref or spec associated QuadSVE
    KOC0975  Abend on )PCOPY 2 GRAPHPAK with QuadPW at 254
    KOC0986  Termination problems after failing to edit namespace object
    KOC0990  )COPY, )PCOPY do not respect most current PW setting
    KOC0991  Prevent )IN and )OUT of session variables
    KOC0994  Column missing from display of floats after KOB2739
    KOC0997  Interpreter crash after call to external function
    KOC1018  Matrix-Add-Downards fails when packaged
    KOC1025  Storage not freed in one )COPY error path
    KOC1030  QuadDL 0 does not always return 0
    KOC1037  Right caret can be lost if error output wraps
    KOC1038  )SYMBOLS xxxxx output contains garbage
    KOC1043  )COPY changes current directory
    KOC1045  SYSTEM ERROR using namespace operands w/user-defined operator
    KOC1046  Slow )COPY when many unknown quad names were used
    KOC1047  System Error when using EXP to reference P12 variable
    KOC1048  )IN of nonexistent file with -lx off corrupts workspace
    KOC1056  Nameclass of some associated system variables reported as 3
    KOC1057  1 QuadAT result 0 0 0 for associated quad names
    KOC1062  QuadES suspends at entry to namespace rather than at call
    KOC1064  No result from each with null arg and namespace function
    KOC1065  Imprecise display of floating point numbers in editors, TF
    KOC1069  4 QuadAT thru EXP of shared variable causes interpreter crash
    KOC1092  Valence error using operator in namespace
    KOC1093  Shared variable value lost in namespace
    KOC1094  Use of function as operand to namespace operator corrupts )OUT
    KOC1097  Disallow association to Quadname without surrogate
    KOC1107  )LOAD fails for ws saved suspended in namespace
    KOC1110  Abend on )COPY of workspace saved suspended in namespace
    KOC1111  )IN crashes interpreter with small wssize
    KOC1118  Using defined function as operand changes function definition
    KOC1122  Leading blanks not tolerated in APLxxxxx envvar values
    KOC1134  Inaccurate rounding in picture format
    KOC1140  No DOMAIN ERROR from exponential of large number
    KOC1180  Incorrect shape, display of null nested arrays
    KOC1203  Reassociating names after )COPY makes names useless
    KOC1270  DOMAIN ERROR from matrix divide
    KOC1279  SYSTEM ERROR on disclose with fill from scalar
    KOC1283  QuadFX does not blow down single byte character strings
    KOC1329  Index replacement of namespace variables uses wrong QuadIO
    KOC1338  SYSTEM ERROR running APL2LM from active ws
    KOC1339  Format converts DBCS to omegas
    KOC1354  SYSTEM ERROR using saved association to LIBS
    KOC1403  QuoteQuad prompt lost when sm is off
    KOC1406  Next output includes 6-blank prompt if no )OFF and -sm piped
    KOC1417  False DOMAIN ERROR running external function from namespace
    KOC1422  Disclose Disclose Each nested array gives SYSTEM ERROR
    KOC1424  Checkws: ALM is not <=AHM allocating large array
    KOC1433  Checkws messages after format of depth 3 null nested array
    KOC1459  Interpreter crashes after )IN from Quad prompt
    KOC1467  Squad can operate in wrong origin after KOC1329
    KOC1502  DOMAIN ERROR from or-reduce on all-zero APV
    KOC1514  Niladic external function called with argument when operand
    KOC1526  Exception, reduce with derived function on external variable
    KOC1527  SYSTEM ERROR, negative replicate on null nested array
    KOC1557  P15 attribute associations fail with namespaces
    KOC1568  )IN SYSTEM ERROR after WS FULL
    KOC1580  SYSTEM ERROR after WS FULL associating to namespace object
    KOC1594  RANK ERROR from squad with axis on scalar
    KOC1596  Interpreter crash on 4 QuadAT of shared variable with no value
    KOC1616  Bad QuadEM on SYNTAX ERROR calling operator in namespace
    KOC1627  Disclose prototype extension incorrect on 3-dimensional result
    KOC1628  Disclose of complex numbers yields garbage in extended items
    KOC1638  Selective spec of bracket index of pick has no effect
    KOC1640  Unicode value corrupted when each results in mixed scalars
    KOC1654  Dyadic QuadES with 0 0 right argument reports error
    KOC1656  Error, trace and )SI output does not respect QuadPW
    KOC1666  All )CHECK TRACE output should use DEBUG output class
    KOC1671  SYSTEM ERROR formatting nested array with large dimension
    KOC1685  External variables cannot be used as indices
    KOC1686  Extra output line produced on stop
    KOC1690  P15 crash associating monitor variable in )loaded ws
    KOC1692  DOMAIN ERROR s/b SYNTAX ERROR with external var in vector spec
    KOC1694  No result from QuadEC with unspecified P15 variable
    KOC1710  AXIS ERROR s/b SYNTAX ERROR when symbol invalid
    KOC1719  SYSTEM ERROR after negative take along last axis
    KOC1731  Refcount too high after divide by zero in left arg of QuadEA
    KOC1733  SYSTEM ERROR indexing literal expression with Boolean scalar
    KOC1742  Cannot interrupt 1-line endlessly recursive function
    KOC1743  CONTINUE not saved due to corrupted wsname
    KOC1748  AP01Serv: Unexpected svps rc=15 reason=307 req=4
    KOC1758  Dyadic Iota slow for APV right argument
    KOC1759  No VALENCE ERROR from reduce with monadic functions
    KOC1761  Array corrupt after selective spec replace with 4-byte chars
    KOC1763  Selective spec pick after overtake changes array
    KOC1764  Selective spec first of empty changes prototype
    KOC1765  Inconsistent errors from selective spec with partition
    KOC1778  Reduce of nested array containing chars returns result
    KOC1790  Trace output that exceeds QuadPW may not wrap
    KOC1793  IN corrupts Unicode data from file written by mainframe
    KOC1810  Wrong items modified, selective spec with enlist and replicate
    KOC1814  Fill/Identity  functions incorrect in Inner Product
    KOC1820  Selective Spec with redundant parentheses has no effect
    KOC1821  SYSTEM ERROR using very large namespace
    KOC1833  Change name used for workspace saved on exceptions
    KOC1845  Workspace corrupt after associating multiple external names
    KOC1854  Class of external objects passed as operands lost
    KOC1855  Domino RANK ERROR s/b LENGTH ERROR
    KOC1858  LENGTH error after each with external function
    KOC1870  If NOT COPIED list exceeds Max QuadPW, interpreter crashes
    KOC1876  Crash after LENGTH ERROR reported through PEACH
    KOC1884  Divide by zero in code run under PEACH can cause crash
    KOC1890  Divide by zero not trapped when called from Java
    KOC1901  Interpreter crash calling LIB external function
    KOC1903  Empty without result may have wrong type
    KOC1911  Call from Java to APL2 to Java causes crash
    KOC1912  Call from APL2 namespace to Java to APL2 causes system error
    KOC1922  External functions cannot signal interrupt
    KOC1937  Wrong prototype from defined function each on null
    KOC1950  Find always returns 0 for complex arguments
    KOC1951  Find wrong answer for rank 2 null left and non-null right
    KOC1954  DOMAIN ERROR from reduction of simple null
    KOC1956  Indexing DOMAIN ERROR s/b INDEX ERROR
    KOC1957  No DOMAIN ERROR with null nested left to QuadEA
    KOC1958  QuadFX error checks inconsistent across systems
    KOC1966  RANK ERROR s/b DOMAIN ERROR for QuadFX of nested matrix
    KOC1967  Negative left arg to QuadSVO s/b DOMAIN ERROR
    KOC1989  Incorrect prototype, fill function with scalar extension
    KOC2010  Crash replacing P12 records with selective pick
    KOC2017  Domino identity returns wrong shape when prototype rank > 2
    KOC2022  QuadTF should not be QuadIO dependent
    KOC2034  )LOAD of large workspace fails second time with expandable ws
    KOC2036  SYSTEM ERROR from find with scalar right argument
    KOC2038  Refcount issues after attempt to edit locked function
    KOC2039  Redundant blank in 2 QuadTF output for scalar nested object
    KOC2040  System Name assignment under 2 QuadTF damages WS
    KOC2042  Default display should not convert characters as if mainframe
    KOC2050  Redundant parentheses in 2 QuadTF nested array representation
    KOC2054  Random incorrect answer from find
    KOC2058  SYSTEM ERROR during )IN of large atf with UCS characters
    KOC2064  Label numbers not refreshed when suspended function edited
    KOC2073  INDEX ERROR using empty result of indexing operation as index
    KOC2077  QUIET option does not suppress display of stacked input
    KOC2079  SYSTEM ERROR on )IN of APL/PC transfer file
    KOC2083  Interpreter crash using TIME when suspended in namespace
    KOC2085  Interpreter crash on QuadTF of function via EXP
    KOC2087  Bad output from 2 QuadTF for null Unicode items in nested arrays
    KOC2088  )CHECK DUMP should save DUMPERR
    KOC2091  SYSTEM ERROR after INDEX ERROR assigning variable in namespace
    KOC2093  Checkws messages after editing function on stack
    KOC2094  SYSTEM ERROR on )RESET n
    KOC2095  Interpreter crash during disclose of very large nested array
    KOC2103  Wrong answer from without, complex left and APV right
    KOC2112  Bad results w/execute in inverse QuadTF assignment expression
    KOC2121  Need DUMPERR on SYSTEM ERROR/CLEAR WS
    KOC2126  Incorrect prototype for overtake along first axis
    KOC2131  Errors or exception after take selective spec on simple null
    KOC2132  No DOMAIN ERROR from invalid dyadic format
    KOC2138  Interpreter crash executing very long string
    KOC2146  Hang in enclose with axis when one dimension is null
    KOC2150  Interpreter crash executing long invalid string via EXP
    KOC2152  No SYNTAX ERROR using invalid character as operand
    KOC2153  Unknown system names removed from function header
    KOC2154  SYSTEM ERROR fixing function with invalid character
    KOC2155  Execute bare branch using EXECUTE_APL crashes interpreter
    KOC2156  SYSTEM ERROR using QuadPrime input via APL2PI
    KOC2159  Hang in member with matrix of character vectors on right
    KOC2163  SYSTEM ERROR from EXP of invalid Unicode character string
    KOC2167  Milliseconds value ignored when setting timestamp
    KOC2168  Invalid numeric tokens split when reporting error
    KOC2171  No DOMAIN ERROR for singular matrix
    KOC2172  Wrong answer from find with numeric null matrix left argument
    KOC2173  Error loop after execute outer product with bad function
    KOC2186  SYSTEM ERROR after freeing token 1 via Calls to APL2
    KOC2189  Timestamp month incorrect in Editor 1 display
    KOC2190  SYSTEM ERROR after bare branch inside namespace
    KOC2200  Error message visible under QuadEA after stacking )RESET with AP 101
    KOC2209  Interpreter or AP 200 abend after SYSTEM LIMIT using PEACHT
    KOC2210  Messages not helpful when exceeding SVP limits
    KOC2212  Catenate/ravel not accepted for transfer file type A
    KOC2214  Improve algorithm for complex equivalence
    KOC2217  Improve algorithm for complex residue
    KOC2231  Interpreter crash after garbage collection during AP 1 call
    KOC2232  Enlist does not check for maximum depth
    KOC2241  Spurious VALUE ERROR executing Quad function from namespace
    KOC2246  Domino incorrect for non-square complex matrix
    KOC2247  Circle on real data may produce small imaginary parts

 Session Manager/Object Editor
    KOB0552  Find/Replace does not flag changed lines
    KOB1383  QuoteQuad output can cause lines to get too long
    KOB1598  Find fails after null character
    KOB1981  No newline before result when tracing
    KOC0006  Find dialog text should be selected initially
    KOC0018  SIGSEGV starting APL2 on fast Windows 2000 machine
    KOC0072  Object editor window pops open when traces are active
    KOC0145  Can't open,query NLS first char name object
    KOC0148  Objects not on task bar do not have min/max buttons
    KOC0152  Balanced quotes and lamps
    KOC0180  Object editor displays long character vector incorrectly
    KOC0204  Session manager and 145 dialogs flicker
    KOC0220  Session Manager shuts down pasting blank lines
    KOC0236  Tab compressed out on Windows 2000
    KOC0282  1.0 registry entries not copied for Demo Version
    KOC0312  APL2 V2 does not preserve smlog size or F keys
    KOC0409  Toolbar drawn wrong after cascade
    KOC0410  Escape and Syntax check do not reset status message
    KOC0440  Object editor titlebar drawn twice after name change
    KOC0454  Last line pasted to end of log is lost at next input
    KOC0468  External leading area not painted when using APLSans font
    KOC0486  Grid deletes row containing cursor
    KOC0495  Object editor does not preserve rank of matrix cells
    KOC0496  Grid loses cell changes on save
    KOC0507  Long lines cause log read to abort
    KOC0577  Format and check does not outdent if blank before colon
    KOC0596  Support mouse wheel
    KOC0639  Session scrolls on double click when inactive
    KOC0645  Object editor title drawn twice on XP
    KOC0732  Background of line numbers wrong color on XP
    KOC0758  Previous token should move to beginning of token
    KOC0776  Make object editor position windows within screen
    KOC0811  Editing matrix with wide column appears empty
    KOC0818  Null replaces last char when pasting with partial line marking
    KOC0826  Editor refuses to open all names beginning with Tdelta
    KOC0837  SM crashes changing type of empty cell to numeric
    KOC0916  Object editor title drawn wrong on XP service pack 2
    KOC0933  Save As should warn if file already exists
    KOC0936  Localize missing from object editor popup menu after CSD 6
    KOC0944  Enter after log open issues )OFF
    KOC0946  Enter in Window List should show selected object
    KOC0971  SIGSEGV on )OFF running from read-only directory
    KOC1004  Support clipboard while editing cell
    KOC1004  Enable wordwrap in character cells
    KOC1005  Grid editor display errors after turning line numbers on/off
    KOC1022  Make Partial Line marking toolbar button have better visual cue
    KOC1023  Changed grid cell wordwrap off responds wrong to Tab and Enter
    KOC1026  Make Alt key move focus to menu bar
    KOC1029  Dialog template editor abends
    KOC1036  Crash after pasting at end of full log
    KOC1060  Edit menu paste of object with Unicode clipboard yields garbage
    KOC1063  Q key missing from keyboard dialog
    KOC1068  SM abend selecting "Localize All" on undefined function line
    KOC1079  Labels colored wrong on modified lines
    KOC1081  Blank between name and QuoteQuad lost in object editor display
    KOC1101  Save size and position of Open Object dialog
    KOC1123  )LOAD on popup menu stacks blank lines
    KOC1132  Grid editor delete columns ignores selected cell position
    KOC1156  Session Manager crashes when editing function header
    KOC1158  Cannot exit from editor 1 after interrupt
    KOC1170  APL characters do not work in SM and AplEdit dialogs in Japan
    KOC1171  Background of lines ending in control chars not drawn
    KOC1175  Disable OS/2 push button styles
    KOC1182  Changing font while editing grid cell causes crash
    KOC1216  Object editor titlebars drawn wrong on Vista
    KOC1229  Paint errors when windows dragged over SM windows
    KOC1247  GetFontUnicodeRanges not available on NT
    KOC1252  apl2key.dll won't load on NT
    KOC1253  Dialog editor grid control data ignored
    KOC1257  Crash changing listview styles in dialog editor
    KOC1264  Session manager help opens with wrong panel
    KOC1268  Make Rename dialog support MAX_PATH characters in filename
    KOC1274  Draw the Find dialog close button differently when hot
    KOC1291  Restore after modify line beyond end of log fails
    KOC1299  Keyboard properties does not display APL characters
    KOC1343  Open Object dialog position not saved after move
    KOC1344  Trailing quotes removed when opening function
    KOC1355  Blank displayed for character 155 using symbol fonts
    KOC1356  Convert ideographic spaces to Latin spaces
    KOC1369  Exception opening Find dialog on Windows 2000
    KOC1380  Configure APL2 toolbar button does not work on demo version
    KOC1382  Cannot use pop-up menu display if  -id specified
    KOC1396  Paste single cell into grid editor can't be saved
    KOC1398  Object editor may open when tracing blank lines
    KOC1416  Labels with delta, delta underscore, or high minus not colored
    KOC1429  Intermittent crash editing function with blank lines
    KOC1430  Deleted characters reappear
    KOC1437  Default color of Quote Quad Output should be black
    KOC1438  Save of suspended function loses breakpoints
    KOC1476  Keyboard Properties draws wrong glyph on changed key
    KOC1479  Can not localize or unlocalize system names
    KOC1488  Abend trying to open name twice when interpreter is busy
    KOC1490  Save Window List size and position
    KOC1528  GUI components do not work on XP x64 SP2
    KOC1529  Object Editor titlebar drawn poorly on Vista when Aero enabled
    KOC1572  Single byte fonts do not work with Russian input language
    KOC1583  Unlocalize in popup menu while editing program with no locals
    KOC1584  Paste strips data from last line
    KOC1589  Open object combo selection erors when not active
    KOC1598  Waiting for interpreter window does not appear
    KOC1604  Minimize shared memory for programs with long lists of locals
    KOC1607  Mouse click does not move caret after drag mark
    KOC1612  Make numeric keypad period produce decimal separator
    KOC1615  APL characters do not work in DISPLAY window titlebars
    KOC1618  Assist bar drawn wrong for short contents
    KOC1675  APL2 windows do not retain size and position on second monitor
    KOC1676  Window list paints incorrectly on HD displays
    KOC1678  Display of output is slower than in CSD 8
    KOC1691  Scrollbar does not update caret position
    KOC1697  Use two colors for incomplete lines
    KOC1701  Keys Help missing Ctrl+Enter
    KOC1702  Document using Escape to close popup windows
    KOC1756  Crash on long user button command
    KOC1772  APL user toolbar buttons are highlighted
    KOC1773  Garbage in expression window for empty array using Symbol font
    KOC1825  Mouse actions ineffective with multiple monitors
    KOC1835  Aplprntf crashes on 32-bit Vista
    KOC1860  Visual cue can move out of window if Open on Stop not checked
    KOC1862  APL characters in status bar wrong if font changes
    KOC1867  Correct ruler storage overrun
    KOC1877  F4 has no effect in dialog editor if dialog has focus
    KOC1878  Localize All should not localize words in comments
    KOC1924  Editor reopens when suspended by attention
    KOC1925  Object editor Close event not posted on F3
    KOC1926  SM calculates character widths even with fixed pitch fonts
    KOC1928  Editor doesn't remove line numbers as wrapped line covers lines
    KOC1930  Pressing Tab does not move focus to all DEMO_APLHELP controls
    KOC1939  Paste in Grid editor causes session manager crash
    KOC1953  Session manager crashes if watch hits Ws Full
    KOC1960  Session manager redraws too often
    KOC1965  Memory device context leak in DEMO_CUSTOM
    KOC1991  Delete Marked toolbar icon ineffective
    KOC2003  Copy, Cut, and Paste do not work in dialog editor
    KOC2004  Size to text makes checkboxes and radio buttons too short
    KOC2011  Debugger should not scroll more than necessary
    KOC2012  Blank watch window when display of array is very wide
    KOC2018  Blank watch window when shared memory size exceeded
    KOC2028  DBCS characters truncated when using APL2 OEM fonts
    KOC2041  Object editor crashes after pressing enter using IBM APL font
    KOC2078  Highlighting fails with APL2 names only
    KOC2098  APL setting change via Mouse does not effect Find dialog
    KOC2102  Format and Check too strict about trailing decimal points
    KOC2108  Use of Grid Editor changes all characters to Unicode
    KOC2115  SM crash executing very long expression from object editor
    KOC2120  Extraneous 0 after E in Grid Editor
    KOC2193  Cannot open new watch windows after "Close watch windows" from menu
    KOC2196  Coloring of highlighted marked text not distinguishable
    KOC2240  Object editor crashes attempting to print empty variable
    KOC2250  Grid editor prints only 2 chars for char cells
    KOC2250  Grid editor "Wrap Columns" option setting ignored
    KOC2257  Color dialog Defaults button ignores reverse video
    KOC2259  Session Manager abend after deleting log
    KOC2261  Characters in APL Image display incorrectly on Windows 10

 Dialog Editor
    KOC0284  Dialog editor clipboard operations do not work
    KOC0821  Dropping time, date, month control changes font
    KOC0866  Setting listview checkboxes style crashes sm on 98
    KOC0899  Dialog editor crashes opening template with events
    KOC1202  Backgrounds drawn incorrectly in dialog editor
    KOC1224  Dialog editor test mode grouped controls do not paint
    KOC1226  Dialog Editor Size-to-Text does not set correct size
    KOC1227  Combobox text in dialog template not preserved
    KOC1394  Accelerators do not work while focus is in status area
    KOC1395  Client and split dialog children do not resize in test mode
    KOC1447  Changes to control with focus lost on save
    KOC1507  Duplicate duplicates more than just the selected controls
    KOC1578  Ctrl+T does not end dialog editor test mode
    KOC1634  Opening template sets fonts for controls
    KOC1750  Dialog editor ignores slider and grid control data

 File Editor
    KOC0747  AplEdit adds null line at end of file
    KOC1243  When AplEdit is run from AP 145 AplExecPgm, Find causes crash
    KOC1331  AplEdit does not accept typed Unicode input
    KOC1391  Save of empty file fails
    KOC1466  SaveAs dialog window contents corrupted
    KOC1539  APL input does not work in non-Unicode mode
    KOC1548  Crash on change all after paste into empty file
    KOC1721  Crash after pageup
    KOC1724  New should remove filename from titlebar
    KOC2113  Extra characters on last line editing UTF-8 file
    KOC2239  AplEdit print dialog line numbers shown in origin 0
    KOC2240  AplEdit crashes attempting to print empty file

 Library Manager
    KOC1114  Focus lost when showing dialog template
    KOC1125  Crash on compare of different definitions
    KOC1127  My APL2 Libraries shortcuts incorrect for paths with blanks
    KOC1131  Window out of range after screen size changes
    KOC1383  APL2LM crashes when browsing for compare program
    KOC1419  APL2LM fails to open namespace with one variable
    KOC1458  Failure comparing Unicode data
    KOC1483  Use negative -id parameter to avoid console messages
    KOC1484  APL2 file association fails in CSD 11
    KOC1563  Setting associations fails on Vista
    KOC1650  Wssize settings ignored
    KOC1831  Font selection not used when entered from sm
    KOC2158  No Print button from SELECT_PRINTER on Windows 7
    KOC2211  Progression vectors in transfer files not reported
    KOC2245  Library Manager will not open GUITOOLS.ans

 Keyboard Handler
    KOB2835  Cannot open keyboard properties if owner closed
    KOC1105  Remove Draw Unicode checkbox from font dialog
    KOC1240  Keyboard handler confused by Japanese conversion mode keys
    KOC1917  1 byte APL characters display incorrectly in Unicode windows

 SVP Monitor
    KOB1420  KILL option in monitor does not clean up
    KOC1229  Paint errors when windows dragged over SVP Monitor
    KOC1425  SVP monitor can report incorrect data size for shared variable

 Shared Variable Processor
    KOB0202  SVP does not post on spec if state does not change
    KOC0394  APL2 APs don't run on fast machines
    KOC0651  SVP does not recover from abend in apserver AP
    KOC0717  getpeername prohibits share through intermediate server
    KOC0833  AP signs on using wrong id with multiple sessions
    KOC0844  Cross-system share fails after KOC0717
    KOC0973  -svptrace with SVP monitor causes initialization problems
    KOC1363  SVP runs out of queue elements.  Message: abp->freequeue == 0
    KOC1393  Intermittent hang on APL2 startup

 AP 119
    KOB2639  Sockets obtained with ACCEPT not tracked
    KOB2639  Increase number of sockets to 256
    KOC1072  Integer form of SELECT does not accept APVs

 AP 124
    KOB2243  AP124 accepts multiple DAT offers
    KOC0346  Handle commands 21 and 22 before command 1
    KOC1861  Input of APL characters does not work

 AP 127/AP 227
    KOC0024  Cannot retrieve timestamp value from Microsoft SQL Server
    KOC0032  New Unicode (Widechar) types not supported by AP 227
    KOC0054  Value list incorrectly processed on re-use of cursor name
    KOC0055  STATE of cursors wrong after COMMIT.
    KOC0067  VALUE ERROR referencing shared variable with LENGTH option
    KOC0068  Duplicate row in result when using certain built-in functions
    KOC0069  Error or Abend fetching very large LONGVARCHAR columns
    KOC0079  Memory leak with matrix value-list
    KOC0326  'CONNECT' '' invalid for AP 227
    KOC0739  AP 127/227 should not build nested arrays of numeric scalars
    KOC0812  Correct handling of extended characters
    KOC0819  Message 149 issued with wrong token
    KOC0827  AP 127 error 148 on DESCRIBE with BOTH
    KOC0941  Double colon in SQL statement rejected by AP 227
    KOC0974  PREPARE not completed after internal describe warning
    KOC1034  CONNECT warning codes not returned
    KOC1130  AP 127 bind files shipped in CSD 8
    KOC1133  AP 227 FETCH abend after PREP/OPEN of non-SELECT
    KOC1386  Exception on AP 227 startup if -odbc option not supplied
    KOC1448  PREPARE error if SQLSetCursorName API not supported
    KOC1503  XMLSIZE has no lower limit.
    KOC1509  SQL TRACE function examples do not work on workstation
    KOC1605  Blank data fetching widechar data types
    KOC1856  Return code 1 0 0 1 144 from SQL function
    KOC2187  ODBCOPEN command hangs

 AP 145
    KOB1504  Correct leading space amount in printing services
    KOB1799  Font property does not work for dialogs
    KOB2230  Tooltips and What's This don't work for statics and groupboxs
    KOC0002  Position property does not work for owned dialogs.
    KOC0155  Dragging splitter mullion should resize children
    KOC0212  Resize AP 207 graphic window in AP 145 control
    KOC0219  Tabs and splitters draw incorrectly
    KOC0313  Position property does not account for horizontal scrollbar
    KOC0342  Grid control does not redraw when cell type changes
    KOC0345  Make grid support changing row sizes after cell size change
    KOC0347  Set MLE DATA property should accept any empty array
    KOC0350  Comboboxes do not return on Enter
    KOC0352  CELL DATA returns original data while editing
    KOC0376  Setting listview font makes setting headings fail
    KOC0382  Groupbox halftone style does not work
    KOC0385  SIZETOTEXT does not wrap with symbol charset fonts
    KOC0392  List views signal select event when SELECTION property set
    KOC0393  Listview select event documented incorrectly
    KOC0412  SET_PROPERTY does not create TOOL TIP
    KOC0413  Context help not shown for group members
    KOC0414  Noninput controls should default to notabstop
    KOC0415  Creating menu after making status area visible does not redraw
    KOC0417  WinMessageBox icon flags have no effect.
    KOC0418  Dialogs with tab controls do not resize
    KOC0424  UNICREATEDLG not same as CREATEDLG
    KOC0429  Setting grid CELL DATA with single vector crashes AP 145
    KOC0432  Correct list of supported static and scrollbar properties
    KOC0437  Selecting column in grid should not select spanned columns
    KOC0438  Split dialog fails if status visible set before children created
    KOC0441  HIGHLIGHTED DAYS property does not work at end of year
    KOC0442  Requesting context help can hang AP 145
    KOC0444  Grid does not redraw when headings set
    KOC0449  Setting Grid cell size twice fails
    KOC0451  CREATECTL does not set focus correctly
    KOC0466  CreateCtl default push buttons do not respond to enter
    KOC0469  Controls should inherit dialog's FONT property
    KOC0477  Fix storage and GDI resource leaks
    KOC0481  Creating control causes other dialogs to blink
    KOC0482  Improve SVP error messages in GUI programs
    KOC0483  Allow replacement and destruction of menus
    KOC0493  SIZETOTEXT does not make text controls tall enough
    KOC0494  GETCHILDREN returns tool tip and status window handles
    KOC0506  Grid control exception on double click
    KOC0509  MLE data property does not accept 4 byte characters
    KOC0527  SIZETOTEXT moves combobox
    KOC0528  Spin buttons have double border
    KOC0530  SIZETOTEXT makes all grid columns the same width
    KOC0534  PRINTWS fails on objects containing 4-byte characters
    KOC0556  Close_Document fails after printing QuadAF 0-31
    KOC0557  Setting status area after setting symbol dialog font fails
    KOC0561  Selecting printer by program is not reflected in dialog
    KOC0569  Tab selects data in dynamic MLE
    KOC0584  Referencing value after specifying DDE value to Excel fails
    KOC0585  SizetoText for combo boxes does not include entry field
    KOC0586  Font property is case sensitive for styles
    KOC0594  Some network printers not listed
    KOC0599  AP 145 issues 2 PAINT events on resize
    KOC0635  Issue Activate event on both activation and deactivation
    KOC0659  Listviews do not signal event on Enter keystroke
    KOC0660  Dynamic Listview does not handle FullRowSel, GridLines styles
    KOC0661  Paint signalled twice when offset used or status area visible
    KOC0682  SET_RANGE CELL DATA does not effect cell being edited
    KOC0695  Misc. inconsistencies between GUITOOLS and GUI book
    KOC0698  State Focus and State Active change zorder
    KOC0725  CreateCtl creates dropdownlist combobox for dropdown style
    KOC0779  Listviews do not redraw in split dialogs
    KOC0781  Pasting data into grid should preserve rank of cell data
    KOC0829  GET_RANGE builds bad CDR for 5 by 3 grid
    KOC0834  Incorrect command 'WINDOW' not handled
    KOC0845  DEMO_LISTVIEW status bar not visible
    KOC0847  Clipboard left open after ref if no text available
    KOC0848  MLE does not report scroll events when dragging thumb
    KOC0859  Reference of Listview STATE CHECKED crashes AP 145
    KOC0860  Enter does not move focus in grid control
    KOC0861  STYLE property for listview always returns CHECKBOXES
    KOC0862  TEMPLATE property returns NOBORDER style MLE
    KOC0869  Dialogs do not paint while AplExecPgm is running
    KOC0872  Checking listview item redraws entire listview
    KOC0873  Use of listview created with CreateWindow crashes AP 145
    KOC0905  Grid control crashes with norowhead or nocolhead
    KOC0934  Grid crashes on delete rows
    KOC0939  Grid Focus Move event signalled on mouse button down
    KOC0960  Grid control does not respond to mouse scroll wheel
    KOC1002  Querying STATUS PARTS property causes AP 145 to crash
    KOC1042  Exception referencing STATE ENABLE property
    KOC1052  Make FILEDLG remember current directory
    KOC1054  Split dialogs show first two visible controls
    KOC1055  Make treeview selection change on right click
    KOC1077  Reduce flicker in split dialogs
    KOC1085  Context help fails with unicode dialogs
    KOC1129  Treeview DATA after Label Changed event returns wrong value
    KOC1138  Static controls with pictures do not redraw when resized
    KOC1144  Picture buttons draw incorrectly with XP themes
    KOC1148  Scrollbars do not signal left and up events
    KOC1149  Correct Unicode/Multibyte data handling in Common Controls
    KOC1152  Listview checkboxes do not display
    KOC1157  Child dialog disappears when you press Alt
    KOC1164  Grids do not handle Multibyte and Unicode data correctly
    KOC1165  TEMPLATE property does not retrieve font styles
    KOC1166  Long grid row headings cause row resize problems
    KOC1167  Listviews and Treeviews do not support SYMBOL_CHARSET fonts
    KOC1169  Timer objects tick too often
    KOC1181  CALLAPI fails when passing doubles by reference
    KOC1184  AplSizeToText fails on Unicode windows
    KOC1191  Register custom window class with CS_OWNDC
    KOC1194  Controls in tabs do not draw properly
    KOC1196  Transparent controls in tabs draw wrong on DATA property set
    KOC1198  Button style tab controls draw background incorrectly
    KOC1199  Resource leak when using icons
    KOC1221  Simple Comboboxes make AP 145 hang on Vista
    KOC1222  Background of radio buttons in tabs drawn wrong on Vista
    KOC1233  Support listview and treeview items with no image
    KOC1245  Radio buttons are drawn wrong if they are taller than 1 line
    KOC1251  Combobox color properties have no effect
    KOC1255  SELECTION property returns bad result for Japanese Unicode edit
    KOC1262  SELECTION property fails for Japanese Unicode
    KOC1263  AP145 abends on missing picture list
    KOC1275  Radio button group doesn't always have exactly 1 button checked
    KOC1289  FileDlg fails if title longer than 12 characters
    KOC1293  Context help does not work for controls in tabs
    KOC1295  Tab key does not move focus to tab control tabs
    KOC1297  Adding menu to dialog created from template draws incorrectly
    KOC1298  Range properties fail when setting one cell
    KOC1301  Tab controls do not respond to context help requests
    KOC1302  WinCreateMenu service broken
    KOC1309  AP 145 hangs on DESTROYDLG if no controls in tab
    KOC1316  Make scrollbars support 32 bit ranges
    KOC1317  Prevent unnecessary Move, Paint, and Size events
    KOC1330  Signal Move, Paint, and Size events when messages received
    KOC1335  Buttons not redrawn when focus moved to tab
    KOC1336  Request for contextual help hangs
    KOC1346  Changing spin button font changes whole dialog
    KOC1348  Reducing and increasing number of grid columns causes crash
    KOC1352  Setting UNICODE FONT property causes crash
    KOC1353  Referencing STATE FOCUS for combobox always returns 0
    KOC1389  Tooltips do not work for spin button controls
    KOC1411  Grid tab key processing moves focus to static cells
    KOC1415  Grid with only static and readonly buttons accepts focus
    KOC1427  Data marked inconsistently when mle opens
    KOC1465  Radio buttons in tab dialogs drawn with wrong font
    KOC1470  GET_PROPERTY with no window handle causes crash
    KOC1473  Floating point id causes AP 145 to crash
    KOC1474  FONTDLG does not work on controls using default font
    KOC1481  Centered text not redrawn as control resized
    KOC1482  Template with FONT presentation parameter drawn wrong
    KOC1494  Setting static PICTURE property with in-core bitmap leaks
    KOC1501  Radio buttons events fire twice on arrow keys
    KOC1512  CREATECTL creates radio buttons too short
    KOC1524  Exception setting grid cell color
    KOC1530  Overlapping controls do not draw and accept focus correctly
    KOC1536  APL2LM different program status bars are drawn wrong
    KOC1554  MB_ICON variables have no effect with UNIMSGBOX.
    KOC1569  Disabled checkboxes draw incorrectly in tabs
    KOC1597  Incorrect default and SIZETOTEXT sizes for spin buttons
    KOC1619  Check boxes drawn incorrectly when disabled
    KOC1622  Check boxes drawn twice when keyboard cues are hidden
    KOC1623  Check boxes do not hide focus rectangle
    KOC1642  Context help does not work for frame/rectangle inside group box
    KOC1704  Inserting a row with the NOROWHEAD style causes an exception
    KOC1708  Referencing cell edges returns cell justification
    KOC1711  Call CREATECTL without class causes crash
    KOC1730  Tab does not work correctly when combobox has focus
    KOC1757  Context help wrong for controls in child of rectangle dialogs
    KOC1796  SET_PROPERTY fails for arbitrary character data
    KOC1800  Graphic events storage is not freed
    KOC1801  Cannot set focus to graphic window
    KOC1802  Cannot set properties for graphics windows
    KOC1803  Correct tab processing for graphic windows
    KOC1823  Spurious radio Button Clicked event during 2nd initialization
    KOC1857  Listview grid lines drawn incorrectly after vertical scroll
    KOC1866  Setting CELL FORMAT range property fails
    KOC1880  Grid does not report Change event when Delete key is pressed
    KOC1889  Suppress Edit-MLE builtin menu if CONTEXT HELP event handler
    KOC1892  Icons stored in the workspace are not transparent
    KOC1929  DEMO_APLHELP More Help button causes suspension
    KOC1933  MSGBOX windows are always topmost
    KOC1940  DEMO_SHEET entry field allows only 1 character
    KOC1941  Remote print objects use wrong minimum margins
    KOC1946  Resizing master grid rows and columns does not effect slaves
    KOC1972  SELECT_PRINTER should not fail when user presses Cancel
    KOC1986  Suppress spinbutton builtin menu if CONTEXT MENU handler set
    KOC1987  Crash on GET_RANGE UNICODE CELL DATA
    KOC2027  Radio buttons do not receive focus event for key presses
    KOC2032  Combobox ignores Escape
    KOC2033  Setting a single cell with SET_RANGE causes AP 145 to crash
    KOC2044  Escape doesn't signal Cancel event when listbox has focus
    KOC2056  SET_PROPERTY result incorrect with multiple properties
    KOC2101  Multiple selection support for AplFileDlg
    KOC2105  Listview check boxes cause spurious event notifications
    KOC2106  Spin buttons ignore specified backgound color
    KOC2107  Cannot set overall background color for grid control
    KOC2130  Spinbuttons do not report hover event
    KOC2134  Escape ineffective from Listview control
    KOC2136  Hang executing AP 145 function inside array editor
    KOC2158  No Print button from SELECT_PRINTER on Windows 7
    KOC2188  Double-click event not reported for Custom controls
    KOC2205  Cannot use DATA property with Date control having UpDown style
    KOC2253  Memory leak after error creating menu

 AP 207
    KOC0014  Copy and SaveAs do not work with floating point world ranges
    KOC0089  AP207 abend after CSD 8
    KOC0223  Cannot open large file
    KOC0436  Dashed line performance bad on NT
    KOC0549  Memory leak in GRDATA command
    KOC0551  WAIT does not return after shift arrow
    KOC0561  Selecting printer by program is not reflected in dialog
    KOC0594  Some network printers not listed
    KOC0632  Fill does not work with series of DRAW commands
    KOC0634  WAIT cursor movement when over Stay on Top window
    KOC0820  Miscellaneous memory leaks
    KOC0910  Remove 16382 points restriction from DRAW and MARKER
    KOC1031  AP 207 crashes after close
    KOC1032  AP 207 does not repaint after maximize or restore
    KOC1049  Marker 8 does not respect MIX
    KOC1086  MENU print to file does not fail with invalid path
    KOC1113  Wrong font style selected
    KOC1187  Window not repainted after close and new open
    KOC1229  Paint errors when windows dragged over 207 window
    KOC1239  Flicker during drag of window over AP 207 window
    KOC1249  Incorrect paint on resize with scissor
    KOC1261  WAIT returns incorrect mouse button number
    KOC1332  CSD 10 AP 207 is slower than the CSD 9 version
    KOC1334  AP 207 does not check product directory for vector fonts
    KOC1461  GDI object leak
    KOC1471  Printer setup causes crash when no default printer
    KOC1528  GUI components do not work on XP x64 SP2
    KOC1609  AP 207 does not support vector fonts when in Unicode mode
    KOC1798  Closing 207 child of 145 child dialog causes exception
    KOC1883  Remove requirement to CLOSE graphic window in AP 145 dialog
    KOC2127  RC 1 from AP 207 'MENU' 'COPY' even on success
    KOB2293  Wrong fonts on repaint after FONTDEF replace font
    KOC2235  Blank title on OPEN with null in title position
    KOC2236  Unnecessary trailing blanks in FONTDEF query output

 AP 210
    KOC0073  Wrong record returned on retry of direct read (command 6)
    KOC0499  AP 210 open returns 1 for filenames with commas
    KOC1738  Cannot handle text file with no LF on last record

 AP 211
    KOC0755  Timestamps not correctly adjusted for time zone
    KOC1010  Negative numbers corrupted converting DOS AP 211 files

 Processor 10
    KOC1737  File functions stop at EOF character on Windows
    KOC1740  DeltaFV should delete trailing blanks on read
    KOC1990  Workspace damaged using DeltaEXEC Function
    KOC2128  DeltaF abend on file with 2039 date

 Processor 11
    KOB1360  P11 passes scalar Char, Short and Float incorrectly
    KOB2709  P11 can return enclosed scalar in result
    KOC0142  Limit on tag text of 511 bytes is too small
    KOC0143  Namescan does not validate tag data length
    KOC0772  P11 does not read names file without trailing LF
    KOC1091  Abend calling C routine using B1 pattern
    KOC1137  Tabs in names files should be ignored
    KOC1413  Processor 11 crashes if no APLP11 defined
    KOC1545  Crash calling external functions from multiple threads

 Processor 12
    KOC0004  WS Full adding zero records to P12 file
    KOC0388  Toleration of scalars during P12 association
    KOC0426  P12 expand does not does not allow for replication
    KOC0617  P12 abend after garbage collection
    KOC0738  P12 should not return nested vectors of scalars
    KOC1084  Wrong prototype generated for 4-byte characters
    KOC1478  SYSTEM LIMIT replacing with longer data on Vista
    KOC1521  Replicate does not extend left when 1 element
    KOC1525  Replicate does not extend right when 1 element
    KOC1674  Problems accessing files >4G in size
    KOC1777  File corrupted replacing data item with different size

 Processor 14/Java Interfaces
    KOC0769  Use of floatValue makes JVM hang or crash
    KOC0770  Use of invalid instance handle makes JVM crash
    KOC0771  Make Apl2exception constructors public
    KOC0790  Apl2object constructor with arbitrary object hits System Error
    KOC0797  Apl2object native array constructor fails
    KOC0802  Redesign code to prevent illegal callbacks
    KOC0804  Apl2object(String[]) yields array of integers
    KOC0809  Errors during callback result in system error
    KOC0840  Intermittent exception under WebSphere
    KOC1464  Floating point control word not protected in calls to Java
    KOC1844  Detect invalid floating point values passed to APL2
    KOC1871  P14 does not issue Rank Error when matrix passed for string
    KOC1896  Preserve APL2's and Java's exception handling environment
    KOC1913  Difficult to tell why P14 association fails if JVM start fails
    KOC1915  Missing blank in Apl2interp.Associate error message
    KOC1916  Java calling APL2 to Java to APL2 can cause crash
    KOC1932  Apl2swt class missing from apl2.jar

 Processor 15
    KOC1766  DOMAIN ERROR, selective spec type change when pattern empty
    KOC1797  Function call in monitor expression causes value display

 Visual Basic Interface
    KOC1024  Handle VB Booleans as Integers
    KOC1155  Nonhomgeneous array parameter containing Booleans causes crash
    KOC1256  Missing switch in data conversion
    KOC1774  APL2-VB hits exception
    KOC2149  Assign API in Calls to APL2 from VB does not work
    KOC2203  Data in VB Currency format incorrectly converted

 Supplied External Routines
    KOC0101  STA builds bad array for nested null object
    KOC0354  STA yields DOMAIN ERROR converting mainframe floating point
    KOC0390  FILE/FSTAT do not blow down 4 byte characters
    KOC0467  Variable length pattern with RTA causes System Error
    KOC0644  OPTION 'CHECKWS' terminates APL2
    KOC0710  VALUE ERROR from EDITOR_2 editing variable
    KOC0793  EDITOR_2 suspension importing from variable
    KOC0874  OPTION handling of 4-byte characters
    KOC0888  Change default Tcl/Tk level to 8.4
    KOC0929  ATR and ATS pad bytes contain random data
    KOC0942  Monadic RTA incorrect result with null APV inside nested
    KOC0988  Use GMT timestamps in ZIPWS function
    KOC1019  COM exception messages are not displayed
    KOC1040  ET codes incorrect when returned from COM function
    KOC1059  IN does not handle filenames with blanks or missing CRLFs
    KOC1066  RTA hits protection exception
    KOC1136  RTA returns garbage if pattern describes more data than given
    KOC1183  CTK issues SYSTEM ERROR when using CP_SYMBOL (42)
    KOC1186  ATR does not handle zero and negative numbers with E4
    KOC1208  Improve IN and PIN detection of invalid files
    KOC1258  Expunging COM crashes interpreter
    KOC1277  Color customization for EDITOR_2
    KOC1300  OPTION fails for names longer than 11 characters
    KOC1340  COM WAIT signals System Error
    KOC1362  ATS could fail after garbage collection
    KOC1408  Help for APL2CFG SVP options are swapped
    KOC1500  COM Storage leak if handlers not removed
    KOC1537  RTA incorrect result with fixed S1 items in pattern
    KOC1543  Prevent mangled names in aplfun.h
    KOC1575  Garbage result flag when no result from APL2PIA
    KOC1601  PEACHT crashes if slave interpreter can not start
    KOC1603  PEACHP incorrect error message for missing function name
    KOC1658  CTK fails when using codepage 50222
    KOC1683  ROUNDC rounds some numbers incorrectly
    KOC1727  RF with large array causes workspace corruption
    KOC1744  Interpreter crash calling OPTION with > 16-element argument
    KOC1794  LENGTH ERROR from CNS using workspace name longer than 8 chars
    KOC1795  DOMAIN ERROR using indexed and named properties in one COM call
    KOC1848  APL2CFG crash: Click APL radio button when no buttons defined
    KOC1875  No error text when PEACHP fails to start APL2 session
    KOC1919  APL2CFG libraries page still grey after "Add Variables"
    KOC1973  PRINTWSG remember window position and font preferences
    KOC1979  PRINTWSG APL samples do not display correctly with Unicode font
    KOC1981  PRINTWSG hang if you select APL2 Image as the body font
    KOC2002  SYSTEM LIMIT in REPLACEX with null in left argument
    KOC2037  DOMAIN ERROR from RTA/SIZEOF with very short pattern
    KOC2051  Referencing Excel Value property via COM consumes storage
    KOC2019  APL2CFG does not save changes on Windows 7
    KOC2089  Tolerate APL high minus in CTN
    KOC2100  RF does not match equivalent Boolean, APV and Integer subitems
    KOC2100  DOMAIN ERROR from RF when both arguments Boolean
    KOC2135  No DOMAIN ERROR from SIZEOF with invalid pattern 'E8 *'
    KOC2145  Incorrect usage of "effect" in online help for Configure APL2
    KOC2183  CTN should try to blow down 4-byte characters
    KOC2184  MD5 should try to blow down 4-byte characters
    KOC2219  COM: No error referencing property value too large for ws
    KOC2251  DOMAIN ERROR from COM referencing property with Unicode data

 Supplied Workspaces
  DDESHARE
    KOC0194  MS2TS and TS2MS are 1 day off
    KOC0614  DDE_TEXT_TO_MATRIX does not handle empty cells correctly
  DEMOJAVA
    KOC0775  Global QuadIO in DEMOJAVA is 0.
    KOC0788  DEMO_JAVA does not give good error message if Java unavailable
  DEMO145
    KOB1923  Make DEMO_SLIDER prettier on Windows
    KOC0227  DEMO_MOVIE does not show movies with names containing blanks
    KOC0459  Make DEMO_EXECUTEDLGX use a single window
    KOC0460  Slow down DEMO_POLLING so it's easier to understand
    KOC0462  Add comments to DEMO_EXECUTEDLGX utility DLGX_PROCESS
    KOC0474  DEMO_207 help issues
    KOC0475  DEMO_DATETIME exits prematurely
    KOC0572  Slider position lost switching between scales
    KOC1128  Incorrect comment in DEMO_SPINBUTTONS
    KOC1162  Demos displaying APL characters fail in Japan
    KOC1219  DEMO_MONTH shows only 2 months on Vista
    KOC1250  Localize GROUP in DEMO_GROUP
    KOC1315  Make DEMO_MOVIE preserve aspect ratio
    KOC2158  No Print button from SELECT_PRINTER on Windows 7
  DEMO207
    KOC1266  DEMO207 horse runs too fast
  FILE
    KOC0751  IN/PIN do not handle external vars with namelist
    KOC0761  IN/PIN do not check return code from QuadNA
    KOC0980  OUT should not put timestamp on external objects
    KOC0981  IN, PIN do not respect transfer file timestamps
    KOC0988  Use GMT timestamps in OUT function
    KOC0993  IN and OUT should not process session quadnames
    KOC1947  IN function cannot find transfer file created by OUT function
    KOC2080  IN fails for functions in APL/PC transfer file
  GRAPHPAK
    KOB0605  Remove undocumented mult variable
    KOB1168  Vector fonts not sizeable in GRAPHPAK TITLE
    KOB2491  USE WIDTH xxx has no effect after OPENGP.
    KOC1345  Failure in PIECHART
  GUITOOLS
    KOB1771  PRINT function adds extra line
    KOC0178  OS/2-only items not marked in HOW_ variables in GUITOOLS
    KOC0202  GUITOOLS EDIT open file fails
    KOC0355  GET_RANGE and SET_RANGE comments wrong
    KOC0366  HOW_PROPERTY missing menu items from STATE ENABLE list
    KOC0455  Improve BITWISE comments
    KOC0456  EXECUTEDLG and EXECUTEDLGX should not hide owner
    KOC0470  CHECK_EVENTS misses events
    KOC0526  UNICREATEDLG error message mentions CREATEDLG
    KOC0568  BITWISE comments incorrect about removing constants
    KOC0655  EDIT and UNIEDIT return wrong rank array
    KOC0657  HOW_RANGE cell type says 1,2,3; should be 0,1,2
    KOC1935  Remove FREEB
    KOC1945  PRINT_PROPERTY doesn't fail referencing invalid property
    KOC1994  UNIdeltaFM creates incorrect output file
    KOC2158  No Print button from SELECT_PRINTER on Windows 7
  GUIVARS
    KOC2158  No Print button from SELECT_PRINTER on Windows 7
  IDIOMS
    KOC2204  SYNTAX ERROR from binary conversion idiom in IDIOMS
  MATHFNS
    KOC2248  Dyadic DOMINO function result has wrong shape
  NETTOOLS
    KOC0208  HTTP_SERVER accept multiple clients on one select
    KOC0502  HTTP_SERVER uses case insensitive MIME type check
    KOC0740  NETTOOLS html link to APL2 site has old address
    KOC1571  Update documentation variables
    KOC2109  Error in NETTOOLS variable CFG_MIME_TYPES
  PRINTWS
    KOC0190  PRINTWS tries to print shared variables
    KOC2225  PRINTWS limits function timestamp year to 2000
  UTILITY
    KOC1390  REPLACEV misses first instance if at beginning of string
    KOC1462  REPLACEV incorrect answer when replacement string is scalar
    KOC1468  INDEX ERROR from REPLACEV
    KOC2124  REPLACEV does not handle scalar right argument
    KOC2133  VALUE ERROR using APSERVER
    KOC2198  Incorrect answer, REPLACEV with length one old string
  WINDOWS
    KOC0522  PIPE can branch to EXIT without SO set
    KOC0719  Windows RENAME does not allow path on new name
    KOC1217  PIPE function fails on Vista
    KOC2082  PIPE will not handle LF-delimited input file
  WSCOMP
    KOC0300  WSCOMP fails if external name will not resolve
    KOC0445  Large variables appear blank in WSCOMP compare dialog
    KOC0816  WSCOMP can say number is different yet display as same
    KOC1458  WSCOMP failure comparing Unicode data
    KOC1893  WSCOMP can not be called from icon because it uses stack
    KOC1944  Suspension comparing names with APL characters
    KOC1961  Crash with large -ws parameter
    KOC1964  No message when files not found
    KOC2096  WSCOMP Transfer File setting for second file ignored
    KOC2097  Timestamp missing in WSCOMP with user compare program

 Fonts
    KOC0439  Unicode version of APL2 Italic missing Lamp
    KOC1058  Courier APL2 Unicode does not appear in SM font dialog

 Installation
    KOB2498  Duplicate APL2 entries in AUTOEXEC.BAT
    KOC0857  Duplicate lines in autoapl2.bat after installing csd
    KOC0917  Messages truncated during environment variable replace
    KOC0918  Reboot not required during install on NT-based systems
    KOC1423  APL2 installers will not run on 64-bit Windows
    KOC1449  Remove dependence on BOOKSHELF environment variable
    KOC1463  Some files not replaced with CSD 11 reinstall
    KOC1564  Installer can not find apl2inst.dll
    KOC2061  Installation fails from non-administrator userid
    KOC2147  All-Users install does not work on Windows 7

 Online Help
    KOC1083  Cannot print "header and all subtopics" in APL2 help files

 Documentation
    KOB0021  )SAVE does not save shared variables
    KOB1149  Document VIEW has no effect on Unix systems
    KOB1958  Document MIX 3 does not work on PostScript printers
    KOB2046  Initial values ignored for cross-system shared variables
    KOB2288  GRAPHPAK PLOT labels cut off when on right
    KOB2339  Fix Windows Dialog Editor online help for Edit menu choices
    KOC0003  Dialog editor test mode documentation hidden on Windows
    KOC0070  Contact info for Unicomp is wrong
    KOC0171  Missing comma from example UPDATE statement
    KOC0175  Default dialog font docs don't mention Japan
    KOC0197  Add Windows XP to documentation
    KOC0238  Document namespace platform differences
    KOC0241  Add APL2 Italic Unicode font to User's Guide
    KOC0258  Document FontDef font replacement can lead to redraw errors
    KOC0265  P12 doc has incorrect statement of mainframe deviation
    KOC0277  Sample AP bat file pipes output preventing multiple instances
    KOC0314  Garbage character in User's Guide Host Workspaces contents entry
    KOC0322  Improve on-line help for -rns
    KOC0453  Bad chars for lamp in AP 144 chapter
    KOC0529  SIZETOTEXT does not support listview, slider, and tab controls
    KOC0605  Errors, Ommisions in cross-system documentation
    KOC0607  Typo in writing external function section of User's Guide
    KOC0681  Menu signals event for menuitem 1 on enter
    KOC0692  Misc. typos in Writing External Routines section
    KOC0716  AP 124 multiple variable policy not documented
    KOC0803  type and rank spelled with wrong case in UG Java section
    KOC0810  DEMOJAVA missing from workspace table
    KOC0886  SO_LINGER value description incorrect
    KOC0914  SQL manual updates for mainframe PK03134
    KOC0931  Parameter errors in APL2 Java Classes Reference
    KOC0958  VB Associate documentation error
    KOC1021  Document that FreeLocator resets QuadET and error msg
    KOC1121  Typos in Websphere documentation
    KOC1135  -svptrace invocation option not recognized under Calls to Apl2
    KOC1192  Update DBCS information in User's Guide
    KOC1231  Update User's Guide TZ information
    KOC1254  Excel Workbook Close method returns -1, not 1
    KOC1327  Add Vista to documentation
    KOC1367  Typo in AP 200 documentation
    KOC1368  Typo in CLASSPATH line of sample APL2.BAT
    KOC1426  Missing \javahtml\resources\inherit.gif
    KOC1435  Document GDI+ in menu and AP 145 return code 5
    KOC1460  Update list of books in SQL manual
    KOC1495  EXTOKEN examples use EXECUTE
    KOC1567  Update demo verson product highlights
    KOC1581  Links not generated for new sections in User's Guide
    KOC1593  Correct P10 documentation references to IBM Object Rexx
    KOC1606  Remove OS/2 listbox SELECTION STYLE property
    KOC1641  Windows Character Support section displays atomic vector incorrectly
    KOC1661  Document custom controls use GetDC rather than BeginPaint
    KOC1747  Typo in PCOPY external function documentation
    KOC1755  Unix example syntax wrong for setting CLASSPATH
    KOC1920  Non-functional links on Supplied Routines page
    KOC1934  Update User's Guide info on establishing the environment
    KOC1948  Improve Java installation instructions
    KOC2020  More incorrect links in APL2 User's Guide
    KOC2053  ROUNDC documentation discrepancy
    KOC2104  Document P10 does not work with 64-bit Rexx
    KOC2114  User's Guide AplEdit limit information out of date
    KOC2122  Document DOAP1EVENTS and GETSIGNALS callback services
    KOC2123  Document how to load APL2 fonts on Windows
    KOC2137  Bad link to FDELETE on Supplied External Routines page
    KOC2139  Deviation list dyadic format limit incorrect
    KOC2142  User's Guide info on system storage allocation incorrect
    KOC2158  No Print button from SELECT_PRINTER on Windows 7
    KOC2164  Runtime external function not-shipped list out of date
    KOC2169  Add Windows 8 information
    KOC2192  APSERVER example does not work on Windows
    KOC2213  Spin Button Up Arrow/Down Arrow events never happen
    KOC2218  WS TOO LARGE message not documented
    KOC2234  Add Windows 10 to documentation
    KOC2242  CLIPBOARD UNICODE DATA property documentation wrong
    KOC2244  Remove Windows Vista from documentation


================================================================================
 Support
================================================================================

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
                USA


================================================================================
 Trademarks
================================================================================

 The following terms are trademarks of the IBM Corporation.  They are
 denoted by an asterisk (*) when they first appear in the text.

     APL2
     DB2
     IBM
     VisualAge
     WebSphere

 The following terms are trademarks of other corporations.  They are
 denoted by a double asterisk (**) when they first appear in the text.

     Java                Sun Microsystems, Inc.
     ActiveX             Microsoft Corporation
     Visual Basic        Microsoft Corporation
     Visual Studio       Microsoft Corporation
     Windows             Microsoft Corporation
     Windows Vista       Microsoft Corporation

