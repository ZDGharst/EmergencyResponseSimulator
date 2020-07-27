#include "EmergencyVehicle.h"

namespace debug {
	bool detailed_view = true;

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
}