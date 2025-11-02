#include "pch.h"
#include "gameobject.h"
#include "GameState.h"
#include "stringHelp.h"

GameObject::GameObject()
{
	//set the GameObject to the origin with no rotation and unit scaling 
	m_pos = Vector3::Zero;
	m_pitch = 0.0f;
	m_yaw = 0.0f;
	m_roll = 0.0f;
	m_scale = Vector3::One;

	m_worldMat = Matrix::Identity;
	m_fudge = Matrix::Identity;
	m_rotMat = Matrix::Identity;
}

GameObject::~GameObject()
{

}

void GameObject::Tick(GameState* _GD)
{
	//build up the world matrix depending on the new position of the GameObject
	//the assumption is that this class will be inherited by the class that ACTUALLY changes this
	Matrix  scaleMat = Matrix::CreateScale(m_scale);
	m_rotMat = Matrix::CreateFromYawPitchRoll(m_yaw, m_pitch, m_roll); //possible not the best way of doing this!
	Matrix  transMat = Matrix::CreateTranslation(m_pos);

	//m_fudge is for any extra adjustments needed to the world matrix due to bad artists or other issues
	m_worldMat = m_fudge * scaleMat * m_rotMat * transMat;
}

void GameObject::Load(ifstream& _file)
{
	StringHelp::String(_file, "NAME", m_name);
	StringHelp::Float3(_file, "POS", m_pos.x, m_pos.y, m_pos.z);
	StringHelp::Float3(_file, "ROT", m_pitch, m_yaw, m_roll);
	m_pitch = XM_PI * m_pitch / 180.0f;
	m_yaw = XM_PI * m_yaw / 180.0f;
	m_roll = XM_PI * m_roll / 180.0f;
	StringHelp::Float3(_file, "SCALE", m_scale.x, m_scale.y, m_scale.z);
}