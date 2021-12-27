/**
 * @file errors.h
 * @author your name (you@domain.com)
 * @brief Error definition file
 * @version 0.1
 * @date 2021-12-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <Arduino.h>

/**
 * @brief NO_ERROR
 * 
 * @details Default error state of no error or warning
 * 
 */
#define NO_ERROR                                    0x0000

/**
 * @brief ASSERT_ERROR
 * 
 * @details Assertion error can be used to test error handling behaviour
 * 
 */
#define ASSERT_ERROR                                0x0001

/**
 * @brief UNKNOWN_STATE_CALLED
 * 
 * @details An unkown message state was received and could not be properly handled
 * 
 */
#define UNKNOWN_STATE_CALLED                        0x0002
