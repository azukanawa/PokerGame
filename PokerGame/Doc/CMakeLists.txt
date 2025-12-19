include_directories(../Include)
link_directories(${CMAKE_SOURCE_DIR}/Lib)
add_executable(PokerGame Button.cpp Function.cpp Game.cpp Init.cpp main.cpp Music.cpp)
target_link_libraries(PokerGame 
  ${CMAKE_SOURCE_DIR}/Lib/libeasyx.a 
  winmm  
  msvcrt  
)