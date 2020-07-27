#pragma once

#include "EmergencyVehicle.h"

/* Default constructor. Set id to -1 to represent an unintialized object. */
EmergencyVehicle::EmergencyVehicle() {
	id = -1;
	type = VehicleType::null_type;
	zipcode = -1;
	availability = false;
}

/* Constructor; takes three parameters for ID of vehicle, vehicle type, and zipcode. Assumes the vehicle is
	automatically available. */
EmergencyVehicle::EmergencyVehicle(int i, VehicleType t, int z) {
	id = i;
	type = t;
	zipcode = z;
	availability = true;
}

/* Getters. */
int EmergencyVehicle::get_id() {
	return id;
}

VehicleType EmergencyVehicle::get_type() {
	return type;
}

int EmergencyVehicle::get_location() {
	return zipcode;
}

bool EmergencyVehicle::get_availability() {
	return availability;
}

/* Setters. */
void EmergencyVehicle::change_location(int z) {
	zipcode = z;
}

void EmergencyVehicle::set_busy() {
	availability = false;
}

void EmergencyVehicle::set_available() {
	availability = true;
}