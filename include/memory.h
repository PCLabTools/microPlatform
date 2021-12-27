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

/**
 * @brief Device Settings
 * 
 * @details These are the core device settings that get loaded during the setup phase
 * 
 */
struct Memory 
{
  uint32_t BAUD_RATE = 115200;
} DeviceSettings;
