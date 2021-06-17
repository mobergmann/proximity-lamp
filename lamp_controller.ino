/**
 * Connections:
 *    - Button: 2
 *    - Relay: 3
 *    - Sensor: 
 *      - echo: 4
 *      - trig: 5
 */

#include <Simple_HCSR04.h>

/**
 * Const Globals
 */

const short     TRIGGER_DISTANCE  = 10; /// distance at which the sensor should be triggered
const short     BUTTON_PIN        = 2;  /// the pin at which the button is connected
const short     RELAY_PIN         = 3;  /// the pin at which the relay is connected
const short     ECHO_PIN          = 4;  /// the pin at which the sensor echo is connected
const short     TRIG_PIN          = 5;  /// the pin at which the sensor trig is connected

/**
 * Variable Globals
 */
 
int             lastState;
int             state;
unsigned long   lastDistance;
Simple_HCSR04*  sensor;



void setup()
{
  Serial.begin(9600);
  Serial.print("init...\n");

  lastState         = HIGH;
  state             = LOW;
  lastDistance      = TRIGGER_DISTANCE + 1; // set to random number larger than 10

  // setting the Button
  pinMode(BUTTON_PIN,   INPUT_PULLUP);
  
  // setting other connections
  pinMode(LED_BUILTIN,  OUTPUT);
  pinMode(RELAY_PIN,    OUTPUT);

  Serial.print("finished init.\n");
  
  sensor = new Simple_HCSR04(ECHO_PIN, TRIG_PIN);
}



bool sensorToggled()
{
  unsigned long distance = sensor->measure()->cm();
  Serial.print("distance: ");
  Serial.print(distance);
  Serial.println("cm");

  bool ret;
  
  // sensor is triggered
  if (distance <= TRIGGER_DISTANCE)
  {
    // sensor is triggerd, but last check it was also triggered
    if (lastDistance <= TRIGGER_DISTANCE)
    {
      ret = false;
    }
    // sensor is triggerd, but last check it wasn't triggered
    else
    {
      ret = true;
    }
  }
  else
  {
    ret = false;
  }

  lastDistance = distance;
  return ret;
}



void loop()
{
  // read the state of the switch/button:
  const int currentState = digitalRead(BUTTON_PIN);



  // Sensor registered movement, or Button state changed
  if (sensorToggled() || (lastState == LOW && currentState == HIGH))
  {
    if (state == HIGH)
    {
      // invert state
      state = LOW;

      // write led
      digitalWrite(LED_BUILTIN, state);

      // write relay
      digitalWrite(RELAY_PIN, state);
    }
    else
    {
      // invert state
      state = HIGH;

      // write led
      digitalWrite(LED_BUILTIN, state);

      // write relay
      digitalWrite(RELAY_PIN, state);
    }
  }



  // save the the last state
  lastState = currentState;

  delay(100);
}
