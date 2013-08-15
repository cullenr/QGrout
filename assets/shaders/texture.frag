#version 150

out vec4 frag_colour;

uniform sampler2D texture;

void main() {
    frag_colour = texture2D(texture, gl_TexCoord[0].st);
}
