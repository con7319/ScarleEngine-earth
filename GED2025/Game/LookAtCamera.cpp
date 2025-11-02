#include "pch.h"
#include "LookAtCamera.h"
#include "Game.h"
#include "stringHelp.h"

LookAtCamera::LookAtCamera()
{
	m_type = "LOOKAT";
	m_canBeMainCamera = true;
}

LookAtCamera::~LookAtCamera()
{
}

void LookAtCamera::Tick(GameState* _GS)
{
	m_target = m_GO->GetPos(); //This is the key line that makes this a LookAt camera
	m_pos = m_target + m_dPos; //TODO:: this could be made more sophisticated e.g. using the GO's orientation
	Camera::Tick(_GS);
}

void LookAtCamera::Load(ifstream& _file)
{
	StringHelp::String(_file, "NAME", m_name);
	StringHelp::Float3(_file, "DPOS", m_dPos.x, m_dPos.y, m_dPos.z);
	StringHelp::String(_file, "GAMEOBJECT", m_GO_Name);
	StringHelp::Float3(_file, "UP", m_up.x, m_up.y, m_up.z);
	StringHelp::Float(_file, "FOV", m_fieldOfView);
	m_fieldOfView = XM_PI * m_fieldOfView / 180.0f;
	StringHelp::Float(_file, "NEAR", m_nearPlaneDistance);
	StringHelp::Float(_file, "FAR", m_farPlaneDistance);
}

void LookAtCamera::Init(ID3D11Device* _GD, IEffectFactory* _EF, Game* _game)
{
	m_GO = _game->GetGOByName(m_GO_Name);

	Camera::Init(_GD, _EF, _game);
}
