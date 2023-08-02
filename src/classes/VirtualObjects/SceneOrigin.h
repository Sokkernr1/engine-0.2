#pragma once

#include "../engine/NodeComponents/BasicNode.h"

namespace Engine
{
    class EngineManager;
}

// TODO: Maybe make SceneOrigin a component in the future?
class SceneOrigin : public Engine::BasicNode
{
    public:
        SceneOrigin() = default;
        ~SceneOrigin() = default;

    private:
        void start() override;
};
