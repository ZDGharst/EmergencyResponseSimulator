#pragma once

struct Distance {
	int zipcode1, zipcode2, distance;

	Distance() {}
	Distance(int, int, int);
	~Distance() {}
};