#pragma config(Sensor, S1,     HTGYRO,              sensorAnalogInactive)
#pragma config(Sensor, S2,     sonarSensor,         sensorSONAR)

#include "constants.h"
#include "rdpartyrobotcdr/drivers/hitechnic-gyro.h"

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
 * Test motor - used for calibration to find optimal position
 */
void test_motor()
{
	while(true)
	{

	  float accum = 0.0;
	  float now = 0;
    nMotorEncoder[motorA] = 0;

    while(now < p_f)
    {
    	motor[motorA] = 20;
    	now = nMotorEncoder[motorA];
    }

    while(nNxtButtonPressed)
    {
      eraseDisplay();
      nxtDisplayTextLine(1, "Done");

      motor[motorA] = 0;
    }
    wait1Msec(3000);
  }
}
