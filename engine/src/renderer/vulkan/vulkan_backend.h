#pragma once

#include "renderer/renderer_backend.h"
#include "resources/resource_types.h"

struct shader;
struct shader_uniform;

b8 vulkan_renderer_backend_initialize(renderer_backend* backend, const char* application_name);
void vulkan_renderer_backend_shutdown(renderer_backend* backend);

void vulkan_renderer_backend_on_resized(renderer_backend* backend, u16 width, u16 height);

b8 vulkan_renderer_backend_begin_frame(renderer_backend* backend, f32 delta_time);
b8 vulkan_renderer_backend_end_frame(renderer_backend* backend, f32 delta_time);

b8 vulkan_renderer_begin_renderpass(struct renderer_backend* backend, u8 renderpass_id);
b8 vulkan_renderer_end_renderpass(struct renderer_backend* backend, u8 renderpass_id);

void vulkan_renderer_draw_geometry(geometry_render_data data);

void vulkan_renderer_texture_create(const u8* pixels, texture* texture);
void vulkan_renderer_texture_destroy(texture* texture);

/**
 * @brief Creates a new writeable texture with no data written to it.
 * 
 * @param t A pointer to the texture to hold the resources.
 */
void vulkan_renderer_texture_create_writeable(texture* t);

/**
 * @brief Resizes a texture. There is no check at this level to see if the
 * texture is writeable. Internal resources are destroyed and re-created at
 * the new resolution. Data is lost and would need to be reloaded.
 * 
 * @param t A pointer to the texture to be resized.
 * @param new_width The new width in pixels.
 * @param new_height The new height in pixels.
 */
void vulkan_renderer_texture_resize(texture* t, u32 new_width, u32 new_height);

/**
 * @brief Writes the given data to the provided texture.
 * NOTE: At this level, this can either be a writeable or non-writeable texture because
 * this also handles the initial texture load. The texture system itself should be
 * responsible for blocking write requests to non-writeable textures.
 * 
 * @param t A pointer to the texture to be written to. 
 * @param offset The offset in bytes from the beginning of the data to be written.
 * @param size The number of bytes to be written.
 * @param pixels The raw image data to be written.
 */
void vulkan_renderer_texture_write_data(texture* t, u32 offset, u32 size, const u8* pixels);

b8 vulkan_renderer_create_geometry(geometry* geometry, u32 vertex_size, u32 vertex_count, const void* vertices, u32 index_size, u32 index_count, const void* indices);
void vulkan_renderer_destroy_geometry(geometry* geometry);

b8 vulkan_renderer_shader_create(struct shader* shader, u8 renderpass_id, u8 stage_count, const char** stage_filenames, shader_stage* stages);
void vulkan_renderer_shader_destroy(struct shader* shader);

b8 vulkan_renderer_shader_initialize(struct shader* shader);
b8 vulkan_renderer_shader_use(struct shader* shader);
b8 vulkan_renderer_shader_bind_globals(struct shader* s);
b8 vulkan_renderer_shader_bind_instance(struct shader* s, u32 instance_id);
b8 vulkan_renderer_shader_apply_globals(struct shader* s);
b8 vulkan_renderer_shader_apply_instance(struct shader* s, b8 needs_update);
b8 vulkan_renderer_shader_acquire_instance_resources(struct shader* s, texture_map** maps, u32* out_instance_id);
b8 vulkan_renderer_shader_release_instance_resources(struct shader* s, u32 instance_id);
b8 vulkan_renderer_set_uniform(struct shader* frontend_shader, struct shader_uniform* uniform, const void* value);

b8 vulkan_renderer_texture_map_acquire_resources(texture_map* map);
void vulkan_renderer_texture_map_release_resources(texture_map* map);