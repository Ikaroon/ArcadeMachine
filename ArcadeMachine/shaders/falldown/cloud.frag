#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;

uniform vec2 _TexCount;
uniform int _TexPos;
uniform vec3 _Color;

out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D _MainTex;

void main(){
	float indexPos = _TexPos;

	float xPos = (indexPos / _TexCount.x) - floor(indexPos / _TexCount.x);//mod(indexPos, _TexCount.x);
	float yPos = floor(indexPos / _TexCount.x);
	
	vec2 cUV = vec2(xPos + UV.x / _TexCount.x, yPos / _TexCount.y + UV.y / _TexCount.y);

	vec4 col = texture(_MainTex, cUV);
	
	if (col.r <= 0.9)
      discard; 
	
	color = col.r * _Color;
}