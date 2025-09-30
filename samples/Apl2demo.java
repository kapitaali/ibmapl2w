import com.ibm.apl2.*;

/* Copyright:   5724-B74 Workstation APL2 Version 2.0            */
/*              Licensed Materials - Property of IBM             */
/*              © Copyright IBM Corporation 2003, 2010           */
/*              All Rights Reserved.                             */
/*              US Government Users Restricted Rights - Use,     */
/*              duplication or disclosure restricted by GSA ADP  */
/*              Schedule Contract with IBM Corp.                 */

public class Apl2demo implements Runnable
{
   //******************************************************************
   //*
   //* Sample static field
   //*
   static public int StaticField = 0 ;

   //******************************************************************
   //*
   //* Sample static method
   //*
   static public int StaticMethod(int Argument) {
      return StaticField + Argument ;
      }

   //******************************************************************
   //*
   //* Sample instance field
   //*
   public int InstanceField = 0 ;

   //******************************************************************
   //*
   //* Sample constructor
   //*
   public Apl2demo() {
      this.InstanceField = 0 ;
   }

   //******************************************************************
   //*
   //* Sample instance method
   //*
   public int InstanceMethod(int Argument) {
      return this.InstanceField + Argument ;
   }

   //******************************************************************
   //*
   //* A main method that creates a slave interpreter
   //*
   //* Call this method from a command line like this:
   //*
   //*    java Apl2demo
   //*
   public static void main(String[] args) {
      try {
         //* Create a slave interpreter
         Apl2interp Slave = new Apl2interp(new String[] {"-ws","1m"}) ;

         //* Reference QuadTS
         Apl2object Time = Slave.Execute(Apl2interp.QTS) ;

         //* Convert it to a Java integer array
         int[] TimeArray = Time.intarrayValue() ;

         //* Print the time
         System.out.println("The time is " + TimeArray[3] + ':' + TimeArray[4] + '.') ;

         //* Get an Apl2cdr object from the Time Apl2object
         Apl2cdr Cdr = Time.cdrValue() ;

         //* Free the workspace object that resulted from the reference
         Time.Free();

         //* Get the byte array representation of the CDR
         byte[] byteArray = Cdr.bytearrayValue() ;

         //* Use the CDR to create a new object
         Apl2object Copy = new Apl2object(Slave,Cdr) ;

         //* Free the copy
         Copy.Free();

         //* Stop the interpreter
         Slave.Stop();
      }
      catch (Apl2exception Exception) {
         System.out.println("Apl2exception caught.");
         System.out.println("Exception message: " + Exception.getMessage());
         System.out.println("Exception cause: " + Exception.getCause());
         System.out.println("Event: " + Exception.Type + " " + Exception.Code) ;
      }
      return ;
   }

   //******************************************************************
   //*
   //* A sample static method that calls back to APL2 several ways
   //*
   static int CallBack(Apl2interp Apl2,String Expression) throws Apl2exception {

      System.out.println("The CallBack method is starting.") ;
      System.out.println("Parameter expression: " + Expression) ;
      System.out.println(" ") ;

      //* Print the Apl2interp object for the APL2 session which called Java.
      System.out.println("The handle of the APL2 interpreter which called Java.") ;
      System.out.println("Apl2interp instance: " + Apl2) ;
      System.out.println(" ") ;

      //* Create a workspace object containing a character vector
      Apl2object aplExpression = new Apl2object(Apl2,Expression) ;
      System.out.println("Create a new Apl2object containing the parameter expression.") ;
      System.out.println("Expression Apl2object: " + aplExpression) ;
      System.out.println(" ") ;

      //* And demonstrate copying it back to Java by getting its string value
      String Copy = aplExpression.stringValue() ;
      System.out.println("Extract the string value of the Apl2object.") ;
      System.out.println("aplExpression.stringValue(): " + Copy) ;
      System.out.println(" ") ;

      //* Print out the Apl2interp object used to create the object
      System.out.println("Print out the Apl2interp object used to create the object.") ;
      System.out.println("aplExpression.Apl2interp(): " + aplExpression.GetApl2interp()) ;
      System.out.println(" ") ;

      //* Create a new workspace object and assign the name Message to it.
      System.out.println("Create a new workspace object and assign the name Message to it.") ;
      System.out.println(" ") ;
      Apl2object MsgFromCallBack = new Apl2object(Apl2,"Hello from the CallBack method") ;
      Apl2.Assign("Message",MsgFromCallBack) ;
      MsgFromCallBack.Free() ;

      //* Execute the parameter expression
      System.out.println("Execute the parameter expression") ;
      System.out.println(" ") ;
      Apl2object aplSum = Apl2.Execute(aplExpression) ;

      //* Free the APL2 object
      aplExpression.Free();

      //* Query the result's type
      String Type = "" ;
      switch(aplSum.type())
         {
         case Apl2object.CDWRTB: Type = "Boolean" ;                    break ;
         case Apl2object.CDWRTI: Type = "Integer" ;                    break ;
         case Apl2object.CDWRTR: Type = "Real" ;                       break ;
         case Apl2object.CDWRTJ: Type = "Complex" ;                    break ;
         case Apl2object.CDWRTC: Type = "Character" ;                  break ;
         case Apl2object.CDWRTD: Type = "Character long" ;             break ;
         case Apl2object.CDWRTA: Type = "Integer progression vector" ; break ;
         case Apl2object.CDWRTG: Type = "General array" ;              break ;
         }
      System.out.println("Query the type of the result.") ;
      System.out.println("aplSum.type(): " + Type) ;
      System.out.println(" ") ;

      //* Extract its integer value
      if(aplSum.type() == Apl2object.CDWRTI)
         {
         int Number = aplSum.intValue() ;
         System.out.println("Extract the integer value of the result.") ;
         System.out.println("Integer value: " + Number) ;
         System.out.println(" ") ;
         }
      aplSum.Free();

      //* Create some workspace objects from primitive Java types
      Apl2object aboolean = new Apl2object(Apl2,true) ;
      Apl2object achar    = new Apl2object(Apl2,'a') ;
      Apl2object abyte    = new Apl2object(Apl2,137) ;
      Apl2object aint     = new Apl2object(Apl2,43456) ;
      Apl2object ashort   = new Apl2object(Apl2,789) ;
      Apl2object along    = new Apl2object(Apl2,444) ;
      Apl2object aarray   = new Apl2object(Apl2,new int[] {1,2,3,4,5,6,7,8,1,2,3,4}) ;
      Apl2object astring  = new Apl2object(Apl2,"This is a string") ;

      //* And free them
      aboolean.Free();
      achar.Free();
      abyte.Free();
      aint.Free();
      ashort.Free();
      along.Free();
      aarray.Free();
      astring.Free();

      //* Declare an integer array and convert it to a workspace object
      int[] IntArray =  {3,4,5,6,7} ;
      Apl2object aplVector = new Apl2object(Apl2,IntArray) ;

      //* Convert it back to a Java array
      int[] intVector = aplVector.intarrayValue() ;
      aplVector.Free();

      //* Associate a name with HOST and use it to query the platform
      System.out.println("Associate a name with HOST and use it to query the platform.") ;
      try {
         Apl2.Associate(3,11,"HOST") ;
         Apl2object CharNull = new Apl2object(Apl2,"") ;
         Apl2object Platform = Apl2.Execute("HOST",CharNull) ;
         CharNull.Free() ;
         System.out.println("Platform: " + Platform.stringValue()) ;
         Platform.Free() ;
      }
      catch (Apl2exception Exception) {
         System.out.println("Apl2exception caught.");
         System.out.println("Exception message: " + Exception.getMessage());
         System.out.println("Exception cause: " + Exception.getCause());
         System.out.println("Event: " + Exception.Type + " " + Exception.Code) ;
      }
      System.out.println(" ") ;

      System.out.println("The CallBack method is ending.") ;
      System.out.println(" ") ;
      return 0 ;
   }

   //******************************************************************
   //*
   //* A sample static method that creates a slave APL2 interpreter
   //*
   public static void SlaveAPL2(Apl2interp Apl2,int Count) throws Apl2exception {

      System.out.println("The SlaveAPL2 method is starting.") ;
      System.out.println(" ") ;

      //* Create a slave interpreter
      Apl2interp Slave = new Apl2interp();
      System.out.println("Start a slave APL2 interpreter.") ;
      System.out.println("Slave Apl2interp instance: " + Slave) ;
      System.out.println(" ") ;

      //* Reference QuadAI
      Apl2object Ai = Slave.Execute(Apl2interp.QAI) ;

      //* Convert it to a Java integer array
      int[] AiArray = Ai.intarrayValue() ;
      Ai.Free() ;

      System.out.println("Reference QuadAI in the slave session.") ;
      System.out.println("Slave account number: " + AiArray[0]) ;
      System.out.println(" ") ;

      //* Check if an interrupt is pending in the interpreter that called SlaveAPL2.
      if(Apl2.IsInterruptPending())
         System.out.println("User has signalled an interrupt.") ;

      Slave.Stop();

      System.out.println("The SlaveAPL2 method is ending.") ;
      System.out.println(" ") ;
      return ;
      }

   //******************************************************************
   //*
   //* Code used by DEMO_THREAD to demonstrate running a slave APL2 interpreter in a thread
   //*

   /* Instance variable containing of Thread class's constructor */
   public Thread StartedThread ;

   /* Instance method run when the thread's start method is called */
   public synchronized void run() {
      Thread CurrentThread = Thread.currentThread();
      try {
         /* Create a slave interpreter */
         Apl2interp Slave   = new Apl2interp(new String[] {"-ws","100k"}) ;
         /* Create some objects in the slave interpreter's workspace */
         Apl2object Beep    = new Apl2object(Slave,"BEEP") ;
         Apl2object FreqDur = new Apl2object(Slave,new int[] {440,250}) ;
         /* Associate a name with the BEEP external function */
         Slave.Associate(3,11,Beep) ;
         /* As long as the current thread equals the started thread, BEEP every so often */
         while(StartedThread == CurrentThread) {
            Apl2object Result = Slave.Execute(Beep,FreqDur) ;
            if(Result != null) Result.Free() ;
            System.out.println("Beep!") ;
            this.wait(500) ;
            }
         /* Free the objects we created */
         Beep.Free() ;
         FreqDur.Free() ;
         /* Stop the slave interpreter */
         Slave.Stop();
         }
      catch (Apl2exception Exception) {
         System.out.println("Apl2exception caught.");
         System.out.println("Exception message: " + Exception.getMessage());
         System.out.println("Exception cause: " + Exception.getCause());
         System.out.println("Event: " + Exception.Type + " " + Exception.Code) ;
         }
      catch (InterruptedException Exception) {
         System.out.println("InterruptedException caught.");
         }
      return ;
      }
}
