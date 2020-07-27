#pragma once

#include "Request.h"

Request::Request() {
	id = -1;
	type = VehicleType::null_type;
	zipcode = -1;
	vehicle_id = -1;
}

Request::Request(int i, VehicleType t, int z) {
	id = i;
	type = t;
	zipcode = z;
	vehicle_id = -1;
}

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

int Request::assign_vehicle() {
	return 0;
}