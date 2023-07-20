#pragma once

#include <vector>

namespace Engine
{
    class WindowManager;

    class BasicNode
    {
        public:
            BasicNode() = default;
            virtual ~BasicNode() = default;

            virtual void start() {};
            virtual void update() {};

            void addAsChild(std::shared_ptr<BasicNode> node);
            void removeFromParent(std::shared_ptr<BasicNode> node);
            void setParent(std::shared_ptr<BasicNode> node) { m_parentNode = node; };

            std::shared_ptr<BasicNode> getParentNode() const { return m_parentNode; };
            std::shared_ptr<BasicNode> getChildNode(int pos) const;
            std::vector<std::shared_ptr<BasicNode>> getChildNodes() const { return m_childNodes; };
            int getChildCount() const { return int(m_childNodes.size()); };

            void removeAllChildNodes();
            void callOnAllNodes(const std::function<void(BasicNode*)>& func);

            static void setWindowManager(WindowManager* newWindowManager) { windowManager = newWindowManager; };
            static WindowManager* getWindowManager() { return windowManager; };
        private:
            std::shared_ptr<BasicNode> m_parentNode;
            std::vector<std::shared_ptr<BasicNode>> m_childNodes;

            static WindowManager* windowManager;
    };
}