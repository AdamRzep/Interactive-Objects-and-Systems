int enablePin = 11; // pin which goes into pin 1 on the h bridge
int 1APin = 10;     // pin which goes into pin 2 on the h bridge
int 2APin = 9;      // pin which goes into pin 7 on the h bridge
int photoPin = 0;   // analog pin 0 for the photocell resistor to change direction of motor
int flexPin = 1;    // analog pin 1 for the flex sensor to change speed of motor
 
void setup()
{
  pinMode(1APin, OUTPUT);       // set pin to output
  pinMode(2APin, OUTPUT);       // set pin to output
  pinMode(enablePin, OUTPUT);   // set pin which enables h bridge drivers 1 and 2 to output

  Serial.begin(9600);           // begin serial monitoring
}
 
void loop()
{

  
  int speed = map(analogRead(1), 60, 320, 70, 255);   // map the speed from the flex sensor to better fit the motor

  if (analogRead(photoPin) > 200){        // if the reading from the photocell resistor is high, spin the motor one direction
    analogWrite(enablePin, speed);
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, LOW);
  }

  else {                                  // if the reading from the photocell resisitor is low, have the motor spin in the opposite direction
    analogWrite(enablePin, speed);
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, HIGH);
  }

  Serial.print("photocell = ");
  Serial.println(analogRead(photoPin));   // print out the readings from the photocell resistor
  Serial.print("flex = ");
  Serial.println(analogRead(flexPin));    // print out the readings from the flex sensor
  delay(100);                             // wait for a moment
  
}
