#ifndef _BUSYBIN_CUBE_SOLVER_H_
#define _BUSYBIN_CUBE_SOLVER_H_

#include "CubeSearcher.h"
#include "../View/RubiksCubeView.h"
#include "../View/RubiksCubeWriter.h"
#include "../Model/RubiksCubeModel.h"
#include "../Model/MoveStore/ModelTwistStore.h"
#include "../Model/MoveStore/ModelG1TwistStore.h"
#include "../Model/MoveStore/ModelG2TwistStore.h"
#include "../Model/MoveStore/ModelG3TwistStore.h"
#include "../Model/MoveStore/ModelRotationStore.h"
#include "../Model/Goal/Goal.h"
#include "../Model/Goal/OrientG0.h"
#include "../Model/Goal/GoalG0_G1.h"
#include "../Model/Goal/GoalG1_G2.h"
#include "../Model/Goal/GoalG2_G3_Corners.h"
#include "../Model/Goal/GoalG2_G3_Edges.h"
#include "../Model/Goal/GoalG3_Solved.h"
#include "../Model/Goal/GoalG3_Permute_Corners.h"
#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <queue>
using std::queue;
#include <memory>
using std::unique_ptr;
#include <string>
using std::string;

namespace busybin
{
  /**
   * Solver controller for the cube.
   */
  class CubeSolver
  {
    struct GoalAndMoveStore
    {
      unique_ptr<Goal> pGoal;
      MoveStore*       pMoveStore;
    };

    RubiksCubeModel*       pCube;
    queue<string>          moveQueue;
    GoalG3_Permute_Corners g3Perms;
    CubeSearcher           searcher;
    RubiksCubeWriter*      pWriter;

    void processGoalMoves(const Goal& goal, MoveStore& moveStore,
      unsigned goalNum, vector<string>& allMoves, vector<string>& goalMoves);

  public:
    CubeSolver(RubiksCubeModel& cube, RubiksCubeWriter& writer);

    void solveCube();
  };
}

#endif

