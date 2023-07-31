#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec4 tint;

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform sampler2D textureSampler;

void main(){

    // Output color = color of the texture at the specified UV
    color = vec4(texture(textureSampler, UV).rgb, 1) * tint;
}