#include "Headers/hfmesh.h"

HFMesh::HFMesh(QObject *parent) : QObject(parent)
{

}

void HFMesh::loadMeshData(QVector<Vertex> vertices, QVector<unsigned int> indices, QVector<Texture *> textures)
{
    m_vertices = vertices;
    m_indices = indices;
    m_textures = textures;
}

void HFMesh::draw(QOpenGLShaderProgram &shaderProgram)
{

}
