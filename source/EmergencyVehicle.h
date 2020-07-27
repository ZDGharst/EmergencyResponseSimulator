#pragma once

enum class VehicleType {
	null_type,
	ambulance,
	fire_truck,
	police
};

class EmergencyVehicle {
	int id, zipcode, availability;
	VehicleType type;

public:
	EmergencyVehicle();
	EmergencyVehicle(int, VehicleType, int);
	~EmergencyVehicle() {}

	int get_id();
	VehicleType get_type();
	int get_location();
	bool get_availability();

	void change_location(int);
	void set_busy(int);
	void set_available();
	void update();
};