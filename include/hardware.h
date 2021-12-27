/**
 * @file hardware.h
 * @author your name (you@domain.com)
 * @brief Hardware definition including board specific definitions and pinouts
 * @version 0.1
 * @date 2021-12-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <Arduino.h>

#if defined BOARD_ATMEL || defined BOARD_STM
  #include <ArduinoUniqueID.h>
  String getHardwareID() 
  {
    String idString = "";
    for (uint8_t i = 0; i < 8; i++)
    {
      if (UniqueID8[i] < 0x10)
      {
        idString += '0';
      }
      idString += String(UniqueID8[i], HEX);
      idString += '-';
    }
    idString.remove(idString.length()-1);
    return idString;
  }
#endif

#if defined BOARD_ARM
  #include <TeensyID.h>
  String getHardwareID() {
    return teensySN();
  }
#endif