#include "Raven_Team.h"


Raven_Team::Raven_Team(int color) : m_color(color)
{
}

void Raven_Team::AddTeamMate(Raven_Bot* bot) {
	m_bots.push_back(bot);
	bot->SetTeam(this);
	
}

void Raven_Team::RemoveTeamMate(Raven_Bot* bot) {
	m_bots.remove(bot);
	bot->SetTeam(this);

}

int Raven_Team::GetTeamSize() const
{
	return m_bots.size();
}

int Raven_Team::GetColor() const
{
	return m_color;
}


void Raven_Team::Update()
{
}
