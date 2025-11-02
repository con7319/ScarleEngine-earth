#include "pch.h"
#include "GamePadPhysCMOGO.h"
#include "stringHelp.h"
#include "GameState.h"
#include <assert.h>

GamePadPhysCMOGO::GamePadPhysCMOGO()
{
	m_type = "GAMEPAD_PHYS_CMOGO";
}

GamePadPhysCMOGO::~GamePadPhysCMOGO()
{
}

void GamePadPhysCMOGO::Tick(GameState* _GS)
{
	//don't tick me if we are paused
	if (_GS->m_FSM == FSM_PAUSE) return;

	assert(m_device != -1); //I don't have a device assigned!
	if (_GS->m_GPS[m_device].connected) //my device is connected
	{
		auto state = _GS->m_GPS[m_device];
		Vector3 force = Vector3(state.thumbSticks.leftX, 20.0f * state.triggers.right, state.thumbSticks.leftY);
		m_yaw += state.thumbSticks.rightX;
		AddForce(force);
	}

	AddAcc(-Vector3::UnitY * 9.8f);
	AddDrag(1.0f);

	PhysCMOGO::Tick(_GS);

	if (m_pos.y < 0.0)
	{
		m_pos.y = 0.0f; //don't fall through the floor
	}
}

void GamePadPhysCMOGO::Load(ifstream& _file)
{
	PhysCMOGO::Load(_file);
	StringHelp::Int(_file, "DEVICE", m_device);
}
