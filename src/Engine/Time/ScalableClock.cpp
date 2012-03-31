#include "ScalableClock.h"

ScalableClock::ScalableClock(const float scale, sf::Uint32 resolution) 
	: TimeScaler(scale), TimeBuffer(0), Scaled(!(scale >= 0.99 && scale <= 1.01)), UpdaterThread(boost::bind(&ScalableClock::UpdateFunction, this))
{

}
void ScalableClock::SetScale(const float scale)
{
	Scaled = scale >= 0.99f && scale <= 1.01f;
	TimeScaler = scale;
}
sf::Uint32 ScalableClock::GetElapsedGameTime()
{
	if (Scaled)
	{
		LockUpdater.Lock();
		sf::Uint32 time = GameClock.GetElapsedTime();
		sf::Uint32 Elapsed =  time - LastUpdate;
		TimeBuffer += static_cast<sf::Uint32>(static_cast<float>(Elapsed) * (TimeScaler - 1.0f));
		LastUpdate = time;
		LockUpdater.Unlock();
		
	}
	//else
	{
		if (TimeBuffer != 0)
			return GameClock.GetElapsedTime() + static_cast<sf::Uint32>(TimeBuffer);
		return GameClock.GetElapsedTime();
	}
}
sf::Uint32 ScalableClock::GetElapsedRealTime() const
{
	return GameClock.GetElapsedTime();
}
void ScalableClock::Reset()
{
	LockUpdater.Lock();
	TimeBuffer = 0;
	Scaled = false;
	TimeScaler = 1.0f;
	LockUpdater.Unlock();
}
bool ScalableClock::IsScaled()
{
	return Scaled;
}
void ScalableClock::UpdateFunction()
{
	//I forget what goes here
	sf::Sleep(Resolution);
}
ScalableClock::~ScalableClock()
{
	UpdaterThread.Terminate();
	//UpdaterThread.Terminate();
}