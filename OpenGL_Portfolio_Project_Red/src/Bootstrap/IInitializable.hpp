#ifndef _IINITIALIZABLE_H

#include "../Logic/GameTime.hpp"

// Filename: IInitializable.hpp

// Interface used for decrypting 
// World Game Class which aggregate 
// Graphics, Sound, Input and Logic systems

#define _IINITIALIZABLE_H

class IInitializable {
public:
	virtual void Exit() = 0;
	virtual void ResetTime() = 0;
	virtual void Run() = 0;
	virtual void Tick() = 0;
	virtual ~IInitializable() {}
protected:
	virtual void Initialize() = 0;
	virtual void LoadContent() = 0;
	virtual void UnloadContent() = 0;
	virtual void Update(GameTime*) = 0;
	virtual void Draw(GameTime*) = 0;
	virtual void Release() = 0;
};

#endif