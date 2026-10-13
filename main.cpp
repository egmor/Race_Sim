#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <array>
#include <limits>
#include <stdexcept>
#include <string_view>
#include "tire.h"
#include "strategy.h"

enum class RoadCondition { Dry, Wet, Damp, Drying, Flooded, };

enum class WeatherCondition { Sunny, Cloudy, LightRain, Rainy, Stormy, };


// ======================= Car =======================
class Car {
private:
	unsigned int carWeight;
	unsigned int carHP;

	static void checkCarWeight(unsigned int weight) {
		if (weight < 768 || weight > 795) { throw std::invalid_argument("Weight of F1 car must be between 768 and 795 kg"); }
	}

	static void checkCarHP(unsigned int horsepower) {
		if (horsepower < 950 || horsepower > 1020) { throw std::invalid_argument("Horsepower of F1 car must be between 950 and 1020 h.p."); }
	}

public:
	// default constructor (значения в допустимых пределах)
	Car() : carWeight(780), carHP(1000) {}

	// constructor with parameters
	Car(unsigned int weight, unsigned int horsepower) : carWeight(weight), carHP(horsepower) {
		checkCarWeight(weight);
		checkCarHP(horsepower);
	}

	void setCarWeight(unsigned int weight) {
		checkCarWeight(weight);
		carWeight = weight;
	}

	void setCarHP(unsigned int horsepower) {
		checkCarHP(horsepower);
		carHP = horsepower;
	}

	unsigned int getCarWeight() const { return carWeight; }
	unsigned int getCarHP() const { return carHP; }

	// формат строки: <weight> <horsepower>
	friend std::istream& operator>>(std::istream& is, Car& car) {
		unsigned int weight;
		unsigned int horsepower;

		if (is >> weight >> horsepower) {
			car.setCarWeight(weight);
			car.setCarHP(horsepower);
			if (is.good()) is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // не падаем, если у последней строки нет перевода строки
		}

		return is;
	}

	void print() const {
		std::cout << "    Car    | Weight: " << carWeight << " kg | Horsepower: " << carHP << " h.p.\n";
	}
};

// ======================= Driver =======================
class Driver {
private:
	std::string driverName;
	std::string driverSurname;
	unsigned int driverAge;
	unsigned int driverWeight;
	unsigned int driverNumber;

	static void checkDriverNSN(std::string_view name) {
		if (name.size() < 2 || name.size() > 20) { throw std::invalid_argument("Driver name/surname must be between 2 and 20 characters"); }
	}

	static void checkDriverAge(unsigned int age) {
		if (age < 18 || age > 45) { throw std::invalid_argument("Driver age must be between 18 and 45"); }
	}

	static void checkDriverWeight(unsigned int weight) {
		if (weight < 80 || weight > 100) { throw std::invalid_argument("Driver weight must be between 80 and 100 kg"); }
	}

	static void checkDriverNumber(unsigned int number) {
		if (number < 1 || number > 99) { throw std::invalid_argument("Driver number must be between 1 and 99"); }
	}

public:
	// default constructor (значения в допустимых пределах)
	Driver() :
		driverName("Unknown"), driverSurname("Unknown"), driverAge(18), driverWeight(80), driverNumber(99) {
	}

	// constructor with parameters
	Driver(std::string_view name, const std::string& surname, unsigned int age, unsigned int weight, unsigned int number) :
		driverName(name), driverSurname(surname), driverAge(age), driverWeight(weight), driverNumber(number) {
		checkDriverNSN(name);
		checkDriverNSN(surname);
		checkDriverAge(age);
		checkDriverWeight(weight);
		checkDriverNumber(number);
	}

	void setDriverName(std::string_view name) {
		checkDriverNSN(name);
		driverName = name;
	}

	void setDriverSurname(std::string_view surname) {
		checkDriverNSN(surname);
		driverSurname = surname;
	}

	void setDriverAge(unsigned int age) {
		checkDriverAge(age);
		driverAge = age;
	}

	void setDriverWeight(unsigned int weight) {
		checkDriverWeight(weight);
		driverWeight = weight;
	}

	void setDriverNumber(unsigned int number) {
		checkDriverNumber(number);
		driverNumber = number;
	}

	const std::string& getDriverName() const { return driverName; }
	const std::string& getDriverSurname() const { return driverSurname; }
	unsigned int getDriverAge() const { return driverAge; }
	unsigned int getDriverWeight() const { return driverWeight; }
	unsigned int getDriverNumber() const { return driverNumber; }

	// читает: <name> <surname> <age> <weight> <number> (конец строки НЕ пропускает,
	// т.к. дальше в той же строке идут навыки для DriverSkills)
	friend std::istream& operator>>(std::istream& is, Driver& driver) {
		std::string name, surname;
		unsigned int age, weight, number;

		if (is >> name >> surname >> age >> weight >> number) {
			driver.setDriverName(name);
			driver.setDriverSurname(surname);
			driver.setDriverAge(age);
			driver.setDriverWeight(weight);
			driver.setDriverNumber(number);
		}

		return is;
	}

	void print() const {
		std::cout << "    Driver | #" << driverNumber << " " << driverName << " " << driverSurname
			<< " | Age: " << driverAge << " | Weight: " << driverWeight << " kg\n";
	}
};

// ======================= DriverSkills =======================
class DriverSkills{
private:
	Driver driver;
	unsigned int pace;
	unsigned int experience;
	unsigned int racecraft;
	unsigned int consistency;
	unsigned int fuelManagement;
	unsigned int tyreManagement;

	static void checkParameter(unsigned int parameter) {
		if (parameter < 1 || parameter > 100) { throw std::invalid_argument("Parameter must be between 1 and 100"); }
	}

public:
	// default constructor
	DriverSkills() :
		driver(), pace(50), experience(50), racecraft(50), consistency(50), fuelManagement(50), tyreManagement(50) {
	}

	// constructor with parameters
	DriverSkills(std::string_view name, const std::string& surname, unsigned int age, unsigned int weight, unsigned int number, //for Driver
		unsigned int PC, unsigned int EXP, unsigned int RC, unsigned int CT, unsigned int FM, unsigned int TM) :
		driver(name, surname, age, weight, number),
		pace(PC), experience(EXP), racecraft(RC), consistency(CT), fuelManagement(FM), tyreManagement(TM) {
		checkParameter(PC);
		checkParameter(EXP);
		checkParameter(RC);
		checkParameter(CT);
		checkParameter(FM);
		checkParameter(TM);
	}

	void setPace(unsigned int parameter) { checkParameter(parameter); pace = parameter; }
	void setExperience(unsigned int parameter) { checkParameter(parameter); experience = parameter; }
	void setRacecraft(unsigned int parameter) { checkParameter(parameter); racecraft = parameter; }
	void setConsistency(unsigned int parameter) { checkParameter(parameter); consistency = parameter; }
	void setFuelManagement(unsigned int parameter) { checkParameter(parameter); fuelManagement = parameter; }
	void setTyreManagement(unsigned int parameter) { checkParameter(parameter); tyreManagement = parameter; }

	unsigned int getPace() const { return pace; }
	unsigned int getExperience() const { return experience; }
	unsigned int getRacecraft() const { return racecraft; }
	unsigned int getConsistency() const { return consistency; }
	unsigned int getFuelManagement() const { return fuelManagement; }
	unsigned int getTyreManagement() const { return tyreManagement; }

	friend std::istream& operator>>(std::istream& is, DriverSkills& d) {
		if (is >> d.driver) {
			unsigned int pc, exp, rc, ct, fm, tm;
			if (is >> pc >> exp >> rc >> ct >> fm >> tm) {
				d.setPace(pc);
				d.setExperience(exp);
				d.setRacecraft(rc);
				d.setConsistency(ct);
				d.setFuelManagement(fm);
				d.setTyreManagement(tm);
				if (is.good()) is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // не падаем, если у последней строки нет перевода строки
			}
		}
		return is;
	}

	void print() const {
		driver.print();
		std::cout << "               Pace: " << pace << " | Experience: " << experience
			<< " | Racecraft: " << racecraft << " | Consistency: " << consistency
			<< " | Fuel: " << fuelManagement << " | Tyres: " << tyreManagement << "\n";
	}
};

// ======================= Team =======================
class Team {
private:
	std::string teamName;
	unsigned int pitstopCrew; //quality of pitstop crew

	std::array<Car, 2> teamCars; //each team has 2 cars
	std::array<DriverSkills, 2> teamDrivers; //each team has 2 drivers

	static void checkTeamName(std::string_view name) {
		if (name.size() < 2 || name.size() > 50) { throw std::invalid_argument("Team name must be between 2 and 50 characters"); }
	}

	static void checkPitstopCrew(unsigned int crew) {
		if (crew < 1 || crew > 100) { throw std::invalid_argument("Pitstop crew quality must be between 1 and 100"); }
	}

public:
	// default constructor (teamCars и teamDrivers создаются автоматически)
	Team() : teamName("Unknown"), pitstopCrew(75) {}

	// constructor with parameters
	Team(std::string_view name, unsigned int crew) : teamName(name), pitstopCrew(crew) {
		checkTeamName(name);
		checkPitstopCrew(crew);
	}

	void setTeamName(std::string_view name) {
		checkTeamName(name);
		teamName = name;
	}
	void setPitstopCrew(unsigned int crew) {
		checkPitstopCrew(crew);
		pitstopCrew = crew;
	}

	const std::string& getTeamName() const { return teamName; }
	unsigned int getPitstopCrew() const { return pitstopCrew; }

	const std::array<Car, 2>& getCars() const { return teamCars; }
	const std::array<DriverSkills, 2>& getDrivers() const { return teamDrivers; }

	void loadCars(const std::string& filename) {
		std::ifstream file(filename);
		if (!file.is_open()) { throw std::runtime_error("Cannot open file: " + filename); }

		for (auto& car : teamCars) {
			if (!(file >> car)) { throw std::runtime_error("Not enough/invalid car data in file: " + filename); }
		}
	}

	void loadDrivers(const std::string& filename) {
		std::ifstream file(filename);
		if (!file.is_open()) { throw std::runtime_error("Cannot open file: " + filename); }

		for (auto& driver : teamDrivers) {
			if (!(file >> driver)) { throw std::runtime_error("Not enough/invalid driver data in file: " + filename); }
		}
	}

	friend std::istream& operator>>(std::istream& is, Team& team) {
		std::string line;

		while (std::getline(is, line)) {
			if (!line.empty() && line.back() == '\r') line.pop_back();
			if (!line.empty()) break;
		}

		if (line.empty()) return is;

		team.setTeamName(line);

		unsigned int crew;

		if (is >> crew) {
			team.setPitstopCrew(crew);
			if (is.good()) is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // не падаем, если у последней строки нет перевода строки
		}

		return is;
	}

	void print() const {
		std::cout << "Team: " << teamName << " | Pitstop Quality: " << pitstopCrew << "\n";
		for (const auto& car : teamCars) car.print();
		for (const auto& driver : teamDrivers) driver.print();
		std::cout << "\n";
	}
};

// ======================= Track =======================
class Track {
private:
	std::string  trackName;
	RoadCondition condition;
	double trackLength; // in kilometers
	unsigned int numberOfCorners;
	double pitlaneLost; //time lost in pitlane in seconds
	unsigned int trackTemperature; // in Celsius
	double baseLaptime; //in seconds on dry track and medium tires
	double abrasivenessAsphalt; // from 0.0 to 1.0

	static void checkTrackName(std::string_view name) {
		if (name.size() < 2 || name.size() > 50) { throw std::invalid_argument("Track name must be between 2 and 50 characters"); }
	}

	static void checkTrackLength(double length) {
		if (length < 3.3 || length > 7.0) { throw std::invalid_argument("Track length must be between 3.3 and 7.0 kilometers"); }
	}
	static void checkNumberOfCorners(unsigned int corners) {
		if (corners < 5 || corners > 25) { throw std::invalid_argument("Number of corners must be between 5 and 25"); }
	}
	static void checkPitlaneLost(double lost) {
		if (lost < 10.0 || lost > 40.0) { throw std::invalid_argument("Pitlane lost time must be between 10.0 and 40.0 seconds"); }
	}
	static void checkTrackTemperature(unsigned int temperature) {
		if (temperature < 15 || temperature > 60) { throw std::invalid_argument("Track temperature must be between 15 and 60 degrees Celsius"); }
	}
	static void checkAbrasivenessAsphalt(double abrasiveness) {
		if (abrasiveness < 0.0 || abrasiveness > 1.0) { throw std::invalid_argument("Abrasiveness of asphalt must be between 0.0 and 1.0"); }
	}
	static void checkBaseLaptime(double laptime) {
		if (laptime < 60.0 || laptime > 120.0) { throw std::invalid_argument("Base laptime must be between 60.0 and 120.0 seconds"); }
	}

public:

	Track() : trackName("Unknown"), condition(RoadCondition::Dry), trackLength(5.0), numberOfCorners(15), pitlaneLost(20.0),
		trackTemperature(30), baseLaptime(90.0), abrasivenessAsphalt(0.5) {
	}
	Track(std::string name, RoadCondition cond, double length, unsigned int corners, double lost, unsigned int temperature,
		double laptime, double abrasiveness) : trackName(name), condition(cond), trackLength(length), numberOfCorners(corners), pitlaneLost(lost),
		trackTemperature(temperature), baseLaptime(laptime), abrasivenessAsphalt(abrasiveness) {
		checkTrackName(name);
		checkTrackLength(length);
		checkNumberOfCorners(corners);
		checkPitlaneLost(lost);
		checkTrackTemperature(temperature);
		checkBaseLaptime(laptime);
		checkAbrasivenessAsphalt(abrasiveness);
	}

	void setTrackName(std::string_view name) { checkTrackName(name); trackName = name; }
	void setTrackCondition(RoadCondition cond) { condition = cond; }
	void setTrackLength(double length) { checkTrackLength(length); trackLength = length; }
	void setNumberOfCorners(unsigned int corners) { checkNumberOfCorners(corners); numberOfCorners = corners; }
	void setPitlaneLost(double lost) { checkPitlaneLost(lost); pitlaneLost = lost; }
	void setTrackTemperature(unsigned int temperature) { checkTrackTemperature(temperature); trackTemperature = temperature; }
	void setBaseLaptime(double laptime) { checkBaseLaptime(laptime); baseLaptime = laptime; }
	void setAbrasivenessAsphalt(double abrasiveness) { checkAbrasivenessAsphalt(abrasiveness); abrasivenessAsphalt = abrasiveness; }

	double getBaseLaptime() const { return baseLaptime; }
	RoadCondition getRoadCondition() const { return condition; }
	unsigned int getTrackTemperature() const { return trackTemperature; }

	friend std::istream& operator>>(std::istream& is, Track& track) {
		std::string line;

		while (std::getline(is, line)) {
			if (!line.empty() && line.back() == '\r') line.pop_back();
			if (!line.empty()) break;
		}

		if (line.empty()) return is;

		track.setTrackName(line);

		double length, pitlost, laptime, abrasiveness;

		unsigned int corners;

		if (is >> length >> corners >> pitlost >> laptime >> abrasiveness) {
			track.setTrackLength(length);
			track.setNumberOfCorners(corners);
			track.setPitlaneLost(pitlost);
			track.setBaseLaptime(laptime);
			track.setAbrasivenessAsphalt(abrasiveness);
			if (is.good()) is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // не падаем, если у последней строки нет перевода строки
		}

		return is;
	}

	void print() const {
		std::cout << "Track: " << trackName << "  \nCondition: " << static_cast<int>(condition)
			<< "  \nLength: " << trackLength << " km  \nCorners: " << numberOfCorners
			<< "  \nPitlane lost: " << pitlaneLost << " s  \nTemperature: " << trackTemperature
			<< " C  \nBase laptime: " << baseLaptime << " s  \nAbrasiveness: " << abrasivenessAsphalt << "\n";
	}
};

class TrackCondition : public Track {
private:
	WeatherCondition weather;

public: 
	TrackCondition() : Track(), weather(WeatherCondition::Sunny) {
	}
	TrackCondition(std::string name, RoadCondition cond, double length, unsigned int corners, double lost, unsigned int temperature,
		double laptime, double abrasiveness, WeatherCondition wCond) :
		Track(name, cond, length, corners, lost, temperature, laptime, abrasiveness), weather(wCond) {
	}
	void setWeatherCondition(WeatherCondition wCond) { weather = wCond; }
	WeatherCondition getWeatherCondition() const { return weather; }

	void print() const {
		Track::print();
		std::cout << "Weather Condition: " << static_cast<int>(weather) << "\n";
	}	
};

int main() {
	std::ifstream file("Teams/teams.dat");
	if (!file.is_open()) {
		std::cerr << "Cannot open Teams/teams.dat\n";
		return 1;
	}

	std::vector<Team> teams;
	Team tempTeam;
	int i{ 0 };

	try {
		while (file >> tempTeam) {
			++i;
			tempTeam.loadCars("Teams/TeamCars/team" + std::to_string(i) + "cars.dat");
			tempTeam.loadDrivers("Teams/TeamDrivers/team" + std::to_string(i) + "drivers.dat");
			teams.push_back(tempTeam);
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error (team #" << i << "): " << e.what() << "\n";
		return 1;
	}

	for (const auto& team : teams) {
		team.print();
	}

	//Tracks------------------------------------------------------

	std::ifstream trackFile("Tracks/tracks.dat");
	if (!trackFile.is_open()) {
		std::cerr << "Cannot open Tracks/tracks.dat\n";
		return 1;
	}

	std::vector<Track> tracks;
	Track tempTrack;
	int i_track{ 0 };

	try {
		while (trackFile >> tempTrack) {
			++i_track;
			tracks.push_back(tempTrack);
		}

	}
	catch (const std::exception& e) {
		std::cerr << "Error (track #" << i_track << "): " << e.what() << "\n";
		return 1;
	}

	for (const auto& track : tracks) {
		track.print();
	}

	//------------------------------------------------------------

	DriverStrategy strategy;
	int choice{};

	std::cout << "\nWhat do you want change in your driver strategy?\n"
		<< "1. Engine mode\n"
		<< "2. Boost mode\n"
		<< "3. Driver risk\n"
		<< "4. Tire mode\n"
		<< "5. Next tire\n\n"
		<< "Enter the correct number: ";

	std::cin >> choice;

	switch (choice) {
	case 1: {
		EngineMode newMode = changeStrategy::changeEngineMode();
		strategy.setEngineMode(newMode);
		break;
	}
	case 2: {
		BoostMode newMode = changeStrategy::changeBoostMode();
		strategy.setBoostMode(newMode);
		break;
	}
	case 3: {
		DriverRisk newRisk = changeStrategy::changeDriverRisk();
		strategy.setDriverRisk(newRisk);
		break;
	}
	case 4: {
		TireMode newMode = changeStrategy::changeTireMode();
		strategy.setTireMode(newMode);
		break;
	}
	case 5: {
		TireType newTire = changeStrategy::changeNextTire();
		strategy.setNextTire(newTire);
		break;
	}
	default:
		break;
	}

	return 0;
}