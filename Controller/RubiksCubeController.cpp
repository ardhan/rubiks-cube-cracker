#include "RubiksCubeController.h"

namespace busybin
{
  /**
   * Main controller.
   */
  void RubiksCubeController::run()
  {
    try
    {
      RubiksCubeWriter writer("training.dat");
      unsigned         iteration = 0;

      while (iteration++ < 1000)
      {
        RubiksCubeModel  cube;
        CubeSolver       solver(cube, writer);

        cout << "\n\nStarting iteration: " << iteration << "\n\n" << endl;

        cube.scramble(100);
        solver.solveCube();
      }
    }
    catch (const exception& ex)
    {
      cout << "Exception encountered.\n" << ex.what() << endl;
    }
  }
}

