#ifndef STRATEGY_H
#define STRATEGY_H

#include "tire.h"

enum class EngineMode { Push, Standard, Economy, };

enum class BoostMode { Overtake, HotLap, Medium, None, };

enum class DriverRisk { Qualifying, Push, Race, Safe, };

namespace changeStrategy {
	EngineMode changeEngineMode();
	BoostMode changeBoostMode();
	DriverRisk changeDriverRisk();
	TireMode changeTireMode();
	TireType changeNextTire();
}

class DriverStrategy {
private:
	EngineMode engineMode;
	BoostMode boostMode;
	DriverRisk driverRisk;
	TireMode tireMode;

	TireType currentTire;
	TireType nextTire;
	unsigned int tireLaps;
	unsigned int tireCondition; //0 to 100 (0 - new tire, 100 - death tire)

	void checkTireLaps(unsigned int tireLaps);
	void checkTireCondition(unsigned int tireCondition);

public:

	DriverStrategy();

	DriverStrategy(EngineMode eMode, BoostMode bMode, DriverRisk dRisk, TireMode tMode, TireType cTire,
		TireType nTire, unsigned int laps, unsigned int tireCond);

	void setEngineMode(EngineMode eMode);
	void setBoostMode(BoostMode bMode);
	void setDriverRisk(DriverRisk dRisk);
	void setTireMode(TireMode tMode);
	void setCurrentTire(TireType cTire);
	void setNextTire(TireType nTire);
	void setTireLaps(unsigned int laps);
	void setTireCondition(unsigned int cond);

	EngineMode getEngineMode() const;
	BoostMode getBoostMode() const;
	DriverRisk getDriverRisk() const;
	TireMode getTireMode() const;
	TireType getCurrentTire() const;
	unsigned int getTireLaps() const;
	unsigned int getTireCondition() const;

};

#endif // STRATEGY_H
