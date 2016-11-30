#ifndef GRENADE_H
#define GRENADE_H
#pragma warning (disable:4786)

/*
	Added class
*/
#include "Raven_Projectile.h"

class Raven_Bot;

class Grenade : public Raven_Projectile
{
private:

	//time before the grenade explosed
	double	m_timeBeforeBlast;

	//the radius of damage, once the grenade has explosed
	double    m_dBlastRadius;

	//this is used to render the splash when the grenade exploses
	double    m_dCurrentBlastRadius;

	//If the grenade has explosed we test all bots to see if they are within the 
	//blast radius and reduce their health accordingly
	void InflictDamageOnBotsWithinBlastRadius();

	//tests the trajectory of the shell for an impact
	void TestForTimeout();

public:

	Grenade(Raven_Bot* shooter, Vector2D target);

	void Render();

	void Update();

};


#endif