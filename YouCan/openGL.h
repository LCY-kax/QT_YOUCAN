#ifndef OPENGL_H
#define OPENGL_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QtOpenGL/QGL>
#include <random>
#include <QDebug>

class MyGLWidget : public QOpenGLWidget
{
public:
    MyGLWidget(QWidget *parent) : QOpenGLWidget(parent) { }
private:
    float a=0,b=0,c=0;

protected:
    void initializeGL() override
    {
        // Set up the rendering context, load shaders and other resources, etc.:
        QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
        f->glClearColor(0, 0, 0, 0);
        qDebug()<<"init openGL";

    }

    void resizeGL(int w, int h) override
    {
        Q_UNUSED(w);
        Q_UNUSED(h);
        // Update projection matrix and other size related settings:
//        m_projection.setToIdentity();
//        m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);

    }

    void paintGL() override
    {
        // Draw the scene:
        QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
//        f->glClear(GL_COLOR_BUFFER_BIT);
        f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        f->glClearColor(0.23f, 0.4f, 0.8f, 0.5f);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        a=dis(gen);
        b=dis(gen);
        c=dis(gen);
//        qDebug()<<"a,b,c"<<a<<b<<c;
//        if(a>1.0 || b>1.0 || c>1.0){a=0;b=0;c=0;}

        f->glClearColor(a, b, c, 0.5f);
    }

};

#endif // OPENGL_H
