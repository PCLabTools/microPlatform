/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <Arduino.h>
#include "errors.h"
#include "variables.h"
#include "hardware.h"
#include "memory.h"
#include "messages.h"

/**
 * @brief Initial Setup
 * 
 * @details When the device is booted the following actions are performed:
 *  -# Set the built-in LED pin to OUTPUT
 *  -# Serial communication is begun at BAUD rate defined by DeviceSettings
 * 
 */
void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(DeviceSettings.BAUD_RATE);
}

/**
 * @brief Main Application Loop
 * 
 * @details Once setup is complete, the following actions are peformed repetatively:
 *  -# Toggle the built-in LED
 *  -# EEPROManager updates EEPROM with new DeviceSettings if changed (print response if in DEBUG mode)
 *  -# Delay for 0.5 second
 * 
 */
void loop() 
{
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  if (uint8_t COUNT = manageDeviceSettings.update() && DeviceSettings.DEBUG) { Serial.println("EEPROM Managed: " + String(COUNT)); }
  delay(500);
}
