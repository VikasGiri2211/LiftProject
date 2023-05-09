set(SOURCES
src/liftOperator.cpp 

)

add_library(myLib ${SOURCES}  "inc/check.h") 

target_include_directories(myLib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)
