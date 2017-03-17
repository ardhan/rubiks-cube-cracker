#include "CubeSolver.h"

namespace busybin
{
  /**
   * Init.
   * @param cube The model to solve.
   */
  CubeSolver::CubeSolver(RubiksCubeModel& cube, RubiksCubeWriter& writer) :
    pCube(&cube), pWriter(&writer)
  {
    // This twist store contains 180-degree twists only (L2, R2, etc.).
    ModelG3TwistStore mdlG3TwistStore(*this->pCube);

    // The cube solver (completely arbitrarily) keeps red on the top and white
    // up front.  X Y2 puts the cube in that state.
    this->pCube->x();
    this->pCube->y2();

    // Generate all corner permutations that can be reached from the solved state
    // using only double twists.  These are stored in this->g3Perms, and used
    // by Group 2 goals.
    this->searcher.findGoal(this->g3Perms, *this->pCube, mdlG3TwistStore);
  }

  /**
   * Solve the cube.  This is run in a separate thread.
   */
  void CubeSolver::solveCube()
  {
    RubiksCubeView             cubeView;
    vector<string>             allMoves;
    vector<string>             goalMoves;
    ModelTwistStore            mdlTwistStore(*this->pCube);
    ModelG1TwistStore          mdlG1TwistStore(*this->pCube);
    ModelG2TwistStore          mdlG2TwistStore(*this->pCube);
    ModelG3TwistStore          mdlG3TwistStore(*this->pCube);
    ModelRotationStore         mdlRotStore(*this->pCube);
    vector<GoalAndMoveStore>   goals;

    // Create the goals.
    goals.push_back({unique_ptr<Goal>(new OrientG0()),                       &mdlRotStore});
    goals.push_back({unique_ptr<Goal>(new GoalG0_G1()),                      &mdlTwistStore});
    goals.push_back({unique_ptr<Goal>(new GoalG1_G2()),                      &mdlG1TwistStore});
    goals.push_back({unique_ptr<Goal>(new GoalG2_G3_Corners(this->g3Perms)), &mdlG2TwistStore});
    goals.push_back({unique_ptr<Goal>(new GoalG2_G3_Edges(this->g3Perms)),   &mdlG2TwistStore});
    goals.push_back({unique_ptr<Goal>(new GoalG3_Solved()),                  &mdlG3TwistStore});

    // Display the intial cube model.
    cout << "Initial cube state." << endl;
    cubeView.render(*this->pCube);
    cout << "Need to achieve " << goals.size() << " goals." << endl;

    for (unsigned i = 0; i < goals.size(); ++i)
    {
      // Find the goal, move to the goal, and then show the cube.
      goalMoves = this->searcher.findGoal(*goals[i].pGoal, *this->pCube, *goals[i].pMoveStore);
      this->processGoalMoves(*goals[i].pGoal, *goals[i].pMoveStore, i + 1, allMoves, goalMoves);
      cubeView.render(*this->pCube);
    }

    // Print the moves.
    cout << "\n\nSolved the cube in " << allMoves.size() << " moves.\n";

    for (string move : allMoves)
      cout << move << ' ';
    cout << endl;

    // Display the cube model.
    cout << "Resulting cube.\n";
    cubeView.render(*this->pCube);
  }

  /**
   * Helper function to process moves after a goal is achived.
   * @param goal The goal for verbosity.
   * @param moveStore The MoveStore for processing the moves
   *        in the RC model copy.
   * @param goalNum The goal number for verbosity.
   * @param allMoves This vector holds all the moves thus far.  The
   *        goalMoves vector will be appended to it.
   * @param goalMoves This vector holds the moves required to achieve
   *        the goal.  These moves will be queued for the GL cube to
   *        display, then the vector will be cleared.
   */
  void CubeSolver::processGoalMoves(const Goal& goal, MoveStore& moveStore,
    unsigned goalNum, vector<string>& allMoves, vector<string>& goalMoves)
  {
    cout << "Found goal " << goalNum << ": " << goal.getDescription() << '\n' << endl;

    // Add goalMoves to the end of allMoves.
    allMoves.insert(allMoves.end(), goalMoves.begin(), goalMoves.end());

    for (string move : goalMoves)
    {
      this->pWriter->write(*this->pCube, move);
      moveStore.getMoveFunc(move)();
    }

    // Clear the vector for the next goal.
    goalMoves.clear();
  }
}

