/*
 * pil.h
 *
 *  Created on: 06.05.2023
 *      Author: Marco Guerreiro
 */

#ifndef TASKS_PIL_H_
#define TASKS_PIL_H_

//=============================================================================
/*-------------------------------- Includes ---------------------------------*/
//=============================================================================
#include <stdint.h>
//=============================================================================

//=============================================================================
/*--------------------------------- Defines ---------------------------------*/
//=============================================================================
/* Priority and stack size of this task */
#define PIL_CONFIG_TASK_PRIO				2
#define PIL_CONFIG_TASK_STACK_SIZE			1024

//=============================================================================

//=============================================================================
/*---------------------------------- Task -----------------------------------*/
//=============================================================================
void pil(void *param);
//=============================================================================

#endif /* TASKS_PIL_H_ */