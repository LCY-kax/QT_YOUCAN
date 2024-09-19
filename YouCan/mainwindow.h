#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QOpenGLWidget>
#include <QDebug>

#include <QFileDialog>
#include <QStandardPaths>
#include <atomic>
#include <QTime>
#include <QTimer>
#include <memory>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_dateTimeEdit_editingFinished();

    void on_openGLWidget_frameSwapped();

    void on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint);

    void on_lcdNumber_overflow();
    
    void on_toolButton_clicked();

    void on_lineEdit_selectionChanged();

    void on_openGLWidget_aboutToCompose();

    void on_openGLWidget_resized();

    void on_pushButton_clicked();

    void on_dockWidget_visibilityChanged(bool visible);

    void on_dockWidget_topLevelChanged(bool topLevel);


    void on_toolButton_3_triggered(QAction *arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QOpenGLWidget *openGLWidget;
    QString *fileName= new QString;
    std::atomic<bool> closeFlag;
    QTime current_time;
//    QTime *current_time;
    QTimer *timer;
    int value=0;
    void showFiles();
};
#endif // MAINWINDOW_H
