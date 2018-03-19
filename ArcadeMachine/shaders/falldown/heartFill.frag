#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;

out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D _MainTex;
uniform vec3 _Color;
uniform vec2 _Fill;

void main(){
	float filled = texture(_MainTex, UV).r;
	
	if (filled >= _Fill.x)
      discard; 
	
	color = _Color;
}