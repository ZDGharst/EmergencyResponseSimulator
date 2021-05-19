#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <queue>

#include "Request.h"
#include "Distance.h"
#include "EmergencyVehicle.h"

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
bool Request::assign_vehicle(std::vector<EmergencyVehicle> &vehicles, int zipcodes[], Distance connections[]) {
	std::unordered_map<int, int> dist;
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> Q;
	
	/* For all zipcodes, set distance to an arbitrarily large number. */
	for (int i = 0; i < 24; i++) {
		dist[zipcodes[i]] = 100000;
	}

	/* Set distance to request (source) to 0 and add it to queue. */
	Q.push(std::make_pair(0, zipcode));
	dist[zipcode] = 0;

	/* For each node closest to the source... */
	while (!Q.empty()) {
		int u = Q.top().second;
		
		/* Iterate across the vehicles to see if any are in the node we are currently visiting. If it is, 
		check if its available and if it is of the right type. If so, set the vehicle to busy and change
		its location. Return true to signify we found the closest vehicle. */
		for (int i = 0; i < 30; i++) {
			if (vehicles[i].get_location() == u && vehicles[i].get_availability() == 0 && vehicles[i].get_type() == type) {
				vehicle_id = vehicles[i].get_id();
				vehicles[i].set_busy(15 + dist[u]);
				vehicles[i].change_location(zipcode);
				return true;
			}
		}

		/* If there are no vehicles in the node u, remove it from the Q, then look at the next closest zipcode to the request. */
		Q.pop();

		/* Find the adjacent nodes to u, then calculate if they have a new closest distance to source. */
		for (int i = 0; i < 39; i++) {
			if (connections[i].zipcode1 == u || connections[i].zipcode2 == u) {
				Distance v = connections[i];

				/* Re-arrange the zipcodes so that u is always zipcode 1. */
				if (v.zipcode1 != u) {
					v.zipcode2 = v.zipcode1;
					v.zipcode1 = u;
				}

				/* Change the distance is a closer one is found. */
				if (dist[v.zipcode2] > dist[v.zipcode1] + v.distance) {
					dist[v.zipcode2] = dist[v.zipcode1] + v.distance;
					Q.push(std::make_pair(dist[v.zipcode2], v.zipcode2));
				}
			}
		}
	}

	/* All vehicles of that type must be busy so return false. */
	return false;
}

/* Overload the << operator so that the information within the object will be output. */
std::ostream& operator<<(std::ostream& os, const Request &r) {
	os << std::setw(4) << r.id << ' '
		<< std::setw(7) << r.zipcode << ' '	<< std::setw(12);

	if (r.type == VehicleType::ambulance) os << "Ambulance";
	else if (r.type == VehicleType::fire_truck) os << "Fire Truck";
	else if (r.type == VehicleType::police) os << "Police Car";

	os << std::setw(5) << r.vehicle_id << '\n';
	return os;
}