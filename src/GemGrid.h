
#pragma once

#include "Entity/EntityBase.h"

namespace game
{
    class GemGrid : public mono::EntityBase
    {
    public:
        
        //! Constructor
        //! @param[in] position Where the grid is positioned in world coordinates
        //! @param[in] cellSize Size of each cell in the grid, horizontal and vertical
        GemGrid(const math::Vector& position, int cellSize);
        
        //! Convert world coordinates to local coordinates
        math::Point GetLocalCoordinates(const math::Vector& worldCoords);
        
        //! Get a cell from local coordinates
        math::Point GetCellFromCoordinates(const math::Point& localCoords);
        
    private:

        virtual void Draw(mono::IRenderer& renderer) const;
        virtual void Update(unsigned int delta);

        const int mCellSize;
    };
}
