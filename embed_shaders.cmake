file(READ "${INPUT_VERT}" VERT_SRC)
file(READ "${INPUT_FRAG}" FRAG_SRC)

# Escape backslashes and quotes for C++ raw string safety
string(REPLACE "\\" "\\\\" VERT_SRC "${VERT_SRC}")
string(REPLACE "\\" "\\\\" FRAG_SRC "${FRAG_SRC}")

# Use a delimiter that is unlikely to appear in shader code
set(RAW_DELIM "GLSL")

file(WRITE "${OUTPUT_FILE}" "
// Auto-generated file. Do not edit.
#pragma once

namespace generated_shaders {

inline constexpr const char* default_vert = R\"${RAW_DELIM}(
${VERT_SRC}
)${RAW_DELIM}\";

inline constexpr const char* default_frag = R\"${RAW_DELIM}(
${FRAG_SRC}
)${RAW_DELIM}\";

} // namespace generated_shaders
")