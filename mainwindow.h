#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define THINKING 0
#define HUNGRY 1
#define EATING 2

#include <QMainWindow>
#include "trem.h"
#include <QMutex>
#include <vector>
#include <QSemaphore>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void updateInterface(int,int,int);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_vel1_valueChanged(int value);

    void on_vel2_valueChanged(int value);

    void on_vel3_valueChanged(int value);

    void on_vel4_valueChanged(int value);

    void on_vel5_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    //Cria os objetos TREM's
    Trem *trem1;
    Trem *trem2;
    Trem *trem3;
    Trem *trem4;
    Trem *trem5;
};

#endif // MAINWINDOW_H
