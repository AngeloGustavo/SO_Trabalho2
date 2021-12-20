#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <QSemaphore>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Cria o trem com seu (ID, posição X, posição Y)
    trem1 = new Trem(1,130,20);
    trem2 = new Trem(2,350,20);
    trem3 = new Trem(3,20,140);
    trem4 = new Trem(4,240,140);
    trem5 = new Trem(5,460,140);


    /*
     * Conecta o sinal UPDATEGUI à função UPDATEINTERFACE.
     * Ou seja, sempre que o sinal UPDATEGUI foi chamado, será executada a função UPDATEINTERFACE.
     * Os 3 parâmetros INT do sinal serão utilizados na função.
     * Trem1 e Trem2 são os objetos que podem chamar o sinal. Se um outro objeto chamar o
     * sinal UPDATEGUI, não haverá execução da função UPDATEINTERFACE
     */
    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem4,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem5,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));

    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();
}

//Função que será executada quando o sinal UPDATEGUI for emitido
void MainWindow::updateInterface(int id, int x, int y){
    ui->label_4->setText(QString::number(trem1->iarea1));
    ui->label_5->setText(QString::number(trem1->iarea2));
    ui->label_6->setText(QString::number(trem1->iconjunto1));
    ui->label_13->setText(QString::number(trem1->iarea3));
    ui->label_16->setText(QString::number(trem1->iconjunto2));

    ui->label_8->setText(QString::number(trem1->area_atual));
    ui->label_9->setText(QString::number(trem2->area_atual));
    ui->label_10->setText(QString::number(trem3->area_atual));
    ui->label_11->setText(QString::number(trem4->area_atual));
    ui->label_12->setText(QString::number(trem5->area_atual));
    switch(id){
    case 1: //Atualiza a posição do objeto da tela (quadrado) que representa o trem1
        ui->label_trem1->setGeometry(x,y,21,17);
        break;
    case 2: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem2->setGeometry(x,y,21,17);
        break;
    case 3: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem3->setGeometry(x,y,21,17);
        break;
    case 4: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem4->setGeometry(x,y,21,17);
        break;
    case 5: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem5->setGeometry(x,y,21,17);
        break;
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Ao clicar, trens começam execução
 */
void MainWindow::on_pushButton_clicked()
{
//    trem1->start();
//    trem2->start();
//    trem3->start();
//    trem4->start();
//    trem5->start();
}

/*
 * Ao clicar, trens param execução
 */
void MainWindow::on_pushButton_2_clicked()
{
//    trem1->terminate();
//    trem2->terminate();
//    trem3->terminate();
//    trem4->terminate();
//    trem5->terminate();
}

void MainWindow::on_vel1_valueChanged(int value)
{
    trem1->setVelocidade(value);
    if(value<200)
        ui->label_trem1->setStyleSheet("QLabel { background: red}");
    else
        ui->label_trem1->setStyleSheet("QLabel { background: grey}");
}

void MainWindow::on_vel2_valueChanged(int value)
{
    trem2->setVelocidade(value);
    if(value<200)
        ui->label_trem2->setStyleSheet("QLabel { background: green}");
    else
        ui->label_trem2->setStyleSheet("QLabel { background: grey}");
}

void MainWindow::on_vel3_valueChanged(int value)
{
    trem3->setVelocidade(value);
    if(value<200)
        ui->label_trem3->setStyleSheet("QLabel { background: purple}");
    else
        ui->label_trem3->setStyleSheet("QLabel { background: grey}");
}

void MainWindow::on_vel4_valueChanged(int value)
{
    trem4->setVelocidade(value);
    if(value<200)
        ui->label_trem4->setStyleSheet("QLabel { background: blue}");
    else
        ui->label_trem4->setStyleSheet("QLabel { background: grey}");
}

void MainWindow::on_vel5_valueChanged(int value)
{
    trem5->setVelocidade(value);

    if(value<200)
        ui->label_trem5->setStyleSheet("QLabel { background: orange}");
    else
        ui->label_trem5->setStyleSheet("QLabel { background: grey}");
}
