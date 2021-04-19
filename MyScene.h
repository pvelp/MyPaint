#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void change_label_color(QColor color);
    void change_label_color_circuit(QColor color);
    QString path() const;
    void setPath(const QString &path);

private slots:
    void _on_scene_mouse_move(double x, double y);

    void on_pushButton_rect_clicked();

    void on_pushButton_2_ellipse_clicked();

    void on_pushButton_3_clear_clicked();

    void on_pushButton_2_color_clicked();

    void on_radioButton_fiilShapes_clicked(bool checked);

    void on_pushButton_2_color_circuit_clicked();

    void on_pushButton_line_clicked();

    void on_pushButton_saveimage_clicked();

    void on_pushButton_set_size_clicked();

private:
    Ui::MainWindow *ui;
    MyScene *_scene;

};
#endif // MAINWINDOW_H
