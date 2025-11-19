#include "pch.h"
#include "TerrainChunk.h"

TerrainChunk::TerrainChunk()
{
    // Initialize map to empty
    for (int x = 0; x < CHUNK_WIDTH; x++)
        for (int y = 0; y < CHUNK_HEIGHT; y++)
            for (int z = 0; z < CHUNK_DEPTH; z++)
                m_voxelMap[x][y][z] = 0;
}

TerrainChunk::~TerrainChunk()
{
    // Clean up memory
    for (VBCube* cube : m_cubes)
    {
        delete cube;
    }
    m_cubes.clear();
}

void TerrainChunk::LoadData(int _voxelMap[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_DEPTH], Vector3 _worldPos)
{
    // Copy data
    for (int x = 0; x < CHUNK_WIDTH; x++)
        for (int y = 0; y < CHUNK_HEIGHT; y++)
            for (int z = 0; z < CHUNK_DEPTH; z++)
                m_voxelMap[x][y][z] = _voxelMap[x][y][z];

    m_pos = _worldPos;
}

bool TerrainChunk::IsSolid(int x, int y, int z)
{
    
    if (x < 0 || x >= CHUNK_WIDTH) return false;
    if (y < 0 || y >= CHUNK_HEIGHT) return false;
    if (z < 0 || z >= CHUNK_DEPTH) return false;

    return m_voxelMap[x][y][z] > 0;
}

void TerrainChunk::Init(ID3D11Device* _GD, IEffectFactory* _EF, Game* _gam)
{
    // Iterate through every voxel position in this chunk
    for (int x = 0; x < CHUNK_WIDTH; x++)
    {
        for (int y = 0; y < CHUNK_HEIGHT; y++)
        {
            for (int z = 0; z < CHUNK_DEPTH; z++)
            {
                // If this voxel is solid
                if (m_voxelMap[x][y][z] > 0)
                {
                    // Calculate Bitmask for Faces
                    // Order: TOP (0), BACK (1), RIGHT (2), BOTTOM (3), FRONT (4), LEFT (5)
                    int sidesToLoad = 0;

                    // Top (Y + 1) - Draw if neighbor is empty
                    if (!IsSolid(x, y + 1, z)) sidesToLoad |= (1 << 0); // Bit 0

                    // Back (Z + 1)
                    if (!IsSolid(x, y, z + 1)) sidesToLoad |= (1 << 1); // Bit 1

                    // Right (X + 1)
                    if (!IsSolid(x + 1, y, z)) sidesToLoad |= (1 << 2); // Bit 2

                    // Bottom (Y - 1)
                    if (!IsSolid(x, y - 1, z)) sidesToLoad |= (1 << 3); // Bit 3

                    // Front (Z - 1)
                    if (!IsSolid(x, y, z - 1)) sidesToLoad |= (1 << 4); // Bit 4

                    // Left (X - 1)
                    if (!IsSolid(x - 1, y, z)) sidesToLoad |= (1 << 5); // Bit 5

                    // If at least one side is visible, create the cube
                    if (sidesToLoad > 0)
                    {
                        VBCube* newCube = new VBCube();

                        
                        newCube->m_size = 3;

               
                        newCube->SetScale(0.5f, 0.5f, 0.5f);

                        // Configure Visibility
                        newCube->ConfigureSides(sidesToLoad);

                        // Initialize geometry
                        newCube->Init(_GD, _EF, _gam);

                        // Set Position relative to World
                        Vector3 localPos = Vector3((float)x, (float)y, (float)z) * VOXEL_SCALE;
                        newCube->SetPos(m_pos + localPos);

                        m_cubes.push_back(newCube);
                    }
                }
            }
        }
    }
}

void TerrainChunk::Tick(GameState* _GS)
{
    for (VBCube* cube : m_cubes)
    {
        
        cube->Tick(_GS);
    }
}

void TerrainChunk::Draw(DrawData* _DD)
{
    for (VBCube* cube : m_cubes)
    {
        cube->Draw(_DD);
    }
}