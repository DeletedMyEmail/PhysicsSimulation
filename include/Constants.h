#pragma once

// particles
#define MAX_PARTICLE_COUNT 2
#define PARTICLE_RADIUS 1.0f

// physics
#define COLLISION_DAMPING 0.4f
#define G -12.00f
#define G_CENTRAL 20.0f
#define CONSTRAIN_RADIUS 22

// partitioning
inline constexpr float CHUNK_SIZE = PARTICLE_RADIUS*2.0f;
inline constexpr unsigned int CHUNKS_PER_DIMENSION = CONSTRAIN_RADIUS*2 / CHUNK_SIZE;

// paths
#define VERT_SHADER_PATH "../shader/BasicVert.glsl"
#define DIFFUSE_FRAG_SHADER_PATH "../shader/DiffuseFrag.glsl"
#define BASIC_FRAG_SHADER "../shader/BasicFrag.glsl"
#define MODEL_PATH "../models/sphere.obj"

// graphics
#define WIDTH 1200.0f
#define HEIGHT 1000.0f
#define CATCH_MOUSE
//#define FULLSCREEN
//#define CULLING
// TODO: disabling vy sync causes random physics violating energy conservation
#define VYSNC