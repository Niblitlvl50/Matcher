
#pragma once

#include "ObjectMatrix.h"
#include <memory>

namespace game
{
    // Gems in a row to be counted as a match
    constexpr int MatchesNeeded = 3;
    
    // Size of each cell in the grid, in pixels
    constexpr int CellSize = 40;
    
    using GemPtr = std::shared_ptr<class Gem>;
    using GemMatrix = ObjectMatrix<GemPtr, 8, 8>;
}