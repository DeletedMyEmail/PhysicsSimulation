#pragma once

// particles
constexpr unsigned int MAX_PARTICLE_COUNT = 200;
constexpr float PARTICLE_RADIUS = 1.0f;

// physics
constexpr float COLLISION_DAMPING = 0.4f;
constexpr float G = -12.00f;
constexpr float G_CENTRAL = 20.0f;
constexpr int CONSTRAIN_RADIUS = 30.0f;

// partitioning
inline constexpr float CHUNK_SIZE = PARTICLE_RADIUS*3.0f;
inline constexpr unsigned int CHUNKS_PER_DIMENSION = CONSTRAIN_RADIUS*2 / CHUNK_SIZE;

// paths
inline auto VERT_SHADER_PATH = "../shader/BasicVert.glsl";
inline auto DIFFUSE_FRAG_SHADER_PATH = "../shader/DiffuseFrag.glsl";
inline auto BASIC_FRAG_SHADER = "../shader/BasicFrag.glsl";
inline auto MODEL_PATH = "../models/sphere.obj";