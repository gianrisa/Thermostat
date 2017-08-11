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
#ifndef RELAYPIDCONTROLLER_H_
#define RELAYPIDCONTROLLER_H_

#include "RelayController.h"
#include "TempSensor.h"

class RelayPidController : public RelayController {
public:
	RelayPidController(TempSensor* ts, int16_t tempSetPoint);
	virtual ~RelayPidController();
	Relay::State execute();

private:
	float iDerivationSum;
	float dPrevDerivation;

	float calculateP(float derivation);
	float calculateI(float derivation);
	float calculateD(float derivation);
};

#endif /* RELAYPIDCONTROLLER_H_ */