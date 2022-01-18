#version 400 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in float aDelta;

out vec3 vertexColor;

uniform float PI;
uniform float time;
uniform float phase;

float remapColor(float color)
{
    return clamp(color, 0.0f, 1.0f);
}

void main()
{
    float x = aPos.x - cos(time) * 0.5f;
    float y = aPos.y + sin(time) * 0.5f;
    gl_Position = vec4(x, y, aPos.z, 1.0f);

    float r = remapColor(sin(time + aDelta * phase));
    float g = remapColor(sin(time + phase + aDelta * phase));
    float b = remapColor(sin(time + 2.0f * phase + aDelta * phase));
    vertexColor = vec3(r, g, b);
}
