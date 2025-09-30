/*-m-aplsvi----------------------------------------------------------
 *
 * Module Name: aplsvi.h
 *
 * Descriptive Name: Shared Variable Interpreter
 *
 * Copyright:   5724-B74 Workstation APL2 Version 2.0
 *              Licensed Materials - Property of IBM
 *              © Copyright IBM Corporation 1994, 2009
 *              All Rights Reserved.
 *              US Government Users Restricted Rights - Use,
 *              duplication or disclosure restricted by GSA ADP
 *              Schedule Contract with IBM Corp.
 *
 * Function:    Define constants used in communicating with an APL
 *              session, when the using partner is acting as a
 *              session manager.  The constants defined here are
 *              used in data fields within CDRs for variables shared
 *              with the interpreter itself.
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

/**********************************************************************/
/*                                                                    */
/*                     Interpreter output                             */
/*                                                                    */
/* Using the shared variable interface, the interpreter sends         */
/* messages and arrays through the APL2 variable as 3 item arrays.    */
/* The first item is an integer scalar return code.                   */
/*                                                                    */
/* If the return code is positive, then it and the rest of the array  */
/* is defined as QuadEC output.  The only case currently implemented  */
/* is a return code of 1. The second item will be a two element       */
/* integer QuadET code (currently always 0 0), and the third item     */
/* will contain the output data.  This may be formatted as character  */
/* vectors or may be arbitrary APL arrays, depending on the output    */
/* setting.                                                           */
/*                                                                    */
/* If the return code is -1, the rest of the array defines either a   */
/* special class of output, or is an input request.  The second item  */
/* is a 2 element integer vector.  Its first element indicates what   */
/* type of output is being sent, or what type of prompt is            */
/* requested.  The second element of the second item is 0 if this     */
/* output completes a line, or 1 if it is an input prompt or more     */
/* data may follow for the same line.  The third item contains any    */
/* output data.                                                       */
/*                                                                    */
/* If the return code is -2, the second item is 0 0 and the third     */
/* item is a 5-element vector, containing the current values of       */
/* QuadPW, QuadPP, PBS, QuadPR, and QuadFC.  The first three are      */
/* integer scalars (PBS is always 0), and the last two are character  */
/* vectors.  These are sent at the beginning of the APL session and   */
/* whenever any of them is modified.                                  */
/*                                                                    */
/* If the return code is -3, the second item is 0 0 and the third     */
/* item is a character vector containing a line from the AP 101       */
/* stack.  This line is sent immediately before requesting input,     */
/* and should normally be returned in response to the following       */
/* input prompt.                                                      */
/*                                                                    */
/**********************************************************************/

/*
 *  Return code values
 */
#define APLRC_NORMAL              1
#define APLRC_MESSAGE            -1
#define APLRC_QUADS              -2
#define APLRC_STACK              -3

/*
 * Message types (when return code == APLRC_MESSAGE)
 */
#define APLMTYP_SYSTEM_MESSAGE    0
#define APLMTYP_APL_PROMPT        1
#define APLMTYP_QUAD_PROMPT       2
#define APLMTYP_FUNCTION_PROMPT   3
#define APLMTYP_FUNCTION_LINE     4
#define APLMTYP_FUNCTION_STAMP    5
#define APLMTYP_NORMAL_OUTPUT     6
#define APLMTYP_FUNCTION_NAME     7
#define APLMTYP_ERROR_MESSAGE     8
#define APLMTYP_SYSTEM_COMMAND    9
#define APLMTYP_TRACED_RESULT    10
#define APLMTYP_QUAD_OUTPUT      11
#define APLMTYP_QQUAD_OUTPUT     12
#define APLMTYP_DEBUG_OUTPUT     13
#define APLMTYP_QQUAD_PROMPT     14

/*
 * Quad variable item indices (when return code == APLRC_QUADS)
 */
#define APLITEM_QUAD_PW           0
#define APLITEM_QUAD_PP           1
#define APLITEM_QUAD_PR           3
#define APLITEM_QUAD_FC           4

/**********************************************************************/
/*                                                                    */
/*                     Requests to the interpreter                    */
/*                                                                    */
/* The following requests may be sent either through the session      */
/* APL2 variable or some other variable shared with the APL2          */
/* interpreter.  Each request is sent as a vector containing two or   */
/* more items.  The first item is always an integer identifying the   */
/* request class, and the second an integer identifying a request     */
/* type within the class.                                             */
/*                                                                    */
/* Classes 0 and 1 are signal codes.  There is no explicit response   */
/* to them.                                                           */
/*                                                                    */
/* Class 0 controls execution, and includes things like               */
/* attention signals.                                                 */
/*                                                                    */
/* Class 1 controls session output.                                   */
/*                                                                    */
/**********************************************************************/

/*
 * Execution Control Signal Codes
 *
 * 0 0    Do nothing.
 *
 * 0 1    Send a weak attention signal (stop at end of line).
 *
 * 0 2    Send a strong interrupt signal (stop as soon as possible).
 *
 * 0 3    Suppress output until the next input request.
 *
 * 0 4    Shut down the APL2 session.
 *
 * 0 5    Shut down the APL2 session, but try to save a CONTINUE ws in the process.
 */

#define APLRQ_EXEC                0

#define APLRQ_EXEC_NOOP           0
#define APLRQ_EXEC_ATTENTION      1
#define APLRQ_EXEC_INTERRUPT      2
#define APLRQ_EXEC_SUPPRESS       3
#define APLRQ_EXEC_SHUTDOWN       4
#define APLRQ_EXEC_CONTINUE       5

/*
 * Output Control Signal Codes
 *
 * 1 0    Send future array output as unformatted arrays, i.e.  as if
 *        the result of the APL statement were assigned to the 3rd item
 *        of the shared variable.
 *
 * 1 1    Send array output formatted, one line at a time, as if
 *        displaying it on a line-oriented output device.
 *
 * 1 2 n  Send array output formatted, but multiple lines at a time, as
 *        a vector of character vectors.  From 1 to n are sent at a time.
 */

#define APLRQ_OUT                 1

#define APLRQ_OUT_ARRAY           0
#define APLRQ_OUT_LINE            1
#define APLRQ_OUT_MULTILINE       2
