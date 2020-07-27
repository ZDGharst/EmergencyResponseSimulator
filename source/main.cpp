#include <iostream>
#include <fstream>
#include <vector>
#include "EmergencyVehicle.h"
#include "Request.h"
#include <queue>
#include <time.h>
#include <string>
#include <sstream>

/* Function proto-types. */
void read_zipcodes_csv(int[]);
Request generate_random_request(int[]);

/* Global variables representing primary keys (starting at 1) for vehicles and requests ONLY. */
int request_primary_key = 1;
int vehicle_primary_key = 1;

int main() {
	/* Load zipcodes into an array (representing vertices of a graph). 
	Load connections between zipcodes into an array (representing edges ofa  graph). */
	int zipcodes[24];
	read_zipcodes_csv(zipcodes);

	/* Declare data structures for unfulfilled requests and vehicles in use. */
	srand(time(NULL));
	std::vector<EmergencyVehicle> vehicles;
	std::queue<Request> unfulfilled_requests;

	getchar();



	/* Our control structure. Represents 24 hours; each iteration represents 1 minute. We will simulate a
	full day (24 * 60 = 1440). */
	for (int i = 0; i < 1440; i++) {
		if (i % 10 == 0)
			unfulfilled_requests.push(generate_random_request(zipcodes));

		if (!unfulfilled_requests.empty())
			break;
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

void read_zipcodes_csv(int zipcodes[]) {
	/* Zipcodes csv is formatted as follows:
	Line 1 is a list of the 24 zipcodes being used. 
	Line 2 and beyond are formatted as zipcode 1, zipcode 2, and distance between them, separated by commas. */
	std::ifstream zipcode_csv("zipcodes.csv");
	if (!zipcode_csv) throw std::runtime_error("Could not open file");

	std::string line, column;
	int value;

	/* Handle the first line which are the 24 zipcodes used. */
	std::getline(zipcode_csv, line);
	std::stringstream ss(line);

	for (int i = 0; i < 24; i++) {
		ss >> zipcodes[i];
		if(ss.peek() == ',') ss.ignore();
	}

	/* Handle all remaining lines treating them as edges in a graph. */
}