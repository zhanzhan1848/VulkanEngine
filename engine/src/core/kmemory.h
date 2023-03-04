#pragma once

#include "defines.h"

typedef enum memory_tag {
    // For temporary use. Should be assigned one of the below or have a new tag created.
    MEMORY_TAG_UNKNOWN,
    MEMORY_TAG_ARRAY,
    MEMORY_TAG_LINEAR_ALLOCATOR,
    MEMORY_TAG_DARRAY,
    MEMORY_TAG_DICT,
    MEMORY_TAG_RING_QUEUE,
    MEMORY_TAG_BST,
    MEMORY_TAG_STRING,
    MEMORY_TAG_APPLICATION,
    MEMORY_TAG_JOB,
    MEMORY_TAG_TEXTURE,
    MEMORY_TAG_MATERIAL_INSTANCE,
    MEMORY_TAG_RENDERER,
    MEMORY_TAG_GAME,
    MEMORY_TAG_TRANSFORM,
    MEMORY_TAG_ENTITY,
    MEMORY_TAG_ENTITY_NODE,
    MEMORY_TAG_SCENE,
    MEMORY_TAG_RESOURCE,
    MEMORY_TAG_VULKAN,
    // "External" vulkan allocations, for reporting purposes only.
    MEMORY_TAG_VULKAN_EXT,
    MEMORY_TAG_DIRECT3D,
    MEMORY_TAG_OPENGL,
    // Representation of GPU-local/vram
    MEMORY_TAG_GPU_LOCAL,

    MEMORY_TAG_MAX_TAGS
} memory_tag;

/** @brief The configuration for the memory system. */
typedef struct memory_system_configuration {
    /** @brief The total memory size in byes used by the internal allocator for this system. */
    u64 total_alloc_size;
} memory_system_configuration;

KAPI b8 memory_system_initialize(memory_system_configuration config);
KAPI void memory_system_shutdown();

KAPI void* kallocate(u64 size, memory_tag tag);

/**
 * @brief Performs an aligned memory allocation from the host of the given size and alignment.
 * The allocation is tracked for the provided tag. NOTE: Memory allocated this way must be freed
 * using kfree_aligned.
 * @param size The size of the allocation.
 * @param alignment The alignment in bytes.
 * @param tag Indicates the use of the allocated block.
 * @returns If successful, a pointer to a block of allocated memory; otherwise 0.
 */
KAPI void* kallocate_aligned(u64 size, u16 alignment, memory_tag tag);

/**
 * @brief Reports an allocation associated with the application, but made externally.
 * This can be done for items allocated within 3rd party libraries, for example, to
 * track allocations but not perform them.
 *
 * @param size The size of the allocation.
 * @param tag Indicates the use of the allocated block.
 */
KAPI void kallocate_report(u64 size, memory_tag tag);

KAPI void kfree(void* block, u64 size, memory_tag tag);

/**
 * @brief Frees the given block, and untracks its size from the given tag.
 * @param block A pointer to the block of memory to be freed.
 * @param size The size of the block to be freed.
 * @param tag The tag indicating the block's use.
 */
KAPI void kfree_aligned(void* block, u64 size, u16 alignment, memory_tag tag);

/**
 * @brief Reports a free associated with the application, but made externally.
 * This can be done for items allocated within 3rd party libraries, for example, to
 * track frees but not perform them.
 *
 * @param size The size in bytes.
 * @param tag The tag indicating the block's use.
 */
KAPI void kfree_report(u64 size, memory_tag tag);

/**
 * @brief Returns the size and alignment of the given block of memory.
 * NOTE: A failure result from this method most likely indicates heap corruption.
 *
 * @param block The memory block.
 * @param out_size A pointer to hold the size of the block.
 * @param out_alignment A pointer to hold the alignment of the block.
 * @return True on success; otherwise false.
 */
KAPI b8 kmemory_get_size_alignment(void* block, u64* out_size, u16* out_alignment);

KAPI void* kzero_memory(void* block, u64 size);

KAPI void* kcopy_memory(void* dest, const void* source, u64 size);

KAPI void* kset_memory(void* dest, i32 value, u64 size);

KAPI char* get_memory_usage_str();

KAPI u64 get_memory_alloc_count();