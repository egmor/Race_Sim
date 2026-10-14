#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <array>
#include <limits>
#include <stdexcept>
#include <string_view>
#include "tire.h"
#include "strategy.h"
#include "track.h"

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

	static std::string checkDriverNSN(std::string name) {
		if (name.size() < 2 || name.size() > 20) { throw std::invalid_argument("Driver name/surname must be between 2 and 20 characters"); }
		return name;
	}
	static unsigned int checkDriverAge(unsigned int age) {
		if (age < 18 || age > 45) { throw std::invalid_argument("Driver age must be between 18 and 45"); }
		return age;
	}
	static unsigned int checkDriverWeight(unsigned int weight) {
		if (weight < 80 || weight > 100) { throw std::invalid_argument("Driver weight must be between 80 and 100 kg"); }
		return weight;
	}
	static unsigned int checkDriverNumber(unsigned int number) {
		if (number < 1 || number > 99) { throw std::invalid_argument("Driver number must be between 1 and 99"); }
		return number;
	}

public:
	Driver() : driverName("Unknown"), driverSurname("Unknown"), driverAge(18), driverWeight(80), driverNumber(99) {}

	Driver(std::string name, std::string surname, unsigned int age, unsigned int weight, unsigned int number) :
		driverName(checkDriverNSN(std::move(name))),
		driverSurname(checkDriverNSN(std::move(surname))),
		driverAge(checkDriverAge(age)),
		driverWeight(checkDriverWeight(weight)),
		driverNumber(checkDriverNumber(number)) {
	}

	void setDriverName(std::string_view name) { driverName = checkDriverNSN(std::string(name)); }
	void setDriverSurname(std::string_view surname) { driverSurname = checkDriverNSN(std::string(surname)); }
	void setDriverAge(unsigned int age) { driverAge = checkDriverAge(age); }
	void setDriverWeight(unsigned int weight) { driverWeight = checkDriverWeight(weight); }
	void setDriverNumber(unsigned int number) { driverNumber = checkDriverNumber(number); }

	const std::string& getDriverName() const { return driverName; }
	const std::string& getDriverSurname() const { return driverSurname; }
	unsigned int getDriverAge() const { return driverAge; }
	unsigned int getDriverWeight() const { return driverWeight; }
	unsigned int getDriverNumber() const { return driverNumber; }

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
	unsigned int tyreManagement;

	static unsigned int checkParameter(unsigned int parameter) {
		if (parameter < 1 || parameter > 100) { throw std::invalid_argument("Parameter must be between 1 and 100"); }
		return parameter;
	}

public:
	DriverSkills() : Driver(), pace(50), experience(50), racecraft(50), consistency(50), fuelManagement(50), tyreManagement(50) {}

	DriverSkills(std::string name, std::string surname, unsigned int age, unsigned int weight, unsigned int number,
		unsigned int PC, unsigned int EXP, unsigned int RC, unsigned int CT, unsigned int FM, unsigned int TM) :
		Driver(std::move(name), std::move(surname), age, weight, number),
		pace(checkParameter(PC)),
		experience(checkParameter(EXP)),
		racecraft(checkParameter(RC)),
		consistency(checkParameter(CT)),
		fuelManagement(checkParameter(FM)),
		tyreManagement(checkParameter(TM)) {
	}

	void setPace(unsigned int parameter) { pace = checkParameter(parameter); }
	void setExperience(unsigned int parameter) { experience = checkParameter(parameter); }
	void setRacecraft(unsigned int parameter) { racecraft = checkParameter(parameter); }
	void setConsistency(unsigned int parameter) { consistency = checkParameter(parameter); }
	void setFuelManagement(unsigned int parameter) { fuelManagement = checkParameter(parameter); }
	void setTyreManagement(unsigned int parameter) { tyreManagement = checkParameter(parameter); }

	unsigned int getPace() const { return pace; }
	unsigned int getExperience() const { return experience; }
	unsigned int getRacecraft() const { return racecraft; }
	unsigned int getConsistency() const { return consistency; }
	unsigned int getFuelManagement() const { return fuelManagement; }
	unsigned int getTyreManagement() const { return tyreManagement; }

	friend std::istream& operator>>(std::istream& is, DriverSkills& d) {
		if (is >> static_cast<Driver&>(d)) {
			unsigned int pc, exp, rc, ct, fm, tm;
			if (is >> pc >> exp >> rc >> ct >> fm >> tm) {
				d.setPace(pc);
				d.setExperience(exp);
				d.setRacecraft(rc);
				d.setConsistency(ct);
				d.setFuelManagement(fm);
				d.setTyreManagement(tm);
				if (is.good()) is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
		return is;
	}

	void print() const {
		Driver::print(); 
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

	std::string_view getTeamName() const { return teamName; }
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

double calculateCurrentLaptime(const Track& track, DriverStrategy strategy, double currentWear, WeatherCondition weather) {
	double laptimeModifier = 1.0;

	TireType tire = strategy.getCurrentTire();

	if (tire == TireType::Soft) laptimeModifier -= 0.010;
	if (tire == TireType::Hard) laptimeModifier += 0.015;
	if (tire == TireType::Intermediate) laptimeModifier += 0.040;
	if (tire == TireType::Wet) laptimeModifier += 0.080;

	if (currentWear >= 15.0 && currentWear < 70.0) {
		laptimeModifier += (currentWear / 70.0) * 0.015;
	}
	else if (currentWear >= 70.0 && currentWear < 85.0) {
		laptimeModifier += 0.045;
	}
	else if (currentWear >= 85.0) {
		laptimeModifier += 0.100;
	}

	RoadCondition condition = track.getRoadCondition();

	if (condition == RoadCondition::Dry) {
		if (tire == TireType::Intermediate) laptimeModifier += 0.04;
		else if (tire == TireType::Wet)     laptimeModifier += 0.08;
	}
	else if (condition == RoadCondition::Damp || condition == RoadCondition::Drying) {
		if (tire == TireType::Soft || tire == TireType::Medium || tire == TireType::Hard) {
			laptimeModifier += 0.035;
		}
		else if (tire == TireType::Intermediate) laptimeModifier += 0.015;
		else if (tire == TireType::Wet)          laptimeModifier += 0.050;
	}
	else if (condition == RoadCondition::Wet) {
		if (tire == TireType::Soft || tire == TireType::Medium || tire == TireType::Hard) {
			laptimeModifier += 0.250;
		}
		else if (tire == TireType::Intermediate) laptimeModifier += 0.060;
		else if (tire == TireType::Wet)          laptimeModifier += 0.040;
	}
	else if (condition == RoadCondition::Flooded) {
		if (tire == TireType::Soft || tire == TireType::Medium || tire == TireType::Hard) {
			laptimeModifier += 0.500;
		}
		else if (tire == TireType::Intermediate) laptimeModifier += 0.200;
		else if (tire == TireType::Wet)          laptimeModifier += 0.080;
	}

	switch (weather) {
	case WeatherCondition::Cloudy:    laptimeModifier += 0.002; break;
	case WeatherCondition::LightRain: laptimeModifier += 0.010; break;
	case WeatherCondition::Rainy:     laptimeModifier += 0.030; break;
	case WeatherCondition::Stormy:    laptimeModifier += 0.080; break;
	default: break;
	}

	switch (strategy.getEngineMode()) {
	case EngineMode::Push:    laptimeModifier -= 0.006; break; // -0.6%
	case EngineMode::Economy: laptimeModifier += 0.010; break; // +1.0%
	default: break;
	}

	switch (strategy.getBoostMode()) {
	case BoostMode::Overtake: laptimeModifier -= 0.013; break; // -1.3%
	case BoostMode::HotLap:   laptimeModifier -= 0.011; break; // -1.1%
	case BoostMode::Medium:   laptimeModifier -= 0.003; break; // -0.3%
	case BoostMode::None:     laptimeModifier += 0.005; break; // +0.5%
	}

	switch (strategy.getDriverRisk()) {
	case DriverRisk::Qualifying: laptimeModifier -= 0.006; break; // -0.6%
	case DriverRisk::Push:      laptimeModifier -= 0.003; break; // -0.3%
	case DriverRisk::Safe:      laptimeModifier += 0.008; break; // +0.8%
	default: break; 
	}

	switch (strategy.getTireMode()) {
	case TireMode::FullPace: laptimeModifier -= 0.009; break; // -0.9%
	case TireMode::Keep:     laptimeModifier += 0.013; break; // +1.3%
	default: break;
	}

	return track.getBaseLaptime() * laptimeModifier;
}

struct DriverLaptime {
	DriverSkills driver;
	double laptime{};
	DriverStrategy strategy;
	double total_time{};
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

	RaceEnvironment track;


	std::vector<DriverLaptime> DriversLaptime{};

	for (const auto& team : teams) {
		for (const auto& driverSkill : team.getDrivers()) {
			DriverLaptime temp;
			temp.driver = driverSkill;
			temp.strategy;
			temp.laptime = 0;
			temp.total_time = 0;
			DriversLaptime.push_back(temp);
		}
	}

	for (int lap{ 0 }; lap < 90; ++lap) {
		for (std::size_t i{ 0 }; i < DriversLaptime.size(); ++i) {
			try {
				double tireDegradationpPerLap = calculateTireWear(DriversLaptime[i].strategy.getCurrentTire(), DriversLaptime[i].strategy.getTireMode(), DriversLaptime[i].strategy.getTireCondition(), 30, track.getAbrasivenessAsphalt());
				double currentTireCondition = DriversLaptime[i].strategy.getTireCondition();
				currentTireCondition += tireDegradationpPerLap * (1.5 - 0.005 * DriversLaptime[i].driver.getTyreManagement());
				if (currentTireCondition > 100.0) {
					throw std::invalid_argument("Tire puncture!");
				}
				DriversLaptime[i].strategy.setTireCondition(currentTireCondition);

				DriversLaptime[i].strategy.setTireLaps(DriversLaptime[i].strategy.getTireLaps() + 1);

				double laptime = calculateCurrentLaptime(track, DriversLaptime[i].strategy, DriversLaptime[i].strategy.getTireCondition(), track.getWeatherCondition());

				DriversLaptime[i].laptime = laptime;

				DriversLaptime[i].total_time += laptime;

			}

			catch (const std::exception& e) {
				std::cerr << "\n\nError (lap " << lap + 1 << "): " << e.what() << "| Driver: " << DriversLaptime[i].driver.getDriverSurname() << "\n";
				return 1;
			}
		}

		std::cout << "\n------------------------------------\nLAP " << lap + 1 << ":\n";

		std::sort(DriversLaptime.begin(), DriversLaptime.end(), [](const DriverLaptime& a, const DriverLaptime& b) {
			return a.total_time < b.total_time;});



		for (std::size_t i{ 0 }; i < DriversLaptime.size(); ++i) {
			unsigned int hours{ static_cast<unsigned int>(DriversLaptime[i].total_time / 3600) };

			unsigned int minutes{ static_cast<unsigned int>(DriversLaptime[i].laptime / 60) };
			unsigned int total_minutes{ static_cast<unsigned int>((DriversLaptime[i].total_time - hours * 3600) / 60) };

			unsigned int seconds{ static_cast<unsigned int>(DriversLaptime[i].laptime - (minutes * 60)) };
			unsigned int total_seconds{ static_cast<unsigned int>(DriversLaptime[i].total_time - (total_minutes * 60)) };

			unsigned int miliseconds{ static_cast<unsigned int>((DriversLaptime[i].laptime - (minutes * 60) - seconds) * 1000) };
			std::cout << "\n" << i + 1 << ". " << DriversLaptime[i].driver.getDriverSurname() << " | " << ": "
				<< minutes << ":" << seconds << "." << ((miliseconds < 10) ? "00" : ((miliseconds < 100) ? "0" : "")) << miliseconds
				<< " | Total time: " << hours << ":" << (total_minutes < 10 ? "0" : "") << total_minutes << ":" << (total_seconds < 10 ? "0" : "")
				<< total_seconds;
		}
	}

	return 0;
}



/*unsigned int minutes{static_cast<unsigned int>(laptime / 60)};

unsigned int seconds{ static_cast<unsigned int>(laptime - (minutes * 60)) };

unsigned int miliseconds{ static_cast<unsigned int>((laptime - (minutes * 60) - seconds) * 1000) };

std::cout << "\n Lap " << i + 1 << ": " << minutes << ":" << seconds << "." << ((miliseconds < 10) ? "00" : ((miliseconds < 100) ? "0" : "")) << miliseconds;
*/