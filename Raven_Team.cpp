#include "Raven_Team.h"
#include "misc/Cgdi.h"

Raven_Team::Raven_Team(int id, Raven_Game* game) : 
	m_id(id),
	m_pWorld(game)
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

void Raven_Team::AddDroppedWeapon(Vector2D pos) {
	m_DroppedWeapons.push_back(pos);
}

void Raven_Team::RemoveDroppedWeapon(Vector2D pos) {
	m_DroppedWeapons.remove(pos);
	
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

void Raven_Team::PenColor(int id) {
	switch (id) {
	case Raven_Team::BLACK:
		gdi->BlackPen();
		break;
	case Raven_Team::BLUE:
		gdi->BluePen();
		break;
	case Raven_Team::GREEN:
		gdi->GreenPen();
		break;
	case Raven_Team::GREY:
		gdi->GreyPen();
		break;
	case Raven_Team::ORANGE:
		gdi->OrangePen();
		break;
	case Raven_Team::RED:
		gdi->RedPen();
		break;
	case Raven_Team::WHITE:
		gdi->WhitePen();
		break;
	case Raven_Team::YELLOW:
		gdi->YellowPen();
		break;
	default:
		gdi->BrownPen();
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

Raven_Game* Raven_Team::GetWorld() const 
{ 
	return m_pWorld; 
}


void Raven_Team::Update()
{
}
