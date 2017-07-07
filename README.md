# ESP2866-In-Out-Notification
Arduino sketch for the Adafruit Feather Huzzah ESP2866 to notify an Adafruit Dashboard

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
