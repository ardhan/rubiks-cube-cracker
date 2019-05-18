#include "ExactDatabaseGoal.h"

namespace busybin
{
  /**
   * Init, storing a pointer to the database.
   * @param pDatabase A pointer to a pattern database.
   */
  ExactDatabaseGoal::ExactDatabaseGoal(ExactPatternDatabase* pDatabase) :
    DatabaseGoal(pDatabase)
  {
  }

  /**
   * Describe the goal.
   */
  string ExactDatabaseGoal::getDescription() const
  {
    return "Create a database of all cube states to a certain depth.";
  }
}

