#version 400 core
out vec4 FragColor;
in vec4 vertexColor;  // 在OpenGL程序代码中设定这个变量

void main()
{
    FragColor = vertexColor;
}
