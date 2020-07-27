#pragma once

enum class VehicleType {
	null_type,
	ambulance,
	fire_truck,
	police
};

class EmergencyVehicle {
	int id, zipcode;
	VehicleType type;
	bool availability;

public:
	EmergencyVehicle();
	EmergencyVehicle(int, VehicleType, int);
	~EmergencyVehicle();

	int get_id();
	VehicleType get_type();
	int get_location();
	bool get_availability();

	void change_location(int);
	void set_busy();
	void set_available();
};