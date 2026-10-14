#include "track.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <istream> // ИСПРАВЛЕНО: Явное подключение потока ввода

// ИСПРАВЛЕНО: Все проверки теперь возвращают проверенные типы данных
std::string Track::checkTrackName(std::string name) {
	if (name.size() < 2 || name.size() > 50) { throw std::invalid_argument("Track name must be between 2 and 50 characters"); }
	return name;
}
double Track::checkTrackLength(double length) {
	if (length < 3.3 || length > 7.0) { throw std::invalid_argument("Track length must be between 3.3 and 7.0 kilometers"); }
	return length;
}
unsigned int Track::checkNumberOfCorners(unsigned int corners) {
	if (corners < 5 || corners > 25) { throw std::invalid_argument("Number of corners must be between 5 and 25"); }
	return corners;
}
double Track::checkPitlaneLost(double lost) {
	if (lost < 10.0 || lost > 40.0) { throw std::invalid_argument("Pitlane lost time must be between 10.0 and 40.0 seconds"); }
	return lost;
}
unsigned int Track::checkTrackTemperature(unsigned int temperature) {
	if (temperature < 15 || temperature > 60) { throw std::invalid_argument("Track temperature must be between 15 and 60 degrees Celsius"); }
	return temperature;
}
double Track::checkAbrasivenessAsphalt(double abrasiveness) {
	if (abrasiveness < 0.0 || abrasiveness > 1.0) { throw std::invalid_argument("Abrasiveness of asphalt must be between 0.0 and 1.0"); }
	return abrasiveness;
}
double Track::checkBaseLaptime(double laptime) {
	if (laptime < 60.0 || laptime > 120.0) { throw std::invalid_argument("Base laptime must be between 60.0 and 120.0 seconds"); }
	return laptime;
}

Track::Track() : trackName("Unknown"), condition(RoadCondition::Dry), trackLength(5.0), numberOfCorners(15), pitlaneLost(20.0),
trackTemperature(30), baseLaptime(90.0), abrasivenessAsphalt(0.5) {
}

// ИСПРАВЛЕНО: Безопасный конструктор через список инициализации с вызовом проверок
Track::Track(std::string name, RoadCondition cond, double length, unsigned int corners, double lost, unsigned int temperature,
	double laptime, double abrasiveness)
	: trackName(checkTrackName(name)),
	condition(cond),
	trackLength(checkTrackLength(length)),
	numberOfCorners(checkNumberOfCorners(corners)),
	pitlaneLost(checkPitlaneLost(lost)),
	trackTemperature(checkTrackTemperature(temperature)),
	baseLaptime(checkBaseLaptime(laptime)),
	abrasivenessAsphalt(checkAbrasivenessAsphalt(abrasiveness)) {
}

void Track::setTrackName(std::string_view name) { trackName = checkTrackName(std::string(name)); }
void Track::setTrackCondition(RoadCondition cond) { condition = cond; }
void Track::setTrackLength(double length) { trackLength = checkTrackLength(length); }
void Track::setNumberOfCorners(unsigned int corners) { numberOfCorners = checkNumberOfCorners(corners); }
void Track::setPitlaneLost(double lost) { pitlaneLost = checkPitlaneLost(lost); }
void Track::setTrackTemperature(unsigned int temperature) { trackTemperature = checkTrackTemperature(temperature); }
void Track::setBaseLaptime(double laptime) { baseLaptime = checkBaseLaptime(laptime); }
void Track::setAbrasivenessAsphalt(double abrasiveness) { abrasivenessAsphalt = checkAbrasivenessAsphalt(abrasiveness); }

double Track::getBaseLaptime() const { return baseLaptime; }
RoadCondition Track::getRoadCondition() const { return condition; }
unsigned int Track::getTrackTemperature() const { return trackTemperature; }
double Track::getAbrasivenessAsphalt() const { return abrasivenessAsphalt; }

// ИСПРАВЛЕНО: Убрано ключевое слово friend (оно пишется только в .h)
std::istream& operator>>(std::istream& is, Track& track) {
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
		if (is.good()) is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return is;
}

void Track::print() const {
	std::cout << "Track: " << trackName << "  \nCondition: " << static_cast<int>(condition)
		<< "  \nLength: " << trackLength << " km  \nCorners: " << numberOfCorners
		<< "  \nPitlane lost: " << pitlaneLost << " s  \nTemperature: " << trackTemperature
		<< " C  \nBase laptime: " << baseLaptime << " s  \nAbrasiveness: " << abrasivenessAsphalt << "\n";
}

// ИСПРАВЛЕНО: Имя класса изменено для соответствия ООП-логике
RaceEnvironment::RaceEnvironment() : Track(), weather(WeatherCondition::Sunny) {}

RaceEnvironment::RaceEnvironment(std::string name, RoadCondition cond, double length, unsigned int corners, double lost, unsigned int temperature,
	double laptime, double abrasiveness, WeatherCondition wCond) :
	Track(name, cond, length, corners, lost, temperature, laptime, abrasiveness), weather(wCond) {
}

void RaceEnvironment::setWeatherCondition(WeatherCondition wCond) { weather = wCond; }
WeatherCondition RaceEnvironment::getWeatherCondition() const { return weather; }

void RaceEnvironment::print() const {
	Track::print();
	std::cout << "Weather Condition: " << static_cast<int>(weather) << "\n";
}