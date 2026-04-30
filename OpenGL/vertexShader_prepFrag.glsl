#version 330 core

layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;
layout(location=2) in vec3 in_Color;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;

uniform vec3 diffuseComponent;
uniform vec4 lightPosWorld;
uniform vec3 cameraPosition;

out vec4 normal;
out vec4 lightDir;
out vec4 viewDir;
out vec3 color;

void main(void)
{
  color = in_Color;
  normal = normalize(normalMatrix * vec4(in_Normal, 0.0));
  vec4 vertexWorldPos = modelMatrix * vec4(in_Position, 1.0);
  lightDir = lightPosWorld - vertexWorldPos;
  viewDir = vec4(cameraPosition, 1.0) - vertexWorldPos;
  gl_Position = projMatrix * viewMatrix * vertexWorldPos;
}