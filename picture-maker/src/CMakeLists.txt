include_directories(AFTER "../../libsvz/src/include/" ${FLEX_INCLUDE_DIRS} "${CMAKE_CURRENT_BINARY_DIR}/src")

set(PM_SRC_FILES
pm.c  
)

set(LIBSVZ_LINK_LIBRARIES
  "/home/sebastien/git/hub/svz/libsvz/build/src/libsvz.so.1"
)

BISON_TARGET(pmparser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.c)
FLEX_TARGET(pmlexer lexer.l  ${CMAKE_CURRENT_BINARY_DIR}/lexer.c)
ADD_FLEX_BISON_DEPENDENCY(pmlexer pmparser)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
add_executable(pm ${PM_SRC_FILES} ${BISON_pmparser_OUTPUTS} ${FLEX_pmlexer_OUTPUTS})
target_link_libraries(pm ${CMAKE_DL_LIBS} ${LIBSVZ_LINK_LIBRARIES})
