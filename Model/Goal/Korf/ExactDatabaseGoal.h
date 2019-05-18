#ifndef _BUSYBIN_EXACT_DATABASE_GOAL_H_
#define _BUSYBIN_EXACT_DATABASE_GOAL_H_

#include "../DatabaseGoal.h"
#include "../../PatternDatabase/Korf/ExactPatternDatabase.h"

namespace busybin
{
  /**
   * A goal for populating an ExactPatternDatabase.  It holds all the possible
   * cube states up to a certain depth.
   */
  class ExactDatabaseGoal : public DatabaseGoal
  {
  public:
    ExactDatabaseGoal(ExactPatternDatabase* pDatabase);
    string getDescription() const;
  };
}

#endif

