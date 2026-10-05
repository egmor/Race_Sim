#include <iostream>
#include <string>

enum class TireType {Soft, Medium, Hard, Intermediate, Wet};

class Car {
private:
	unsigned int carWeight;
	unsigned int carHP;

	static void checkCarWeight(unsigned int weight) {
		if (weight < 768 || weight > 795) {throw std::invalid_argument("Weight of F1 car cannot be over than 795kg or less than 768kg");}
	}

	static void checkCarHP(unsigned int horsepower) {
		if (horsepower < 950 || horsepower > 1020) {throw std::invalid_argument("Horsepower of F1 car cannot be over than 1020 h.p. or less than 950 h.p.");}
	}

public:
	//default constractor
	Car() : carWeight(900), carHP(1000) {};

	//constractor with parametrs
	Car(unsigned int weight, unsigned int horsepower) :
		carWeight(weight), carHP(horsepower) {
		setCarWeight(weight);
		setCarHP(horsepower);
	}

	void setCarWeight(unsigned int &weight) {
		checkCarWeight(weight);
		carWeight = weight;
	}

	void setCarHP(unsigned int horsepower) {
		checkCarHP(horsepower);
		carHP = horsepower;
	}

	unsigned int getCarWeight() const { return carWeight; }
	unsigned int getCarHP() const { return carHP; }

	~Car() {};
};

class Driver : public Car {
private:
	std::string driverName;
	std::string driverSurname;
	unsigned int driverAge;
	unsigned int driverWeight;
	unsigned int driverNumber;

	void checkDriverNSN(const std::string& name) {
		if (name.size() < 2 || name.size() > 20) { throw std::invalid_argument("Driver name/surname must be between 2 and 20 characters"); }
	}

	void checkDriverAge(unsigned int age) {
		if (age < 18 || age > 45) { throw std::invalid_argument("Driver age must be between 18 and 45"); }
	}

	void checkDriverWeight(unsigned int weight) {
		if (weight < 50 || weight > 90) { throw std::invalid_argument("Driver weight must be between 50 and 90 kg"); }
	}

	void checkDriverNumber(unsigned int number) {
		if (number < 1 || number > 99) { throw std::invalid_argument("Driver number must be between 1 and 99"); }
	}

public:
	//default constractor
	Driver() :
		Car(), driverName("Unknown"), driverSurname("Unknown"), driverAge(18), driverWeight(75), driverNumber(99) {};

	//constractor with parametrs
	Driver(unsigned int carWeight, unsigned int carHP, std::string name, std::string surname, unsigned int age, unsigned int weight, unsigned int number) :
		Car(carWeight, carHP), driverName(name), driverSurname(surname), driverAge(age), driverWeight(weight), driverNumber(number) {
		setDriverName(name);
		setDriverSurname(surname);
		setDriverAge(age);
		setDriverWeight(weight);
		setDriverNumber(number);
	};

	void setDriverName(const std::string& name) {
		checkDriverNSN(name);
		driverName = name;
	}

	void setDriverSurname(const std::string& surname) {
		checkDriverNSN(surname);
		driverSurname = surname;
	}	

	void setDriverAge(unsigned int age) {
		checkDriverAge(age);
		driverAge = age;
	};

	void setDriverWeight(unsigned int weight) {
		checkDriverWeight(weight);
		driverWeight = weight;
	};

	void setDriverNumber(unsigned int number) {
		checkDriverNumber(number);
		driverNumber = number;
	}

	std::string getDriverName() const { return driverName; }
	std::string getDriverSurname() const { return driverSurname; }
	unsigned int getDriverAge() const { return driverAge; }
	unsigned int getDriverWeight() const { return driverWeight; }
	unsigned int getDriverNumber() const { return driverNumber; }

	~Driver() {};
};