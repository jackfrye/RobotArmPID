#pragma config(Sensor, S1,     HTGYRO,              sensorAnalogInactive)
#pragma config(Sensor, S2,     sonarSensor,         sensorSONAR)


#include "constants.h"
#include "rdpartyrobotcdr/drivers/hitechnic-gyro.h"
#include "component_test.c"

/*
 * Debug Modes
 *		0 - off
 *		1 - test ultrasonic sensor
 *		2 - test HiTechnic Gyro Sensor
 *		3	- test motor
 */
const int DEBUG = 0;



float init_gyro()
{
    float gyro_offset = HTGYROstartCal(HTGYRO);
    wait1Msec(100);

    return gyro_offset;
}


task main()
{

    /*
     * Constants
     *    angle_t 				- current angle
     *		angle_offset 		- angle originally read during calibration
     *		gyro_offset			- offset calculated at calibration
     *		sonar_distance	- distance sensed by sonar
     */
    float angle_t;
    float angle_offset;
    float gyro_offset;
    float sonar_distance;

    /*
     * Ensure motors will float when nothing is applied
     */
    bFloatDuringInactiveMotorPWM = true;


    /*
     * Initialize the HiTechnic Gyro Sensor
     *		initializes gyro_offset
     */
    gyro_offset = init_gyro();

    /*
     * Read angle_offset
     */
    angle_offset = HTGYROreadCal(HTGYRO);


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
       * TODO: implement PID logic
       */

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
           if(motor_power > 100)
           {
             motor_power = 100;
           }
           else if(motor_power < 0)
           {
             motor_power = 0;
           }

           motor[motorA] = motor_power;
           bFloatDuringInactiveMotorPWM = true;

           last_error = error;

       }


}
