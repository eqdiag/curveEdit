#version 330 core

layout (location = 0) in vec3 position;


uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform vec3 eye;

void main(){
	vec3 pos = (view *model* vec4(position,1.0)).xyz;
	gl_Position = vec4(pos.x/eye.z,pos.y/eye.z,0.0,1.0);
}