#ifndef __MYSTEPPER2_H__
#define __MYSTEPPER2_H__

	/// ///////////////////////////////////////////////////////////////////
	/// ///////////////////////////////////////////////////////////////////
	///	STEPPER MOTORS
	/// ///////////////////////////////////////////////////////////////////
	/// ///////////////////////////////////////////////////////////////////


//	#include <cstdlib>
	#include <math.h> /// per fabs()
	#include "parameters.h"
//	#include "MyRobotModelSmall.h"
//	#include <wiringPi.h>
//	#include <wiringSerial.h>
	
//	#include "hw_config2.hpp"
	/// struttura della classe motore
	typedef unsigned long motCk_t; // was typedef uint32_t motCk; 

	//CHANNEL ON BIT 7
	#define MOTOR_LEFT  0
	#define MOTOR_RIGTH 128  /*1000 0000*/

	//DIRECTION ON BIT 6
	#define FORWARD 64  /*0100 0000*/
	#define REVERSE  0	


	/// classe motore
	class mydcmotor_c
	{
		public:
			mydcmotor_c(int channel);
			void 		init();
			void 		goCmdVel(float targetVelocity);		// Chiamare questo comando	
			void 		setLimiter(int OnOff);  // non bool perchè il parametro caricato è int
			void 		stop();
			bool    	isMoving;

		private:
			int			_fd; 		//puntatore alla seriale
			int  		_channel;	// memorizza MOTOR_LEFT o MOTOR_RIGTH
			void 		_motorSetSpeed(int speed);
			
			//robotDir_e 	_commandDir;
			bool		_en;		//enable
			bool		_cw;		// direzione 1 = CW
			float 		_targetVelocity;		// velocità finale in m/s
			double 		_targetVelocityLastTime; // millis() dell'ultimo comando

 			bool 		_blEnabled;
			bool 		_blSpeedLimiterOn ;


			float 		_rpm;

			
			void 		_motorSetPWMCK(float herz);	
			//void 		_setMotorDir(robotDir_e dir);
			void 		_enable();
			float 		_cmdVelLimit( float cmdvel);
	};


#endif
