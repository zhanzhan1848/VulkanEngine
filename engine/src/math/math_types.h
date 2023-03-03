#pragma once

#include "defines.h"

typedef union vec2_u {
    // An array of x, y
    f32 elements[2];
    struct {
        union {
            // The first element.
            f32 x, r, s, u;
        };
        union {
            // The second element.
            f32 y, g, t, v;
        };
    };
} vec2;

typedef union vec3_u {
    // An array of x, y, z
    f32 elements[3];
    struct {
        union {
            // The first element.
            f32 x, r, s, u;
        };
        union {
            // The second element.
            f32 y, g, t, v;
        };
        union {
            // The third element.
            f32 z, b, p, w;
        };
    };
} vec3;

typedef union vec4_u {

    // An array of x, y, z, w
    f32 elements[4];
    union {
        struct {
            union {
                // The first element.
                f32 x, r, s;
            };
            union {
                // The second element.
                f32 y, g, t;
            };
            union {
                // The third element.
                f32 z, b, p;
            };
            union {
                // The fourth element.
                f32 w, a, q;
            };
        };
    };
} vec4;

typedef vec4 quat;

typedef union mat4_u {
    f32 data[16];
} mat4;

/**
 * @brief Represents the extents of a 2d object.
 */
typedef struct extents_2d {
    /** @brief The minimum extents of the object. */
    vec2 min;
    /** @brief The maximum extents of the object. */
    vec2 max;
} extents_2d;

/**
 * @brief Represents the extents of a 3d object.
 */
typedef struct extents_3d {
    /** @brief The minimum extents of the object. */
    vec3 min;
    /** @brief The maximum extents of the object. */
    vec3 max;
} extents_3d;

typedef struct vertex_3d
{
    vec3 position;
    vec3 normal;
    vec2 texcoord;
    vec4 color;
    vec3 tangent;
} vertex_3d;

typedef struct vertex_2d
{
    vec2 position;
    vec2 texcoord;
} vertex_2d;

/**
 * @brief Represents the transform of an object in the world.
 * Transforms can have a parent whose own transform is then
 * taken into account. NOTE: The properties of this should not
 * be edited directly, but done via the functions in transform.h
 * to ensure proper matrix generation.
 */
typedef struct transform {
    /** @brief The position in the world. */
    vec3 position;
    /** @brief The rotation in the world. */
    quat rotation;
    /** @brief The scale in the world. */
    vec3 scale;
    /**
     * @brief Indicates if the position, rotation or scale have changed,
     * indicating that the local matrix needs to be recalculated.
     */
    b8 is_dirty;
    /**
     * @brief The local transformation matrix, updated whenever
     * the position, rotation or scale have changed.
     */
    mat4 local;

    /** @brief A pointer to a parent transform if one is assigned. Can also be null. */
    struct transform* parent;
} transform;