/* *************************************************************
   Encoder definitions
   
   Add an "#ifdef" block to this file to include support for
   a particular encoder board or library. Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   ************************************************************ */
   
///////////////////////////////////////////////////////////////////////
///	Encoder
///////////////////////////////////////////////////////////////////////

#include <Encoder.h>
Encoder encL(2, 4);
Encoder encR(3, 5);

  /* The Robogaia Mega Encoder shield */
 // #include "MegaEncoderCounter.h"


  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return encL.read();
    else return encR.read();
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT) 
		encL.write(0);	
    else 
		encR.write(0);
  }

	void resetEncoders(){
		encL.write(0);	
		encR.write(0);		
	};




