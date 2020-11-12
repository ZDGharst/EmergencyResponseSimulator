#include "EmergencyVehicle.h"

namespace debug {
	bool detailed_view = false;

	void debug_vehicles(std::vector<EmergencyVehicle> vehicles) {
		for (int i = 0; i < 30; i++) {
			std::cout << "Vehicle #" << vehicles[i].get_id() << " at location " << vehicles[i].get_location() << " is " << (vehicles[i].get_availability() == 0 ? "available" : "busy") << " and it is ";
			if (vehicles[i].get_type() == VehicleType::ambulance) std::cout << "an ambulance";
			else if (vehicles[i].get_type() == VehicleType::fire_truck) std::cout << "a fire truck";
			else if (vehicles[i].get_type() == VehicleType::police) std::cout << "a police car";
			else std::cout << "null_type";
			std::cout << '\n';
		}
	}

	void debug_zipcodes(int zipcodes[]) {
		std::cout << "Zipcodes:\n";
		for (int i = 0; i < 24; i++)
			std::cout << zipcodes[i] << '\n';
	}
}


///* Create adjacency list. */
//for (int i = 0; i < 39; i++) {
//	if (connections[i].zipcode1 == u || connections[i].zipcode2 == u) {
//		Distance v = connections[i];
//		if (v.zipcode1 != u) {
//			v.zipcode2 = v.zipcode1;
//			v.zipcode1 = u;
//		}
//
//		if (dist[v.zipcode2] > dist[v.zipcode1] + v.distance) {
//			dist[v.zipcode2] = dist[v.zipcode1] + v.distance;
//			Q.push(std::make_pair(dist[v.zipcode2], v.zipcode2));
//		}
//
//		adjacencies.push_back(v);
//
//		std::cout << v.zipcode1 << ' ' << v.zipcode2 << '\n';
//		getchar();
//	}
//}