#pragma once

#include <vector>

#include "EmergencyVehicle.h"
#include "Distance.h"

class Request {
	int id, zipcode, vehicle_id;
	VehicleType type;

public:
	Request();
	Request(int, VehicleType, int);
	~Request() {};

	int get_id();
	VehicleType get_type();
	int get_location();
	int get_vehicle_id();

	bool assign_vehicle(std::vector<EmergencyVehicle> &vehicles, int zipcodes[], Distance connections[]);

	friend std::ostream&operator <<(std::ostream&, const Request&);
};