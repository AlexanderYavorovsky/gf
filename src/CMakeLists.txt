set(SOURCES gf.c poly.c)
set(HEADERS gf.h poly.h)

add_library(gf STATIC ${SOURCES} ${HEADERS})

target_include_directories(gf PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

