#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    unsigned int ID;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char* vertexPath, const char* fragmentPath)
    {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        CheckCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        CheckCompileErrors(fragment, "FRAGMENT");
        // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        CheckCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);

    }

    ~Shader()
    {
        uniformLocations.clear();
    }

    // activate the shader
    // ------------------------------------------------------------------------
    void Use() const
    {
        glUseProgram(ID);
    }
    // utility uniform functions
    // ------------------------------------------------------------------------
    void SetBool(const std::string& name, bool value)
    {
        glUniform1i(GetUniformLocation(name), (int)value);
    }
    // ------------------------------------------------------------------------
    void SetInt(const std::string& name, int value)
    {
        glUniform1i(GetUniformLocation(name), value);
    }
    // ------------------------------------------------------------------------
    void SetFloat(const std::string& name, float value)
    {
        glUniform1f(GetUniformLocation(name), value);
    }
    // ------------------------------------------------------------------------
    void SetVec2(const std::string& name, const glm::vec2& value)
    {
        glUniform2fv(GetUniformLocation(name), 1, &value[0]);
    }
    void SetVec2(const std::string& name, float x, float y)
    {
        glUniform2f(GetUniformLocation(name), x, y);
    }
    // ------------------------------------------------------------------------
    void SetVec3(const std::string& name, const glm::vec3& value)
    {
        glUniform3fv(GetUniformLocation(name), 1, &value[0]);
    }
    void SetVec3(const std::string& name, float x, float y, float z)
    {
        glUniform3f(GetUniformLocation(name), x, y, z);
    }
    // ------------------------------------------------------------------------
    void SetVec4(const std::string& name, const glm::vec4& value)
    {
        glUniform4fv(GetUniformLocation(name), 1, &value[0]);
    }
    void SetVec4(const std::string& name, float x, float y, float z, float w)
    {
        glUniform4f(GetUniformLocation(name), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void SetMat2(const std::string& name, const glm::mat2& mat)
    {
        glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void SetMat3(const std::string& name, const glm::mat3& mat)
    {
        glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void SetMat4(const std::string& name, const glm::mat4& mat)
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
    }

private:

    std::unordered_map<std::string, GLint> uniformLocations;

    GLint GetUniformLocation(const std::string& name)
    {
        if (uniformLocations.count(name) == 0)
        {
            uniformLocations[name] = glGetUniformLocation(ID, name.c_str());
        }

        return uniformLocations[name];
    }

    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void CheckCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};
#endif