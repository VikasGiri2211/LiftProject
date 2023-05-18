add_executable(test1 main.cpp )
add_executable(test2 main2.cpp)
add_executable(test3 final.cpp)



target_link_libraries(test1 myLib) 
target_link_libraries(test2 myLib)
target_link_libraries(test3 myLib)