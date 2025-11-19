#include "pch.h"
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
#include "PerlinNoise.h"

namespace PerlinNoise {

    // Permutation table (512 entries with duplicated values for overflow)
    static std::vector<int> p;

    // Initialize permutation with default seed
    static void Init(unsigned int seed = 0u)
    {
        p.resize(512);
        std::vector<int> permutation(256);
        for (int i = 0; i < 256; ++i) permutation[i] = i;

        // Use seed to shuffle
        std::mt19937 generator(seed ? seed : 1777u);
        std::shuffle(permutation.begin(), permutation.end(), generator);

        for (int i = 0; i < 256; ++i)
        {
            p[i] = permutation[i];
            p[i + 256] = permutation[i];
        }
    }

    // Allow user to set seed for deterministic noise
    void SetSeed(unsigned int seed)
    {
        Init(seed);
    }

    // Fade function as defined by Ken Perlin. This eases coordinate values
    inline float fade(float t)
    {
        // 6t^5 - 15t^4 + 10t^3
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    inline float lerp(float a, float b, float t)
    {
        return a + t * (b - a);
    }

    // Gradient function for 2D. Uses low 4 bits of hash to select a gradient.
    inline float grad(int hash, float x, float y)
    {
        int h = hash & 7; // 8 possible directions
        float u = (h < 4) ? x : y;
        float v = (h < 4) ? y : x;
        // Select signs based on bits
        return ((h & 1) ? -u : u) + ((h & 2) ? -2.0f * v : 2.0f * v) * 0.5f;
    }

    // Ensure permutation table initialized before first use
    struct InitGuard {
        InitGuard() { if (p.size() != 512) Init(0u); }
    };
    static InitGuard _initGuard;

    // Main 2D Perlin noise function returning value in [0,1]
    float GetNoise(float x, float y)
    {
        if (p.size() != 512) Init(0u);

        // Find unit grid cell containing point
        int X = static_cast<int>(std::floor(x)) & 255;
        int Y = static_cast<int>(std::floor(y)) & 255;

        // Relative x,y within cell
        float xf = x - std::floor(x);
        float yf = y - std::floor(y);

        // Compute fade curves for x and y
        float u = fade(xf);
        float v = fade(yf);

        // Hash coordinates of the 4 cube corners
        int aa = p[p[X] + Y];
        int ab = p[p[X] + Y + 1];
        int ba = p[p[X + 1] + Y];
        int bb = p[p[X + 1] + Y + 1];

        // Add blended results from 4 corners of the square
        float x1 = lerp(grad(aa, xf, yf), grad(ba, xf - 1.0f, yf), u);
        float x2 = lerp(grad(ab, xf, yf - 1.0f), grad(bb, xf - 1.0f, yf - 1.0f), u);
        float result = lerp(x1, x2, v);

        // Perlin returns in range roughly [-1,1]. Map to [0,1].
        return (result * 0.5f) + 0.5f;
    }

} // namespace PerlinNoise