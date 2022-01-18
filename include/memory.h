/**
 * @file memory.h
 * @author your name (you@domain.com)
 * @brief Memory structure definition file
 * @version 0.1
 * @date 2021-12-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <Arduino.h>
#include "EEPROManager.h"

/**
 * @brief Device Settings
 * 
 * @details These are the core device settings that get loaded during the setup phase
 * 
 */
struct Settings 
{
  uint32_t BAUD_RATE = 115200;
  uint8_t DEBUG = 0;
} DeviceSettings;

EEPROManager<Settings> manageDeviceSettings(&DeviceSettings, 0x0001);
