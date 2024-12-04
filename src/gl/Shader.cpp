//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#include <gl/gl.h>
#include <gl/Shader.hpp>

#include <vector>
#include <stdexcept>
#include <cstdio>

namespace gl
{
  Shader::Shader(unsigned type)
  {
    shader_ = glCreateShader(type);
  }

  Shader::~Shader()
  {
    glDeleteShader(shader_);
  }

  void Shader::source(const char* source)
  {
    glShaderSource(shader_, 1, &source, nullptr);
  }

  void Shader::compile()
  {
    // Compile the shader
    glCompileShader(shader_);

    // Check compilation status
    int status_, length_;
    glGetShaderiv(shader_, GL_COMPILE_STATUS, &status_);
    if (status_ == GL_FALSE)
    {
      glGetShaderiv(shader_, GL_INFO_LOG_LENGTH, &length_);
      std::vector<char> infoLog_(length_);
      glGetShaderInfoLog(shader_, length_, nullptr, infoLog_.data());
      throw std::runtime_error(infoLog_.data());
    }
  }

  Shader Shader::defaultVertexShader()
  {
    Shader shader(GL_VERTEX_SHADER);
    shader.source(
        "#version 140\n"
        "attribute vec3 aPos;\n"
        "attribute vec3 aNormal;\n"
        "\n"
        "varying vec3 FragPos;\n"
        "varying vec3 Normal;\n"
        "\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "\n"
        "void main()\n"
        "{\n"
        "    FragPos = vec3(model * vec4(aPos, 1.0));\n"
        "    Normal = mat3(transpose(inverse(model))) * aNormal;\n"
        "    gl_Position = projection * view * vec4(FragPos, 1.0);\n"
        "}\n"
    );
    shader.compile();
    return shader;
  }

  Shader Shader::defaultFragmentShader()
  {
    Shader shader(GL_FRAGMENT_SHADER);
    shader.source(
        "#version 140\n"
        "varying vec3 FragPos;\n"
        "varying vec3 Normal;\n"
        "\n"
        "uniform vec3 lightPos;\n"
        "uniform vec3 viewPos;\n"
        "uniform vec3 lightColor;\n"
        "uniform vec3 objectColor;\n"
        "\n"
        "void main()\n"
        "{\n"
        "    // Ambient\n"
        "    float ambientStrength = 0.1;\n"
        "    vec3 ambient = ambientStrength * lightColor;\n"
        "\n"
        "    // Diffuse\n"
        "    vec3 norm = normalize(Normal);\n"
        "    vec3 lightDir = normalize(lightPos - FragPos);\n"
        "    float diff = max(dot(norm, lightDir), 0.0);\n"
        "    vec3 diffuse = diff * lightColor;\n"
        "\n"
        "    // Specular\n"
        "    float specularStrength = 0.5;\n"
        "    vec3 viewDir = normalize(viewPos - FragPos);\n"
        "    vec3 reflectDir = reflect(-lightDir, norm);\n"
        "    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);\n"
        "    vec3 specular = specularStrength * spec * lightColor;\n"
        "\n"
        "    vec3 result = (ambient + diffuse + specular) * objectColor;\n"
        "    gl_FragColor = vec4(result, 1.0);\n"
        "}\n"
    );
    shader.compile();
    return shader;
  }

  size_t Shader::getShadingLanguageVersion()
  {
    const char* versionStr{
      reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)) };
    if (!versionStr)
    {
      throw std::runtime_error{ "Failed to get GLSL version" };
    }
    // Assume format is like "1.40 - Build 31.0.101.5186" or "4.50 NVIDIA"
    double version{ 0.0 };
    if (std::sscanf(versionStr, "%lf", &version) != 1)
    {
      throw std::runtime_error{ "Failed to parse GLSL version" };
    }
    return static_cast<size_t>(version * 100);
  }

} // namespace gl
