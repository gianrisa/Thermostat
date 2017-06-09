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
#include "Thermostat.h"

static TempSensor* tempSensor;
static Stats* stats;
static RelayDriver* relayDriver;
static Display* display;
static ServiceSuspender* serviceSuspender;
static Buttons* buttons;
static SystemStatus* systemStatus;

//static void init(Initializable* ini){
//	ini->init();
//}

static inline uint16_t getFreeRam() {
	extern int __heap_start, *__brkval;
	int v;
	return (uint16_t) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void setup() {
	util_setup();
	log_setup();

	Serial.print(F("FR1:"));Serial.println(getFreeRam());
	tempSensor = new TempSensor();
	Serial.print(F("FR2:"));Serial.println(getFreeRam());
	stats = new Stats(tempSensor);
	Serial.print(F("FR3:"));Serial.println(getFreeRam());
	//relayDriver = new RelayDriver(tempSensor);
	Serial.print(F("FR4:"));Serial.println(getFreeRam());
	//serviceSuspender = new ServiceSuspender();log_freeRAM("X-4");
	//systemStatus = new SystemStatus();log_freeRAM("X-5");
	//display = new Display(tempSensor, stats, relayDriver);log_freeRAM("X-6");
	//buttons = new Buttons();log_freeRAM("X-7");

	// init phase
	//init(tempSensor);
	//init(stats);
	//init(relayDriver);
	//init(display);
	//init(buttons);
}

void loop() {
	//Serial.print(F("LOOP:"));Serial.println(getFreeRam());
	util_cycle();
	log_cycle();

	// Hart beat
	eb_fire(BusEvent::CYCLE);
}
