#include "IDACubeSearcher.h"

namespace busybin
{
  /**
   * Initialize the searcher with a PatternDatabase instance.
   * @param pPatternDatabase A pointer to a PatternDatabase that will be used
   * to get an estimated distance from a scramble to the solved state.
   */
  IDACubeSearcher::IDACubeSearcher(const PatternDatabase* pPatternDB) :
    CubeSearcher(), pPatternDB(pPatternDB)
  {
  }

  /**
   * Search the cube until goal is reached and return the moves required
   * to achieve goal.
   * @param goal The goal to achieve (isSatisfied is called on the goal).
   * @param cube The cube to search.
   * @param moveStore A MoveStore instance for retrieving moves.
   */
  vector<string> IDACubeSearcher::findGoal(Goal& goal, RubiksCubeModel& cube,
    MoveStore& moveStore)
  {
    AutoTimer      timer;
    vector<string> moves;
    uint8_t        bound  = this->pPatternDB->getNumMoves(cube);
    bool           solved = false;
    seen_t         seen;

    seen.insert(cube);

    while (!solved)
    {
      uint8_t newBound = this->findGoal(goal, cube, moveStore, bound, moves, solved, seen);

      cout << "IDA*: Finished bound " << (unsigned)bound << ".  Elapsed time "
           << timer.getElapsedSeconds() << "s." << endl;

      bound = newBound;
    }

    return moves;
  }

  /**
   * Private helper method that recursively searches for a goal, and cuts off
   * when bound is reached.
   * @param goal The goal to achieve.
   * @param cube The cube to search.
   * @param moveStore A MoveStore instance for retrieving moves.
   * @param bound The cut-off point, which is an maximum estimated distance from
   * the root state to the solved state.
   * @param moves A vector of moves that will be filled.
   * @param solved A boolean that will be set to true when solved.
   * @param seen A set of cubes that have been seen on this path.
   */
  uint8_t IDACubeSearcher::findGoal(Goal& goal, RubiksCubeModel& cube, MoveStore& moveStore,
    const uint8_t& bound, vector<string>& moves, bool& solved, seen_t& seen)
  {
    // Estimated number of moves to the solved state from here.
    uint8_t estMovesFromHere = this->pPatternDB->getNumMoves(cube);

    // This holds the next bound, which is the minimum cost that's greater than
    // the current bound.
    uint8_t min = 0xFF;

    // This keeps track of the current move index in moveStore.
    uint8_t moveInd = 0;

    // This keeps track of the move priority index.
    uint8_t movePrio = 0;

    if (moves.size() + estMovesFromHere > bound)
      return moves.size() + estMovesFromHere;

    // This assumes that the heuristic returns 0 cost when the cube is solved.
    //if (estMovesFromHere == 0 && goal.isSatisfied(cube)) {
    if (goal.isSatisfied(cube)) {
      solved = true;
      return moves.size() + estMovesFromHere;
    }

    // Keep track of this state so that if it's seen later it can be pruned.
    seen.insert(cube);

    while (!solved && (moveInd = this->getNextMove(movePrio++, cube, moveStore, moves, seen)) != 0xFF)
    {
      // Apply the next move.
      moves.push_back(moveStore.getMove(moveInd));
      moveStore.getMoveFunc(moveStore.getMove(moveInd))();

      uint8_t succCost = this->findGoal(goal, cube, moveStore, bound, moves,
        solved, seen);

      if (!solved)
      {
        moves.pop_back();

        if (succCost < min)
          min = succCost;
      }

      // Revert the move.
      moveStore.getInverseMoveFunc(moveStore.getMove(moveInd))();
    }

    seen.erase(cube);
    return min;
  }

  /**
   * Given a move index, returns the next successor prioritized by cost.
   */
  uint8_t IDACubeSearcher::getNextMove(uint8_t movePrio, RubiksCubeModel& cube,
    MoveStore& moveStore, const vector<string>& moves, const seen_t& seen) const
  {
    typedef priority_queue<PrioritizedMove, vector<PrioritizedMove>,
      greater<PrioritizedMove> > moveQueue_t;

    uint8_t numMoves = moveStore.getNumMoves();
    moveQueue_t successors;

    // Set up the successor nodes in order.
    for (uint8_t i = 0; i < numMoves; ++i)
    {
      string move = moveStore.getMove(i);

      if (!this->prune(move, moves))
      {
        // Apply the next move.
        moveStore.getMoveFunc(move)();

        if (!seen.count(cube))
        {
          // Get the estimated moves to solved.
          uint8_t estSuccMoves = moves.size() + 1 + this->pPatternDB->getNumMoves(cube);

          // Queue the successor.
          successors.push({i, estSuccMoves});
        }

        // Revert the move.
        moveStore.getInverseMoveFunc(move)();
      }
    }

    if (movePrio < successors.size())
    {
      for (uint8_t i = 0; i < successors.size(); ++i)
      {
        uint8_t nextMoveInd = successors.top().moveInd;
        successors.pop();

        if (i == movePrio)
          return nextMoveInd;
      }
    }

    return 0xFF;
  }
}

