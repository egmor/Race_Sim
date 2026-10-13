#ifndef TRACK_H
#define TRACK_H

enum class TireType { Soft, Medium, Hard, Intermediate, Wet, };
enum class TireMode { FullPace, Medium, Keep, };

struct TireConfig {
	double baseWear;
	double cliffThreshold;
	double cliffMultiplier;
	int optimalTempMin;
	int optimalTempMax;
	double overheatMultiplier;
};

TireConfig getTireConfig(TireType tire);
double calculateTireWear(TireType tire, TireMode mode, double condition, int temperature);

#endif // TRACK_H
