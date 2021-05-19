#include <iostream>
#include <vector>
#include <queue>
#include <time.h>
#include <fstream>
#include <sstream>
#include <string>

#include "EmergencyVehicle.h"
#include "Request.h"
#include "Distance.h"

/* Function proto-types. */
Request generate_random_request(int[]);
void read_zipcodes_csv(int zipcodes[], Distance connections[]);

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

				fulfilled_requests.push_back(unfulfilled_requests.front());
				unfulfilled_requests.pop();
			}
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

	return random_request;
}

void read_zipcodes_csv(int zipcodes[], Distance connections[]) {
	/* Zipcodes csv is formatted as follows:
	Line 1 is a list of the 24 zipcodes being used.
	Line 2 and beyond are formatted as zipcode 1, zipcode 2, and distance between them, separated by commas. */
	std::ifstream zipcode_csv("data/zipcodes.csv");
	if (!zipcode_csv) throw std::runtime_error("Could not open file");

	/* Handle the first line which are the 24 zipcodes used. */
	std::string line;
	std::getline(zipcode_csv, line);
	std::stringstream ss(line);

	for (int i = 0; i < 24; i++) {
		ss >> zipcodes[i];
		ss.ignore();
	}

	/* Handle all remaining lines treating them as edges in a graph. */
	for (int i = 0; i < 39; i++) {
		std::getline(zipcode_csv, line);
		std::stringstream ss(line);

		ss >> connections[i].zipcode1;
		ss.ignore();
		ss >> connections[i].zipcode2;
		ss.ignore();
		ss >> connections[i].distance;
	}
}