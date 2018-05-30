#pragma config(Sensor, S1,     HTGYRO,              sensorAnalogInactive)


#include "constants.h"
#include "rdpartyrobotcdr/drivers/hitechnic-gyro.h"


task main()
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
