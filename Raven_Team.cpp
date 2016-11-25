#include "Raven_Team.h"
#include "misc/Cgdi.h"

Raven_Team::Raven_Team(int id) : m_id(id)
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

void Raven_Team::BrushColor(int id) {
	switch (id) {
	case Raven_Team::BLACK:
		gdi->BlackBrush();
		break;
	case Raven_Team::BLUE:
		gdi->BlueBrush();
		break;
	case Raven_Team::GREEN:
		gdi->GreenBrush();
		break;
	case Raven_Team::GREY:
		gdi->GreyBrush();
		break;
	case Raven_Team::ORANGE:
		gdi->OrangeBrush();
		break;
	case Raven_Team::RED:
		gdi->RedBrush();
		break;
	case Raven_Team::WHITE:
		gdi->WhiteBrush();
		break;
	case Raven_Team::YELLOW:
		gdi->YellowBrush();
		break;
	default:
		gdi->BrownBrush();
	}
}

int Raven_Team::GetTeamSize() const
{
	return m_bots.size();
}

int Raven_Team::GetId() const
{
	return m_id;
}


void Raven_Team::Update()
{
}
