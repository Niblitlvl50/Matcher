
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
        math::Vector GetLocalCoordinates(const math::Vector& worldCoords) const;
        
        //! Get a cell from local coordinates
        math::Point GetCellFromCoordinates(const math::Vector& localCoords) const;
        
    private:

        virtual void Draw(mono::IRenderer& renderer) const;
        virtual void Update(unsigned int delta);

        const int mCellSize;
    };
}
