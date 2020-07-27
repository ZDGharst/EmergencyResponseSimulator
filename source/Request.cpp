#pragma once

#include "Request.h"

/* Default constructor. Set id to -1 to represent an unintialized object. */
Request::Request() {
	id = -1;
	type = VehicleType::null_type;
	zipcode = -1;
	vehicle_id = -1;
}

/* Constructor; takes three parameters for ID of request, request type, and zipcode of request. Sets the
	vehicle ID to -1 to represent a request that has not been assigned a vehicle. */
Request::Request(int i, VehicleType t, int z) {
	id = i;
	type = t;
	zipcode = z;
	vehicle_id = -1;
}

/* Getters. */
int Request::get_id() {
	return id;
}

VehicleType Request::get_type() {
	return type;
}

int Request::get_location() {
	return zipcode;
}

int Request::get_vehicle_id() {
	return vehicle_id;
}

/* Assign vehicle by searching for closest available vehicle. If it returns true, there was a 
	vehicle available that was assigned. If false, a vehicle was not available. */
bool Request::assign_vehicle(std::vector<EmergencyVehicle> &vehicles) {
	for (int i = 0; i < 30; i++) {
		if (vehicles[i].get_location() == zipcode && vehicles[i].get_availability() == 0 && vehicles[i].get_type() == type) {
			vehicle_id = vehicles[i].get_id();
			vehicles[i].set_busy(10);
			return true;
		}
	}

	return false;
}