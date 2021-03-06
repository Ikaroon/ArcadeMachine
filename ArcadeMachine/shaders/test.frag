#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;

in vec3 fragmentColor;

out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler2;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;


void main(){
  color = (texture( myTextureSampler, UV ).rgb * fragmentColor) + texture( myTextureSampler2, UV ).rgb;
}