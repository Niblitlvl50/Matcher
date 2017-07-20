
#include "GemGrid.h"
#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "Point.h"
#include <cmath>

using namespace game;

GemGrid::GemGrid(const math::Vector& position, int cellSize)
    : mCellSize(cellSize)
{
    m_position = position;
    m_scale = math::Vector(1.5f, 1.5f);
}

void GemGrid::Draw(mono::IRenderer& renderer) const
{ }

void GemGrid::Update(unsigned int delta)
{ }

math::Point GemGrid::GetLocalCoordinates(const math::Vector& worldCoords)
{
    math::Matrix matrix = Transformation();
    math::Inverse(matrix);

    const math::Vector& output = math::Transform(matrix, worldCoords);
    return math::Point(output.x, output.y) + math::Point(mCellSize / 2, mCellSize / 2);
}

math::Point GemGrid::GetCellFromCoordinates(const math::Point& localCoords)
{
    const math::Vector& cell = math::Vector(localCoords.x, localCoords.y) / float(mCellSize);
    return math::Point(std::floor(cell.x), -std::floor(cell.y));
}
