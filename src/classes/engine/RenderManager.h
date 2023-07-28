#pragma once

#include "ObjectHelper.h"

#include <string>
#include <vector>
#include <map>

#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
    class GeometryComponent;
    class RenderManager
    {
        public:
            RenderManager();
            ~RenderManager() = default;

            std::shared_ptr<ObjectData> registerObject(const char* filePath);
            void deregisterObject(std::shared_ptr<ObjectData>& obj);
            void clearObjects();

            GLuint registerTexture(const char* filePath);
            void deregisterTexture(GLuint tex);
            void clearTextures();

            GLuint getUniform(ShaderType shader, const std::string& uniformName);

            std::map<ShaderType, GLuint> getShader() { return m_shaderList; };

            void renderVertices(GeometryComponent* object, const glm::mat4& mvp);

            std::map<std::string, std::shared_ptr<ObjectData>> getObjects() { return m_objectList; };

            template <typename T>
            static GLuint createVBO(std::vector<T>& data)
            {
                int dataSize = data.size() * sizeof(T);

                // Identify the vertex buffer
                GLuint vbo;
                // Generate a buffer with our identifier
                glGenBuffers(1, &vbo);
                glBindBuffer(GL_ARRAY_BUFFER, vbo);

                // Give vertices to OpenGL
                glBufferData(GL_ARRAY_BUFFER, dataSize, &data[0], GL_STATIC_DRAW);

                return vbo;
            };

        private:
            std::map<ShaderType, GLuint> m_shaderList;
            std::map<std::string, std::shared_ptr<ObjectData>> m_objectList;
            std::map<std::string, GLuint> m_textureList;
    };

}
