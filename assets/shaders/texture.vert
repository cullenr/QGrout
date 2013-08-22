#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp;

attribute vec2 position;
attribute vec2 texturePosition;

varying vec2 v_texcoord;

//! [0]
void main()
{
    // Calculate vertex position in screen space
    gl_Position = mvp * vec4(position.x, position.y, 0, 1);
//    gl_Position = projectionMatrix * viewMatrix * modelMatrix * position;

    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces
    v_texcoord = texturePosition;
}
//! [0]
