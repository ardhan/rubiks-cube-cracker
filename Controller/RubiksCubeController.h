#ifndef _BUSYBIN_RUBIKS_CUBE_CONTROLLER_H_
#define _BUSYBIN_RUBIKS_CUBE_CONTROLLER_H_

#include "../Model/RubiksCubeModel.h"
#include "../View/RubiksCubeWriter.h"
#include "CubeSolver.h"
#include <iostream>
using std::cout;
using std::endl;
#include <exception>
using std::exception;

namespace busybin
{
  class RubiksCubeController
  {
  public:
    void run();
  };
}

#endif

