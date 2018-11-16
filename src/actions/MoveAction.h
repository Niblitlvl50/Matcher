
#pragma once

#include "IAction.h"
#include "Math/Vector.h"
#include "MonoPtrFwd.h"

#include <functional>

namespace game
{
    class MoveAction : public IAction
    {
    public:
        
        //! Move action, will move a entity over time
        //! @param[in] entity The entity to move
        //! @param[in] target Target position
        //! @param[in] duration Time in milliseconds for the action
        MoveAction(mono::IEntityPtr entity, const math::Vector& target, unsigned int duration);
        
        //! Sets a callback that will be called when the action has finished
        //! @param[in] callback A callback function
        void SetCallback(const std::function<void (mono::IEntityPtr)>& callback);

    private:
        
        virtual void Update(unsigned int delta);
        virtual bool Finished() const;
        
        mono::IEntityPtr mEntity;
        const math::Vector mTarget;
        const unsigned int mDuration;
        unsigned int mCounter;
        bool mDoOnce;
        
        math::Vector mPosition;
        math::Vector mVector;
        
        std::function<void (mono::IEntityPtr)> mCallback;
    };
}
