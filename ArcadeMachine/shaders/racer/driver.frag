#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;

out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D _MainTex;

void main(){
	vec4 col = texture(_MainTex, UV);
	
	if (col.a <= 0.5)
      discard; 
	
	color = col.rgb;
}