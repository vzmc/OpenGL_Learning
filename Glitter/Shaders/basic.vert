#version 400 core
layout (location = 0) in vec3 aPos;
out vec4 vertexColor;   // 为片段着色器指定一个颜色输出

void main()
{
    gl_Position = vec4(aPos, 1.0);
    vertexColor = vec4(0.5, 0.1, 0.3, 1.0);
}
