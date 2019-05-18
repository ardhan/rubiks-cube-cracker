#include "ExactPatternDatabase.h"

#include <iostream>
using std::cout;
using std::endl;

namespace busybin
{
  /**
   * Init.  This database is non-typical, and does not use a NibbleArray (it
   * uses an unordered_map).  Hence the 0.
   */
  ExactPatternDatabase::ExactPatternDatabase(size_t capacity) :
    PatternDatabase(0),
    database(),
    numItems(0),
    capacity(capacity)
  {
  }

  /**
   * Convert the cube to a string, then hash it to get an index into the
   * database.
   */
  size_t ExactPatternDatabase::getDatabaseIndex(const RubiksCube& cube) const
  {
    typedef RubiksCubeIndexModel::CORNER CORNER;
    typedef RubiksCubeIndexModel::EDGE   EDGE;

    const RubiksCubeIndexModel& iCube = static_cast<const RubiksCubeIndexModel&>(cube);

    // A 40-byte string is used to store the cube: 1 byte for each cubie index,
    // and 1 byte for each cubie orientation.
    string cubeStr(40, 0x00);

    // std::hash is used to hash the cube string.
    hash<string> hashFunc;

    for (uint8_t i = 0; i < 8; ++i)
    {
      cubeStr[(2*i)]   = iCube.getCornerIndex((CORNER)i);
      cubeStr[(2*i)+1] = iCube.getCornerOrientation((CORNER)i);
    }

    for (uint8_t i = 0; i < 12; ++i)
    {
      cubeStr[(2*i)+16] = iCube.getEdgeIndex((EDGE)i);
      cubeStr[(2*i)+17] = iCube.getEdgeOrientation((EDGE)i);
    }

    return hashFunc(cubeStr);
  }

  /**
   * Set the number of moves to get to a scrambled cube state using an index.
   */
  bool ExactPatternDatabase::setNumMoves(const size_t ind, const uint8_t numMoves)
  {
    database_t::const_iterator it = this->database.find(ind);

    if (it == this->database.end())
      ++this->numItems;

    if (it == this->database.end() || it->second > numMoves)
    {
      this->database[ind] = numMoves;

      return true;
    }

    return false;
  }

  /**
   * Set the number of moves to get to a scrambled cube state.  The index is
   * computed using getDatabaseIndex.
   */
  bool ExactPatternDatabase::setNumMoves(const RubiksCube& cube, const uint8_t numMoves)
  {
    return this->setNumMoves(this->getDatabaseIndex(cube), numMoves);
  }

  /**
   * Get the number of moves to get to a cube state using an index.  Returns 0
   * if the cube state is not indexed.
   */
  uint8_t ExactPatternDatabase::getNumMoves(const size_t ind) const
  {
    database_t::const_iterator it = this->database.find(ind);

    if (it != this->database.end())
    {
      cout << "Hit with " << (unsigned)it->second << " number of moves." << endl;
    }

    return it == this->database.end() ? 0 : it->second;
  }

  /**
   * Get the number of moves to get to a cube state, or 0 if the state is not
   * indexed.
   */
  uint8_t ExactPatternDatabase::getNumMoves(const RubiksCube& cube) const
  {
    return this->getNumMoves(this->getDatabaseIndex(cube));
  }

  /**
   * Get the number of items indexed in the database.
   */
  size_t ExactPatternDatabase::getNumItems() const
  {
    return this->numItems;
  }

  /**
   * The database is full when the number of items indexed is the capacity.
   */
  bool ExactPatternDatabase::isFull() const
  {
    return this->numItems == this->capacity;
  }

  /**
   * Clear the database.
   */
  void ExactPatternDatabase::reset()
  {
    this->numItems = 0;
    this->database.clear();
  }

  size_t ExactPatternDatabase::getSize() const
  {
    throw RubiksCubeException("ExactPatternDatabase::getSize not implemented.");
  }

  void ExactPatternDatabase::toFile(const string& filePath) const
  {
    throw RubiksCubeException("ExactPatternDatabase::toFile not implemented.");
  }

  bool ExactPatternDatabase::fromFile(const string& filePath)
  {
    throw RubiksCubeException("ExactPatternDatabase::fromFile not implemented.");
  }

  vector<uint8_t> ExactPatternDatabase::inflate() const
  {
    throw RubiksCubeException("ExactPatternDatabase::inflate not implemented.");
  }
}

