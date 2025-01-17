#pragma once

#include "../nodeComponents/UiDebugWindow.h"

namespace Engine
{
    class EngineManager;

    namespace Ui
    {
        class UiElementPlot;
        class UiElementText;

        class SceneSettingsDebugWindow : public UiDebugWindow
        {
            public:
                SceneSettingsDebugWindow();
                ~SceneSettingsDebugWindow() = default;

                void update() override;

            private:
                void onWireframeToggle(bool value) const;
                void onGridToggle(bool value) const;

                std::shared_ptr<EngineManager> m_engineManager;
        };
    } // namespace Ui
} // namespace Engine