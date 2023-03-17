#ifndef HFOPENGLWIDGET_H
#define HFOPENGLWIDGET_H

#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include "hfmodel.h"
class HFOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
public:
    HFOpenGLWidget(QWidget* parent = nullptr);
    ~HFOpenGLWidget() override;
protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
private:
    QOpenGLVertexArrayObject m_VAO;
    QOpenGLBuffer m_VBO;
    QOpenGLBuffer m_EBO;
    QOpenGLTexture m_texture;
    QOpenGLShaderProgram m_shaderProgram;
};

#endif // HFOPENGLWIDGET_H
