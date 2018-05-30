#pragma config(Sensor, S1,     HTGYRO,              sensorAnalogInactive)

#include "constants.h"
#include "robotcdriversuite/include/hitechnic-gyro.h"


task main()
{
  displayTextLine(0, "HT Gyro");
  displayTextLine(1, "Test 1");
  displayTextLine(5, "Press enter");
  displayTextLine(6, "to set relative");
  displayTextLine(7, "heading");

  sleep(2000);
  eraseDisplay();

  // Create struct to hold sensor data
  tHTGYRO gyroSensor;

  // Initialise and configure struct and port
  initSensor(&gyroSensor, S1);

  time1[T1] = 0;
  while(true)
  {
    if (time1[T1] > 1000) {
      eraseDisplay();
      displayTextLine(1, "Resetting");
      displayTextLine(1, "offset");
      sleep(500);

      // Start the calibration and display the offset
      sensorCalibrate(&gyroSensor);

      displayTextLine(2, "Offset: %f", gyroSensor.offset);
      playSound(soundBlip);
      while(bSoundActive) sleep(1);
      time1[T1] = 0;
    }

    while(!getXbuttonValue(xButtonEnter))
    {
      eraseDisplay();

      displayTextLine(1, "Reading");

      // Read the current rotational speed
      readSensor(&gyroSensor);

      // Read the current calibration offset and display it
      displayTextLine(2, "Offset: %4f", gyroSensor.offset);

      displayClearTextLine(4);
      // Read the current rotational speed and display it
      displayTextLine(4, "Gyro:   %4f", gyroSensor.rotation);
      displayTextLine(6, "Press enter");
      displayTextLine(7, "to recalibrate");
      sleep(100);
    }
  }
}
