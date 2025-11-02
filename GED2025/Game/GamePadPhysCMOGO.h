#pragma once
#include "PhysCMOGO.h"

//a Game Object that is a physics object controlled by a gamepad
//and has a model loaded from a .cmo file
class GamePadPhysCMOGO : public PhysCMOGO
{
public:
	GamePadPhysCMOGO();
	~GamePadPhysCMOGO();
	virtual void Tick(GameState* _GS) override;
	virtual void Load(ifstream& _file) override;

protected:

	int m_device = -1;//which gamepad to use

};

