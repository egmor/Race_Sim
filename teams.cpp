#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <array>
#include <limits>
#include <iomanip>

enum class TireType { Soft, Medium, Hard, Intermediate, Wet, };

enum class TrackCondition { Dry, Wet, Damp, };

enum class WeatherCondition { Sunny, Cloudy, LightRain, Rainy, Stormy, };

enum class EngineMode { Push, Standart, Economy, };

enum class BoostMode { Overtake, HotLap, Medium, None, };

enum class DriverRisk { Qualifing, Push, Race, Safe, }; //driver hitting the kerbs and track limits.

enum class TireMode { FullPace, Medium, Keep, };


// ======================= Car =======================
class Car {
private:
	unsigned int carWeight;
	unsigned int carHP;

	void checkCarWeight(unsigned int weight) {
		if (weight < 768 || weight > 795) { throw std::invalid_argument("Weight of F1 car cannot be over than 795kg or less than 768kg"); }
	}

	void checkCarHP(unsigned int horsepower) {
		if (horsepower < 950 || horsepower > 1020) { throw std::invalid_argument("Horsepower of F1 car cannot be over than 1020 h.p. or less than 950 h.p."); }
	}

public:
	// default constructor (значения в допустимых пределах)
	Car() : carWeight(780), carHP(1000) {}

	// constructor with parameters
	Car(unsigned int weight, unsigned int horsepower) : carWeight(780), carHP(1000) {
		setCarWeight(weight);
		setCarHP(horsepower);
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

	void checkDriverNSN(std::string_view name) {
		if (name.size() < 2 || name.size() > 20) { throw std::invalid_argument("Driver name/surname must be between 2 and 20 characters"); }
	}

	void checkDriverAge(unsigned int age) {
		if (age < 18 || age > 45) { throw std::invalid_argument("Driver age must be between 18 and 45"); }
	}

	void checkDriverWeight(unsigned int weight) {
		if (weight < 80 || weight > 100) { throw std::invalid_argument("Driver weight must be between 80 and 100 kg"); }
	}

	void checkDriverNumber(unsigned int number) {
		if (number < 1 || number > 99) { throw std::invalid_argument("Driver number must be between 1 and 99"); }
	}

public:
	// default constructor (значения в допустимых пределах)
	Driver() :
		driverName("Unknown"), driverSurname("Unknown"), driverAge(18), driverWeight(80), driverNumber(99) {
	}

	// constructor with parameters
	Driver(const std::string& name, const std::string& surname, unsigned int age, unsigned int weight, unsigned int number) :
		Driver() {
		setDriverName(name);
		setDriverSurname(surname);
		setDriverAge(age);
		setDriverWeight(weight);
		setDriverNumber(number);
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

	std::string getDriverName() const { return driverName; }
	std::string getDriverSurname() const { return driverSurname; }
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
class DriverSkills : public Driver {
private:
	unsigned int pace;
	unsigned int experience;
	unsigned int racecraft;
	unsigned int consistency;
	unsigned int fuelManagement;
	unsigned int tyreManagment;

	void checkParametr(unsigned int parametr) {
		if (parametr < 1 || parametr > 100) { throw std::invalid_argument("Parametr must be between 1 and 100"); }
	}

public:
	// default constructor
	DriverSkills() :
		Driver(), pace(50), experience(50), racecraft(50), consistency(50), fuelManagement(50), tyreManagment(50) {
	}

	// constructor with parameters
	DriverSkills(const std::string& name, const std::string& surname, unsigned int age, unsigned int weight, unsigned int number, //for Driver
		unsigned int PC, unsigned int EXP, unsigned int RC, unsigned int CT, unsigned int FM, unsigned int TM) :
		Driver(name, surname, age, weight, number),
		pace(50), experience(50), racecraft(50), consistency(50), fuelManagement(50), tyreManagment(50) {
		setPace(PC);
		setExperience(EXP);
		setRacecraft(RC);
		setConsistency(CT);
		setfuelManagement(FM);
		setTyreManagment(TM);
	}

	void setPace(unsigned int parametr) { checkParametr(parametr); pace = parametr; }
	void setExperience(unsigned int parametr) { checkParametr(parametr); experience = parametr; }
	void setRacecraft(unsigned int parametr) { checkParametr(parametr); racecraft = parametr; }
	void setConsistency(unsigned int parametr) { checkParametr(parametr); consistency = parametr; }
	void setfuelManagement(unsigned int parametr) { checkParametr(parametr); fuelManagement = parametr; }
	void setTyreManagment(unsigned int parametr) { checkParametr(parametr); tyreManagment = parametr; }

	unsigned int getPace() const { return pace; }
	unsigned int getExperience() const { return experience; }
	unsigned int getRacecraft() const { return racecraft; }
	unsigned int getConsistency() const { return consistency; }
	unsigned int getfuelManagement() const { return fuelManagement; }
	unsigned int getTyreManagment() const { return tyreManagment; }

	// формат строки:
	// <name> <surname> <age> <weight> <number> <pace> <exp> <racecraft> <consistency> <fuel> <tyre>
	friend std::istream& operator>>(std::istream& is, DriverSkills& d) {
		if (is >> static_cast<Driver&>(d)) {
			unsigned int pc, exp, rc, ct, fm, tm;
			if (is >> pc >> exp >> rc >> ct >> fm >> tm) {
				d.setPace(pc);
				d.setExperience(exp);
				d.setRacecraft(rc);
				d.setConsistency(ct);
				d.setfuelManagement(fm);
				d.setTyreManagment(tm);
				if (is.good()) is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // не падаем, если у последней строки нет перевода строки
			}
		}
		return is;
	}

	void print() const {
		Driver::print();
		std::cout << "               Pace: " << pace << " | Experience: " << experience
			<< " | Racecraft: " << racecraft << " | Consistency: " << consistency
			<< " | Fuel: " << fuelManagement << " | Tyres: " << tyreManagment << "\n";
	}
};


// ======================= Team =======================
class Team {
private:
	std::string teamName;
	unsigned int pitstopCrew; //quality of pitstop crew

	std::array<Car, 2> teamCars; //each team has 2 cars
	std::array<DriverSkills, 2> teamDrivers; //each team has 2 drivers

	void checkTeamName(const std::string& name) {
		if (name.size() < 2 || name.size() > 50) { throw std::invalid_argument("Team name must be between 2 and 50 characters"); }
	}

	void checkPitstopCrew(unsigned int crew) {
		if (crew < 1 || crew > 100) { throw std::invalid_argument("The team's skill level must be between 1 and 100"); }
	}

public:
	// default constructor (teamCars и teamDrivers создаются автоматически)
	Team() : teamName("Unknown"), pitstopCrew(75) {}

	// constructor with parameters
	Team(const std::string& name, unsigned int crew) : Team() {
		setTeamName(name);
		setPitstopCrew(crew);
	}

	void setTeamName(const std::string& name) {
		checkTeamName(name);
		teamName = name;
	}
	void setPitstopCrew(unsigned int crew) {
		checkPitstopCrew(crew);
		pitstopCrew = crew;
	}

	std::string getTeamName() const { return teamName; }
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

		double budget;
		unsigned int crew;

		if (is >> budget >> crew) {
			team.setPitstopCrew(crew);
			if (is.good()) is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // не падаем, если у последней строки нет перевода строки
		}

		return is;
	}

	void print() const {
		std::cout << "Team: " << teamName << " |"
			<< " millions dollar | Pitstop Quality: " << pitstopCrew << "\n";
		for (const auto& car : teamCars) car.print();
		for (const auto& driver : teamDrivers) driver.print();
		std::cout << "\n";
	}
};

class Track {
private:
	TrackCondition condition;
	double trackLength; // in kilometers
	unsigned int numberOfCorners;
	double pitlaneLost; //time lost in pitlane in seconds
	unsigned int trackTemperature; // in Celsius	
	double baseLaptime; //in seconds
	double abrasivenessAsphalt; // from 0.0 to 1.0


	void checkTrackLength(double length) {
		if (length < 3.3 || length > 7.0) { throw std::invalid_argument("Track length must be between 3.3 and 7.0 kilometers"); }
	}
	void checkNumberOfCorners(unsigned int corners) {
		if (corners < 5 || corners > 25) { throw std::invalid_argument("Number of corners must be between 5 and 25"); }
	}
	void checkPitlaneLost(double lost) {
		if (lost < 10.0 || lost > 40.0) { throw std::invalid_argument("Pitlane lost time must be between 10.0 and 40.0 seconds"); }
	}
	void checkTrackTempurature(unsigned int temperature) {
		if (temperature < 15 || temperature > 60) { throw std::invalid_argument("Track temperature must be between 15 and 60 degree of Celcium"); }
	}





};

class DriverStrategy {
private:
	EngineMode engineMode;
	BoostMode boostMode; 
	DriverRisk driverRisk;
	TireMode tireMode;

	TireType currentTire;
	TireType nextTire;

public:

	DriverStrategy() : engineMode(EngineMode::Standart), boostMode(BoostMode::Medium), driverRisk(DriverRisk::Race),
		tireMode(TireMode::Medium), currentTire(TireType::Medium), nextTire(TireType::Hard) {};

	DriverStrategy(EngineMode eMode, BoostMode bMode, DriverRisk dRisk, TireMode tMode, TireType cTire, TireType nTire) :
		engineMode(eMode), boostMode(bMode), driverRisk(dRisk), tireMode(tMode), currentTire(cTire), nextTire(nTire) {};

	void setEngineMode(EngineMode eMode) { engineMode = eMode; }
	void setBoostMode(BoostMode bMode) { boostMode = bMode; }
	void setDriverRisk(DriverRisk dRisk) { driverRisk = dRisk; }
	void setTireMode(TireMode tMode) { tireMode = tMode; }
	void setCurrentTire(TireType cTire) { currentTire = cTire; }
	void setNextTire(TireType nTire) { nextTire = nTire; }

	EngineMode getEngineMode() const { return engineMode; }

};

namespace changeStrategy {
	EngineMode changeEngineMode() {
		int choice{};
		std::cout << "Select a new engine operation mode:\n\n"
			<< "1. Push\n"
			<< "2. Standart\n"
			<< "3. Economy\n";

		std::cin >> choice;
		EngineMode selectMode{};

		switch (choice) {
		case 1: selectMode = EngineMode::Push; break;
		case 2: selectMode = EngineMode::Standart; break;
		case 3: selectMode = EngineMode::Economy; break;
		default: selectMode = EngineMode::Standart; break;
		}

		return selectMode;
	}

	BoostMode changeBoostMode() {
		int choice{};
		std::cout << "Select a new boost operation mode:\n\n"
			<< "1. Overtake\n"
			<< "2. HotLap\n"
			<< "3. Medium\n"
			<< "4. None\n\n";

		std::cin >> choice;
		BoostMode selectMode{};

		switch (choice) {
		case 1: selectMode = BoostMode::Overtake; break;
		case 2: selectMode = BoostMode::HotLap; break;
		case 3: selectMode = BoostMode::Medium; break;
		default: selectMode = BoostMode::None; break;
		}

		return selectMode;
	}


}

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

	DriverStrategy strategy;
	int choice{};

	std::cout << "What do you want change in your driver strategy?\n\n"
		<< "1. Engine Mode\n"
		<< "2. Boost Mode\n"
		<< "3. Driver Risk\n"
		<< "4. Tire Mode\n"
		<< "5. Next Tire\n\n"
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
	default:
		break;
	}

	return 0;
}