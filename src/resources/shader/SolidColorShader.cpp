
#include "SolidColorShader.h"

using namespace Engine;

SolidColorShader::SolidColorShader(const std::shared_ptr<RenderManager>& renderManager)
{
    registerShader(renderManager, "resources/shader/solidColor", "solidColor");

    addActiveUniform("MVP");
    addActiveUniform("tintColor");
}

void SolidColorShader::renderVertices(GeometryComponent* object, const glm::mat4& mvp)
{
    if(object->getObjectData()->m_vertexBuffer == -1)
    {
        fprintf(stderr, "Object is missing vertices!");
        return;
    }

    if(object->getObjectData()->m_normalBuffer == -1)
    {
        fprintf(stderr, "Object is missing vertex normals!");
        return;
    }

    if(object->getTextureBuffer() == -1)
    {
        fprintf(stderr, "Object is missing vertex normals!");
        return;
    }

    glUseProgram(getShaderIdentifier().second);

    // Load MVP matrix into uniform
    glUniformMatrix4fv(getActiveUniform("MVP"), 1, GL_FALSE, &mvp[0][0]);

    // Load tint value into uniform
    const glm::vec4 tint = object->getTint();
    glUniform4f(getActiveUniform("tintColor"), tint.x, tint.y, tint.z, tint.w);

    bindVertexData(GLOBAL_VERTEX_POSITION, GL_ARRAY_BUFFER, object->getObjectData()->m_vertexBuffer, 3, GL_FLOAT, false, 0);
    bindVertexData(GLOBAL_VERTEX_NORMAL, GL_ARRAY_BUFFER, object->getObjectData()->m_normalBuffer, 3, GL_FLOAT, false, 0);
    bindVertexData(GLOBAL_VERTEX_COLOR, GL_ARRAY_BUFFER, object->getTextureBuffer(), 4, GL_FLOAT, false, 0);

    // Drawing the object
    glDrawArrays(GL_TRIANGLES, 0, object->getObjectData()->getVertexCount());
    glDisableVertexAttribArray(GLOBAL_VERTEX_POSITION);
    glDisableVertexAttribArray(GLOBAL_VERTEX_COLOR);
    glDisableVertexAttribArray(GLOBAL_VERTEX_NORMAL);
}