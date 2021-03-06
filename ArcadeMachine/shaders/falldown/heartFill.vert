#version 330 core
// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 2) in vec2 vertexUV;

// Values that stay constant for the whole mesh.
uniform mat4 _MVP;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

void main(){
  // Output position of the vertex, in clip space : MVP * position
  gl_Position =  _MVP * vec4(vertexPosition_modelspace,1);
  
  UV = vertexUV;
}