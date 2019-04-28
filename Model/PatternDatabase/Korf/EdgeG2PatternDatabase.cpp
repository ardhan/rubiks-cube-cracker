#include "EdgeG2PatternDatabase.h"

namespace busybin
{
  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t EdgeG2PatternDatabase::getDatabaseIndex(const RubiksCubeModel& cube) const
  {
    // UB RY 0.
    edge_t ub =
    {
      cube.get(F::UP,   0, 1),
      cube.get(F::BACK, 0, 1)
    };

    // UF RW 2.
    edge_t uf =
    {
      cube.get(F::UP,    2, 1),
      cube.get(F::FRONT, 0, 1)
    };

    // FR WG 4.
    edge_t fr =
    {
      cube.get(F::FRONT, 1, 2),
      cube.get(F::RIGHT, 1, 0)
    };

    // BL YB 6.
    edge_t bl =
    {
      cube.get(F::BACK, 1, 2),
      cube.get(F::LEFT, 1, 0)
    };

    // DL OB 9.
    edge_t dl =
    {
      cube.get(F::DOWN, 1, 0),
      cube.get(F::LEFT, 2, 1)
    };

    // DR OG 11.
    edge_t dr =
    {
      cube.get(F::DOWN,  1, 2),
      cube.get(F::RIGHT, 2, 1)
    };

    perm_t edgePerm =
    {
      this->getCubieIndex(ub),
      this->getCubieIndex(uf),
      this->getCubieIndex(fr),
      this->getCubieIndex(bl),
      this->getCubieIndex(dl),
      this->getCubieIndex(dr)
    };

    // Now get the orientation of each edge.
    array<uchar, 6> edgeOrientations =
    {
      this->getCubieOrientation(ub),
      this->getCubieOrientation(uf),
      this->getCubieOrientation(fr),
      this->getCubieOrientation(bl),
      this->getCubieOrientation(dl),
      this->getCubieOrientation(dr)
    };

    return EdgePatternDatabase::getDatabaseIndex(edgePerm, edgeOrientations);
  }
}

