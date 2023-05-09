set(SOURCES
src/liftOperator.cpp 

)

add_library(myLib ${SOURCES} ) 

target_include_directories(myLib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)
