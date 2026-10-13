#include "strategy.h"
#include <iostream>

namespace changeStrategy {
	EngineMode changeEngineMode() {
		int choice{};
		std::cout << "\nSelect a new engine operation mode:\n"
			<< "1. Push\n"
			<< "2. Standard\n"
			<< "3. Economy\n\n"
			<< "Enter the correct number: ";

		std::cin >> choice;
		EngineMode selectMode{};

		switch (choice) {
		case 1: selectMode = EngineMode::Push; break;
		case 2: selectMode = EngineMode::Standard; break;
		case 3: selectMode = EngineMode::Economy; break;
		default: selectMode = EngineMode::Standard; break;
		}

		return selectMode;
	}

	BoostMode changeBoostMode() {
		int choice{};
		std::cout << "\nSelect a new boost operation mode:\n"
			<< "1. Overtake\n"
			<< "2. HotLap\n"
			<< "3. Medium\n"
			<< "4. None\n\n"
			<< "Enter the correct number: ";

		std::cin >> choice;
		BoostMode selectMode{};

		switch (choice) {
		case 1: selectMode = BoostMode::Overtake; break;
		case 2: selectMode = BoostMode::HotLap; break;
		case 3: selectMode = BoostMode::Medium; break;
		case 4: selectMode = BoostMode::None; break;
		default: selectMode = BoostMode::Medium; break;
		}

		return selectMode;
	}

	DriverRisk changeDriverRisk() {
		int choice{};
		std::cout << "\nSelect a new driver risk level:\n"
			<< "1. Qualifying\n"
			<< "2. Push\n"
			<< "3. Race\n"
			<< "4. Safe\n\n"
			<< "Enter the correct number: ";
		std::cin >> choice;
		DriverRisk selectRisk{};
		switch (choice) {
		case 1: selectRisk = DriverRisk::Qualifying; break;
		case 2: selectRisk = DriverRisk::Push; break;
		case 3: selectRisk = DriverRisk::Race; break;
		case 4: selectRisk = DriverRisk::Safe; break;
		default: selectRisk = DriverRisk::Race; break;
		}
		return selectRisk;
	}

	TireMode changeTireMode() {
		int choice{};
		std::cout << "\nSelect a new tire mode:\n"
			<< "1. Full pace\n"
			<< "2. Medium\n"
			<< "3. Keep\n\n"
			<< "Enter the correct number: ";
		std::cin >> choice;
		TireMode selectMode{};
		switch (choice) {
		case 1: selectMode = TireMode::FullPace; break;
		case 2: selectMode = TireMode::Medium; break;
		case 3: selectMode = TireMode::Keep; break;
		default: selectMode = TireMode::Medium; break;
		}
		return selectMode;
	}

	TireType changeNextTire() {
		int choice{};
		std::cout << "\nSelect a new next tire type:\n"
			<< "1. Soft\n"
			<< "2. Medium\n"
			<< "3. Hard\n"
			<< "4. Intermediate\n"
			<< "5. Wet\n\n"
			<< "Enter the correct number: ";
		std::cin >> choice;
		TireType selectTire{};
		switch (choice) {
		case 1: selectTire = TireType::Soft; break;
		case 2: selectTire = TireType::Medium; break;
		case 3: selectTire = TireType::Hard; break;
		case 4: selectTire = TireType::Intermediate; break;
		case 5: selectTire = TireType::Wet; break;
		default: selectTire = TireType::Medium; break;
		}
		return selectTire;
	}
}

void DriverStrategy::checkTireLaps(unsigned int tireLaps) {
		if (tireLaps > 73) { throw std::invalid_argument("Incorrect data"); }
	}

void DriverStrategy::checkTireCondition(unsigned int tireCondition) {
	if (tireCondition > 100) { throw std::invalid_argument("incorrent data"); }
}


DriverStrategy::DriverStrategy() : engineMode(EngineMode::Standard), boostMode(BoostMode::Medium), driverRisk(DriverRisk::Race),
	tireMode(TireMode::Medium), currentTire(TireType::Medium), nextTire(TireType::Hard), tireLaps(0), tireCondition(0) {
}

DriverStrategy::DriverStrategy(EngineMode eMode, BoostMode bMode, DriverRisk dRisk, TireMode tMode, TireType cTire, TireType nTire, unsigned int laps, unsigned int tireCond) :
	engineMode(eMode), boostMode(bMode), driverRisk(dRisk), tireMode(tMode), currentTire(cTire), nextTire(nTire), tireLaps(laps), tireCondition(tireCond) {
	checkTireLaps(laps);
	checkTireCondition(tireCond);
}

void DriverStrategy::setEngineMode(EngineMode eMode) { engineMode = eMode; }
void DriverStrategy::setBoostMode(BoostMode bMode) { boostMode = bMode; }
void DriverStrategy::setDriverRisk(DriverRisk dRisk) { driverRisk = dRisk; }
void DriverStrategy::setTireMode(TireMode tMode) { tireMode = tMode; }
void DriverStrategy::setCurrentTire(TireType cTire) { currentTire = cTire; }
void DriverStrategy::setNextTire(TireType nTire) { nextTire = nTire; }
void DriverStrategy::setTireLaps(unsigned int laps) {
	checkTireLaps(laps);
	tireLaps = laps;
}
void DriverStrategy::setTireCondition(unsigned int cond) {
	checkTireCondition(cond);
	tireCondition = cond;
}

EngineMode DriverStrategy::getEngineMode() const { return engineMode; }
BoostMode DriverStrategy::getBoostMode() const { return boostMode; }
DriverRisk DriverStrategy::getDriverRisk() const { return driverRisk; }
TireMode DriverStrategy::getTireMode() const { return tireMode; }
TireType DriverStrategy::getCurrentTire() const { return currentTire; }
unsigned int DriverStrategy::getTireLaps() const { return tireLaps; }
unsigned int DriverStrategy::getTireCondition() const { return tireCondition; }
