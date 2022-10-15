#include "heightMap.h"

void fillHeightMap(struct HeightMap* heightMap, float cX, float cZ, struct NoiseOptions* noiseOptions, int seed){
	for (int x = 0; x < CHUNK_WIDTH; x++){
		for (int z = 0; z < CHUNK_DEPTH; z++){
            float value = getNoiseAt(cX * CHUNK_WIDTH + x, cZ * CHUNK_DEPTH + z, noiseOptions, seed);
			heightMap->map[x][z] = value;
            //printf("%f ", heightMap->map[x][z]);
		}
	}
}

float getNoiseAt(float voxelX, float voxelZ, struct NoiseOptions* options, int seed){
    float value = 0;
    float accumulatedAmps = 0;
    for (int i = 0; i < options->octaves; i++)
    {
        float frequency = pow(2.0f, i);
        float amplitude = pow(options->roughness, i);

        float x = voxelX * frequency / options->smoothness;
        float y = voxelZ * frequency / options->smoothness;

        //printf("%f ", options->smoothness);
        float noise = noise2(x, y);
        noise = (noise + 1.0f) / 2.0f;
        value += noise * amplitude;
        accumulatedAmps += amplitude;
    }
    return (value / accumulatedAmps) * options->amplitude;
}