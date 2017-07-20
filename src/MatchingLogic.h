
#pragma once

#include "IUpdatable.h"
#include "MonoPtrFwd.h"
#include "Globals.h"
#include <vector>

namespace mono
{
    class EntityBase;
}

namespace game
{
    class ActionManager;
    typedef std::pair<int, int> Match;
    
    // Logic that will perform matches on the cells
    class MatchingLogic : public mono::IUpdatable
    {
    public:
        
        //! Constructor that takes the matrix, container and an action manager
        //! @param[in] matrix The gem matrix data type, contains all the gems
        //! @param[in] gemContainer An object that holds and draws the gems
        //! @param[in] actionManager The action manager, performs actions on enteties
        MatchingLogic(GemMatrix& matrix,
                      std::shared_ptr<mono::EntityBase> gemContainer,
                      std::shared_ptr<ActionManager> actionManager,
                      mono::EventHandler& handler);
        
        virtual void doUpdate(unsigned int delta);
        
    private:
        
        void FillEmptyCellsWithGems();
        
        void HandleMatchesInRow(int row, const std::vector<Match>& matches);
        void HandleMatchesInColumn(int column, const std::vector<Match>& matches);
        void HandleMatch(int row, int column);
        void HandleRemoveGem(mono::IEntityPtr gem);
        
        GemMatrix& mMatrix;
        std::shared_ptr<mono::EntityBase> mGemContainer;
        std::shared_ptr<ActionManager> mActionManager;
        mono::EventHandler& mEventHandler;
        
        std::vector<mono::IEntityPtr> mGemsToRemove;
    };
    
    //! Function for checking if a range contains a match
    //! @param[in] it A GemMatrix iterator
    //! @return bool If this range has a valid match
    bool HasMatchInRange(GemMatrix::iterator& it);
}
