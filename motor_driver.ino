/***************************************************************
   Motor driver definitions
   
   Add a "#elif defined" block to this file to include support
   for a particular motor driver.  Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   *************************************************************/
#define MDDS10  //mia scheda driver motori in CC , versione con interfaccia seriale
#ifdef MDDS10
 /// ///////////////////////////////////////////////////////////////////
/// ///////////////////////////////////////////////////////////////////
/// DRIVER MOTORI 
/// ///////////////////////////////////////////////////////////////////
/// ///////////////////////////////////////////////////////////////////
#include "mydcmotor_serial.h"
static mydcmotor_c mot_L(MOTOR_LEFT);
static mydcmotor_c mot_R(MOTOR_RIGTH);


  /* Wrap the motor driver initialization */
  void initMotorController() {

    mot_L.init();
	mot_R.init();
  }

  /* Wrap the drive motor set speed function */
  void setMotorSpeed(int i, int spd) {
    if (i == LEFT) mot_L.goCmdVel(spd) ;
    else mot_R.goCmdVel(spd) ;
  }

  // A convenience function for setting both motor speeds
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
     mot_L.goCmdVel( leftSpeed);
     mot_R.goCmdVel(rightSpeed);
  }

/*
	//void cbk_cmdVel( const geometry_msgs::Twist& vel) {
	void cbk_cmdVel2( const geometry_msgs::Twist& cmdvel) {

		//callback every time the robot's linear velocity is received
		ros::Time current_time = ros::Time::now();
		robot.cmdVel = cmdvel;


		speed_wish_right =robot.cmdVel.linear.x + (robot.cmdVel.angular.z*par_wheelDistance)/2  ;
		speed_wish_left =robot.cmdVel.linear.x  - (robot.cmdVel.angular.z*par_wheelDistance)/2 ;



		if  (fabs(robot.cmdVel.linear.x)>0|| fabs(robot.cmdVel.angular.z) >0)		// movimento
		{
			if ( (!isBumpForwardOn()) && (!isBumpLeftOn())  && (!isBumpRightOn()) ){ // no bumpers
							
				mot_L.goCmdVel(speed_wish_left) ;	
				mot_R.goCmdVel(speed_wish_right) ;	//  fattore -1 per tenere conto del motore ruotato di 180° rispetto all'altro
				 
				ROS_DEBUG_THROTTLE(1,"\nOK MOVING @Speed FW:%f , Rot:%f, \tLeft Speed %f, Right Speed %f \n",robot.cmdVel.linear.x, robot.cmdVel.angular.z,speed_wish_left,speed_wish_right);
			}else
			{
				if (robot.cmdVel.linear.x < 0)
				{
					mot_L.goCmdVel(speed_wish_left) ;
					mot_R.goCmdVel(speed_wish_right) ;	
					ROS_INFO(" Mi muovo indietro, ma attenzione  ***  BUMPERS ATTIVATI ! ");
					
				}else
				{
					//robot.cmdVel.linear.x = 0; robot.cmdVel.angular.z =0;
					mot_L.stop();	mot_R.stop();


					ROS_INFO("  ***  BUMPERS ATTIVATI ! cmd_vel rifiutato  e mi fermo");
					
				}
				
				
			
			}
		}else
		{
			ROS_DEBUG_THROTTLE(1,"MOT STOP\n");		
			mot_L.stop();	mot_R.stop();		
		}
		

		g_vel_dt = (current_time - g_last_vel_time).toSec();
		g_last_vel_time = current_time;

	}
*/

#endif // 0

 

