#pragma once

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>

class UIComponent
{
public:

    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO;

    // constructor
    UIComponent(Renderer *renderer)
    {
        Vertex vTL = { glm::vec3(-0.5f, 0.5f, 0.0f) };
        Vertex vTR = { glm::vec3(0.5f, 0.5f, 0.0f) };
        Vertex vBR = { glm::vec3(0.5f, -0.5f, 0.0f) };
        Vertex vBL = { glm::vec3(-0.5f, -0.5f, 0.0f) };

        this->vertices = { vTL, vTR, vBR, vBL };
        this->indices = { 0, 1, 3, 3, 2, 1 };

        this->position = glm::vec3(0.0f, 0.0f, -0.2f);
        this->scale = glm::vec3(1.00f, 1.0f, 1.0f);
        this->color = glm::vec3(1.0f, 1.0f, 1.0f);

        this->p_shader = nullptr;
        this->p_renderer = renderer;

        SetupMesh();
    }

    ~UIComponent()
    {
        vertices.clear();
        indices.clear();
        VAO = 0;
    }

    void Render()
    {
        if (!p_shader) return;

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(p_renderer->SCR_WIDTH * position.x, p_renderer->SCR_HEIGHT * position.y, position.z));
        model = glm::scale(model, scale);
        p_shader->SetMat4("model", model);
        p_shader->SetVec3("uiComponentColor", color);

        // draw mesh
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void SetShader(Shader* shader)
    {
        this->p_shader = shader;
    }

protected:
    unsigned int VBO, EBO;
    glm::vec3 position, scale, color;
    Shader *p_shader;
    Renderer *p_renderer;

    // initializes all the buffer objects/arrays
    void SetupMesh()
    {
        // create buffers/arrays
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        // load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    }
};