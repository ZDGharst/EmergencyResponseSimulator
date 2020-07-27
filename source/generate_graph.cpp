void read_zipcodes_csv(int zipcodes[], Distance connections[]) {
	/* Zipcodes csv is formatted as follows:
	Line 1 is a list of the 24 zipcodes being used.
	Line 2 and beyond are formatted as zipcode 1, zipcode 2, and distance between them, separated by commas. */
	std::ifstream zipcode_csv("zipcodes.csv");
	if (!zipcode_csv) throw std::runtime_error("Could not open file");

	/* Handle the first line which are the 24 zipcodes used. */
	std::string line;
	std::getline(zipcode_csv, line);
	std::stringstream ss(line);

	for (int i = 0; i < 24; i++) {
		ss >> zipcodes[i];
		ss.ignore();
	}

	/* Handle all remaining lines treating them as edges in a graph. */
	for (int i = 0; i < 39; i++) {
		std::getline(zipcode_csv, line);
		std::stringstream ss(line);

		ss >> connections[i].zipcode1;
		ss.ignore();
		ss >> connections[i].zipcode2;
		ss.ignore();
		ss >> connections[i].distance;
	}
}

