cmake_minimum_required(VERSION 2.6)
project(RubiksCubeDataGen)

# All source files.
set(SRC
  "./rubiksCubeDataGen.cpp"
  "./Model/RubiksCubeModel.cpp"
  "./Model/Goal/OrientG0.cpp"
  "./Model/Goal/GoalG0_G1.cpp"
  "./Model/Goal/GoalG1_G2.cpp"
  "./Model/Goal/GoalG2_G3_Corners.cpp"
  "./Model/Goal/GoalG2_G3_Edges.cpp"
  "./Model/Goal/GoalG3_Solved.cpp"
  "./Model/Goal/GoalG3_Permute_Corners.cpp"
  "./Model/MoveStore/MoveStore.cpp"
  "./Model/MoveStore/RotationStore.cpp"
  "./Model/MoveStore/TwistStore.cpp"
  "./Model/MoveStore/ModelRotationStore.cpp"
  "./Model/MoveStore/ModelTwistStore.cpp"
  "./Model/MoveStore/ModelG1TwistStore.cpp"
  "./Model/MoveStore/ModelG2TwistStore.cpp"
  "./Model/MoveStore/ModelG3TwistStore.cpp"
  "./View/RubiksCubeView.cpp"
  "./View/RubiksCubeWriter.cpp"
  "./Util/RubiksCubeException.cpp"
  "./Util/Random.cpp"
  "./Util/Timer.cpp"
  "./Util/AutoTimer.cpp"
  "./Controller/RubiksCubeController.cpp"
  "./Controller/CubeSearcher.cpp"
  "./Controller/CubeSolver.cpp"
)

# Build the RubiksCubee executable.
add_executable(rubiksCubeDataGen ${SRC})

# Release build by default.
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -Wall -pedantic -std=c++0x -Wno-strict-aliasing")

