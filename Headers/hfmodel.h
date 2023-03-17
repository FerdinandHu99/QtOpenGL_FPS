#ifndef HFMODEL_H
#define HFMODEL_H

#include <QObject>
#include <QDir>
#include <QDebug>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Headers/hfmesh.h"
class HFModel : public QObject
{
    Q_OBJECT
public:
    explicit HFModel(QOpenGLShaderProgram* shaderProgram, QObject *parent = nullptr);
    bool loadModelFile(QDir filePath);
    void draw();
private:
    QDir                   m_directory;            // 模型文件目录
    QVector<HFMesh*>       m_meshs;                // 储存模型的所有网格
    QVector<Texture*>      m_texturesLoaded;       // 储存模型已加载的所有贴图
    QOpenGLShaderProgram*  m_shaderProgram;        // 着色器

    void     processNode(aiNode* node, const aiScene* scene); // 处理模型的节点
    HFMesh*  processMesh(aiMesh* mesh, const aiScene* scene); // 处理模型的网格（顶点数据、索引数据、纹理坐标）
    QVector<Texture*> loadMaterialTextures(aiMaterial* material, aiTextureType type, QString typeName); // 从文件中加载材质的贴图
signals:

public slots:
};

#endif // HFMODEL_H
