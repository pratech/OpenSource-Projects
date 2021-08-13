#include <VirtualWire.h>

#define XJOY_PIN A0
#define YJOY_PIN A1
#define XXJOY_PIN A2
#define YYJOY_PIN A3
#define SWITCH_XY 2
#define SWITCH_XXYY 3

char SensorCharMsg[7] = {};
int index_SensorCharMsg = 0;
void setup()
{
  Serial.begin(9600);
  pinMode(SWITCH_XY, INPUT_PULLUP);
  pinMode(SWITCH_XXYY, INPUT_PULLUP);
  // VirtualWire setup
  vw_setup(2000);     // Bits per sec
}
void loop()
{
  Serial.println("1");
readController();
  Serial.println("2");
  //Serial.println(SensorCharMsg);
  sendData();
  Serial.println("3");
  SensorCharMsg[] = {};
  Serial.println("4");
  //Serial.println(SensorCharMsg);
}
void sendData() {
  vw_send((uint8_t *)SensorCharMsg, strlen(SensorCharMsg));  // send the message
  vw_wait_tx(); // Wait until the whole message is gone
}

void dataAdding(char jys_input) {
  SensorCharMsg[index_SensorCharMsg] = jys_input ;
  index_SensorCharMsg++;
}

void readController() {
  int joystickXVal = analogRead(XJOY_PIN) ;
  int joystickYVal = analogRead(YJOY_PIN) ;
  int joystickXXVal = analogRead(XXJOY_PIN) ;
  int  joystickYYVal = analogRead(YYJOY_PIN) ;

  //Robot Direction Controller Joystick.
  if (joystickXVal >= 900) {
    dataAdding('F');//Forward
  }
  else if (joystickXVal <= 300) {
    dataAdding('B'); //Backward
  }
  else if (joystickYVal >= 900) {
    dataAdding('L'); //Left
  }
  else if (joystickYVal <= 300 ) {
    dataAdding('R'); //Right
  }
  else {
    dataAdding('S'); //Stop
  }

  //Arm Controller Joystick
  if (joystickXXVal >= 900) {
    dataAdding('C'); //GripperClose
  }
  else if (joystickXXVal <= 300) {
    dataAdding('O') ;//GripperOpen
  }
  else {
    dataAdding('N'); //Stop
  }

  if (joystickYYVal >= 900) {
    dataAdding('U');//ArmUp
  }
  else if (joystickYYVal <= 300 ) {
    dataAdding('D');//ArmDown
  }
  else {
    dataAdding('M'); //Stop
  }

  if (digitalRead(SWITCH_XY) == LOW) {
    dataAdding('W'); //Pump ON
  }
  else {
    dataAdding('X'); //Pump OFF
  }
  if (digitalRead(SWITCH_XXYY) == LOW) {
    dataAdding('Y'); //Shoot ON
  } else {
    dataAdding('Z'); //Shoot OFF
  }

  dataAdding('\0');
}
