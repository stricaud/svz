include_directories(AFTER ${LIBSVZ_INCLUDE_DIRS})
include_directories(AFTER "./lzlib-1.11")

set(LZIPLIB_SRC
  lzlib-1.11/lzlib.c
)

set(LIBSVZ_SRC
basic-shapes.c
decode.c
draw-text.c
encode.c
features.c
image.c
lzcompress.c
svz.c
)

set(LIBSVZ_HEADERS
)

add_library(svz SHARED ${LIBSVZ_SRC} ${LZIPLIB_SRC})
set_target_properties(svz PROPERTIES SOVERSION 1)
target_link_libraries(svz ${LIBSVZ_LINK_LIBRARIES})
