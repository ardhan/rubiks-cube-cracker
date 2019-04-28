#include "EdgeG1PatternDatabase.h"

namespace busybin
{
  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t EdgeG1PatternDatabase::getDatabaseIndex(const RubiksCubeModel& cube) const
  {
    // UR RG 1.
    edge_t ur =
    {
      cube.get(F::UP,    1, 2),
      cube.get(F::RIGHT, 0, 1)
    };

    // UL RB 3.
    edge_t ul =
    {
      cube.get(F::UP,   1, 0),
      cube.get(F::LEFT, 0, 1)
    };

    // FL WB 5.
    edge_t fl =
    {
      cube.get(F::FRONT, 1, 0),
      cube.get(F::LEFT,  1, 2)
    };

    // BR YG 7.
    edge_t br =
    {
      cube.get(F::BACK,  1, 0),
      cube.get(F::RIGHT, 1, 2)
    };

    // DF OW 8.
    edge_t df =
    {
      cube.get(F::DOWN,  0, 1),
      cube.get(F::FRONT, 2, 1)
    };

    // DB OY 10.
    edge_t db =
    {
      cube.get(F::DOWN, 2, 1),
      cube.get(F::BACK, 2, 1)
    };

    perm_t edgePerm =
    {
      this->getCubieIndex(ur),
      this->getCubieIndex(ul),
      this->getCubieIndex(fl),
      this->getCubieIndex(br),
      this->getCubieIndex(df),
      this->getCubieIndex(db)
    };

    // Now get the orientation of each edge.
    array<uchar, 6> edgeOrientations =
    {
      this->getCubieOrientation(ur),
      this->getCubieOrientation(ul),
      this->getCubieOrientation(fl),
      this->getCubieOrientation(br),
      this->getCubieOrientation(df),
      this->getCubieOrientation(db)
    };

    return EdgePatternDatabase::getDatabaseIndex(edgePerm, edgeOrientations);
  }
}

