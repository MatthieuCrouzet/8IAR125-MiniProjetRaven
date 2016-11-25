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

class Raven_Team
{
public:

	enum { BLACK, BLUE, GREEN, GREY, ORANGE, RED, WHITE, YELLOW };
	Raven_Team(int id);

	void AddTeamMate(Raven_Bot* bot);
	void RemoveTeamMate(Raven_Bot* bot);

	static void BrushColor(int id);
	static void PenColor(int id);

	int GetTeamSize() const;
	int GetId() const;

	void Update();

	static const int MAX_TEAMS = 8;

private:
	std::list<Raven_Bot*> m_bots;

	int m_id;

};

#endif

