#version 460 core

layout(std140, binding = 0) uniform Transformation {
	mat4 transformation;
};

layout(std140, binding = 1) uniform ViewProjection {
	mat4 projection;
	mat4 view;
};

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 TextureCoordinate;

out vec2 out_TextureCoordinate;
out vec3 out_Normal;

void main() {
	mat4 MVP = projection * view * transformation;
	gl_Position = MVP * vec4(Position, 1.0f);
	out_TextureCoordinate = TextureCoordinate;
	out_Normal = Normal;
}