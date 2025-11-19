#pragma once



namespace PerlinNoise
{
	
	void SetSeed(unsigned int seed = 0u);

	// Get 2D Perlin noise in range [0, 1] for coordinates (x, y).
	float GetNoise(float x, float y);
}