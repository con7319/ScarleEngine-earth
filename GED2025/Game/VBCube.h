#pragma once
#include "VBGO.h"
#include "vertex.h"

//=================================================================
//procedurally generate a VBGO Cube
//each side be divided in to _size * _size squares (2 triangles per square)
//=================================================================

class VBCube : public VBGO
{
public:
	VBCube() {};
	virtual ~VBCube() {};

	//initialize the Vertex and Index buffers for the cube
	void Init(ID3D11Device* _GD, IEffectFactory* _EF, Game* _gam) override;

	void ConfigureSides(int _sidesToLoad);

	void Load(ifstream& _file) override;


protected:
	//this is to allow custom versions of this which create the basic cube and then distort it
	//see VBSpiral and VBPillow
	virtual void Transform(WORD* _indices = nullptr) { _indices; };
	
	
	int _sidesToLoad;

	int m_size = 0;
	myVertex* m_vertices = nullptr;
	// sides: order is TOP, BACK, RIGHT, BOTTOM, FRONT, LEFT
	enum SideIndex { SIDE_TOP = 0, SIDE_BACK = 1, SIDE_RIGHT = 2, SIDE_BOTTOM = 3, SIDE_FRONT = 4, SIDE_LEFT = 5 };
	bool m_sides[6] = { true, true, true, true, true, true };
};