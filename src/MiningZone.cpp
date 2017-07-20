
#include "MiningZone.h"

#include "Point.h"
#include "Background.h"
#include "GemGrid.h"
#include "Gem.h"
#include "FuseFlame.h"

#include "Math/Vector.h"
#include "Rendering/ICamera.h"

#include "EventHandler/EventHandler.h"
#include "Events/EventFuncFwd.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"
#include "Events/QuitEvent.h"

#include "CountdownEvent.h"
#include "MatchingLogic.h"

#include "ActionManager.h"
#include "MoveAction.h"
#include "SequenceAction.h"

#include "CountdownTimer.h"
#include "ScoreCounter.h"

#include "RenderLayers.h"

#include <cstdlib>

using namespace game;


MiningZone::MiningZone(mono::EventHandler& eventHandler)
    : mEventHandler(eventHandler),
      mHasSelectedGem(false)
{
    using namespace std::placeholders;
    const event::MouseUpEventFunc mouseUpFunc = std::bind(&MiningZone::OnMouseUp, this, _1);
    mMouseUpToken = mEventHandler.AddListener(mouseUpFunc);
    
    const event::KeyUpEventFunc onKeyUpFunc = std::bind(&MiningZone::OnKeyUp, this, _1);
    mKeyUpToken = mEventHandler.AddListener(onKeyUpFunc);
    
    std::function<bool (const CountdownEvent&)> func = std::bind(&MiningZone::OnCountdown, this, _1);
    mCountdownToken = mEventHandler.AddListener(func);
}

MiningZone::~MiningZone()
{
    mEventHandler.RemoveListener(mMouseUpToken);
    mEventHandler.RemoveListener(mKeyUpToken);
    mEventHandler.RemoveListener(mCountdownToken);
}

void MiningZone::OnLoad(mono::ICameraPtr& camera)
{
    // Set camera and create the background and the top of the frame around the gems
    camera->SetPosition(math::Vector(0, 0));
    AddEntity(std::make_shared<Background>(), BACKGROUND);
    //AddEntity(std::make_shared<BackgroundTop>(), FOREGROUND);
    
    // Create the fuses flame, this was meant to move along the fuse but there was no time...
    //AddEntity(std::make_shared<FuseFlame>(math::Vector(-110, -255)), MIDDLEGROUND);
    
    // GemGrid is the holder of all the gems which makes the positioning easier
    mGemGrid = std::make_shared<GemGrid>(math::Vector(-200, 200), CellSize);
    AddEntity(mGemGrid, MIDDLEGROUND);
    
    // Create and assign the gems
    for(int row = 0; row < mMatrix.Rows(); ++row)
    {
        for(int column = 0; column < mMatrix.Columns(); ++column)
        {
            const math::Vector position(column * CellSize, row * -CellSize);
            auto gem = game::CreateRandomGem(position);
            mGemGrid->AddChild(gem);
            mMatrix.Assign(gem, row, column);
        }
    }
    
    // Add the counters
    AddEntity(std::make_shared<CountdownTimer>(60, math::Vector(0, 350), mEventHandler), FOREGROUND);
    AddEntity(std::make_shared<ScoreCounter>(math::Vector(-200, -350), mEventHandler), FOREGROUND);
    
    // Create the action manager
    mActionManager = std::make_shared<ActionManager>();
    AddUpdatable(mActionManager);

    // Create logic and add as a updater
    AddUpdatable(std::make_shared<MatchingLogic>(mMatrix, mGemGrid, mActionManager, mEventHandler));
}

void MiningZone::OnUnload()
{ }

bool MiningZone::OnCountdown(const game::CountdownEvent& event)
{
    mEventHandler.DispatchEvent(event::QuitEvent());
    return false;
}

bool MiningZone::OnKeyUp(const event::KeyUpEvent& event)
{
    if(event.key == Keycode::ESCAPE)
        mEventHandler.DispatchEvent(event::QuitEvent());
    
    return false;
}

bool MiningZone::OnMouseUp(const event::MouseUpEvent& event)
{
    const math::Point local = mGemGrid->GetLocalCoordinates(math::Vector(event.worldX, event.worldY));
    const math::Point cell = mGemGrid->GetCellFromCoordinates(local);
    
    // Validate clicked cell, else reset and return
    const bool validCell = mMatrix.Validate(cell.y, cell.x);
    if(!validCell)
    {
        mHasSelectedGem = false;
        mMatrix.Get(mSelectedCell.y, mSelectedCell.x)->SetSelected(false);
        return false;
    }
    
    // If we dont have a selected gem, save the clicked cell and return
    if(!mHasSelectedGem)
    {
        mSelectedCell = cell;
        mHasSelectedGem = true;
        mMatrix.Get(cell.y, cell.x)->SetSelected(true);
        return false;
    }
    
    // If we end up here, we have a valid cell previously selected and now its time to swap gems
    
    const auto IsValidNeighbour = [](const math::Point& first, const math::Point& second) {
        const math::Point diff = first - second;
        
        const bool xIsValid = (std::abs(diff.x) == 1);
        const bool xIsZero  = (std::abs(diff.x) == 0);
        
        const bool yIsValid = (std::abs(diff.y) == 1);
        const bool yIsZero  = (std::abs(diff.y) == 0);
        
        return (xIsValid && yIsZero) || (xIsZero && yIsValid);
    };

    // Save the selected gem for reset after possible match
    auto selectedGem = mMatrix.Get(mSelectedCell.y, mSelectedCell.x);

    // Check that we have selected a valid neighbour, prevent diagonal selection
    // and cells that are further away than one cell
    const bool validNeighbour = IsValidNeighbour(mSelectedCell, cell);
    if(validNeighbour)
        DoSwap(cell);
    
    // Reset selected gem...
    mHasSelectedGem = false;
    selectedGem->SetSelected(false);

    return false;
}

void MiningZone::DoSwap(const math::Point& cell)
{
    const auto IsHorizontalSwap = [](const math::Point& first, const math::Point& second) {
        const math::Point diff = first - second;
        return (std::abs(diff.y) == 0);
    };

    // Get objects
    auto selectedGem = mMatrix.Get(mSelectedCell.y, mSelectedCell.x);
    auto neighbourGem = mMatrix.Get(cell.y, cell.x);
    
    // Swap
    mMatrix.Swap(mSelectedCell.y, mSelectedCell.x, cell.y, cell.x);
    
    // Get iterators to the affected ranges
    const bool horizontalSwap = IsHorizontalSwap(mSelectedCell, cell);
    GemMatrix::iterator temp = horizontalSwap ? mMatrix.iterate_column(cell.x) : mMatrix.iterate_row(mSelectedCell.y);
    GemMatrix::iterator column = mMatrix.iterate_column(mSelectedCell.x);
    GemMatrix::iterator row = mMatrix.iterate_row(cell.y);
    
    // Check if any range got a match
    const bool matches1 = game::HasMatchInRange(temp);
    const bool matches2 = game::HasMatchInRange(column);
    const bool matches3 = game::HasMatchInRange(row);
    
    // If we have a match then move them. Else swap back.
    const bool willMatch = matches1 || matches2 || matches3;
    if(willMatch)
    {
        // Do swap animation
        mActionManager->AddAction(std::make_shared<MoveAction>(selectedGem, neighbourGem->Position(), 200));
        mActionManager->AddAction(std::make_shared<MoveAction>(neighbourGem, selectedGem->Position(), 200));
    }
    else
    {
        // Swap back!
        mMatrix.Swap(mSelectedCell.y, mSelectedCell.x, cell.y, cell.x);
        
        // Do swap back and forth animation
        auto sequence1 = std::make_shared<SequenceAction>();
        sequence1->AddAction(std::make_shared<MoveAction>(selectedGem, neighbourGem->Position(), 200));
        sequence1->AddAction(std::make_shared<MoveAction>(selectedGem, selectedGem->Position(), 200));
        mActionManager->AddAction(sequence1);
        
        auto sequence2 = std::make_shared<SequenceAction>();
        sequence2->AddAction(std::make_shared<MoveAction>(neighbourGem, selectedGem->Position(), 200));
        sequence2->AddAction(std::make_shared<MoveAction>(neighbourGem, neighbourGem->Position(), 200));
        mActionManager->AddAction(sequence2);
    }
}
