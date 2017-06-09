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
#include "Stats.h"

Stats::Stats(TempSensor* tempSensor) :
		tempSensor(tempSensor), systemTimer(), dayProbeIdx(0), lastProbeMs(0), dayHistoryIdx(0), dayHistoryFull(false), dit_idx(
				0), actualProbesIdx(0), actualProbesFull(false) {
}

void Stats::init(){
#if TRACE
	log(F("ST init"));
#endif
	systemTimer.start();
	actualTemp.day = 0;
	probeDayTemp();
	probeActualTemp();
}

void Stats::onEvent(BusEvent event, va_list ap) {
	if (!eb_inGroup(event, BusEventGroup::RELAY)) {
		return;
	}
	int relayId = va_arg(ap, int);

	if (event == BusEvent::RELAY_ON) {
		relayTimer[relayId].start();

	} else if (event == BusEvent::RELAY_OFF) {
		relayTimer[relayId].suspend();
	}
}
uint8_t Stats::listenerId(){
	return deviceId();
}

Time* Stats::getRelayTime(uint8_t relayId) {
	return relayTimer[relayId].getTime();
}

Time* Stats::getUpTime() {
	return systemTimer.getTime();
}

Temp* Stats::getActual() {
	return &actualTemp;
}

void Stats::cycle() {
	uint32_t currentMillis = util_millis();
	if (currentMillis - lastProbeMs >= DAY_PROBE_MS) {
		probeDayTemp();
		probeActualTemp();
		lastProbeMs = currentMillis;
	}
}

uint8_t Stats::deviceId() {
	return DEVICE_ID_STATS;
}

void Stats::probeActualTemp() {
	if (actualProbesIdx == ACTUAL_PROBES_SIZE) {
		actualProbesIdx = 0;
		actualProbesFull = true;
#if TRACE
		log(F("ST day stats"));
#endif
	}
	int8_t actTemp = tempSensor->getTemp();
	actualProbes[actualProbesIdx] = actTemp;

	uint8_t probesSize = actualProbesFull ? ACTUAL_PROBES_SIZE : actualProbesIdx;
	actualTemp.avg = util_avg_i16(actualProbes, probesSize);
	actualTemp.min = util_min_i16(actualProbes, probesSize);
	actualTemp.max = util_max_i16(actualProbes, probesSize);

#if TRACE
	log(F("ST Actual(%d/%d)->%d,%d,%d,%d"), actualProbesIdx, probesSize, actTemp, actualTemp.min,
			actualTemp.max, actualTemp.avg);
#endif
	actualProbesIdx++;
}

void Stats::probeDayTemp() {
	if (dayProbeIdx == PROBES_PER_DAY) {
		if (dayHistoryIdx == DAY_HISTORY_SIZE) {
			dayHistoryIdx = 0;
			dayHistoryFull = true;
		}
		Temp* temp = &dayHistory[dayHistoryIdx++];
		temp->avg = util_avg_i16(dayProbes, PROBES_PER_DAY);
		temp->min = util_min_i16(dayProbes, PROBES_PER_DAY);
		temp->max = util_max_i16(dayProbes, PROBES_PER_DAY);
		dayProbeIdx = 0;
#if LOG
		log(F("ST H(%d)->%d,%d,%d"), dayHistoryIdx, temp->avg, temp->min, temp->max);
#endif
	} else {
		dayProbes[dayProbeIdx++] = tempSensor->getTemp();
	}
}

boolean Stats::dit_hasNext() {
	boolean has = dit_idx > 0;
#if TRACE
	log(F("ST HN %d->%d"), (has ? 1 : 0), dit_idx);
#endif
	return has;
}

boolean Stats::dit_hasPrev() {
	uint8_t size = _dit_size();
	boolean has = dit_idx < size - 1;
#if TRACE
	log(F("ST HP %d->ss%d/%d"), (has ? 1 : 0), dit_idx, size);
#endif
	return has;
}

Temp* Stats::dit_next() {
	uint8_t histIdx = --dit_idx;
#if TRACE
	log(F("ST NE %d"), histIdx);
#endif
	Temp* temp = &dayHistory[histIdx];
	updateDayTemp(temp);
	return temp;
}

Temp* Stats::dit_prev() {
	uint8_t histIdx = ++dit_idx;
#if TRACE
	log(F("ST PRE %d"), histIdx);
#endif

	Temp* temp = &dayHistory[histIdx];
	updateDayTemp(temp);
	return temp;
}

inline void Stats::updateDayTemp(Temp* temp) {
	temp->day = _dit_size() - dit_idx;
}

void Stats::dit_reset() {
	dit_idx = _dit_size();
}

uint8_t Stats::_dit_size() {
	return dayHistoryFull ? DAY_HISTORY_SIZE : dayHistoryIdx;
}

uint8_t Stats::dit_size() {
	return _dit_size();
}
