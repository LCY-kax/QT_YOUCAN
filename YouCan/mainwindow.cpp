#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "openfile.h"
#include "openGL.h"
#include "public.h"
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QInputDialog>
#include <QFontDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , current_time(QTime::currentTime())
    , timer(new QTimer(this))
{
    ui->setupUi(this);

    connect(timer, &QTimer::timeout, this, [this](){
        current_time = QTime::currentTime();
        ui->label_3->setText(current_time.toString("hh:mm:ss"));
        ui->progressBar->setValue(value);
        if(value>100){value=0;}else{value+=10;}

    });
    timer->start(1000);


//    ui->progressBar->setRange(0,100);
    ui->quickWidget->setSource(QUrl("qrc:/quickqml.qml"));
//    ui->dockWidget->setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetMovable);

    openGLWidget = findChild<QOpenGLWidget *>(QStringLiteral("openGLWidget"));
    if (openGLWidget)
    {
        //        openGLWidget->initializeGL();
        qDebug() << "Success find openGLWidget!";
        MyGLWidget * myGL= new MyGLWidget(this);
        ui->openGLWidget->setAutoFillBackground(true); // 设置QOpenGLWidget自动填充背景
        QVBoxLayout *layout = new QVBoxLayout(ui->openGLWidget);
        layout->addWidget(myGL);
        ui->openGLWidget->setLayout(layout);

        QSurfaceFormat format;
        format.setDepthBufferSize(24);
        format.setStencilBufferSize(8);
        format.setVersion(3, 2);
        format.setProfile(QSurfaceFormat::CoreProfile);
        QSurfaceFormat::setDefaultFormat(format);
        connect(timer, &QTimer::timeout, this, [myGL](){
            if (myGL) {
                myGL->update();
            }
        });

    } else
    {
        qDebug() << "Failed to find openGLWidget!";
    }
    closeFlag=true;



}

MainWindow::~MainWindow()
{
    delete fileName;
//    delete current_time;
    delete timer;
    delete openGLWidget;
    delete ui;
}


void MainWindow::on_dateTimeEdit_editingFinished()
{

}

void MainWindow::on_openGLWidget_frameSwapped()
{
//    qDebug() << "Frame swapped!";


}

void MainWindow::on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint)
{
    Q_UNUSED(viewportRect);
    Q_UNUSED(fromScenePoint);
    Q_UNUSED(toScenePoint);
      qDebug() << "rubber";
}

void MainWindow::on_lcdNumber_overflow()
{
    
}

void MainWindow::on_toolButton_clicked()
{
    qDebug() << "Current path:" << QDir::currentPath();
    showFileInFolder(QDir::currentPath());
}

void MainWindow::on_lineEdit_selectionChanged()
{
    showFiles();
    QString imgFile = ui->lineEdit->text();
    QPixmap pixmap(imgFile);  // 替换为你的图片路径

    QGraphicsScene* scene = new QGraphicsScene(this); // 创建一个 QGraphicsScene 对象
    QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(pixmap); // 创建一个 QGraphicsPixmapItem 对象，并传入图片

    scene->addItem(pixmapItem); // 将 pixmapItem 添加到 scene 中
    ui->graphicsView->setScene(scene); // 将 scene 设置为 graphicsView 的场景
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setRenderHint(QPainter::SmoothPixmapTransform);
//    ui->graphicsView->setMouseTracking(true);//
//    ui->graphicsView->fitInView(pixmapItem, Qt::KeepAspectRatio); // 根据图片大小调整视图的显示
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag); //可拖动
//    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);//橡皮筋，选框
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

}
void MainWindow::showFiles()
{
    // QString str = QFileDialog::getOpenFileName(this, "File Explorer", QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),"Excel 文件(*.xls *.xlsx);;All file(*.*)");
    QString str = QFileDialog::getOpenFileName(this, "File Explorer", QStandardPaths::writableLocation(QStandardPaths::PicturesLocation), "Images (*.png *.jpg *.jpeg);;All Files (*.*)");

    ui->lineEdit->setText(str.toUtf8());

    if (fileName) {
        *fileName = ui->lineEdit->text();
        qDebug() << "File Name: " << *fileName << "\n";
    } else {
        qDebug() << "Error: fileName pointer is nullptr\n";
    }
}

void MainWindow::on_openGLWidget_aboutToCompose()
{

}

void MainWindow::on_openGLWidget_resized()
{

}


void MainWindow::on_pushButton_clicked()
{
    QMessageBox::information(this, "QT...", "正常提示。。。。。。。。。。",QMessageBox::Cancel|QMessageBox::Ok);
}

void MainWindow::on_dockWidget_visibilityChanged(bool visible)
{
    Q_UNUSED(visible);
    qDebug() << "关闭dockwidget\n";

    if((ui->dockWidget->isHidden() == true)&&closeFlag){
//    if(closeFlag&&visible){
        int ret =QMessageBox::information(this, "关闭...", "正常提示。。。。。。。。。。",QMessageBox::Cancel|QMessageBox::Ok);
        switch (ret) {
            case QMessageBox::Cancel:
                 qDebug() << "关闭取消 \n";
                 ui->dockWidget->setVisible(true);
                 closeFlag =false;
            break;
        default:
            break;
        }
    }
    closeFlag =true;
}

void MainWindow::on_dockWidget_topLevelChanged(bool topLevel)
{
    Q_UNUSED(topLevel);
    closeFlag =false;
}

void MainWindow::on_toolButton_3_triggered(QAction *arg1)
{
    Q_UNUSED(arg1);
    QMessageBox::warning(this, "Input", "Hello", "!");
}

void MainWindow::on_pushButton_2_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, "Input Dialog", "Enter your name:", QLineEdit::Normal, "name", &ok);
    if (ok && !text.isEmpty()) {
        QMessageBox::information(this, "Input", "Hello, " + text + "!");
    }

}

void MainWindow::on_pushButton_3_clicked()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok,  ui->label->font(), this);
    if (ok) {
        ui->label_2->setFont(font);
        ui->label->setFont(font);
    }
}
