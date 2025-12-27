#pragma once

#include "SFML/System/Time.hpp"
#include <vector>
#include <unordered_set>

class Timekeeper
{
public:
	enum Period {
		Day,
		Night,
		Dawn,
		Dusk,
		Noon,
		Midnight
	};

public:
	Timekeeper();
	
	void update(sf::Time dt);

	sf::Time timeUntil(Period s);

	static std::vector<Period> getTimeperiod();
	

private:
	static sf::Time mCycleLength;
	static sf::Time mCurrentTime;
	
	static std::vector<Timekeeper::Period> mActive;

	//Proportions from 0.0 - 1.0
	//Day + Night = 1
	//Dawn, Dusk, Noon, and Midnight overlap with day and night
	double mDay;
	double mNight;
	double mDawn;
	double mDusk;
	double mNoon;
	double mMidnight;

};

