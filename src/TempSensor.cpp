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
#include "TempSensor.h"

TempSensor::TempSensor() :
		probeIdx(0), curentTemp(0), lastTemp(0), lastProbeTime(0), oneWire(DIG_PIN_TEMP_SENSOR), dallasTemperature(
				&oneWire) {
}

int8_t TempSensor::getTemp() {
	return curentTemp;
}

int8_t TempSensor::getQuickTemp() {
	return lastTemp;
}

void TempSensor::init() {
	dallasTemperature.begin();
	curentTemp = readTemp();
}

void TempSensor::cycle() {
	uint32_t ms = util_ms();
	if (ms - lastProbeTime < TS_PROBE_FREQ_MS) {
		return;
	}
	lastProbeTime = ms;
	int8_t temp = readTemp();
	lastTemp = temp;
	if (probeIdx == TS_PROBES_SIZE) {
		util_sort_i8(probes, TS_PROBES_SIZE);
		curentTemp = probes[TS_PROBES_MED_IDX];
		probeIdx = 0;
#if TRACE
		log(F("TS CY %d->%d %d %d"), curentTemp, probes[0], probes[1], probes[2]);
#endif

	} else {
		probes[probeIdx++] = temp;
	}
}

uint8_t TempSensor::deviceId() {
	return DEVICE_ID_TEMP_SENSOR;
}

inline int8_t TempSensor::readTemp() {
	dallasTemperature.requestTemperatures();
	int8_t temp = (int8_t) (dallasTemperature.getTempCByIndex(0) + 0.5);
#if USE_FEHRENHEIT
	temp = temp * 1.8 + 32;
#endif
	return temp;
}
