#ifndef TREM_H
#define TREM_H

#include <QThread>
#include <QMutex>
#include <vector>
#include <QSemaphore>

/*
 * Classe Trem herda QThread
 * Classe Trem passa a ser uma thread.
 * A função START inicializa a thread. Após inicializada, a thread irá executar a função RUN.
 * Para parar a execução da função RUN da thread, basta executar a função TERMINATE.
 *
*/
class Trem: public QThread{
 Q_OBJECT
public:
    Trem(int ID, int x, int y);  //construtor
    void run();         //função a ser executada pela thread
    void setVelocidade(int velocidade);
    int iarea1,iarea2, iarea3,iconjunto1, iconjunto2, igeral;
    int area_atual;

//Cria um sinal
signals:
    void updateGUI(int,int,int);

private:
   int x_init;
   int y_init;
   int x;           //posição X do trem na tela
   int y;           //posição Y do trem na tela
   int ID;          //ID do trem
   int velocidade;  //Velocidade. É o tempo de dormir em milisegundos entre a mudança de posição do trem
   //+std::vector <int> &estados;
   bool test1;
   bool test2;
   bool test3;
   bool test4;
   bool test5;
   bool parado;

};

#endif // TREM_H
