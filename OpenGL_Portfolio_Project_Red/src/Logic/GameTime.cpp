#include "GameTime.hpp"

GameTime::GameTime(){
	this->timer = new boost::timer();
	this->timer->restart();
	this->stopValue = 0;
}
GameTime::GameTime(const GameTime& copyObj){

}

GameTime::~GameTime(){
	delete this->timer;
	this->timer = 0;
}

void GameTime::Start(){
	this->timer->restart();
	this->stopValue = 0;
}

void GameTime::Stop(){
	this->stopValue = this->timer->elapsed();
}

double GameTime::Elapsed() const {
	if (this->stopValue == 0) {
		return this->timer->elapsed();
	}
	else {
		return this->stopValue;
	}
}