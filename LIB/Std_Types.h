/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  -
 *	   	   File:  STD_TYPES.h
 *		  Layer:  LIB
 *       Module:  STD_TYPES
 *		Version:  1.00
 *	
 *  Description:  Standard types definitions      
 *  
 *********************************************************************************************************************/
#ifndef STD_TYPES_H_
#define STD_TYPES_H_
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Platform_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define NULL	(void*) 0

#define SET 1
#define RESET 0

#define ON 1
#define OFF 0

#define HIGH 1
#define LOW 0

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef enum
{
	IDLE=0,
	BUSY
}Peripheral_State;

typedef enum
{
	SEND_CHAR=0,
	SEND_STRING,
	SEND_BUFFER,
	RECEIVE_CHAR,
	RECEIVE_BUFFER,
	SINGLE_CONVERSION,
	CHAIN_CONVERSION
}ISR_Src;

typedef enum
{
	FALSE=0,
	TRUE
}bool;

typedef enum
{
	E_OK=0,
	E_NOK,
	E_NULL_POINTER,
	E_WRONG_OPTION,
    E_BUSY,
	E_BUSY_FUNC,
	E_TIME_OUT,
	E_NO_RESPOSE,
	E_CONNECTION_FAILED,
	E_DIV_BY_ZERO
}ErrorState_t;

typedef enum
{
	LOCKED=0,
	UNLOCKED
} Lock_t;

typedef enum
{
    FLAG_LOW=0,
    FLAG_HIGH
}Flag_State_t;

#endif /* STD_TYPES_H_ */

/**********************************************************************************************************************
 *  END OF FILE: STD_TYPES.h
 *********************************************************************************************************************/
