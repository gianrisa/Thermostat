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
#ifndef RELAYCONTROLLER_H_
#define RELAYCONTROLLER_H_

#import "Relay.h"

class RelayController {

public:
	RelayController();
	virtual ~RelayController();
	virtual Relay::State execute(int16_t currentTemp, int16_t tempSetpoint) = 0;
};

#endif /* RELAYCONTROLLER_H_ */