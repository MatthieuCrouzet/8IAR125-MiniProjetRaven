#include "Trigger_WeaponDrop.h"
#include "lua/Raven_Scriptor.h"
#include "Raven_ObjectEnumerations.h"
#include "Raven_Team.h"
#include "Raven_Bot.h"
#include "Raven_WeaponSystem.h"


Trigger_WeaponDrop::Trigger_WeaponDrop(Vector2D pos, unsigned int weaponType, int ammo, int team, Raven_Game* world) :
	Trigger<Raven_Bot>(BaseGameEntity::GetNextValidID()),
	m_WeaponType(weaponType),
	m_Ammo(ammo),
	m_Team(team),
	m_pWorld(world)
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
{
	if (!m_pWorld->IsTeamMode())
	{
		SetToBeRemovedFromGame();
	}
}

void Trigger_WeaponDrop::Try(Raven_Bot* pBot)
{
	if (m_pWorld->IsTeamMode()) 
	{
		if (this->isActive() && pBot->GetTeam()->GetId() == m_Team && this->isTouchingTrigger(pBot->Pos(), pBot->BRadius()))
		{
			pBot->GetWeaponSys()->AddWeapon(EntityType());
			pBot->GetTeam()->RemoveDroppedWeapon(m_vPosition);
			SetToBeRemovedFromGame();
		}
	}
}


void Trigger_WeaponDrop::Render()
 {
	if (isActive())
	{
		gdi->BlackPen();
		Raven_Team::BrushColor(m_Team);
		int sz = 5;
		gdi->Rect(Pos().x - sz, Pos().y - sz, Pos().x + sz + 1, Pos().y + sz + 1);
		//gdi->Circle(m_vPosition, 5);
	}
}
