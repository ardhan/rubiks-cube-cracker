#ifndef _BUSYBIN_EXACT_PATTERN_DATABASE_H_
#define _BUSYBIN_EXACT_PATTERN_DATABASE_H_

#include "../PatternDatabase.h"
#include "../../RubiksCube.h"
#include "../../RubiksCubeIndexModel.h"
#include "../../../Util/RubiksCubeException.h"
#include <string>
using std::string;
#include <functional>
using std::hash;
#include <unordered_map>
using std::unordered_map;

namespace busybin
{
  /**
   * A pattern database that holds all scrambles of the cube up to a certain
   * depth.  The number of moves associated with a cube state is thus an exact
   * heuristic.  But since only scrambles to a certain depth are stored, this
   * database is only useful when the cube is nearly solved.
   */
  class ExactPatternDatabase : public PatternDatabase
  {
    typedef unordered_map<size_t, uint8_t> database_t;

    database_t database;
    size_t numItems;
    size_t capacity;

  public:
    ExactPatternDatabase(size_t capacity);

    size_t getDatabaseIndex(const RubiksCube& cube) const;
    bool setNumMoves(const size_t ind, const uint8_t numMoves);
    bool setNumMoves(const RubiksCube& cube, const uint8_t numMoves);
    uint8_t getNumMoves(const size_t ind) const;
    uint8_t getNumMoves(const RubiksCube& cube) const;
    size_t getNumItems() const;
    bool isFull() const;

    size_t getSize() const;
    void toFile(const string& filePath) const;
    bool fromFile(const string& filePath);
    vector<uint8_t> inflate() const;
    void reset();
  };
}

#endif

