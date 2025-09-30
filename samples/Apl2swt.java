import com.ibm.apl2.*;
import org.eclipse.swt.events.*;

/* Copyright:   5724-B74 Workstation APL2 Version 2.0            */
/*              Licensed Materials - Property of IBM             */
/*              © Copyright IBM Corporation 2007                 */
/*              All Rights Reserved.                             */
/*              US Government Users Restricted Rights - Use,     */
/*              duplication or disclosure restricted by GSA ADP  */
/*              Schedule Contract with IBM Corp.                 */

/**
 * Demonstrate calling APL2 from Java event listeners
 * <p>
 * Used by DEMOJAVA workspace's DEMO_SWT function.
 * <p>
 * Apl2swt implements ModifyListener so it can listen for text widget events.
 * Apl2swt implements SelectionListener so it can listen for button widget events.
 */

public class Apl2swt implements ModifyListener, SelectionListener
{

/**
 * Construct an object from an APL2 interpreter and a function name
 *
 * @param Interp - an APL2 interpreter the listener should call
 * @param Function - name of function the listener should call
 */
   public Apl2swt(Apl2interp Interp,String Function) {
      this.SwtInterp   = Interp ;
      this.SwtFunction = Function ;
   }

/**
 * Sent when the text is modified
 */
   public void modifyText(org.eclipse.swt.events.ModifyEvent Event) {
      this.Callback(Event) ;
      return ;
   }

/**
 * Sent when default selection occurs in the button
 */
   public void widgetDefaultSelected(org.eclipse.swt.events.SelectionEvent Event) {
      widgetSelected(Event) ;
      return ;
   }

/**
 * Sent when selection occurs in the button
 */
   public void widgetSelected(org.eclipse.swt.events.SelectionEvent Event) {
      this.Callback(Event) ;
      return ;
   }

/**
 * Swtinterp - an APL2 interpreter the listener should call
 */
   private Apl2interp SwtInterp ;

/**
 * Function - name of function the listener should call
 */
   private String     SwtFunction ;

/**
 * Call the APL2 function ans pass the event object
 *
 * @param Event - Event object sent by widget
 */
   private void Callback(org.eclipse.swt.events.TypedEvent Event) {
      try {
         //* Create an APL2 object containing a global reference to the event
         //* so it can be passed to APL2
         Apl2object Token = new Apl2object(this.SwtInterp,Event,true) ;

         //* Call an APL2 function and pass the object
         this.SwtInterp.Execute(this.SwtFunction,Token) ;

         //* Free the object
         Token.Free() ;
      }
      catch (Apl2exception Exception) {
         System.out.println("Apl2swt Callback method caught Apl2exception.");
         System.out.println("Exception message: " + Exception.getMessage());
         System.out.println("Exception cause: " + Exception.getCause());
         System.out.println("Event: " + Exception.Type + " " + Exception.Code) ;
      }
      return ;
   }
}
