#version 130

in vec4 fragmentColor;
in vec2 fragmentPosition;


out vec4 color;

uniform float time;

void main() {
	color = vec4(fragmentColor.r * (cos(fragmentPosition.x * 4 + time) + 1.0) * 0.5,
				 fragmentColor.g * (cos(fragmentPosition.y * 8+ time) + 1.0) * 0.5,
				 fragmentColor.b * (cos(fragmentPosition.x*0.2 + time) + 1.0) * 0.5,
				 fragmentColor.a);
	
}