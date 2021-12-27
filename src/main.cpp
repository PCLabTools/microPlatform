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
 *  -# Device memory is read for device settings
 *  -# Serial communication is begun at desired baud rate defined by device settings
 * 
 */
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(DeviceSettings.BAUD_RATE);
}

/**
 * @brief Main Application Loop
 * 
 * @details Provide details of how the main application loop is configured and expected actions
 * 
 */
void loop() {
  //
}
