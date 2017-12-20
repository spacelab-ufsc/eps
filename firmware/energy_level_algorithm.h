/*
 * energy_level_algorithm.c
 *
 *  Created on: 26/06/2017
 *      Author: Bruno Eiterer
 */

#ifndef ENERGY_LEVEL_ALGORITHM_C_
#define ENERGY_LEVEL_ALGORITHM_C_

#include <msp430.h>
#include <stdint.h>
#include "hal.h"

#define maxChargeLevel 0x1300
#define level1 0x01
#define level2 0x02
#define level3 0x03
#define level4 0x04
#define level5 0x05

uint8_t energyLevelAlgorithm(uint8_t previous_level, uint16_t chargeLevel);


#endif /* ENERGY_LEVEL_ALGORITHM_C_ */