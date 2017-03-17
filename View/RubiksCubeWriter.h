#ifndef _BUSYBIN_RUBIKS_CUBE_WRITER_H_
#define _BUSYBIN_RUBIKS_CUBE_WRITER_H_

#include "../Model/RubiksCubeModel.h"
#include <fstream>
using std::ofstream;
#include <string>
using std::string;
#include <sstream>
using std::ostringstream;
#include <set>
using std::set;

namespace busybin
{
  /**
   * File writer for the cube.
   */
  class RubiksCubeWriter
  {
    ofstream    fileStream;
    set<string> logEntries;

  public:
    RubiksCubeWriter(const string& fileName);
    ~RubiksCubeWriter();
    void write(const RubiksCubeModel& cube, const string& move);
  };
}

#endif

