#include "Trigger_WeaponDrop.h"
#include "lua/Raven_Scriptor.h"
#include "Raven_ObjectEnumerations.h"
#include "Raven_Team.h"
#include "Raven_Bot.h"
#include "Raven_WeaponSystem.h"


Trigger_WeaponDrop::Trigger_WeaponDrop(Vector2D pos, unsigned int weaponType, int ammo, int team) :
	Trigger<Raven_Bot>(BaseGameEntity::GetNextValidID()),
	m_WeaponType(weaponType),
	m_Ammo(ammo),
	m_Team(team)
{
		SetPos(pos);
		AddCircularTriggerRegion(pos, 5);

		//create the vertex buffer for the rocket shape
		const int NumRocketVerts = 8;
		const Vector2D rip[NumRocketVerts] = { Vector2D(0, 3),
			Vector2D(1, 2),
			Vector2D(1, 0),
			Vector2D(2, -2),
			Vector2D(-2, -2),
			Vector2D(-1, 0),
			Vector2D(-1, 2),
			Vector2D(0, 3) };

		for (int i = 0; i<NumRocketVerts; ++i)
		{
			m_vecRLVB.push_back(rip[i]);
		}
}

void Trigger_WeaponDrop::Update()
{}

void Trigger_WeaponDrop::Try(Raven_Bot* pBot)
{
	if (this->isActive() && pBot->GetTeam()->GetId() == m_Team && this->isTouchingTrigger(pBot->Pos(), pBot->BRadius()))
		{
		pBot->GetWeaponSys()->AddWeapon(EntityType());
		SetToBeRemovedFromGame();
		}
}

void Trigger_WeaponDrop::Render()
 {
	if (isActive())
		 {
		gdi->PinkPen();
		gdi->BlackBrush();
		gdi->Circle(m_vPosition, 5);
		}
	}
