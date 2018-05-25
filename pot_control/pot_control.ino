#include <Servo.h>

#define debug false
#define numAxis 4

struct ServoParams {
  int servoPin;
  int potPin;
  int servoMin;
  int servoMax;
  int potMin;
  int potMax;
  Servo servo;
};

// initialize axis parameters
ServoParams axis[] = {
  { // joint 1 / base
    8, // servoPin
    5, // potPin
    5, // servoMin 0-180
    175, // servoMax
    845, // potMin 0-1023
    200, // potMax
    Servo()
  },
  { // joint 2 / shoulder
    9, // servoPin
    4, // potPin
    5, // servoMin 0-180
    175, // servoMax
    20, // potMin 0-1023
    700, // potMax
    Servo()
  },
  { // joint 3 / elbow
    10, // servoPin
    3, // potPin
    5, // servoMin 0-180
    175, // servoMax
    300, // potMin 0-1023
    1020, // potMax
    Servo()
  },
  { // joint 4 / grabber
    11, // servoPin
    2, // potPin
    5, // servoMin 0-180
    175, // servoMax
    1020, // potMin 0-1023
    470, // potMax
    Servo()
  }
};
int val;

void setup() {
  if (debug) {
    Serial.begin(9600);
  } else {
    delay(5000);
    for (int i=0; i < numAxis; i++) {
      axis[i].servo.attach(axis[i].servoPin);
      delay(1000);
    }
  }
}

void loop() {
  if (debug) { // just read pot values
    String tmp = "";
    for (int i=0; i < numAxis; i++) {
      // read the value of the potentiometer (value between 0 and 1023)
      val = analogRead(axis[i].potPin);
      tmp += String(i) + " " + val + ", ";
    }
    Serial.println(tmp);
    delay(15); // wait for the servo to get there
  } else {
    for (int i=0; i < numAxis; i++) {
      // read the value of the potentiometer (value between 0 and 1023)
      val = analogRead(axis[i].potPin);
      // scale it to use it with the servo (value between 0 and 180)
      val = map(val, axis[i].potMin, axis[i].potMax, axis[i].servoMin, axis[i].servoMax);
      // sets the servo position according to the scaled value
      axis[i].servo.write(val);
    }
    delay(15); // wait for the servo to get there
  }
}
