cmake_minimum_required (VERSION 3.0)

project (SIMDIntroDemo)

set (HDRS SIMDFuncsNone.h)
set (DEFS )

option (ENABLE_SSE "Enable SSE intrinsics" ON)
option (ENABLE_AVX "Enable AVX intrinsics" ON)
option (ENABLE_NEON "Enable NEON intrinsics" OFF)

if (ENABLE_SSE)
    set (DEFS ${DEFS} ENABLE_SSE)
    set (HDRS ${HDRS} SIMDFuncsSSE.h)
endif()

if (ENABLE_AVX)
    set (DEFS ${DEFS} ENABLE_AVX)
    set (HDRS ${HDRS} SIMDFuncsAVX.h)
endif()

if (ENABLE_NEON)
    set (DEFS ${DEFS} ENABLE_NEON)
    set (HDRS ${HDRS} SIMDFuncsNEON.h)
endif()

add_executable (SIMDIntroDemo main.cpp ${HDRS})

target_compile_definitions (SIMDIntroDemo PUBLIC ${DEFS})

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options (SIMDIntroDemo PUBLIC -mavx)
endif()
