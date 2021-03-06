/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef CONFIG_H_
#define CONFIG_H_

// ############### Relays ###############
const static uint8_t RELAYS_AMOUNT = 2;

/* Temperature threshold to enable first relay (DIG_PIN_RELAY_0) and start cooling. */
const static int8_t RELAY_TEMP_SET_POINT_0 = 21;

/* Temperature threshold to enable second relay (DIG_PIN_RELAY_1) and start cooling. */
const static int8_t RELAY_TEMP_SET_POINT_1 = 25;

/* Minimum time to switch next relay. 300000 - 5 minutes */
const static uint32_t RELAY_DELAY_AFTER_SWITCH_MS = 300000;

// ############### Pins ###############
const static uint8_t DIG_PIN_BUTTON_RESET = 1;
const static uint8_t DIG_PIN_BUTTON_NEXT = 2;
const static uint8_t DIG_PIN_BUTTON_PREV = 3;

const static uint8_t DIG_PIN_LCD_D7 = 4;
const static uint8_t DIG_PIN_LCD_D6 = 5;
const static uint8_t DIG_PIN_LCD_D5 = 6;
const static uint8_t DIG_PIN_LCD_D4 = 7;
const static uint8_t DIG_PIN_LCD_ENABLE = 8;
const static uint8_t DIG_PIN_LCD_RS = 9;

const static uint8_t DIG_PIN_RELAY_0 = 10;
const static uint8_t DIG_PIN_RELAY_1 = 11;

const static uint8_t DIG_PIN_TEMP_SENSOR = 12;

const static uint8_t DIG_PIN_SYSTEM_STATUS_LED = 13;

// ############### Devices ###############
const static uint8_t DEVICE_ID_TEMP_SENSOR = 1;
const static uint8_t DEVICE_ID_RELAY_DRIVER = 2;
const static uint8_t DEVICE_ID_STATS = 3;
const static uint8_t DEVICE_ID_TIME_STATS = 4;

// ############### Listeners ###############
const static uint8_t LISTENER_ID_BUTTONS = 200;
const static uint8_t LISTENER_ID_DISPLAY = 201;
const static uint8_t LISTENER_ID_SUSPENDER = 202;
const static uint8_t LISTENER_ID_STATUS = 203;

// ############### Display ###############
/* Time to resume normal operation after pause for user input. */
const static uint16_t DISP_SHOW_INFO_MS = 3000;

#define USE_FEHRENHEIT false

// ############### Relay Hysteresis Controller ###############
/* Prevents frequent switches of the particular relay. 3600000 - 1 hour*/
const static uint32_t RHC_RELAY_MIN_SWITCH_MS = 3600000;

// RPC - Relay PID Controller
const static float RPC_AMP_P = 1.0;
const static float RPC_AMP_I = 2.0;
const static float RPC_AMP_D = 0.3;

// PID threshold when relay should be switched on
const static float RPC_PID_SWITCH_THRESHOLD = -10;

// ############### Statistics ###############
/** Take 24 temp probes per day to calculate agv/min/max per day*/
const static uint8_t ST_PROBES_PER_DAY = 24;

/**
 * Take probe every hour - 24 probes gives us full day:
 * #PROBES_PER_DAY * #DAY_PROBE_MS = 24h.
 */
const static uint32_t ST_DAY_PROBE_MS = 3600000; // 3600000 = 1000 * 60 * 60; //TODO

// Frequency to probe for current temp, min and max (info on main screen)
const static uint32_t ST_ACTUAL_PROBE_MS = 300;

/** Keep history for last 60 days. */
const static uint8_t ST_DAY_HISTORY_SIZE = 60;

// ############### Temp Sensor ###############
/**
 * We take #TS_PROBES_SIZE probes from temp sensor, each one with delay of #PROBE_DELAY milliseconds.
 * After collecting all required probes we calculate median and this is the temperature.
 */
// log statement assumes at least 4 probes - adopt it after changing size!
const static uint8_t TS_PROBES_SIZE = 3;
const static uint8_t TS_PROBES_MED_IDX = 1; // it's an array index, starting from 0
const static uint32_t TS_PROBE_FREQ_MS = 200;

#endif /* CONFIG_H_ */
