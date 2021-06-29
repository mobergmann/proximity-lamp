# lamp-controller
Arduino Programm, which controls a distance sensor and turns on a high Voltage Lamp, whenever the distance to the sensor is smaller than 10 cm. 

# Hardware
- Arduino Board
- Relay
- HCSR04 Sensor

# Pins
- HCSR04 Sensor
  - echo: 4
  - trig: 5
- Relay: 3
- Button: 2

You can also cahange the Pins in the source code jourself.

# Increase Distance
To increase the distance just set the `TRIGGER_DISTANCE` variable in the source code.
