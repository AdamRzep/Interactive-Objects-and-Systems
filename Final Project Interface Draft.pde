import com.temboo.core.*;
import com.temboo.Library.Yahoo.Weather.*;

// Create a session using your Temboo account application details
TembooSession session = new TembooSession("adamr71", "myFirstApp", "7kAMzy57l75JnLqHoG9TVQaqfDVDGFh1");

int temperature;
int high;
int low;
String day = "";
String date = "";
int weather;
XML weatherResults;

int rectX, rectY;      // Position of square button
int rectSize = 90;     // Diameter of rect
int mode = 0;
String input = "";
color rectColor, baseColor;
color rectHighlight;
color currentColor;
boolean rectOverOne = false;
boolean rectOverTwo = false;
boolean rectOverThree = false;

int index = 0;
int spacing = 0;
StringList reminders;
String[] allReminders;


void setup() {
  size(1280, 720);
  //fullScreen();
  background(229, 229, 204);
  rectColor = color(0);
  rectHighlight = color(51);
  baseColor = color(102);
  currentColor = baseColor;
  rectX = width/2-rectSize-10;
  rectY = height/2-rectSize/2;
  ellipseMode(CENTER);
  
  // Run the GetWeatherByAddress Choreo function
  runGetWeatherByAddressChoreo();
  getTemperatureFromXML();
  
  reminders = new StringList();
}

void draw() {
  update(mouseX, mouseY);
  background(229, 229, 204);
  stroke(0);
  
  // Record button
  if (rectOverOne) {
    fill(135, 135, 108);
  } else {
    fill(219, 218, 214);
  }
  rect(rectX - 300, rectY + 250, 200, 50);
  
  // Playback button
  if (rectOverTwo) {
    fill(135, 135, 108);
  } else {
    fill(219, 218, 214);
  }
  rect(rectX, rectY + 250, 200, 50);
  
  // Clear button
  if (rectOverThree) {
    fill(135, 135, 108);
  } else {
    fill(219, 218, 214);
  }
  rect(rectX + 300, rectY + 250, 200, 50);
  
  fill(0);
  textSize(36);
  text("Record", rectX - 260, rectY + 290);
  text("Playback", rectX + 25, rectY + 290);
  text("Clear", rectX + 354, rectY + 290);
  
  // neutral state
  if (mode == 0){
    fill(0);
    textSize(60);
    text(day+"      "+date, 50, 70);
    text(hour()+":"+minute(), 1060, 70);
    //text(date, 600, 90);
    
    textSize(360);
    text(temperature, 170, 460);
    textSize(60);
    text("ºF", 610, 230);
    
    textSize(70);
    text("High: "+high+"ºF", 740, 290);
    text("Low: "+low+"ºF", 740, 380);
  }
  
  // record status
  if (mode == 1){
    fill(0);
    textSize(50);
    text("Enter Reminder", 450, 190);
    
    // Input box
    fill(225, 236, 247);
    rect(rectX - 400, rectY - 100, 1000, 200);
    
    fill(0);
    text(input, 160, 270);
  }
  
  // playback status
  if (mode == 2){
    textSize(50);
    for (int i = 0; i < index; i++){
      text(allReminders[i], 150, 100 + spacing);
      spacing += 60;
    }
    delay(5000);
    mode = 0;
    spacing = 0;
  }
  
  // clear status
  if (mode == 3){
    textSize(130);
    text("Clearing list", 260, 300);
    allReminders = null;
    reminders = new StringList();
    delay(2000);
    mode = 0;
  }
}

void update(int x, int y) {
  if ( overRect(rectX - 300, rectY + 250, 200, 50) ) {
    rectOverOne = true;
  } else {
    rectOverOne = false;
  }
  
  if ( overRect(rectX, rectY + 250, 200, 50) ) {
    rectOverTwo = true;
  } else {
    rectOverTwo = false;
  }
  
  if ( overRect(rectX + 300, rectY + 250, 200, 50) ) {
    rectOverThree = true;
  } else {
    rectOverThree = false;
  }
}

void mousePressed() {
  if (rectOverOne) {
    mode = 1;
  }
  
  if (rectOverTwo) {
    mode = 2;
  }
  
  if (rectOverThree) {
    mode = 3;
  }
}

boolean overRect(int x, int y, int width, int height)  {
  if (mouseX >= x && mouseX <= x+width && 
      mouseY >= y && mouseY <= y+height) {
    return true;
  } else {
    return false;
  }
}

void runGetWeatherByAddressChoreo() {
  // Create the Choreo object using your Temboo session
  GetWeatherByAddress getWeatherByAddressChoreo = new GetWeatherByAddress(session);

  // Set inputs
  getWeatherByAddressChoreo.setAddress("New York");

  // Run the Choreo and store the results
  GetWeatherByAddressResultSet getWeatherByAddressResults = getWeatherByAddressChoreo.run();

  // Store results in an XML object
  weatherResults = parseXML(getWeatherByAddressResults.getResponse());
}

void getTemperatureFromXML() {
  // Narrow down to weather condition
  XML condition = weatherResults.getChild("channel/item/yweather:condition");
  XML forecast = weatherResults.getChild("channel/item/yweather:forecast");

  // Get the current temperature in Fahrenheit from the conditions
  temperature = condition.getInt("temp");
  high = forecast.getInt("high");
  low = forecast.getInt("low");
  day = forecast.getString("day");
  date = forecast.getString("date");

  // Print temperature value
  println("The current temperature in New York is "+temperature+"ºF");
  println("The high for today is "+high+"ºF");
  println("The low for today is "+low+"ºF");
}

void keyPressed(){
  if (mode == 1){
    if (key==ENTER||key==RETURN) {
      mode = 0;
      reminders.append(input);
      input = "";
      index++;
      allReminders = reminders.array();
    } else {
      input = input + key;
    }
  }
}
