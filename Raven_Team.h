#ifndef RAVEN_TEAM_H
#define RAVEN_TEAM_H
//-----------------------------------------------------------------------------
//
//  Name:   Raven_Team.h
//
//  Author: BLACKBURN Mathieu & BRANGER Mathias & CROUZET Matthieu & ELLAPIN Jordan & MACE Quentin
//
//  Desc:
//-----------------------------------------------------------------------------
#include <list>

#include "Raven_Bot.h"
#include "Raven_Game.h"

class Raven_Team
{
public:

	enum { BLACK, BLUE, GREEN, GREY, ORANGE, RED, WHITE, YELLOW };
	Raven_Team(int id, Raven_Game* game);

	void AddTeamMate(Raven_Bot* bot);
	void RemoveTeamMate(Raven_Bot* bot);

	void AddDroppedWeapon(Vector2D pos);
	void RemoveDroppedWeapon(Vector2D pos);

	static void BrushColor(int id);
	static void PenColor(int id);

	int GetTeamSize() const;
	int GetId() const;
	Raven_Game* GetWorld() const;

	void Update();

	static const int MAX_TEAMS = 8;

private:
	std::list<Raven_Bot*> m_bots;
	std::list<Vector2D> m_DroppedWeapons;

	int m_id;
	Raven_Game* m_pWorld;
};

#endif

