
#include "MatchingLogic.h"
#include "Gem.h"
#include "Entity/EntityBase.h"
#include "ActionManager.h"
#include "MoveAction.h"
#include "Random.h"
#include "ScoreEvent.h"
#include "EventHandler/EventHandler.h"
#include <stack>

using namespace game;
using namespace std::placeholders;

namespace
{
    std::vector<Match> GetMatchesInRange(GemMatrix::iterator& it)
    {
        std::vector<Match> matches;
        
        // Get the first type
        GemType matchType = (*it)->GetType();
        
        // Set count to once since we have at least one
        int matchCount = 1;
        int matchOffset = 0;
        
        // Step the iterator one step
        ++it;
        
        // Iterate through all items, add one to matchCount if its the same type
        // If the type changes, check if we have a valid match count
        for(; it.HasMore(); ++it)
        {
            const GemType type = (*it)->GetType();
            if(type == matchType)
            {
                ++matchCount;
            }
            else
            {
                // If we change type, check if we have enough for a match
                if(matchCount >= game::MatchesNeeded)
                    matches.push_back(Match(matchOffset, matchOffset + matchCount));
                
                matchCount = 1;
                matchOffset = it.Index();
                matchType = type;
            }
        }
        
        // Special case for when the last cell created a valid match
        if(matchCount >= game::MatchesNeeded)
            matches.push_back(Match(matchOffset, matchOffset + matchCount));
        
        return matches;
    }
}


MatchingLogic::MatchingLogic(GemMatrix& matrix,
                             std::shared_ptr<mono::EntityBase> gemContainer,
                             std::shared_ptr<ActionManager> actionManager,
                             mono::EventHandler& handler)
    : mMatrix(matrix),
      mGemContainer(gemContainer),
      mActionManager(actionManager),
      mEventHandler(handler)
{ }

void MatchingLogic::doUpdate(unsigned int delta)
{
    // Dont do any matching while we have active actions, i.e. stuff that moves around
    if(mActionManager->HasActiveActions())
        return;
    
    // Gather all the matches and process them later
    typedef std::pair<int, std::vector<Match>> MatchPair;
    std::vector<MatchPair> rowMatches;
    std::vector<MatchPair> columnMatches;
    
    // Find matches in rows
    for(int index = 0; index < mMatrix.Rows(); ++index)
    {
        auto it = mMatrix.iterate_row(index);
        const std::vector<Match>& matches = GetMatchesInRange(it);
        if(!matches.empty())
            rowMatches.push_back(std::make_pair(index, matches));
    }
    
    // Find matches in columns
    for(int index = 0; index < mMatrix.Columns(); ++index)
    {
        auto it = mMatrix.iterate_column(index);
        const std::vector<Match>& matches = GetMatchesInRange(it);
        if(!matches.empty())
            columnMatches.push_back(std::make_pair(index, matches));
    }
    
    // Deal with row matches
    for(const MatchPair& match : rowMatches)
        HandleMatchesInRow(match.first, match.second);

    // Deal with column matches
    for(const MatchPair& match : columnMatches)
        HandleMatchesInColumn(match.first, match.second);
    
    //             |
    // Do this...  v
    FillEmptyCellsWithGems();

    // Remove all the stuff that needs to be removed, its safe to do it here
    for(mono::IEntityPtr gem : mGemsToRemove)
        mGemContainer->RemoveChild(gem);
    
    mGemsToRemove.clear();
}

void MatchingLogic::FillEmptyCellsWithGems()
{
    for(int column = 0; column < mMatrix.Columns(); ++column)
    {
        std::stack<std::shared_ptr<Gem>> gems;
        for(auto it = mMatrix.iterate_column(column); it.HasMore(); ++it)
        {
            // An empty cell will contain nullptr
            auto gem = *it;
            if(gem)
                gems.push(gem);
        }
        
        // Check if we have empty cells or not
        const int emptyCells = mMatrix.Rows() - int(gems.size());
        if(emptyCells == 0)
            continue;

        int row = mMatrix.Rows() -1;
        
        // Move down the existing gems
        while(!gems.empty())
        {
            auto gem = gems.top();
            gems.pop();

            mMatrix.Assign(gem, row, column);
            
            const math::Vector position(column * CellSize, row * -CellSize);
            auto action = std::make_shared<MoveAction>(gem, position, 400);
            mActionManager->AddAction(action);

            --row;
        }
        
        // Create new gems for the empty cells that are left
        while(row >= 0)
        {
            auto newGem = game::CreateRandomGem(math::Vector(column * CellSize, 60));
            const math::Vector position(column * CellSize, row * -CellSize);

            auto action = std::make_shared<MoveAction>(newGem, position, 400);
            mActionManager->AddAction(action);
            mGemContainer->AddChild(newGem);
            mMatrix.Assign(newGem, row, column);

            --row;
        }
    }
}


void MatchingLogic::HandleMatchesInRow(int row, const std::vector<Match>& matches)
{
    const auto matchFunc = std::bind(&MatchingLogic::HandleMatch, this, row, _1);
    for(const Match& match : matches)
    {
        for(int index = match.first; index < match.second; ++index)
            matchFunc(index);
    }
}

void MatchingLogic::HandleMatchesInColumn(int column, const std::vector<Match>& matches)
{
    const auto matchFunc = std::bind(&MatchingLogic::HandleMatch, this, _1, column);
    for(const Match& match : matches)
    {
        for(int index = match.first; index < match.second; ++index)
            matchFunc(index);
    }
}

void MatchingLogic::HandleMatch(int row, int column)
{
    // The gem can be nullptr if it was part of both a vertical and a horizontal match
    auto oldGem = mMatrix.Get(row, column);
    if(!oldGem)
        return;
    
    mMatrix.Assign(nullptr, row, column);
    
    const int duration = mono::RandomInt(600, 800);
    auto action = std::make_shared<MoveAction>(oldGem, math::Vector(0, -380), duration);
    action->SetCallback(std::bind(&MatchingLogic::HandleRemoveGem, this, _1));
    
    mActionManager->AddAction(action);
}

void MatchingLogic::HandleRemoveGem(mono::IEntityPtr gem)
{
    // Stuff that will be removed in the next frame
    mGemsToRemove.push_back(gem);
    mEventHandler.DispatchEvent(ScoreEvent());
}

bool game::HasMatchInRange(GemMatrix::iterator& it)
{
    return !GetMatchesInRange(it).empty();
}



