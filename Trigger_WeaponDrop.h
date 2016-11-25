#ifndef WEAPON_DROP_H
#define WEAPON_DROP_H

//-----------------------------------------------------------------------------
//
//  Name:     Trigger_WeaponDrop.h
//
//  Author:     Author: BLACKBURN Mathieu & BRANGER Mathias & CROUZET Matthieu & ELLAPIN Jordan & MACE Quentin
//
//  Desc:     
//-----------------------------------------------------------------------------
#include "Triggers/Trigger.h"
#include "Raven_Bot.h"
#include "Raven_Game.h"

class Trigger_WeaponDrop : public Trigger<Raven_Bot>
{
private:
	//vrtex buffers for rocket shape
	std::vector<Vector2D>         m_vecRLVB;
	std::vector<Vector2D>         m_vecRLVBTrans;

	unsigned int m_WeaponType;
	int m_Ammo;
	int m_Team;
	Raven_Game* m_pWorld;

public :

	Trigger_WeaponDrop(Vector2D pos, unsigned int weapon, int ammo, int team, Raven_Game* world);
	
	void Update();

	//if triggered, this trigger will call the PickupWeapon method of the
	//bot. PickupWeapon will instantiate a weapon of the appropriate type.
	void Try(Raven_Bot* bot);

	//draws a symbol representing the weapon type at the trigger's location
	void Render();

};

#endif