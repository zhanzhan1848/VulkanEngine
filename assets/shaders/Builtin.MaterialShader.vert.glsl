#version 450

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_texcoord;

layout(set = 0, binding = 0) uniform global_uniform_object
{
    mat4 projection;
    mat4 view;
} global_ubo;

layout(push_constant) uniform push_constants
{
    // Only guaranteed a total for 128 bytes
    mat4 model; // 64 bytes
} u_push_constants;

layout(location = 0) out int out_mode;
layout(location = 1) out struct dto
{
    vec2 tex_coord;
} out_dto;

void main()
{
    out_dto.tex_coord = in_texcoord;
    out_mode = 1;
    gl_Position = global_ubo.projection * global_ubo.view * u_push_constants.model * vec4(in_position, 1.0);
}