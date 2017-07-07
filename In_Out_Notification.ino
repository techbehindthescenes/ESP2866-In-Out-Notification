/*
 * This sketch sends a notice to an Adafruit Dashboard 
 * when someone arrives (presses a green button) or leaves (presses a red button).
 * This uses: 
 * an Adafruit Feather Huzzah ESP2866 -- important to select this as the board in the Arduino IDE
 * an Adafruit IO account to capture the data
 * an Adafruit text feed to receive text-based notifications from the ESP2866
 * an Adafruit dashboard to display the notifications
 * 1 RGB LED, common anode
 * 2 buttons, ideally with 1 red cover and 1 green cover
 */
#include <AdafruitIO.h>
#include <AdafruitIO_Data.h>
#include <AdafruitIO_Feed.h>
#include <AdafruitIO_WiFi.h>

/************************* Adafruit IO and Wifi Setup *********************************/
 
#define IO_USERNAME    "xxxxxxx"  //your Adafruit IO Username
#define IO_KEY         "xxxxxxx"  //Your Adafruit IO Key
#define WIFI_SSID      "xxxxxxx"   //Your Wifi SSID name
#define WIFI_PASS      "xxxxxxx" //Your Wifi password

// based on Adafruit Feather Huzzah ESP2866
#define RED_LED 14
#define BLUE_LED 12
#define GREEN_LED 13
#define IN_BUTTON 4
#define OUT_BUTTON 5

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Set up the Adafruit text feed to receive notifications
// Important: if making Dashboard public, make sure to also change the Feed settings to public!
AdafruitIO_Feed *digital = io.feed("xxxxxxxx");   //Your Adafruit Feed name

// variable for reading the pushbutton statuses
int inButtonState = 0;         
int outButtonState = 0; 
int inButtonReading = 0;         
int outButtonReading = 0; 
int lastInButtonState = 0;
int lastOutButtonState = 0;
int inOutState = 0;  //0 = out, 1 = in

//For Debouncing based on code from adafruit.com
// the following variables are unsigned long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {

  //Serial.begin(115200);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(IN_BUTTON, INPUT);
  pinMode(OUT_BUTTON, INPUT);

   //Upon startup, cycle through a few LED colors
   digitalWrite(RED_LED, LOW);
   digitalWrite(GREEN_LED, HIGH);
   digitalWrite(BLUE_LED, HIGH);
   delay(500);

   digitalWrite(RED_LED, HIGH);
   digitalWrite(GREEN_LED, LOW);
   digitalWrite(BLUE_LED, HIGH);
   delay(500);

   digitalWrite(RED_LED, HIGH);
   digitalWrite(GREEN_LED, HIGH);
   digitalWrite(BLUE_LED, LOW);
   delay(500);

   digitalWrite(RED_LED, HIGH);
   digitalWrite(GREEN_LED, HIGH);
   digitalWrite(BLUE_LED, HIGH);
   delay(500);

  // wait for a connection.... show blue LED while connecting
   io.connect();

  while(io.status() < AIO_CONNECTED) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);
    delay(500);
    }
    
   //blink blue light twice after connection is established, then by default LED to red
   digitalWrite(RED_LED, HIGH);
   digitalWrite(GREEN_LED, HIGH);
   digitalWrite(BLUE_LED, LOW);
   delay(500);
   digitalWrite(RED_LED, HIGH);
   digitalWrite(GREEN_LED, HIGH);
   digitalWrite(BLUE_LED, LOW);
   delay(500);
   
   digitalWrite(RED_LED, LOW);
   digitalWrite(GREEN_LED, HIGH);
   digitalWrite(BLUE_LED, HIGH);

   
}

// the loop function runs over and over again forever
void loop() {

  io.run();
  
  inButtonReading = digitalRead(IN_BUTTON);
  outButtonReading = digitalRead(OUT_BUTTON);
  
  if (inButtonReading != lastInButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (inButtonReading != inButtonState) {
      inButtonState = inButtonReading;
      if (inButtonState == HIGH and inOutState == 0) {
        //turn green
          digitalWrite(RED_LED, HIGH);
          digitalWrite(GREEN_LED, LOW);
          digitalWrite(BLUE_LED, HIGH);
          inOutState = 1;
          digital->save("Member arrived");  //notification message sent to Adafruit Feed, change as needed
      }
    }
  }
  
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastInButtonState = inButtonReading;

  //out button
  if (outButtonReading != lastOutButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (outButtonReading != outButtonState) {
      outButtonState = outButtonReading;
      if (outButtonState == HIGH and inOutState == 1) {
        //turn red
          digitalWrite(RED_LED, LOW);
          digitalWrite(GREEN_LED, HIGH);
          digitalWrite(BLUE_LED, HIGH);
          inOutState = 0;
          digital->save("Member left");  //notification message sent to Adafruit Feed, change as needed
      }
    }
  }
  
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastOutButtonState = outButtonReading;
}
