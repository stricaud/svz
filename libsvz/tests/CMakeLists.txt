
enable_testing()
include_directories(AFTER ${LIBSVZ_INCLUDE_DIRS})

add_executable(encoder encoder.c)
target_link_libraries(encoder ${LIBSVZ_LIBRARY} ${CMAKE_DL_LIBS})
add_test(Encoder encoder)

add_executable(decoder decoder.c)
target_link_libraries(decoder ${LIBSVZ_LIBRARY} ${CMAKE_DL_LIBS})
add_test(Decoder decoder)
