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
#ifndef TEMPSENSOR_H_
#define TEMPSENSOR_H_

#include "Arduino.h"
#include "OneWire.h"
#include "Util.h"
#include "DallasTemperature.h"

#include "ArdLogSetup.h"
#include "Service.h"
#include "Config.h"

class TempSensor: public Service {
public:
	TempSensor();
	virtual int8_t getTemp();
	virtual int8_t getQuickTemp();
	void init();

private:
	int8_t probes[TS_PROBES_SIZE] = {};
	uint8_t probeIdx;
	int8_t curentTemp;
	int8_t lastTemp;
	uint32_t lastProbeTime;
	OneWire oneWire;
	DallasTemperature dallasTemperature;

	inline int8_t readTemp();
	uint8_t deviceId();
	void cycle();
};

#endif /* TEMPSENSOR_H_ */
