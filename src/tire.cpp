#include "tire.h"

TireConfig getTireConfig(TireType tire) {
	switch (tire) {
	case TireType::Soft:
		return { 3.5, 70.0, 1.75, 20, 40, 1.5 };
	case TireType::Medium:
		return { 2.0, 75.0, 1.80, 25, 45, 1.4 };
	case TireType::Hard:
		return { 1.0, 80.0, 2.00, 35, 55, 1.3 };
	case TireType::Intermediate:
		return { 2.5, 65.0, 2.20, 15, 30, 2.5 };
	case TireType::Wet:
		return { 3.0, 60.0, 2.50, 10, 25, 3.5 };
	default:
		return { 2.0, 75.0, 1.80, 25, 45, 1.4 };
	}
}

double calculateTireWear(TireType tire, TireMode mode, double condition, int temperature, double abrasiveness) {
	TireConfig config = getTireConfig(tire);

	double baseTCPL = 1.0;

	if (condition < 15.0) {
		baseTCPL *= 1.2;
	}
	else if (condition >= config.cliffThreshold) {
		baseTCPL *= config.cliffMultiplier;
	}

	if (mode == TireMode::FullPace) {
		baseTCPL *= 1.6;
	}
	else if (mode == TireMode::Keep) {
		baseTCPL *= 0.65;
	}

	if (temperature < config.optimalTempMin) {
		baseTCPL *= 1.2;
	}
	else if (temperature > config.optimalTempMax) {
		baseTCPL *= config.overheatMultiplier;
	}

	return config.baseWear * baseTCPL * (0.5 + abrasiveness);
}