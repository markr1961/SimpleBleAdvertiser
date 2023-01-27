// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Sketch shows how to use SimpleBLE to advertise the name of the device and change it on the press of a button
// Useful if you want to advertise some sort of message
// Button is attached between GPIO 0 and GND, and the device name changes each time the button is pressed

#include "SimpleBLE.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

SimpleBLE ble;

#define BUTTON_PIN  0

void onButton()
{
    String out = "ESP32";
    out += String(millis() / 1000);
    Serial.println(out);
    ble.begin(out);
}

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    Serial.print("ESP32 SDK: ");
    Serial.println(ESP.getSdkVersion());
    ble.begin("ESP32 SimpleBLE");
    Serial.println("Press the button to change the device's name");

    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
}

void loop()
{
    static uint8_t lastPinState = 1;
    static int lastmillisec, nextmillisec = 1000; // don't toggle for the first second
    static bool laststate = false;

    // this should toggle the LED every 1000mS, but it seems like the background scanning makes it slower.
    int thismillisec = millis();
    if (nextmillisec <= thismillisec)
    {
        Serial.print("Last loop: ");
        Serial.print(thismillisec - lastmillisec);
        Serial.print(" mS.");

        lastmillisec = thismillisec;
        nextmillisec = thismillisec + 1000;       // wait another 1000mS

        Serial.print(" Current loop: ");
        Serial.print(thismillisec);
        Serial.print(", next loop: ");
        Serial.println(nextmillisec);

        laststate = !laststate;
        digitalWrite(LED_BUILTIN, laststate); // toggle the LED;

    }

    //read the button on pin 0:
    uint8_t pinState = digitalRead(BUTTON_PIN);
    if(!pinState && lastPinState)
    {
        Serial.print("Button press at ");
        Serial.println(millis());
        onButton(); // restart advertising.
    }
    lastPinState = pinState;

    // flush the serial (keyboard) buffer
    while(Serial.available())
        Serial.write(Serial.read());
}
