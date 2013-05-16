#ifndef _GAMETIME_H

#include <boost\timer.hpp>

// Filename: IInitializable.hpp

// Interface used for decrypting 
// World Game Class which aggregate 
// Graphics, Sound, Input and Logic systems

#define _GAMETIME_H

class GameTime {
public:
	GameTime();
	GameTime(const GameTime& copyObj);
	~GameTime();
	void Start();
	void Stop();
	double Elapsed() const;
private:
	boost::timer *timer;
	double stopValue;
};

#endif