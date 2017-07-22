
#include "GemGrid.h"
#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "Math/Point.h"
#include <cmath>

using namespace game;

GemGrid::GemGrid(const math::Vector& position, int cellSize)
    : mCellSize(cellSize)
{
    m_position = position;
    m_scale = math::Vector(1.8f, 1.8f);
}

void GemGrid::Draw(mono::IRenderer& renderer) const
{ }

void GemGrid::Update(unsigned int delta)
{ }

math::Vector GemGrid::GetLocalCoordinates(const math::Vector& worldCoords) const
{
    math::Matrix matrix = Transformation();
    math::Inverse(matrix);

    const math::Vector& output = math::Transform(matrix, worldCoords);
    return output + math::Vector(mCellSize / 2, mCellSize / 2);
}

math::Point GemGrid::GetCellFromCoordinates(const math::Vector& localCoords) const
{
    const math::Vector& cell = localCoords / float(mCellSize);
    return math::Point(std::floor(cell.x), -std::floor(cell.y));
}
