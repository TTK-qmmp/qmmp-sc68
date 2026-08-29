cmake_minimum_required(VERSION 3.18.0)

project(sc68)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-multichar")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-multichar")

add_definitions(-DHAVE_STDLIB_H)
add_definitions(-DHAVE_STDINT_H)
add_definitions(-DHAVE_STRING_H)
add_definitions(-DHAVE_LIMITS_H)
add_definitions(-DHAVE_ASSERT_H)
add_definitions(-DHAVE_BASENAME)
add_definitions(-DEMU68_MONOLITIC)
add_definitions(-DEMU68_EXPORT)
add_definitions(-DUSE_UNICE68)
if(UNIX)
    add_definitions(-DHAVE_LIBGEN_H)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/file68)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/file68/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/file68/sc68)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libsc68)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libsc68/dial68)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libsc68/emu68)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libsc68/io68)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libsc68/sc68)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/unice68)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/desa68)

set(HEADERS
    libsc68/sc68/sc68.h
)

set(SOURCES
    file68/src/gzip68.c
    file68/src/vfs68.c
    file68/src/ice68.c
    file68/src/vfs68_ao.c
    file68/src/vfs68_null.c
    file68/src/msg68.c
    file68/src/timedb68.c
    file68/src/init68.c
    file68/src/vfs68_z.c
    file68/src/replay68.c
    file68/src/registry68.c
    file68/src/uri68.c
    file68/src/rsc68.c
    file68/src/vfs68_fd.c
    file68/src/vfs68_file.c
    file68/src/vfs68_mem.c
    file68/src/file68.c
    file68/src/string68.c
    file68/src/endian68.c
    file68/src/vfs68_curl.c
    file68/src/option68.c
    file68/src/ferror68.c
    libsc68/dial68/dial68.c
    libsc68/dial68/dial_conf.c
    libsc68/dial68/dial_finf.c
    libsc68/dial68/dial_tsel.c
    unice68/unice68_unpack.c
    unice68/unice68_pack.c
    unice68/unice68_version.c
    libsc68/conf68.c
    libsc68/api68.c
    libsc68/mixer68.c
    libsc68/io68/paulaemul.c
    libsc68/io68/ym_envel.c
    libsc68/io68/ymemul.c
    libsc68/io68/shifter_io.c
    libsc68/io68/paula_io.c
    libsc68/io68/mw_io.c
    libsc68/io68/ym_dump.c
    libsc68/io68/mfp_io.c
    libsc68/io68/mwemul.c
    libsc68/io68/ym_io.c
    libsc68/io68/io68.c
    libsc68/io68/ym_blep.c
    libsc68/io68/mfpemul.c
    libsc68/io68/ym_puls.c
    libsc68/libsc68.c
    libsc68/emu68/lines68.c
    libsc68/emu68/ioplug68.c
    libsc68/emu68/mem68.c
    libsc68/emu68/getea68.c
    libsc68/emu68/inst68.c
    libsc68/emu68/emu68.c
    libsc68/emu68/error68.c
    desa68/desa68.c
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}${STATIC_LIB_SUFFIX})

install(TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    COMPONENT library
)

install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/lib${PROJECT_NAME}/sc68)
