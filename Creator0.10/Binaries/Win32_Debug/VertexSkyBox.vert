#version 430 core

layout (location = 0) in vec3 vVertex;

out vec3 TexCoords;

uniform mat4 mModel;
uniform mat4 mView;
uniform mat4 mProjection;

uniform mat4 mModelViewProjection;

void main()
{
    TexCoords = vVertex;
    vec4 pos = mProjection * mat4(mat3(mView)) * vec4(vVertex, 1.0);
    gl_Position = pos.xyww;
}