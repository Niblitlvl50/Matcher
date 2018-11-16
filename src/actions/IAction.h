
#pragma once

#include <memory>

namespace game
{
    class IAction
    {
    public:

        virtual ~IAction()
        { }

        virtual void Update(unsigned int delta) = 0;
        virtual bool Finished() const = 0;
    };

    using IActionPtr = std::shared_ptr<IAction>;
}
