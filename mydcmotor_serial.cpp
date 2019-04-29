
/// ///////////////////////////////////////////////////////////////////
/// ///////////////////////////////////////////////////////////////////
///	DC MOTORS CONTROL NODE THROUGH SERIAL 
/// ///////////////////////////////////////////////////////////////////
/// ///////////////////////////////////////////////////////////////////
#include <Arduino.h>
//	#include <cstdlib>
	#include <math.h> /// per fabs()
	#include "parameters.h"
//	#include "MyRobotModelSmall.h"
//	#include <wiringPi.h>

#define SERIAL_MOTORDRIVER Serial1
#define SERIAL_MOTORDRIVER_SPEED 115200 
#include "mydcmotor_serial.h" /// per fabs()



template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

int minInt(const int a, const int b) {
  return !(b<a)?a:b;     // or: return !comp(b,a)?a:b; for version (2)
}

int map(float x, float in_min, float in_max, int out_min, int out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

mydcmotor_c::mydcmotor_c(  int channel) //channel = MOTOR_LEFT or MOTOR_RIGHT
{
	_channel = channel;
	
	//init();
	//stop();
};

void mydcmotor_c::init( )
{
	SERIAL_MOTORDRIVER.begin(SERIAL_MOTORDRIVER_SPEED);


	isMoving=false;
	_targetVelocity = 0.0;
	_blSpeedLimiterOn = true;
	_rpm = 0.0;
	stop();
}

void mydcmotor_c::setLimiter(int OnOff){
	if(OnOff==1){
	_blSpeedLimiterOn = true;
	}
	else{
	_blSpeedLimiterOn = false;
	}
}
/// ---------------------------------------------------------
/// invia la richiesta di velocità tra 0 e 63 alla seriale
/// ---------------------------------------------------------
void mydcmotor_c::_motorSetSpeed(int speed){
	
	 // 0 =reverse 1000000= 64=forward
	uint8_t speedcmd;
	uint8_t dir = 0; 
	uint8_t cmd = 0;
	if (speed  == 0)//stop
	{
	
		speedcmd = 0;
		cmd = _channel + dir + speedcmd;
		//printf("\n\t\t[Driver stop (ch: %d) ]\n", _channel);

	}else  
	{
		//speed limiter 0-63
		speedcmd = min(abs(speed),63); 
		//speedcmd = 30; //solo per test
	
		if (speed > 0 ) { //forward
		
			cmd = _channel + FORWARD + speedcmd;
		
		}else //reverse
		{
			cmd = _channel + REVERSE + speedcmd;
			
		}
		
		//printf("\n\t\t[Driver cmd %d: Speed %d ]\n",cmd, speedcmd);
	}
	SERIAL_MOTORDRIVER.print( cmd) ;

}

/////////////////////////////////////////////////////
///  COMANDO CHIAMATO DALL'ESTERNO
///////////////////////////////////////////////////
// targetVelocity è la velocità tangenziale (e non di rotazione) di ogni ruota rispetto al suolo
void mydcmotor_c::goCmdVel(float targetVelocity) 
{
	const float maxSpeedLinear = 1.0; //m/s
	if (_blSpeedLimiterOn)
	{
		_targetVelocity = _cmdVelLimit(targetVelocity);
		
	}else
	{
		_targetVelocity = targetVelocity;
		
	}
	if (fabs(_targetVelocity) !=  0)
	{
		
		/// converto da velocità lineare in rpm
		isMoving = true;	/// segnala che si sta muovendo
		// v = [omega_rad/s] * ROBOT_WHEEL_DIAMETER/2
		//_rpm= _targetVelocity/MAX ;	///ROBOT_M2STEPS 3536.7765	
		
	//	int speed_0_63 =(int8_t)( (_targetVelocity/maxSpeedLinear)*63.0 ); 
		int speed_0_63 =(int8_t)map(_targetVelocity,-1.0,1,-63,63);
		
		_motorSetSpeed(speed_0_63); 
	}
	else///stop generazione clock
	{
		_en = 0;
		isMoving = false;	// segnala che si sta muovendo
		//_commandDir = DIR_S;
		_targetVelocity=0.0;
		_motorSetSpeed(0); 
		
	}
	

}

/// Ferma i motori disabilitando gli avvolgimenti
void mydcmotor_c::stop() {
	// disabilito l'alimentazione degli avvolgimenti
	_motorSetSpeed(0);
}

/// abilita i motori 
void mydcmotor_c::_enable() {
//	digitalWrite(_Pin_MotEN, ROBOT_MOTORENABLE_ACTIVE);
	_blEnabled = true;
}




////////////////////////////////////////////////////////
/// limitatore di velocità
////////////////////////////////////////////////////////

float mydcmotor_c::_cmdVelLimit( float cmdVel){

	if (fabs(cmdVel) != 0){
		if (fabs(cmdVel) <  (float)MOTOR_MINIMUM_ANGULAR_VELOCITY ){
				cmdVel = sgn(cmdVel)*MOTOR_MINIMUM_ANGULAR_VELOCITY;
				printf("WARNING: MINIMUM SPEED SET TO %f", cmdVel);	
				
		}
		else if ( fabs(cmdVel ) >  (float)1 ){
				cmdVel = sgn(cmdVel)*MOTOR_MAXIMUM_ANGULAR_VELOCITY;
				printf("WARNING: SPEED LIMITED TO:  %f",cmdVel);				
				
		}						
	}
	return cmdVel;		
}




