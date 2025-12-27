#include "Timekeeper.h"
#include <algorithm>
#include <cmath>

static double norm01(double v)
{
	v = std::fmod(v, 1.0);
	if (v < 0.0) v += 1.0;
	return v;
}

static bool inInterval(double t, double a, double b)
{
	// Interval is [a, b) on a circular domain [0,1)
	a = norm01(a);
	b = norm01(b);
	t = norm01(t);

	if (a <= b) {
		return t >= a && t < b;
	}
	// wrapped interval
	return t >= a || t < b;
}

sf::Time Timekeeper::mCycleLength(sf::seconds(2 * 60)); //2 min cycles for testing, change to 10 min later
sf::Time Timekeeper::mCurrentTime(sf::seconds(0));
std::vector<Timekeeper::Period> Timekeeper::mActive;

Timekeeper::Timekeeper()
	: mDay(0.5)
	, mNight(0.5)
	, mDawn(0.05)
	, mDusk(0.05)
	, mNoon(0.01)
	, mMidnight(0.01)
{
}

void Timekeeper::update(sf::Time dt) {
	mCurrentTime += dt;
	if (mCurrentTime >= mCycleLength) {
		mCurrentTime -= mCycleLength;
	}
	const double cycleSec = std::max(1e-6, double(mCycleLength.asSeconds()));
	const double t = norm01(mCurrentTime.asSeconds() / cycleSec);

	const double dayStart = 0.25;
	const double dayEnd = 0.75;
	const double dayCenter = 0.5;

	// compute overlap windows (start..end)
	auto window = [](double center, double width) -> std::pair<double, double> {
		double a = norm01(center - width * 0.5);
		double b = norm01(center + width * 0.5);
		return { a, b };
		};

	auto dawnW = window(dayStart, mDawn);
	auto duskW = window(dayEnd, mDusk);
	auto noonW = window(dayCenter, mNoon);
	auto midnightW = window(0.0, mMidnight);

	mActive.clear();

	// Day: middle half [dayStart, dayEnd)
	if (inInterval(t, dayStart, dayEnd)) {
		mActive.push_back(Day);
	}

	// Night: first quarter [0, dayStart) and last quarter [dayEnd, 1)
	if (inInterval(t, 0.0, dayStart) || inInterval(t, dayEnd, 1.0)) {
		mActive.push_back(Night);
	}

	// Overlaps
	if (inInterval(t, dawnW.first, dawnW.second)) {
		mActive.push_back(Dawn);
	}
	if (inInterval(t, duskW.first, duskW.second)) {
		mActive.push_back(Dusk);
	}
	if (inInterval(t, noonW.first, noonW.second)) {
		mActive.push_back(Noon);
	}
	if (inInterval(t, midnightW.first, midnightW.second)) {
		mActive.push_back(Midnight);
	}
}

sf::Time Timekeeper::timeUntil(Period s)
{
	const double cycleSec = std::max(1e-6, double(mCycleLength.asSeconds()));
	const double t = norm01(mCurrentTime.asSeconds() / cycleSec);

	// canonical key points (normalized)
	const double dayStart = 0.25;    // start of middle half (day)
	const double dayEnd = 0.75;      // end of middle half (day)
	const double dayCenter = 0.5;

	// compute centers and starts for overlaps
	const double dawnCenter = dayStart;
	const double duskCenter = dayEnd;
	const double noonCenter = dayCenter;
	const double midnightCenter = 0.0; // wrap-around center

	auto makeStart = [](double center, double width)->double {
		return norm01(center - width * 0.5);
		};

	std::vector<double> candidates;

	switch (s) {
	case Day:
		candidates.push_back(dayStart);
		break;
	case Night:
		// Night begins at 0.0 (first quarter) and again at dayEnd (start of last quarter)
		candidates.push_back(0.0);
		candidates.push_back(dayEnd);
		break;
	case Dawn:
		candidates.push_back(makeStart(dawnCenter, mDawn));
		break;
	case Dusk:
		candidates.push_back(makeStart(duskCenter, mDusk));
		break;
	case Noon:
		candidates.push_back(makeStart(noonCenter, mNoon));
		break;
	case Midnight:
		candidates.push_back(makeStart(midnightCenter, mMidnight));
		break;
	default:
		break;
	}

	// find smallest positive forward delta (in normalized units)
	double bestDelta = 1.0; // max one full cycle
	for (double cand : candidates) {
		double delta = norm01(cand - t);
		if (delta < bestDelta) bestDelta = delta;
	}

	// If no candidates (shouldn't happen), return zero
	if (candidates.empty()) return sf::Time();

	return sf::seconds(float(bestDelta * cycleSec));
}

std::vector<Timekeeper::Period> Timekeeper::getTimeperiod()
{
	return mActive;
}