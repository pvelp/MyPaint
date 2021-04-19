#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QColorDialog>
#include <QFileDialog>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _scene(new MyScene(this))
{
    ui->setupUi(this);

    ui->graphicsView->setScene(_scene);
    ui->label_currentmode->setText(QString("Текущий режим: 'Карандаш'"));
    _scene->setSceneRect(-1000, -1000, 2000, 2000);

    connect(_scene, &MyScene::mouse_moved,
            this, &MainWindow::_on_scene_mouse_move);
    change_label_color(Qt::white);
    change_label_color_circuit(Qt::black);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::_on_scene_mouse_move(double x, double y)
{
    ui->statusbar->showMessage(QString("%1 X %2").arg(x).arg(y));
}


void MainWindow::on_pushButton_rect_clicked()
{
    _scene->setCurrent_figure_type(MyScene::Rect);
    ui->label_currentmode->setText(QString("Текущий режим: 'Прямоугольник'"));
}

void MainWindow::on_pushButton_2_ellipse_clicked()
{
    _scene->setCurrent_figure_type(MyScene::Ellipse);
    ui->label_currentmode->setText(QString("Текущий режим: 'Эллипс'"));
}

void MainWindow::on_pushButton_3_clear_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Очистка", "Очистить экран?",
                                  QMessageBox::No|QMessageBox::Yes);
    if (reply == QMessageBox::Yes) {
        _scene->clear();
        change_label_color(Qt::white);
        change_label_color_circuit(Qt::black);
        ui->pushButton_2_color->setEnabled(false);
        _scene->set_color_square(Qt::white);
        _scene->setColor_circuit(Qt::black);
        ui->label_currentmode->setText(QString("Текущий режим: 'Карандаш'"));
        ui->spinBox_size->setValue(1);
        _scene->setSize(1);
    }
}

void MainWindow::change_label_color(QColor color){
    QPalette palette;
    palette.setColor(QPalette::Window, color);
    palette.setColor(QPalette::Window, color);
    ui->label_color->setAutoFillBackground(true);
    ui->label_color->setPalette(palette);
}

void MainWindow::on_pushButton_2_color_clicked()
{
    QColor color = QColorDialog::getColor();
    _scene->set_color_square(color);
    change_label_color(color);
}

void MainWindow::on_radioButton_fiilShapes_clicked(bool checked)
{
    if (checked) {
        _scene->setFill_shape(true);
        ui->pushButton_2_color->setEnabled(true);
    } else {
        _scene->setFill_shape(false);
        ui->pushButton_2_color->setEnabled(false);
    }
}

void MainWindow::on_pushButton_2_color_circuit_clicked()
{
    QColor color = QColorDialog::getColor();
    _scene->setColor_circuit(color);
    change_label_color_circuit(color);
}

void MainWindow::change_label_color_circuit(QColor color){
    QPalette palette;
    palette.setColor(QPalette::Window, color);
    palette.setColor(QPalette::Window, color);
    ui->label_circuit->setAutoFillBackground(true);
    ui->label_circuit->setPalette(palette);
}

void MainWindow::on_pushButton_line_clicked()
{
    _scene->setCurrent_figure_type(MyScene::Line);
    ui->label_currentmode->setText(QString("Текущий режим: 'Карандаш'"));
}

void MainWindow::on_pushButton_saveimage_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "",QCoreApplication::applicationDirPath(),"Image (*.png);; JPEG(*.JPEG)");
    if (!fileName.isNull()){
        QPixmap pm = ui->graphicsView->grab();
        pm.save(fileName);

    }
}


void MainWindow::on_pushButton_set_size_clicked()
{
    _scene->setSize(ui->spinBox_size->value());
}
