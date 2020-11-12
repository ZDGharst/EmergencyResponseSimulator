#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <time.h>
#include <string>
#include <sstream>

#include "EmergencyVehicle.h"
#include "Request.h"
#include "Distance.h"
#include "debug.cpp"
#include "generate_graph.cpp"

/* Function proto-types. */
Request generate_random_request(int[]);

/* Global variables representing primary keys (starting at 1) for vehicles and requests ONLY. */
int request_primary_key = 1;
int vehicle_primary_key = 1;

int main() {
	/* Load zipcodes into an array (representing vertices of a graph).
	Load connections between zipcodes into an array (representing edges of a graph). */
	int zipcodes[24];
	Distance connections[39];
	read_zipcodes_csv(zipcodes, connections);

	/* Generate 10 of each vehicle type in a random zipcode of our dispatch area. */
	std::vector<EmergencyVehicle> vehicles;
	for (int i = 0; i < 10; i++) {
		int random_zipcode = rand() % 24;
		vehicles.push_back(EmergencyVehicle(vehicle_primary_key++, VehicleType::ambulance, zipcodes[random_zipcode]));
	}
	for (int i = 0; i < 10; i++) {
		int random_zipcode = rand() % 24;
		vehicles.push_back(EmergencyVehicle(vehicle_primary_key++, VehicleType::fire_truck, zipcodes[random_zipcode]));
	}
	for (int i = 0; i < 10; i++) {
		int random_zipcode = rand() % 24;
		vehicles.push_back(EmergencyVehicle(vehicle_primary_key++, VehicleType::police, zipcodes[random_zipcode]));
	}

	/* Declare data structures for requests. */
	std::queue<Request> unfulfilled_requests;
	std::vector<Request> fulfilled_requests;

	/* Our control structure emulating time. Represents 24 hours; each iteration represents 1 minute. We will simulate a
	full day (24 * 60 = 1440). */
	srand(time(NULL));
	for (int i = 0; i < 1440; i++) {
		/* Every 10 minutes, generate a new request. */
		if (i % 10 == 0)
			unfulfilled_requests.push(generate_random_request(zipcodes));

		/* If there are requests awaiting a vehicle, look for the closest vehicle that matches the type of
		request that is available and match them. If no vehicles of that type are available, wait for one
		to become available. */
		if (!unfulfilled_requests.empty()) {
			if (unfulfilled_requests.front().assign_vehicle(vehicles, zipcodes, connections)) {
				if (debug::detailed_view) std::cout << "Vehicle #" << unfulfilled_requests.front().get_vehicle_id() << " assigned to help request #" << unfulfilled_requests.front().get_id() << "with an estimated arrival time of " << vehicles[unfulfilled_requests.front().get_vehicle_id() - 1].get_availability() << '\n';

				fulfilled_requests.push_back(unfulfilled_requests.front());
				unfulfilled_requests.pop();
			}
			else if (debug::detailed_view) std::cout << "Attempted to fulfill request #" << unfulfilled_requests.front().get_id() << " but there are no vehicles of that type available!\n";
		}

		/* Time has incremented by 1, so all busy vehicles must be updated to see if they are no longer busy. */
		for (int i = 0; i < 30; i++) {
			vehicles[i].update();
		}
	}

	/* Output the requests fulfilled over an emulated period of 24 hours with a call every 10 minutes. */
	std::cout << "  ID  Zipcode     Type     VID\n";
	for (int i = 0; i < fulfilled_requests.size(); i++) {
		std::cout << fulfilled_requests[i];
	}

	return 0;
}

Request generate_random_request(int locations[]) {
	/* Generate a random type from our enums; ambulance, fire, or police. */
	VehicleType random_type = static_cast<VehicleType>(rand() % 3 + 1);

	/* Generate a random zip code. */
	int random_zipcode = rand() % 24;

	/* Create the request and return it. Set the primary key of the request and increment it by one for
	the next request. */
	Request random_request(request_primary_key++, random_type, locations[random_zipcode]);

	/* Detailed output. */
	if (debug::detailed_view) {
		std::cout << "Just got a call: person #" << random_request.get_id() << " at " << random_request.get_location() << " needs ";
		if (random_request.get_type() == VehicleType::ambulance) std::cout << "an ambulance";
		else if (random_request.get_type() == VehicleType::fire_truck) std::cout << "a fire truck";
		else if (random_request.get_type() == VehicleType::police) std::cout << "a police car";
		else std::cout << "null_type";
		std::cout << '\n';
	}

	return random_request;
}