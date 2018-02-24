/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "io_types.h"
#include "pg/pg.h"
#include "fc/rc_modes.h"

typedef enum {
    CAMERA_CONTROL_KEY_ENTER,
    CAMERA_CONTROL_KEY_LEFT,
    CAMERA_CONTROL_KEY_UP,
    CAMERA_CONTROL_KEY_RIGHT,
    CAMERA_CONTROL_KEY_DOWN,
    CAMERA_CONTROL_KEYS_COUNT
} cameraControlKey_e;

typedef enum {
    CAMERA_CONTROL_MODE_HARDWARE_PWM,
    CAMERA_CONTROL_MODE_SOFTWARE_PWM,
    CAMERA_CONTROL_MODE_DAC,
    CAMERA_CONTROL_MODES_COUNT
} cameraControlMode_e;

typedef struct {
  cameraControlKey_e key;
  uint8_t repeat;
} cameraControlKeyRepeat_t;

#define CAMERA_CONTROL_MAX_SEQ_LEN 31 // 30 non-repeated key-presses plus a terminator

typedef struct cameraControlConfig_s {
    cameraControlMode_e mode;
    // measured in 10 mV steps
    uint16_t refVoltage;
    uint16_t keyDelayMs;
    uint16_t seqPauseMs;
    // measured 100 Ohm steps
    uint16_t internalResistance;

    ioTag_t ioTag;
} cameraControlConfig_t;

PG_DECLARE(cameraControlConfig_t, cameraControlConfig);

typedef struct {
    cameraControlKeyRepeat_t seq[BOXCAMERA3 - BOXCAMERA1][CAMERA_CONTROL_MAX_SEQ_LEN];
} cameraControlKeySequence_t;

PG_DECLARE_ARRAY(cameraControlKeySequence_t, 1 + BOXCAMERA3 - BOXCAMERA1, cameraControlKeySequences);

void cameraControlInit(void);

void cameraControlProcess(uint32_t currentTimeUs);
void cameraControlKeyPress(cameraControlKey_e key, uint32_t holdDurationMs);
