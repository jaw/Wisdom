#pragma once
#define noxnd noexcept(!DEBUG_MODE)

#ifdef WISDOM_BUILD_BINARIES // If we are building the binaries
#define WIS_INLINE
#else
#define WIS_INLINE inline
#endif // WISDOM_BUILD_BINARIES

namespace wis {
inline constexpr const bool debug_mode = DEBUG_MODE;
inline constexpr const bool debug_layer = debug_mode || DEBUG_LAYER;

inline constexpr const unsigned max_render_targets = 8u;
inline constexpr const unsigned max_vertex_bindings = 16u;
inline constexpr const unsigned max_shader_stages = 5;
} // namespace wis
