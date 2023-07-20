#pragma once

#include "../engine/NodeComponents/BasicNode.h"

namespace Engine { class EngineManager; }

class SceneOrigin : public Engine::BasicNode
{
    public:
        SceneOrigin() = default;
        ~SceneOrigin() = default;
    private:
        Engine::EngineManager* m_engineManager;
        void start() override;


};
