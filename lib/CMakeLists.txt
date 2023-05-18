set(SOURCES
src/lift3.cpp
)
#src/operate.cpp 
#src/lift2.cpp


add_library(myLib ${SOURCES})  

target_include_directories(myLib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc) 
