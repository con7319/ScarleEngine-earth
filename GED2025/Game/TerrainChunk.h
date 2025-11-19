#pragma once
#include "VBGO.h"
#include "VBCube.h"
#include "TerrainConstants.h"
#include <vector>

class TerrainChunk : public GameObject
{
public:
    TerrainChunk();
    virtual ~TerrainChunk();

    // Setup the rendering resources
    void Init(ID3D11Device* _GD, IEffectFactory* _EF, Game* _gam);

    // Receive the voxel data from the manager
    void LoadData(int _voxelMap[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_DEPTH], Vector3 _worldPos);

    // Update and Draw (propagate to children cubes)
    void Tick(GameState* _GS) override;
    void Draw(DrawData* _DD) override;

protected:
    //voxel data (1 = solid, 0 = air)
    int m_voxelMap[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_DEPTH];

    // List of cube objects to render
    std::vector<VBCube*> m_cubes;

    // Helper to check if a voxel at specific local coordinates is solid
    bool IsSolid(int x, int y, int z);
};