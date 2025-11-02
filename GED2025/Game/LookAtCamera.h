#pragma once
#include "camera.h"

// a camera that looks at a specified Game Object

class LookAtCamera : public Camera
{
public:
	LookAtCamera();
	~LookAtCamera();

	virtual void Tick(GameState* _GS) override;

	virtual void Load(ifstream& _file) override;
	virtual void Init(ID3D11Device* _GD, IEffectFactory* _EF, Game* _game) override;

protected:

	Vector3 m_dPos; // offset from the target object's position

	string m_GO_Name; // name of the Game Object to look at

	GameObject* m_GO; // pointer to the Game Object to look at pulled in at Init time using m_GO_Name
};

