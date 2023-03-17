#include "Headers/hfopenglwidget.h"
#include <QDebug>
#include <QMatrix4x4>
HFOpenGLWidget::HFOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent), m_VBO(QOpenGLBuffer::VertexBuffer),
                                                  m_EBO(QOpenGLBuffer::IndexBuffer), m_texture(QOpenGLTexture::Target2D)
{
    //m_texture = new Texture;
    //m_texture.create();

}

void HFOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    GLfloat vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };

    GLuint indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    m_shaderProgram.create();
    m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/vertexshader.vert");
    m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/fragshader.frag");

    m_VAO.create();
    m_VBO.create();
    m_EBO.create();

    m_VAO.bind();
    m_VBO.bind();
    m_VBO.allocate(vertices, sizeof (vertices));
    m_VBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_EBO.bind();
    m_EBO.allocate(indices, sizeof (indices));
    m_EBO.setUsagePattern(QOpenGLBuffer::StaticDraw);

    m_shaderProgram.bind();
    m_shaderProgram.setAttributeBuffer(0, GL_FLOAT, 0, 3, 8 * sizeof (GLfloat));
    m_shaderProgram.enableAttributeArray(0);

    m_shaderProgram.setAttributeBuffer(1, GL_FLOAT, 12, 3, 8 * sizeof (GLfloat));
    m_shaderProgram.enableAttributeArray(1);

    m_shaderProgram.setAttributeBuffer(2, GL_FLOAT, 24, 2, 8 * sizeof (GLfloat));
    m_shaderProgram.enableAttributeArray(2);

    m_texture.setWrapMode(QOpenGLTexture::DirectionS,QOpenGLTexture::Repeat);
    m_texture.setWrapMode(QOpenGLTexture::DirectionT,QOpenGLTexture::Repeat);
    m_texture.setMinMagFilters(QOpenGLTexture::LinearMipMapLinear,QOpenGLTexture::Linear);
    //m_texture->texture.create();
    QImage data(":/Images/container_diff.png");
    if (!data.isNull()) {
        m_texture.setData(data);
    } else {
        qDebug() << "图片读取失败" ;
    }

    m_VAO.release();

//    HFModel model(&m_shaderProgram);
//    model.loadModelFile(QString("E:/Qt_Projects/QtOpenGL_FPS/Models/nanosuit/nanosuit.obj"));
}
void HFOpenGLWidget::paintGL()
{
    // 清空并更新背景颜色
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //glActiveTexture(GL_TEXTURE0);
    m_texture.bind();

    //m_shaderProgram.setUniformValue("ourTexture1", 0);

    m_shaderProgram.bind();

    QMatrix4x4 modelMat;
    modelMat.scale(0.5);
    m_shaderProgram.setUniformValue("model", modelMat);

    m_VAO.bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    update();
}

void HFOpenGLWidget::resizeGL(int w, int h)
{
    //glViewport(0, 0, w, h);
}

HFOpenGLWidget::~HFOpenGLWidget()
{
    makeCurrent(); // 获取当前上下文属性
}
