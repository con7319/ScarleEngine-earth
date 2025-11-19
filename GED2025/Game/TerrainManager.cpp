#include "pch.h"
#include "TerrainManager.h"
#include "PerlinNoise.h" 

TerrainManager::TerrainManager()
{
    // Initialize the noise seed
    PerlinNoise::SetSeed(12345);
}

TerrainManager::~TerrainManager()
{
    for (TerrainChunk* chunk : m_chunks)
    {
        delete chunk;
    }
    m_chunks.clear();
}

void TerrainManager::Init(ID3D11Device* _GD, IEffectFactory* _EF, Game* _gam)
{
    // Loop through the grid of chunks we want to create
    for (int cX = 0; cX < NUM_CHUNKS_X; cX++)
    {
        for (int cZ = 0; cZ < NUM_CHUNKS_Z; cZ++)
        {
            // Create temporary data buffer for this chunk
            int chunkData[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_DEPTH];

            // Determine the world offset for this chunk
            float chunkWorldX = cX * CHUNK_WIDTH * VOXEL_SCALE;
            float chunkWorldZ = cZ * CHUNK_DEPTH * VOXEL_SCALE;

            // Generate Data using Perlin Noise
            for (int x = 0; x < CHUNK_WIDTH; x++)
            {
                for (int z = 0; z < CHUNK_DEPTH; z++)
                {
                    // Calculate absolute world coordinates
                    float worldX = chunkWorldX + (x * VOXEL_SCALE);
                    float worldZ = chunkWorldZ + (z * VOXEL_SCALE);

                    // Get Noise value (0.0 to 1.0)
                    float noiseVal = PerlinNoise::GetNoise(worldX * m_noiseScale, worldZ * m_noiseScale);

                    // Convert to integer height
                    int terrainHeight = (int)(noiseVal * m_heightMultiplier);

                    // Clamp height to chunk bounds
                    if (terrainHeight < 0) terrainHeight = 0;
                    if (terrainHeight >= CHUNK_HEIGHT) terrainHeight = CHUNK_HEIGHT - 1;

                    // Fill the vertical column
                    for (int y = 0; y < CHUNK_HEIGHT; y++)
                    {
                        if (y <= terrainHeight)
                        {
                            chunkData[x][y][z] = 1; // Solid
                        }
                        else
                        {
                            chunkData[x][y][z] = 0; // Air
                        }
                    }
                }
            }

            // Create the Chunk Object
            TerrainChunk* newChunk = new TerrainChunk();

            // Pass the data and position
            newChunk->LoadData(chunkData, Vector3(chunkWorldX, 0, chunkWorldZ));

            // Initialize graphics resources for the chunk
            newChunk->Init(_GD, _EF, _gam);

            m_chunks.push_back(newChunk);
        }
    }
}

void TerrainManager::Tick(GameState* _GS)
{
    for (TerrainChunk* chunk : m_chunks)
    {
        chunk->Tick(_GS);
    }
}

void TerrainManager::Draw(DrawData* _DD)
{
    for (TerrainChunk* chunk : m_chunks)
    {
        chunk->Draw(_DD);
    }
}