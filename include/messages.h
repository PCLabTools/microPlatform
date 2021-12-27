/**
 * @file messages.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <Arduino.h>
#include <MessageParser.h>
#include <time.h>

/**
 * @brief Process a stream message and call an appropriate action if message valid
 * 
 * @details Calls a subfunction based on the state information of the incoming message.
 * Included data in the incoming message can be used to customise the action taken.
 * 
 * State  | Description       | Data                | Example                    |
 * ------ | ----------------- | ------------------- | -------------------------- |
 * *IDN?  | Identity Query    |                     |                            |
 * *ECHO  | Echo String       | *Anything*          |                            |
 * *RST   | Software Reset    |                     |                            |
 * *TST   | Perform Self-Test |                     |                            |
 * *ERR?  | Query Error       |                     |                            |
 * *AST   | Assert Error      |                     |                            |
 * *CLR?  | Clear Error       |                     |                            |
 * *SYNC  | Synchronise Time  | yyyy-mm-dd,HH:MM:SS | *TIME::2021-12-27,12:21:22 |
 * *TIME? | Query Time        |                     |                            |
 * *BAUD  | Set BAUD rate     | BAUD Rate           | *BAUD::115200              |
 * *BAUD? | Query BAUD rate   |                     |                            |
 * 
 * @param STREAM Communication stream (Serial/I2C/Ethernet/FileIO)
 * @param MESSAGE Message to parse (MESSAGE.state & MESSAGE.data[])
 */
void handleMessage(Stream &STREAM, Message MESSAGE) 
{
 
  /**
   * ***
   * @par *IDN?
   * 
   * @details This command queries the board information including software version
   * and build time and the hardware ID. 
   * 
   * @return idn "SOFTWARE_ID | COMPANY_ID | Serial: xx-xx-xx-xx-xx | Version: x.x.x | MCU: MODEL | BUILD: *cTime*"
   * 
   */
  if (MESSAGE.state == "*idn?") 
  {
    #if defined BOARD_ATMEL
      time_t buildTime = BUILD_TIME - 946684800;
    #else
      time_t buildTime = BUILD_TIME;
    #endif
    STREAM.println(SOFTWARE_ID + " | " + COMPANY_ID + " | Serial: " + getHardwareID() + " | Version: " + String(SOFTWARE_VERSION_MAJOR, HEX) + "." + String(SOFTWARE_VERSION_MINOR, HEX) + "." + String(SOFTWARE_VERSION_FIX, HEX) + " | MCU: " + BOARD_MODEL + " | Build: " + ctime(&buildTime));
  } 

  /**
   * ***
   * @par *ECHO
   * 
   * @details This command instructs the board to echo a string sent as the data
   * portion of the message
   * 
   * @param echo_data *Anything*
   * 
   * @return *Anything*
   * 
   */
  else if (MESSAGE.state == "*echo") 
  {
    STREAM.println(MESSAGE.data[0]);
  } 

  /**
   * ***
   * @par *RST
   * 
   * @details Instructs the board to perform a software reset which will also close
   * the current STREAM connection so no response is provided
   * 
   */
  else if (MESSAGE.state == "*rst") 
  {
    // perform target specific reset
  } 

  /**
   * ***
   * @par *TST
   * 
   * @details Instructs the board to perform a self-test and reporst the status
   * 
   * @return status "PASS" or "FAIL"
   * 
   */
  else if (MESSAGE.state == "*tst") 
  {
    STREAM.println(String("Performing Self Test..."));
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    if (SYSTEM_ERROR) {STREAM.println(String("FAIL"));}
    else {STREAM.println(String("PASS"));}
  } 

  /**
   * ***
   * @par *ERR?
   * 
   * @details Queries the board for the current error code (0: NO ERROR)
   * 
   * @return error_code 
   * 
   */
  else if (MESSAGE.state == "*err?") 
  {
    STREAM.println(String(SYSTEM_ERROR));
  } 

  /**
   * ***
   * @par *AST
   * 
   * @details Assert an error which can be used for testing error handling code
   * 
   */
  else if (MESSAGE.state == "*ast") 
  {
    SYSTEM_ERROR = ASSERT_ERROR;
  } 

  /**
   * ***
   * @par *CLR
   * 
   * @details Clears the current error code on the board, this should return the board
   * to normal operating mode
   * 
   */
  else if (MESSAGE.state == "*clr") 
  {
    SYSTEM_ERROR = NO_ERROR;
  } 

  /**
   * ***
   * @par UNKNOWN_STATE_CALLED
   * 
   * @details If an unknown state is called the board will generate an error
   * 
   * @return response "ERROR::UNKNOWN_STATE_CALLED"
   * 
   */
  else 
  {
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
String readStream(Stream &STREAM) 
{
  String inputStream = "";
  while (STREAM.available()) 
  {
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
void serialEvent() 
{
  Message currentMessage = uart_comms.parse(readStream(Serial));
  if (currentMessage.state != "") 
  {
    handleMessage(Serial, currentMessage);
    currentMessage.state = "";
  }
}
