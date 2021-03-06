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
#include "Service.h"

Service::Service() :
		enabled(true), serviceBusListener(this) {
}

Service::~Service() {

}

// ############### ServiceBusListener ###############
void Service::ServiceBusListener::onEvent(BusEvent event, va_list ap) {
	if (eb_inGroup(event, BusEventGroup::SERVICE)) {
		if (event == BusEvent::SERVICE_RESUME) {
			service->enabled = true;

		} else if (event == BusEvent::SERVICE_SUSPEND && service->enabled) {
			service->enabled = false;
		}
#if LOG
		log(F("SE %s - %d"), service->enabled ? "E" : "D", service->deviceId());
#endif

	} else if (service->enabled && event == BusEvent::CYCLE) {
		service->cycle();
	}
}

uint8_t Service::ServiceBusListener::listenerId() {
	return service->deviceId() + 100;
}

Service::ServiceBusListener::ServiceBusListener(Service* service) :
		service(service) {
}

