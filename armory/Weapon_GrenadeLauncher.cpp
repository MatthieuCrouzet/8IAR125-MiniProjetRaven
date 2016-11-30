#include "Weapon_GrenadeLauncher.h"
#include "../Raven_Bot.h"
#include "misc/Cgdi.h"
#include "../Raven_Game.h"
#include "../Raven_Map.h"
#include "../lua/Raven_Scriptor.h"
#include "fuzzy/FuzzyOperators.h"


//--------------------------- ctor --------------------------------------------
//-----------------------------------------------------------------------------
GrenadeLauncher::GrenadeLauncher(Raven_Bot*   owner) :

Raven_Weapon(type_grenade_launcher,
script->GetInt("GrenadeLauncher_DefaultRounds"),
script->GetInt("GrenadeLauncher_MaxRoundsCarried"),
script->GetDouble("GrenadeLauncher_FiringFreq"),
script->GetDouble("GrenadeLauncher_IdealRange"),
script->GetDouble("Grenade_MaxSpeed"),
owner)
{
	//setup the vertex buffer
	const int NumWeaponVerts = 8;
	const Vector2D weapon[NumWeaponVerts] = { Vector2D(0, -3),
		Vector2D(6, -3),
		Vector2D(6, -1),
		Vector2D(15, -1),
		Vector2D(15, 1),
		Vector2D(6, 1),
		Vector2D(6, 3),
		Vector2D(0, 3)
	};
	for (int vtx = 0; vtx<NumWeaponVerts; ++vtx)
	{
		m_vecWeaponVB.push_back(weapon[vtx]);
	}

	//setup the fuzzy module
	InitializeFuzzyModule();

}


//------------------------------ ShootAt --------------------------------------
//-----------------------------------------------------------------------------
inline void GrenadeLauncher::ShootAt(Vector2D pos)
{
	if (NumRoundsRemaining() > 0 && isReadyForNextShot())
	{
		//fire off a Grenade!
		m_pOwner->GetWorld()->AddGrenade(m_pOwner, pos);

		m_iNumRoundsLeft--;

		UpdateTimeWeaponIsNextAvailable();

		//add a trigger to the game so that the other bots can hear this shot
		//(provided they are within range)
		m_pOwner->GetWorld()->GetMap()->AddSoundTrigger(m_pOwner, script->GetDouble("GrenadeLauncher_SoundRange"));
	}
}

//---------------------------- Desirability -----------------------------------
//
//-----------------------------------------------------------------------------
double GrenadeLauncher::GetDesirability(double DistToTarget)
{
	if (m_iNumRoundsLeft == 0)
	{
		m_dLastDesirabilityScore = 0;
	}
	else
	{
		//fuzzify distance and amount of ammo
		m_FuzzyModule.Fuzzify("DistToTarget", DistToTarget);
		m_FuzzyModule.Fuzzify("AmmoStatus", (double)m_iNumRoundsLeft);

		m_dLastDesirabilityScore = m_FuzzyModule.DeFuzzify("Desirability", FuzzyModule::max_av);
	}

	return m_dLastDesirabilityScore;
}

//-------------------------  InitializeFuzzyModule ----------------------------
//
//  set up some fuzzy variables and rules
//-----------------------------------------------------------------------------
void GrenadeLauncher::InitializeFuzzyModule()
{
	FuzzyVariable& DistToTarget = m_FuzzyModule.CreateFLV("DistToTarget");

	FzSet& Target_VeryClose = DistToTarget.AddLeftShoulderSet("Target_VeryClose", 0, 20, 100);
	FzSet& Target_Close = DistToTarget.AddTriangularSet("Target_Close", 20, 125, 150);
	FzSet& Target_Medium = DistToTarget.AddTriangularSet("Target_Medium", 125, 125, 300);
	FzSet& Target_Far = DistToTarget.AddTriangularSet("Target_Far", 125, 250, 500);
	FzSet& Target_VeryFar = DistToTarget.AddRightShoulderSet("Target_VeryFar", 250, 350, 1000);

	FuzzyVariable& Desirability = m_FuzzyModule.CreateFLV("Desirability");

	FzSet& VeryDesirable = Desirability.AddRightShoulderSet("VeryDesirable", 75, 100, 125);
	FzSet& HighDesirable = Desirability.AddTriangularSet("HighDesirable", 55, 75, 90);
	FzSet& Desirable = Desirability.AddTriangularSet("Desirable", 25, 55, 75);
	FzSet& LowDesirable = Desirability.AddTriangularSet("LowDesirable", 10, 25, 50);
	FzSet& Undesirable = Desirability.AddLeftShoulderSet("Undesirable", 0, 10, 25);

	FuzzyVariable& AmmoStatus = m_FuzzyModule.CreateFLV("AmmoStatus");

	FzSet& Ammo_Loads = AmmoStatus.AddRightShoulderSet("Ammo_Loads", 12, 30, 100);
	FzSet& Ammo_High = AmmoStatus.AddTriangularSet("Ammo_High", 8, 12, 40);
	FzSet& Ammo_Medium = AmmoStatus.AddTriangularSet("Ammo_Medium", 2, 8, 15);
	FzSet& Ammo_Low = AmmoStatus.AddTriangularSet("Ammo_Low", 1, 2, 10);
	FzSet& Ammo_Out = AmmoStatus.AddLeftShoulderSet("Ammo_Out", 0, 0, 0);

	m_FuzzyModule.AddRule(FzAND(Target_VeryClose, Ammo_Loads), Undesirable);
	m_FuzzyModule.AddRule(FzAND(Target_VeryClose, Ammo_High), Undesirable);
	m_FuzzyModule.AddRule(FzAND(Target_VeryClose, Ammo_Medium), Undesirable);
	m_FuzzyModule.AddRule(FzAND(Target_VeryClose, Ammo_Low), LowDesirable);
	m_FuzzyModule.AddRule(FzAND(Target_VeryClose, Ammo_Out), LowDesirable);

	m_FuzzyModule.AddRule(FzAND(Target_Close, Ammo_Loads), Undesirable);
	m_FuzzyModule.AddRule(FzAND(Target_Close, Ammo_High), Undesirable);
	m_FuzzyModule.AddRule(FzAND(Target_Close, Ammo_Medium), Undesirable);
	m_FuzzyModule.AddRule(FzAND(Target_Close, Ammo_Low), LowDesirable);
	m_FuzzyModule.AddRule(FzAND(Target_Close, Ammo_Out), Desirable);

	m_FuzzyModule.AddRule(FzAND(Target_Medium, Ammo_Loads), Undesirable);
	m_FuzzyModule.AddRule(FzAND(Target_Medium, Ammo_High), LowDesirable);
	m_FuzzyModule.AddRule(FzAND(Target_Medium, Ammo_Medium), Desirable);
	m_FuzzyModule.AddRule(FzAND(Target_Medium, Ammo_Low), Desirable);
	m_FuzzyModule.AddRule(FzAND(Target_Medium, Ammo_Out), HighDesirable);

	m_FuzzyModule.AddRule(FzAND(Target_Far, Ammo_Loads), Undesirable);
	m_FuzzyModule.AddRule(FzAND(Target_Far, Ammo_High), LowDesirable);
	m_FuzzyModule.AddRule(FzAND(Target_Far, Ammo_Medium), Desirable);
	m_FuzzyModule.AddRule(FzAND(Target_Far, Ammo_Low), HighDesirable);
	m_FuzzyModule.AddRule(FzAND(Target_Far, Ammo_Out), VeryDesirable);

	m_FuzzyModule.AddRule(FzAND(Target_VeryFar, Ammo_Loads), Undesirable);
	m_FuzzyModule.AddRule(FzAND(Target_VeryFar, Ammo_High), LowDesirable);
	m_FuzzyModule.AddRule(FzAND(Target_VeryFar, Ammo_Medium), HighDesirable);
	m_FuzzyModule.AddRule(FzAND(Target_VeryFar, Ammo_Low), VeryDesirable);
	m_FuzzyModule.AddRule(FzAND(Target_VeryFar, Ammo_Out), VeryDesirable);
}


//-------------------------------- Render -------------------------------------7
//-----------------------------------------------------------------------------
void GrenadeLauncher::Render()
{
	m_vecWeaponVBTrans = WorldTransform(m_vecWeaponVB,
		m_pOwner->Pos(),
		m_pOwner->Facing(),
		m_pOwner->Facing().Perp(),
		m_pOwner->Scale());

	gdi->RedPen();

	gdi->ClosedShape(m_vecWeaponVBTrans);
}