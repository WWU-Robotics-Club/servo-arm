/*
 * Title:        Bluetooth Remote Control
 * Description:  This program is intented to work with a connected
 *               Bluetooth dongle to the robot and an Android phone
 *               running Blueberry application
 * Author:       Karl Kangur <karl.kangur@gmail.com>
 * Modified by:  CalebJ2
 * Version:      1.0
 * Website:      github
 */
#include <Servo.h>

// how many servos are attached
#define numChannels 4

Servo servos[numChannels];
int servoPins[] = {8,9,10,11};
int* tmpArr;
// keyframe inputs. Default everything to 90
int* currentFrame = new int[7]; // transition from
int* midFrame = new int[7]; // currently at
int* nextFrame = new int[7]; // transition to
unsigned long frameStart = 0; // time

char serialData[32];
byte error = 0;
unsigned long lastRxTime;
unsigned long lastServoTime;
unsigned long currentTime;
boolean connected; //has communicated with phone within last second? This is mostly unused.

void setup()
{
  // the bluetooth dongle communicates at 9600 baud only
  Serial.begin(115200);
  lastRxTime = millis();
  
  for (int i=0; i < numChannels; i++) {
    servos[i].attach(servoPins[i]);
  }
  // default frames to 90
  for (int i=0; i < 7; i++) {
    currentFrame[i] = 90;
    midFrame[i] = 90;
    nextFrame[i] = 90;
  }
}

void loop()
{
  if(millis()-lastRxTime > 1500 && connected == true){//if this hasn't heard from phone for 1.5 seconds
    //Serial.println("reset due to timeout ");
    //connected = false;
    //reset();
  }
  if(Serial.available() > 0)
  {
    // clear timeout
    connected = true;
    lastRxTime = millis();

    Serial.readBytesUntil('\n', serialData, 31);
    switch(serialData[0])
    {
    case 0: //basically the blueberry ping command
      Serial.println(0);
      break;
    case 'k':
      // set up transition from current position to recieved frame
      tmpArr = new int[7];
      if(parseCommand(serialData, tmpArr, 7)) {
        // start next frame. midFrame should be close to next frame, so just transition from it
        // to avoid jumps. Delete currentFrame and shift everything else down to avoid memory leaks.
        midFrame[0] = nextFrame[0];
        delete currentFrame;
        currentFrame = midFrame;
        midFrame = nextFrame;
        nextFrame = tmpArr;
        frameStart = millis();
        Serial.println('0'); // confirm reception
      } else {
        delete tmpArr;
        Serial.print("Error while parsing command. ");
        Serial.println(String(serialData));
      }
      break;
    case 'r':
      reset();
      Serial.println("Robot reset");
      break;
    default:
      // inform user of non existing command
      Serial.print("Command not recognised. ");
      Serial.println(String(serialData));
    }

    // clear serialData array
    memset(serialData, 0, sizeof(serialData));
  }
  //k,5000,10,10,10,10,0,0
  //String tmp = "";
  int timeIntoFrame = constrain(millis() - frameStart, 0, currentFrame[0]);
  // like percent except out of 1000 to minimize integer rounding errors
  // (frame delay - timeElapsed) / frame delay * 1000
  int scalar = ((long)currentFrame[0] - (long)timeIntoFrame) * (long)1000 / (long)currentFrame[0];
  midFrame[0] = currentFrame[0] - timeIntoFrame;
  //tmp += "millis " + String(millis()) + ", time " + String(timeIntoFrame) + ", ft0 " + String(currentFrame[0]) + ", scalar " + String(scalar);
  for (int i = 1; i < numChannels+1; i++) {
    midFrame[i] = (long)currentFrame[i] * scalar / 1000 + (long)nextFrame[i] * (1000 - scalar) / 1000;
    midFrame[i] = constrain(midFrame[i], 6, 174);
    //tmp += "; i " + String(i) + ", val " + String(midFrame[i]);
  }
  for (int i = 0; i < numChannels; i++) {
    servos[i].write(midFrame[i+1]);
  }
  //Serial.println(tmp);
  //delay(50);
}

void reset()
{
  for (int i=1; i <= 4; i++) {
    //servos[i-1].write(90);
  }
}

/**
 * This function makes ints out of the received serial data, the 2 first
 * characters are not counted as they consist of the command character and
 * a comma separating the first variable.
 *
 * @params command The whole serial data received as an address
 * @params returnValues The array where the return values go as an address
 * @params returnNumber The number of values to set inside the returnValues variable
 */
boolean parseCommand(char* command, int* returnValues, byte returnNumber)
{
  // parsing state machine
  byte i = 1, j = 0, sign = 0, ch = 0, number;
  int temp = 0;
  while(i++)
  {
    switch(*(command + i))
    {
    case '\0':
    case ',':
      // set return value
      if(ch != 0)
      {
        returnValues[j++] = sign?-temp:temp;
        sign = 0;
        temp = 0;
        ch = 0;
      }
      else
      {
        return false;
      }
      break;
    case '-':
      sign = 1;
      break;
    default:
      // convert string to int
      number = *(command + i) - '0';
      if(number < 0 || number > 9)
      {
        return false;
      }
      temp = temp * 10 + number;
      ch++;
    }

    // enough return values have been set
    if(j == returnNumber)
    {
      return true;
    }
    // end of command reached
    else if(*(command + i) == '\0')
    {
      return false;
    }
  }
}

