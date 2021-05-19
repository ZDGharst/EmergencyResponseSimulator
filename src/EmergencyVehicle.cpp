#include <iostream>
#include "EmergencyVehicle.h"

/* Default constructor. Set id to -1 to represent an unintialized object. */
EmergencyVehicle::EmergencyVehicle() {
	id = -1;
	type = VehicleType::null_type;
	zipcode = -1;
	availability = -1;
}

/* Constructor; takes three parameters for ID of vehicle, vehicle type, and zipcode. Assumes the vehicle is
	automatically available. */
EmergencyVehicle::EmergencyVehicle(int i, VehicleType t, int z) {
	id = i;
	type = t;
	zipcode = z;
	availability = 0;
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

int EmergencyVehicle::get_availability() {
	return availability;
}

/* Setters. */
void EmergencyVehicle::change_location(int z) {
	zipcode = z;
}

/* Availability is an integer that represents how much time until the vehicle is no longer busy. */
void EmergencyVehicle::set_busy(int i) {
	availability = i;
}

void EmergencyVehicle::set_available() {
	availability = 0;
}

/* Update vehicle time every minute. */
void EmergencyVehicle::update() {
	if (availability > 0) --availability;
}