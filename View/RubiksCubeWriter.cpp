#include "RubiksCubeWriter.h"
#include <iostream>
using std::cout;
using std::endl;

namespace busybin
{
  /**
   * Initialize the writer.
   * @param fileName The path to the log file.
   */
  RubiksCubeWriter::RubiksCubeWriter(const string& fileName) :
    fileStream(fileName, std::ios::app)
  {
  }

  /**
   * Close the file.
   */
  RubiksCubeWriter::~RubiksCubeWriter()
  {
    for (string ent : this->logEntries)
    {
      this->fileStream << ent << '\n';
    }

    this->fileStream.close();
  }

  /**
   * Write the cube to the file.
   * @param cube The cube.  The state and move will be written.
   * @param move The move to perform given this state.
   */
  void RubiksCubeWriter::write(const RubiksCubeModel& cube, const string& move)
  {
    char          colors[] = {'W', 'G', 'R', 'B', 'O', 'Y'};
    ostringstream buf;

    for (unsigned face = 0; face < 6; ++face)
    {
      for (unsigned row = 0; row < 3; ++row)
      {
        for (unsigned col = 0; col < 3; ++col)
        {
          // Centers are fixed and are skipped to save space.
          if (row != 1 || col != 1)
          {
            buf << colors[(unsigned)cube.get((RubiksCubeModel::FACE)face, row, col)];
          }
        }
      }
    }

    buf << move;

    if (!logEntries.count(buf.str()))
    {
      this->logEntries.insert(buf.str());
      cout << "New entry: "   << buf.str()
           << " Num entries: " << this->logEntries.size()
           << endl;
    }
  }
}

