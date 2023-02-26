#pragma once

#include "renderer/renderer_types.inl"

typedef struct texture_system_config
{
    u32 max_texture_count;
} texture_system_config;

#define DEFAULT_TEXTURE_NAME "default"

/** @brief The default diffuse texture name. */
#define DEFAULT_DIFFUSE_TEXTURE_NAME "default_DIFF"

/** @brief The default specular texture name. */
#define DEFAULT_SPECULAR_TEXTURE_NAME "default_SPEC"

/** @brief The default normal texture name. */
#define DEFAULT_NORMAL_TEXTURE_NAME "default_NORM"

b8 texture_system_initialize(u64* memory_requirement, void* state, texture_system_config config);
void texture_system_shutdown(void* state);

texture* texture_system_acquire(const char* name, b8 auto_release);

/**
 * @brief Attempts to acquire a writeable texture with the given name. This does not point to
 * nor attempt to load a texture file. Does also increment the reference counter.
 * NOTE: Writeable textures are not auto-released.
 *
 * @param name The name of the texture to acquire.
 * @param width The texture width in pixels.
 * @param height The texture height in pixels.
 * @param channel_count The number of channels in the texture (typically 4 for RGBA)
 * @param has_transparency Indicates if the texture will have transparency.
 * @return A pointer to the generated texture.
 */
texture* texture_system_aquire_writeable(const char* name, u32 width, u32 height, u8 channel_count, b8 has_transparency);

void texture_system_release(const char* name);

/**
 * @brief Wraps the provided internal data in a texture structure using the parameters
 * provided. This is best used for when the renderer system creates internal resources
 * and they should be passed off to the texture system. Can be looked up by name via
 * the acquire methods.
 * NOTE: Wrapped textures are not auto-released.
 *
 * @param name The name of the texture.
 * @param width The texture width in pixels.
 * @param height The texture height in pixels.
 * @param channel_count The number of channels in the texture (typically 4 for RGBA)
 * @param has_transparency Indicates if the texture will have transparency.
 * @param is_writeable Indicates if the texture is writeable.
 * @param internal_data A pointer to the internal data to be set on the texture.
 * @param register_texture Indicates if the texture should be registered with the system.
 * @return A pointer to the wrapped texture.
 */
texture* texture_system_wrap_internal(const char* name, u32 width, u32 height, u8 channel_count, b8 has_transparency, b8 is_writeable, b8 register_texture, void* internal_data);

/**
 * @brief Sets the internal data of a texture. Useful for replacing internal data from within the
 * renderer for wrapped textures, for example.
 *
 * @param t A pointer to the texture to be updated.
 * @param internal_data A pointer to the internal data to be set.
 * @return True on success; otherwise false.
 */
b8 texture_system_set_internal(texture* t, void* internal_data);

/**
 * @brief Resizes the given texture. May only be done on writeable textures.
 * Potentially regenerates internal data, if configured to do so.
 *
 * @param t A pointer to the texture to be resized.
 * @param width The new width in pixels.
 * @param height The new height in pixels.
 * @param regenerate_internal_data Indicates if the internal data should be regenerated.
 * @return True on success; otherwise false.
 */
b8 texture_system_resize(texture* t, u32 width, u32 height, b8 regenerate_internal_data);

/**
 * @brief Writes the given data to the provided texture. May only be used on
 * writeable textures.
 *
 * @param t A pointer to the texture to be written to.
 * @param offset The offset in bytes from the beginning of the data to be written.
 * @param size The number of bytes to be written.
 * @param data A pointer to the data to be written.
 * @return True on success; otherwise false.
 */
b8 texture_system_write_data(texture* t, u32 offset, u32 size, void* data);

texture* texture_system_get_default_texture();
texture* texture_system_get_default_diffuse_texture();
texture* texture_system_get_default_specular_texture();
texture* texture_system_get_default_normal_texture();