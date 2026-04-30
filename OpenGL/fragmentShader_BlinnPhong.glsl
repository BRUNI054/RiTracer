#version 330 core

layout(location=0) out vec4 fragmentColor;

uniform vec3 diffuseComponent;

in vec4 normal;
in vec4 lightDir;
in vec4 viewDir;
in vec3 color;

void main(void)
{
  float val1 = min(max(0.0, dot(normal, normalize(lightDir))), 1.0);
  vec4 halfVector = normalize(lightDir + viewDir);
  float val2 = min(pow(max(0.0, dot(normal, halfVector)), 128.0), 1.0);
  vec3 diffuseShading = vec3( color.r * val1, color.g * val1, color.b * val1 );
  vec3 specularityShading = vec3(val2, val2, val2);

  fragmentColor = vec4(diffuseShading + specularityShading, 1.0);
}