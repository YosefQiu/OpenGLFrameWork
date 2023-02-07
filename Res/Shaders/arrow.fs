#version 330 core
out vec4 fragColor;
uniform bool U_Color;
void main()
{
	vec4 color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	if (U_Color)
	{
		color = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	}
	else
	{
		color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	fragColor = color;
}