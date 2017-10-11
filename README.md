# ESP8266-In-Out-Notification
Arduino sketch for the Adafruit Feather Huzzah ESP8266 to notify an Adafruit Dashboard

/*
 * This sketch sends a notice to an Adafruit IO Dashboard 
 * when someone arrives (presses a green button) or leaves (presses a red button) the Maker Space.
 * Everyone at the Maker Space can view the Adafruit IO Dashboard to see if someone is currently present at the space.
 * This uses: 
 * an Adafruit Feather Huzzah ESP8266 -- important to select this as the board in the Arduino IDE
 * an Adafruit IO account to capture the data
 * an Adafruit text feed to receive text-based notifications from the ESP8266
 * an Adafruit dashboard to display the notifications
 * 1 RGB LED, common anode
 * 2 buttons, ideally with 1 red cover and 1 green cover
 */
