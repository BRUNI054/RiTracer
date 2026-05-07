#version 330 core

layout(location=0) out vec4 fragmentColor;

uniform vec3 diffuseComponent;
uniform sampler2D textureUnit;

in vec4 normal;
in vec4 lightDir;
in vec3 color;
in vec2 tCoord;


void main(void)
{
  float val = max(0.0, dot(normal, normalize(lightDir)));
  vec3 diffuseShading = vec3( diffuseComponent.r * val, diffuseComponent.g * val, diffuseComponent.b * val );

  vec3 texel = texture(textureUnit, tCoord).rgb;
  vec3 finalDiffuse = diffuseCOmponent.rgb * texel;

  fragmentColor = vec4(diffuseShading, 1.0);
}