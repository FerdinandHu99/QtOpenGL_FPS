#include "Headers/hfopenglwidget.h"
#include <QDebug>
#include <QMatrix4x4>
HFOpenGLWidget::HFOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent), m_VBO(QOpenGLBuffer::VertexBuffer),
                                                  m_EBO(QOpenGLBuffer::IndexBuffer), m_texture(QOpenGLTexture::Target2D),
                                                  m_camera(new HFCamera)
{
    //m_texture = new Texture;
    //m_texture.create();
    this->setFocusPolicy(Qt::StrongFocus);                       // 获得键盘焦点
    this->setMouseTracking(true);                                // 启用鼠标跟踪
    this->setCursor(Qt::BlankCursor);                            // 取消光标显示
    /* 时间开始 */
    m_lastTime = 0;
    m_time.start();


}

void HFOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    m_centerMousePoint = QPoint(width()/2, height()/2);
    glEnable(GL_DEPTH_TEST);

    m_shaderProgram.create();
    m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/vertexshader.vert");
    m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/fragshader.frag");


    model = new HFModel(&m_shaderProgram, context());
    model->loadModelFile(QString("E:/Qt_Projects/QtOpenGL_FPS/Models/nanosuit/nanosuit.obj"));

    //model->loadModelFile(QString("D:/Qt_Projects/AssimpTest/Models/container/container.obj"));
    model->Info();
}
void HFOpenGLWidget::paintGL()
{
    /* 计算帧率 */
    int currentTime = m_time.elapsed();
    m_deltaTime = currentTime - m_lastTime;
    int FPS = (1.0 / m_deltaTime) * 1000;
    m_lastTime = currentTime;

    /* 接受接盘更新 */
    keyBoardProcess();

    /* 清空并更新背景颜色,清除颜色缓冲区、深度缓冲区 */
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_TEST);

    //glActiveTexture(GL_TEXTURE0);
    //m_texture.bind();

    //m_shaderProgram.setUniformValue("ourTexture1", 0);

    m_shaderProgram.bind();

    QMatrix4x4 modelMat, viewMat, projectionMat;
    //modelMat.rotate(currentTime*0.01, QVector3D(0, 1, 0));
    //viewMat.translate(QVector3D(0.0f, 0.0f, -3.0f));
    projectionMat.perspective(m_camera->Fov(), width()/height(), 0.1f, 100.0f);
    //qDebug() << m_camera->getViewMatrix();
    //qDebug() << viewMat;
    m_shaderProgram.setUniformValue("model", modelMat);
    m_shaderProgram.setUniformValue("view", m_camera->getViewMatrix());
    m_shaderProgram.setUniformValue("projection", projectionMat);


    //m_VAO.bind();
    model->draw();
    //glDrawArrays(GL_TRIANGLES, 0, 36);

    update();
}

void HFOpenGLWidget::resizeGL(int w, int h)
{
    //glViewport(0, 0, w, h);
}

HFOpenGLWidget::~HFOpenGLWidget()
{
    makeCurrent(); // 获取当前上下文属性
    //QOpenGLWidget::~QOpenGLWidget();
    //::~QOpenGLFunctions_3_3_Core();
}

// 接收键盘按下事件
void HFOpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if (key == Qt::Key_Escape) {
        //emit EscBtnPressed();  // 当Esc按下时，发射信号给主窗口
    }
    if (key >= 0 && key < 1024) {
        if (event->type() == QEvent::KeyPress) {
            keys[key] = true;
        }
    }
}

// 接收键盘松开事件
void HFOpenGLWidget::keyReleaseEvent(QKeyEvent *event)
{
    int key = event->key();
    if (key >= 0 && key < 1024) {
        if (event->type() == QEvent::KeyRelease) {
            keys[key] = false;
        }
    }
}

// 键盘事件处理函数（实现多个按键同时按下功能）
void HFOpenGLWidget::keyBoardProcess()
{
    if (keys[Qt::Key_W] == true) m_camera->processKeyboard(HFCamera::FORWARD, m_deltaTime);
    if (keys[Qt::Key_S] == true) m_camera->processKeyboard(HFCamera::BACKWARD, m_deltaTime);
    if (keys[Qt::Key_A] == true) m_camera->processKeyboard(HFCamera::LEFT, m_deltaTime);
    if (keys[Qt::Key_D] == true) m_camera->processKeyboard(HFCamera::RIGHT, m_deltaTime);
}

// 接收鼠标移动事件
void HFOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint currentMousePoint = event->pos();
    QPoint deltaMousePoint = currentMousePoint - m_centerMousePoint;
    if (event->buttons() == Qt::MidButton) {
        m_camera->processMouseMidBtnMovement(deltaMousePoint.y());
        QPoint center = this->mapToGlobal(m_centerMousePoint);
        QCursor::setPos(center);
    } else {
        m_camera->processMouseMovement(deltaMousePoint.x(), deltaMousePoint.y());
        QPoint center = this->mapToGlobal(m_centerMousePoint);
        QCursor::setPos(center);
    }
}

// 鼠标滚轮事件
void HFOpenGLWidget::wheelEvent(QWheelEvent *event)
{
    m_camera->processMouseWheel(event->angleDelta().y());
}
