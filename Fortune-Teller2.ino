#include <SPI.h>

/*
  LiquidCrystal Library - Hello World
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD
 and shows the time.
 
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 12 Feb 2012
 by Juan Hernandez
 
 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the number of the sspin 
//(or the latch pin of the 74HC595)
LiquidCrystal lcd(9);

int tempSensorPin = 0;  // analog pin which the temperature sensor is connected to
float initialTemp;      // holds the initial temp of the room on startup
bool isReady = true;    // checks to see whether fortune machine is ready to make another prediction

void setup() {
  lcd.begin(16, 2);                           // set up number of columns and rows

  // prints start screen to lcd
  lcd.print("Find Out When");
  lcd.setCursor(0, 1);
  lcd.print("You'll Die...");

  initialTemp = analogRead(tempSensorPin);    // takes a reading of the temperature of the room to use as a control

  Serial.begin(9600);                         // begin serial monitoring
}

void loop() {
  int voltage = analogRead(tempSensorPin);    // take temperature reading

  int difference = voltage - initialTemp;     // calculate the difference between the current temperature reading and the room temperature

  if (difference <= 5 && difference >= -5){        // if current temperature returns back to around room temperature, reset the fortune machine
    isReady = true;
    lcd.clear();
    lcd.print("Find Out When");
    lcd.setCursor(0, 1);
    lcd.print("You'll Die...");
  }

  if (difference >= 10 && isReady){     // if the temperature has gone up significantly, begin reading a fortune
    int fortuneNumber = random(69);     // grab a random number between 0 and 69 (exclusive)
    transition();                       // play transition between main screen and fortune

    // START POSSIBLE FORTUNES
    // print one of many possible fortunes based off of randomly picked number
    // positive fortune are more probable
    if (fortuneNumber >= 1 && fortuneNumber <= 3){
      lcd.clear();
      lcd.print("Hopefully Soon");
      delay(2000);
      isReady = false;
    }

    if (fortuneNumber >= 4 && fortuneNumber <= 6){
      lcd.clear();
      lcd.print("In About 5");
      lcd.setCursor(0, 1);
      delay(1500);
      lcd.print("4..");
      delay(1500);
      lcd.print("3..");
      delay(1500);
      lcd.print("2..");
      delay(1500);
      lcd.print("1..");
      delay(500);
      isReady = false;
    }

    if (fortuneNumber >= 7 && fortuneNumber <= 9){
      lcd.clear();
      lcd.print("Right About");
      delay(800);
      lcd.print(".");
      delay(800);
      lcd.print(".");
      delay(800);
      lcd.print(".");
      delay(800);
      lcd.print(".");
      lcd.setCursor(0, 1);
      lcd.print("Now");
      delay(1500);
      isReady = false;
    }

    if (fortuneNumber >= 10 && fortuneNumber <= 12){
      lcd.clear();
      lcd.print("On A Tuesday");
      delay(2000);
      isReady = false;
    }

    if (fortuneNumber >= 13 && fortuneNumber <= 15){
      lcd.clear();
      lcd.print("The Next Time");
      lcd.setCursor(0, 1);
      lcd.print("You Say 'Hi'");
      delay(2000);
      isReady = false;
    }

    if (fortuneNumber >= 16 && fortuneNumber <= 18){
      lcd.clear();
      lcd.print("The Next Time");
      lcd.setCursor(0, 1);
      lcd.print("You Think Of Cats");
      delay(2000);
      isReady = false;
    }

    if (fortuneNumber >= 19 && fortuneNumber <= 21){
      lcd.clear();
      lcd.print("The First Of");
      lcd.setCursor(0, 1);
      lcd.print("October");
      delay(2000);
      isReady = false;
    }

    if (fortuneNumber >= 22 && fortuneNumber <= 24){
      lcd.clear();
      lcd.print("Valentine's Day");
      delay(2500);
      lcd.setCursor(0, 1);
      lcd.print("Don't We All");
      delay(800);
      lcd.print(".");
      delay(800);
      lcd.print(".");
      delay(800);
      lcd.print(".");
      delay(800);
      lcd.print(".");
      delay(800);
      lcd.print(".");
      delay(1500);
      isReady = false;
    }

    if (fortuneNumber >= 25 && fortuneNumber <= 27){
      lcd.clear();
      lcd.print("The Day You");
      lcd.setCursor(0, 1);
      lcd.print("Were Conceived");
      delay(2500);
      lcd.clear();
      lcd.print("Go Ahead...");
      delay(1000);
      lcd.setCursor(0, 1);
      lcd.print("Ask Your Parents");
      delay(1500);
      lcd.clear();
      lcd.print("I Dare You.");
      delay(800);
      lcd.print(".");
      delay(800);
      lcd.print(".");
      delay(800);
      lcd.print(".");
      delay(800);
      lcd.print(".");
      delay(1500);
      isReady = false;
    }

    if (fortuneNumber >= 28 && fortuneNumber <= 30){
      lcd.clear();
      lcd.print("Solve for x:");
      delay(2000);
      lcd.setCursor(0, 1);
      lcd.print("(4y/20x)^8=3x/y");
      delay(1000);
      lcd.clear();
      lcd.print("Too Late");
      delay(1500);
      lcd.clear();
      lcd.print("Now You'll");
      lcd.setCursor(0, 1);
      lcd.print("Never Know");
      delay(2000);
      isReady = false;
    }

    if (fortuneNumber >= 31 && fortuneNumber <= 33){
      lcd.clear();
      lcd.print("Next Time You");
      lcd.setCursor(0, 1);
      lcd.print("Blink");
      delay(1500);
      isReady = false;
    }

    if (fortuneNumber >= 34 && fortuneNumber <= 36){
      lcd.clear();
      lcd.print("Wouldn't You");
      lcd.setCursor(0, 1);
      lcd.print("Like To Know");
      delay(2000);
      lcd.print(":)");
      delay(1500);
      isReady = false;
    }

    if (fortuneNumber >= 37 && fortuneNumber <= 44){
      lcd.clear();
      lcd.print("     Never");
      delay(1500);
      isReady = false;
    }
    
    if (fortuneNumber >= 45 && fortuneNumber <= 47){
      lcd.clear();
      lcd.print("Whenever I");
      lcd.setCursor(0, 1);
      lcd.print("Decide It...");
      delay(1500);
      isReady = false;
    }

    if (fortuneNumber >= 48 && fortuneNumber <= 50){
      lcd.clear();
      lcd.print("Fuck If I");
      lcd.setCursor(0, 1);
      lcd.print("Know...");
      delay(1500);
      isReady = false;
    }

    if (fortuneNumber >= 51 && fortuneNumber <= 53){
      lcd.clear();
      lcd.print("Go Ask Someone");
      lcd.setCursor(0, 1);
      lcd.print("Else");
      delay(1500);
      isReady = false;
    }

    if (fortuneNumber >= 54 && fortuneNumber <= 60){
      lcd.clear();
      lcd.print("You Have Plenty");
      lcd.setCursor(0, 1);
      lcd.print("Of Time");
      delay(2000);
      isReady = false;
    }

    if (fortuneNumber >= 61 && fortuneNumber <= 68){
      lcd.clear();
      lcd.print("You've Got More");
      lcd.setCursor(0, 1);
      lcd.print("Time Than Me");
      delay(2000);
      isReady = false;
    }
    // END POSSIBLE FORTUNES
    
  }

  if (difference >= 10 && isReady){     // if the temperature has gone down significantly, begin reading a fortune
    int fortuneNumber = random(49);     // grab a random number between 0 and 49 (exclusive)
    transition();                       // play transition between main screen and fortune

    // START POSSIBLE FORTUNES
    // print one of many possible fortunes based off of randomly picked number
    // positive fortune are less probable
    if (fortuneNumber >= 1 && fortuneNumber <= 3){
      lcd.clear();
      lcd.print("Hopefully Soon");
      delay(2000);
      isReady = false;
    }

    if (fortuneNumber >= 4 && fortuneNumber <= 6){
      lcd.clear();
      lcd.print("In About 5");
      lcd.setCursor(0, 1);
      delay(1500);
      lcd.print("4..");
      delay(1500);
      lcd.print("3..");
      delay(1500);
      lcd.print("2..");
      delay(1500);
      lcd.print("1..");
      delay(500);
      isReady = false;
    }

    if (fortuneNumber >= 7 && fortuneNumber <= 9){
      lcd.clear();
      lcd.print("Right About");
      delay(800);
      lcd.print(".");
      delay(800);
      lcd.print(".");
      delay(800);
      lcd.print(".");
      delay(800);
      lcd.print(".");
      lcd.setCursor(0, 1);
      lcd.print("Now");
      delay(1500);
      isReady = false;
    }

    if (fortuneNumber >= 10 && fortuneNumber <= 12){
      lcd.clear();
      lcd.print("On A Tuesday");
      delay(2000);
      isReady = false;
    }

    if (fortuneNumber >= 13 && fortuneNumber <= 15){
      lcd.clear();
      lcd.print("The Next Time");
      lcd.setCursor(0, 1);
      lcd.print("You Say 'Hi'");
      delay(2000);
      isReady = false;
    }

    if (fortuneNumber >= 16 && fortuneNumber <= 18){
      lcd.clear();
      lcd.print("The Next Time");
      lcd.setCursor(0, 1);
      lcd.print("You Think Of Cats");
      delay(2000);
      isReady = false;
    }

    if (fortuneNumber >= 19 && fortuneNumber <= 21){
      lcd.clear();
      lcd.print("The First Of");
      lcd.setCursor(0, 1);
      lcd.print("October");
      delay(2000);
      isReady = false;
    }

    if (fortuneNumber >= 22 && fortuneNumber <= 24){
      lcd.clear();
      lcd.print("Valentine's Day");
      delay(2500);
      lcd.setCursor(0, 1);
      lcd.print("Don't We All");
      delay(800);
      lcd.print(".");
      delay(800);
      lcd.print(".");
      delay(800);
      lcd.print(".");
      delay(800);
      lcd.print(".");
      delay(800);
      lcd.print(".");
      delay(1500);
      isReady = false;
    }

    if (fortuneNumber >= 25 && fortuneNumber <= 27){
      lcd.clear();
      lcd.print("The Day You");
      lcd.setCursor(0, 1);
      lcd.print("Were Conceived");
      delay(2500);
      lcd.clear();
      lcd.print("Go Ahead...");
      delay(1000);
      lcd.setCursor(0, 1);
      lcd.print("Ask Your Parents");
      delay(1500);
      lcd.clear();
      lcd.print("I Dare You.");
      delay(800);
      lcd.print(".");
      delay(800);
      lcd.print(".");
      delay(800);
      lcd.print(".");
      delay(800);
      lcd.print(".");
      delay(1500);
      isReady = false;
    }

    if (fortuneNumber >= 28 && fortuneNumber <= 30){
      lcd.clear();
      lcd.print("Solve for x:");
      delay(2000);
      lcd.setCursor(0, 1);
      lcd.print("(4y/20x)^8=3x/y");
      delay(1000);
      lcd.clear();
      lcd.print("Too Late");
      delay(1500);
      lcd.clear();
      lcd.print("Now You'll");
      lcd.setCursor(0, 1);
      lcd.print("Never Know");
      delay(2000);
      isReady = false;
    }

    if (fortuneNumber >= 31 && fortuneNumber <= 33){
      lcd.clear();
      lcd.print("Next Time You");
      lcd.setCursor(0, 1);
      lcd.print("Blink");
      delay(1500);
      isReady = false;
    }

    if (fortuneNumber >= 34 && fortuneNumber <= 36){
      lcd.clear();
      lcd.print("Wouldn't You");
      lcd.setCursor(0, 1);
      lcd.print("Like To Know");
      delay(2000);
      lcd.print(":)");
      delay(1500);
      isReady = false;
    }

    if (fortuneNumber == 37){
      lcd.clear();
      lcd.print("     Never");
      delay(1500);
      isReady = false;
    }
    
    if (fortuneNumber >= 38 && fortuneNumber <= 40){
      lcd.clear();
      lcd.print("Whenever I");
      lcd.setCursor(0, 1);
      lcd.print("Decide It...");
      delay(1500);
      isReady = false;
    }

    if (fortuneNumber >= 41 && fortuneNumber <= 43){
      lcd.clear();
      lcd.print("Fuck If I");
      lcd.setCursor(0, 1);
      lcd.print("Know...");
      delay(1500);
      isReady = false;
    }

    if (fortuneNumber >= 44 && fortuneNumber <= 46){
      lcd.clear();
      lcd.print("Go Ask Someone");
      lcd.setCursor(0, 1);
      lcd.print("Else");
      delay(1500);
      isReady = false;
    }

    if (fortuneNumber == 47){
      lcd.clear();
      lcd.print("You Have Plenty");
      lcd.setCursor(0, 1);
      lcd.print("Of Time");
      delay(2000);
      isReady = false;
    }

    if (fortuneNumber == 48){
      lcd.clear();
      lcd.print("You've Got More");
      lcd.setCursor(0, 1);
      lcd.print("Time Than Me");
      delay(2000);
      isReady = false;
    }
    // END POSSIBLE FORTUNES
    
  }

  Serial.print("Room Temp: ");
  Serial.println(initialTemp);          // prints the room temperature recorded at start
  Serial.print("Current Reading: ");
  Serial.println(voltage);              // prints current temperature

  delay(500);                           // wait a bit
}

// prints a short transition
// used between main screen and fortune
void transition(){
  lcd.clear();                      // clears the screen of all text
  for (int i = 0; i < 16; i++){     // goes through all 16 columns in the 2 visible rows, creating dots all the way across
    lcd.setCursor(i, 0);            // sets the cursor to the i position on the top row
    lcd.print(".");                 // prints a dot
    delay(50);                      // wait a bit
    lcd.setCursor((15 - i), 1);     // sets the cursor to the 15-i position on the bottom row
    lcd.print(".");                 // prints a dot
    delay(50);                      // wait a bit
  }
  for (int i = 0; i < 16; i++){     // run through all 16 columns again, this time removing the dots one by one
    lcd.setCursor(i, 0);            // sets the cursor to the i position on the top row
    lcd.print(" ");                 // creates a blank space
    delay(50);                      // wait a bit
    lcd.setCursor((15 - i), 1);     // sets the cursor to the 15-i position on the bottom row
    lcd.print(" ");                 // creates a blank space
    delay(50);                      // wait a bit
  }
}

