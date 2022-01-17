#version 400 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in float aDelta;

out vec3 vertexColor;

uniform float PI;
uniform float time;
uniform float phase;

float mapColor(float color)
{
    return clamp(color, 0.0f, 1.0f);
}

void main()
{
    gl_Position = vec4(aPos, 1.0);

    float delta = aDelta;
    float r = mapColor(sin(time + delta * phase));
    float g = mapColor(sin(time + phase + delta * phase));
    float b = mapColor(sin(time + 2.0f * phase + delta * phase));

    vertexColor = vec3(r, g, b);
}
