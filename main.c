#pragma config(Sensor, S1,     HTGYRO,              sensorAnalogInactive)
#pragma config(Sensor, S2,     sonarSensor,         sensorSONAR)

#include "constants.h"
#include "component_test.c"

/*
 * Debug Modes
 *		0 - off
 *		1 - test ultrasonic sensor
 *		2 - test HiTechnic Gyro Sensor
 *		3	- test motor
 */
const int DEBUG = 0;

task main()
{

			/*
			 * These functions will perform tests on brick peripherals
			 * considered for the design
			 */
    	if(DEBUG == 1)
    	{
    		test_ultrasonic_sensor();
      }
      else if(DEBUG == 2)
      {
        test_gyro_sensor();
      }
      else if(DEBUG == 3)
      {
        test_motor();
      }

       /*
        * Set tachometer to 0
        */
       nMotorEncoder[motorA] = 0;
       float current_position = 0;
       float error = 0;
       float last_error = 0;
       float integral = 0;
       float derivative = 0;
       float motor_power = 0;

       current_position = nMotorEncoder[motorA];
       last_error = p_f - current_position;

       while(true)
       {
           current_position = nMotorEncoder[motorA];

           error = p_f - current_position;

           integral = integral + error;
           derivative =  last_error - error;
           motor_power = (kp * error) + (kd * derivative) + (ki * integral);

           /*
            * Limit motor power at 100 and do not let it move in reverse;
            * Gravity will do the work
            */
           if(motor_power > 100)
           {
             motor_power = 100;
           }
           else if(motor_power < 0)
           {
             motor_power = 0;
           }

           motor[motorA] = motor_power;

           /*
     			  * Ensure motors will float when nothing is applied
     				*/
           bFloatDuringInactiveMotorPWM = true;

           last_error = error;

       }


}
