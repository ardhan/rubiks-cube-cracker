#ifndef _BUSYBIN_EDGE_G2_PATTERN_DATABASE_
#define _BUSYBIN_EDGE_G2_PATTERN_DATABASE_

#include "../../RubiksCubeModel.h"
#include "EdgePatternDatabase.h"
#include <cstdint>

namespace busybin
{
  /**
   * A database for 6 of the 12 edge positions that indexes edge positions and
   * the number of moves required to get the edges to the solved state.  The 6
   * edges are the chosen such that there's at least one edge on each side,
   * which improves pruning performance in the breadth-first search.
   */
  class EdgeG2PatternDatabase : public EdgePatternDatabase
  {
  public:
    uint32_t getDatabaseIndex(const RubiksCubeModel& cube) const;
  };
}

#endif
