#version 330 core
out vec4 fragColor;
uniform vec4 U_Color;
in vec4 V_Color;
void main(){
	fragColor = V_Color;
}