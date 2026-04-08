##Vertex Shader

#version 330 core

layout(location = 0) in vec2 in_position;
layout(location = 1) in vec2 in_texCoords;

out vec2 v_texCoord;

uniform vec2 u_pos_offset;

void main()
{
  gl_Position = vec4(in_position, 0.0, 1.0);
  v_texCoord = in_texCoords + u_pos_offset;
}

##Fragment Shader

#version 330 core

layout(location = 0) out vec4 o_FragColor;

in vec2 v_texCoord;

uniform vec4 u_Color;
uniform sampler2D u_texture;

void main()
{
  vec4 tex_color = texture(u_texture, v_texCoord);
  o_FragColor = tex_color;
}