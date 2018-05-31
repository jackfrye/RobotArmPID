#pragma config(Sensor, S1,     HTGYRO,              sensorAnalogInactive)
#pragma config(Sensor, S2,     sonarSensor,         sensorSONAR)


#include "constants.h"
#include "rdpartyrobotcdr/drivers/hitechnic-gyro.h"

/*
 * Debug Modes
 *		0 - off
 *		1 - test ultrasonic sensor
 *		2 - test HiTechnic Gyro Sensor
 *		3	- test motor
 */
const int DEBUG = 3;



float init_gyro()
{
    float gyro_offset = HTGYROstartCal(HTGYRO);
    wait1Msec(100);

    return gyro_offset;
}

/*
 * Display measurements from ultrasonic sensor
 */
void test_ultrasonic_sensor()
{
	while(true)
	{
		 float sonar_distance_l;

		  eraseDisplay();
    	wait1Msec(50);

  		sonar_distance_l = SensorValue[sonarSensor];

    	nxtDisplayTextLine(1, "Sonar: %3.2f", sonar_distance_l);
    	wait1Msec(50);
  }
}

/*
 * Re-initialize the gyro and display measurements
 *
 */
void test_gyro_sensor()
{
    nxtDisplayTextLine(0, "HT Gyro");
	  nxtDisplayTextLine(1, "Test 1");
	  nxtDisplayTextLine(5, "Press enter");
	  nxtDisplayTextLine(6, "to set relative");
	  nxtDisplayTextLine(7, "heading");

	  wait1Msec(2000);
	  eraseDisplay();
	  time1[T1] = 0;
	  while(true) {
	    if (time1[T1] > 1000) {
	      eraseDisplay();
	      nxtDisplayTextLine(1, "Resetting");
	      nxtDisplayTextLine(1, "offset");
	      wait1Msec(500);

	      // Start the calibration and display the offset
	      nxtDisplayTextLine(2, "Offset: %f", HTGYROstartCal(HTGYRO));
	      PlaySound(soundBlip);
	      while(bSoundActive) EndTimeSlice();
	      time1[T1] = 0;
	    }

	    while(nNxtButtonPressed != kEnterButton) {
	      eraseDisplay();

	      nxtDisplayTextLine(1, "Reading");
	      // Read the current calibration offset and display it
	      nxtDisplayTextLine(2, "Offset: %4f", HTGYROreadCal(HTGYRO));

	      nxtDisplayClearTextLine(4);
	      // Read the current rotational speed and display it
	      nxtDisplayTextLine(4, "Gyro:   %4f", HTGYROreadRot(HTGYRO));
	      nxtDisplayTextLine(6, "Press enter");
	      nxtDisplayTextLine(7, "to recalibrate");
	      wait1Msec(100);
	    }
	  }
}


/*
 * Test motor
 */
void test_motor()
{

	  const float rCount = 0.5;
	  float accum = 0.0;
	  float now = 0;
    nMotorEncoder[motorA] = 0;

    while(now < p_f)
    {
    	motor[motorA] = 20;
    	//eraseDisplay();
    	now = nMotorEncoder[motorA];
    	//nxtDisplayTextLine(1, "Accum=%.6f", now);
  }

  while(nNxtButtonPressed)
  {
    eraseDisplay();
    nxtDisplayTextLine(1, "Done");

    motor[motorA] = 0;
  }
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


}
