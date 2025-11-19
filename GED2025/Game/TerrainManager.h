#pragma once
#include "TerrainChunk.h"
#include "GameObject.h"
#include <vector>

class TerrainManager : public GameObject
{
public:
    TerrainManager();
    ~TerrainManager();

    // Setup the terrain (Generates data and creates Chunks)
    void Init(ID3D11Device* _GD, IEffectFactory* _EF, Game* _gam);

    void Tick(GameState* _GD);
    void Draw(DrawData* _DD);

private:
    std::vector<TerrainChunk*> m_chunks;

    // How many chunks to spawn in X and Z
    const int NUM_CHUNKS_X = 4;
    const int NUM_CHUNKS_Z = 4;

    // Perlin Noise settings
    float m_noiseScale = 0.1f;
    float m_heightMultiplier = 10.0f;
};