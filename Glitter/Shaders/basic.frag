#version 400 core
in vec4 vertexColor;    // 从顶点着色器输入
out vec4 FragColor;

void main()
{
    FragColor = vertexColor;
}
