#ifndef TRACK_H
#define TRACK_H

#include <string>
#include <string_view>
#include <iostream> // Важно для istream

enum class RoadCondition { Dry, Wet, Damp, Drying, Flooded, };
enum class WeatherCondition { Sunny, Cloudy, LightRain, Rainy, Stormy, };

class Track {
private:
	std::string trackName;
	RoadCondition condition;
	double trackLength;
	unsigned int numberOfCorners;
	double pitlaneLost;
	unsigned int trackTemperature;
	double baseLaptime;
	double abrasivenessAsphalt;

	// ИСПРАВЛЕНО: Функции теперь возвращают проверенное значение для списка инициализации
	static std::string checkTrackName(std::string name);
	static double checkTrackLength(double length);
	static unsigned int checkNumberOfCorners(unsigned int corners);
	static double checkPitlaneLost(double lost);
	static unsigned int checkTrackTemperature(unsigned int temperature);
	static double checkAbrasivenessAsphalt(double abrasiveness);
	static double checkBaseLaptime(double laptime);

public:
	Track();
	Track(std::string name, RoadCondition cond, double length, unsigned int corners, double lost,
		unsigned int temperature, double laptime, double abrasiveness);

	void setTrackName(std::string_view name);
	void setTrackCondition(RoadCondition cond);
	void setTrackLength(double length);
	void setNumberOfCorners(unsigned int corners);
	void setPitlaneLost(double lost);
	void setTrackTemperature(unsigned int temperature);
	void setBaseLaptime(double laptime);
	void setAbrasivenessAsphalt(double abrasiveness);

	double getBaseLaptime() const;
	RoadCondition getRoadCondition() const;
	unsigned int getTrackTemperature() const;
	double getAbrasivenessAsphalt() const;

	friend std::istream& operator>>(std::istream& is, Track& track);
	void print() const;
};

// Класс переименован в RaceEnvironment, чтобы убрать путаницу с условиями трассы
class RaceEnvironment : public Track {
private:
	WeatherCondition weather;

public:
	RaceEnvironment();
	RaceEnvironment(std::string name, RoadCondition cond, double length, unsigned int corners, double lost,
		unsigned int temperature, double laptime, double abrasiveness, WeatherCondition wCond);

	void setWeatherCondition(WeatherCondition wCond);
	WeatherCondition getWeatherCondition() const;
	void print() const;
};
#endif //TRACK_H