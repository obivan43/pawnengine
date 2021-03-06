#version 460 core

in vec2 out_TextureCoordinate;
in vec3 out_Normal;

out vec4 color;

void main() {
	vec3 normalized = normalize(out_Normal);
	color = vec4((normalized + 1) * 0.5f, 1.0f);
}