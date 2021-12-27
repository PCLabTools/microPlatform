/*************************************************************************
  File        : Messages.h
  Description : Message definition file
*************************************************************************/

#include <Arduino.h>
#include <MessageParser.h>
#include <time.h>

/**
 * MESSAGES:
 * 
 *  *IDN?   - Identity
 *  *ECHO   - Echo Data
 *  *STS?   - Query Available States
 *  *RST    - Reset
 *  *TST?   - Self-Test
 *  *ERR?   - Error
 *  *AST    - Assert Error
 *  *CLR    - Clear Error Status
 *  *TIME?  - Query Current Time
 *  *SYNC   - Syncrhonise Time Clock
 * 
 **/

/**
 * @brief Process a stream message and call an appropriate action if message valid
 * 
 * @details Calls a subfunction based on the state information of the incoming message.
 * Included data in the incoming message can be used to customise the action taken.
 * 
 * State        | Description       | Data         | Example      |
 * ------------ | ----------------- | ------------ | ------------ |
 * *IDN?        | Identity Query    |              |              |
 * *ECHO
 * *TST
 * *ERR?
 * *AST
 * *CLR?
 * 
 * @param STREAM Communication stream (Serial/I2C/Ethernet/FileIO)
 * @param MESSAGE Message to parse (MESSAGE.state & MESSAGE.data[])
 */
void handleMessage(Stream &STREAM, Message MESSAGE) {

  /*************************************************************************
    State       : *IDN?
    Parameters  : -
    Description : Queries the hardware and software ID
  *************************************************************************/
  if (MESSAGE.state == "*idn?") {
    #if defined BOARD_ATMEL
      time_t buildTime = BUILD_TIME - 946684800;
    #else
      time_t buildTime = BUILD_TIME;
    #endif
    STREAM.println(SOFTWARE_ID + " | " + COMPANY_ID + " | Serial: " + getHardwareID() + " | Version: " + String(SOFTWARE_VERSION_MAJOR, HEX) + "." + String(SOFTWARE_VERSION_MINOR, HEX) + "." + String(SOFTWARE_VERSION_FIX, HEX) + " | MCU: " + BOARD_MODEL + " | Build: " + ctime(&buildTime));
  } 

  /*************************************************************************
    State       : *ECHO
    Parameters  : -
    Description : Instructs the target to echo the message data[0]
  *************************************************************************/
  else if (MESSAGE.state == "*echo") {
    STREAM.println(MESSAGE.data[0]);
  } 

  /*************************************************************************
    State       : *RST
    Parameters  : -
    Description : Software resets the microcontroller
  *************************************************************************/
  else if (MESSAGE.state == "*rst") {
    // perform target specific reset
  } 

  /*************************************************************************
    State       : *TST?
    Parameters  : -
    Description : Instruct the system to perform a self-test and report
                  the system status
  *************************************************************************/
  else if (MESSAGE.state == "*tst?") {
    STREAM.println(String("Performing Self Test..."));
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    if (SYSTEM_ERROR) {STREAM.println(String("FAIL"));}
    else {STREAM.println(String("PASS"));}
  } 

  /*************************************************************************
    State       : *ERR?
    Parameters  : -
    Description : Queries the system for the current error code
  *************************************************************************/
  else if (MESSAGE.state == "*err?") {
    STREAM.println(String(SYSTEM_ERROR));
  } 

  /*************************************************************************
    State       : *AST
    Parameters  : -
    Description : Assert a system error which can be used for code testing
  *************************************************************************/
  else if (MESSAGE.state == "*ast") {
    SYSTEM_ERROR = ASSERT_ERROR;
  } 

  /*************************************************************************
    State       : *CLR
    Parameters  : -
    Description : Clears the current system error and return to 0
  *************************************************************************/
  else if (MESSAGE.state == "*clr") {
    SYSTEM_ERROR = NO_ERROR;
  } 

  /*************************************************************************
    State       : -
    Parameters  : -
    Description : Invalid STATE called produce system error (2)
  *************************************************************************/
  else {
    SYSTEM_ERROR = UNKNOWN_STATE_CALLED;
    STREAM.println("ERROR::UNKNOWN_STATE_CALLED");
  }
}

/**
 * @brief Function to simplify reading available bytes in any stream
 * 
 * @param STREAM Communication stream (Serial/I2C/Ethernet/FileIO)
 * @return String Byte stream
 */
String readStream(Stream &STREAM) {
  String inputStream = "";
  while (STREAM.available()) {
    char inChar = (char)STREAM.read();
    inputStream += inChar;
  }
  return inputStream;
}

/**
 * @brief MessageParser Object
 * 
 * @details A MessageParser object is created to deal with incoming stream messages and allows parsing into MESSAGE format
 * 
 */
MessageParser uart_comms;

/**
 * @brief serialEvent
 * 
 * @details Provides serial interrupt-style reading of incoming bytes
 * 
 */
void serialEvent() {
  Message currentMessage = uart_comms.parse(readStream(Serial));
  if (currentMessage.state != "") {
    handleMessage(Serial, currentMessage);
    currentMessage.state = "";
  }
}
