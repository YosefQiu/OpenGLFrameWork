#version 330 core
in vec4 normal;
in vec4 position;
in vec4 texcoord;


uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat4 LightView;
uniform mat4 LightProj;

out vec2 teTexCoord;
out vec3 teNormal;
out vec3 teWorldPos;



void main()
{
	teTexCoord = (((texcoord)  + 1.0f ) / 2.0f).xy;
	teNormal =  (transpose(inverse(M)) * normal).xyz;
    teWorldPos = (M * position).xyz;
	gl_Position = P * V * M * position;
}

