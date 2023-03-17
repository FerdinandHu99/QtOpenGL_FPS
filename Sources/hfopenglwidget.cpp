#include "Headers/hfopenglwidget.h"
#include <QDebug>
HFOpenGLWidget::HFOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent), m_VBO(QOpenGLBuffer::VertexBuffer),
                                                  m_EBO(QOpenGLBuffer::IndexBuffer)
{

}

void HFOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    GLfloat vertices[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
    };

    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
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
    m_shaderProgram.setAttributeBuffer(0, GL_FLOAT, 0, 3, 3 * sizeof (GLfloat));
    m_shaderProgram.enableAttributeArray(0);

    m_VAO.release();

    HFModel model;
    //model.loadModelFile(QString("D:/Qt_Projects/KingGuns/Models/gun/m4a1_s.obj"));
    //model.loadModelFile(QString("D:/Qt_Projects/KingGuns/Models/container/container.obj"));
    model.loadModelFile(QString("E:/Qt_Projects/QtOpenGL_FPS/Models/nanosuit/nanosuit.obj"));
}
void HFOpenGLWidget::paintGL()
{
    // 清空并更新背景颜色
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_shaderProgram.bind();
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
