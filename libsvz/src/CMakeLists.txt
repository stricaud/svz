include_directories(AFTER ${LIBSVZ_INCLUDE_DIRS})

set(LIBSVZ_SRC
encode.c
)

set(LIBSVZ_HEADERS
)

add_library(svz SHARED ${LIBSVZ_SRC})
set_target_properties(svz PROPERTIES SOVERSION 1)
target_link_libraries(svz ${LIBSVZ_LINK_LIBRARIES})
