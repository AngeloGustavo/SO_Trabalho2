#include "trem.h"
#include <QtCore>
#include <QSemaphore>

#define THINKING 0
#define HUNGRY 1
#define EATING 2

static QMutex trem[6];
static QMutex regiaoCritica;
static QMutex regiao[4];
static int estados[8] = {THINKING};

using namespace  std;
//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x_init = x;
    this->y = y_init = y;
    velocidade = 30;
    parado = false;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1: //Trem 1
            if(x == x_init + 220 && y == y_init){
                test1 = regiao[0].try_lock();
                if(test1){
                    test2 = regiao[2].try_lock();
                    if(!test2){
                        regiao[0].unlock();
                        parado = true;
                    }else
                        parado = false;
                 }else
                    parado = true;
            }
            else if(x == x_init + 220 && y == y_init + 110){
                regiao[0].unlock();
            }
            else if(x == x_init + 110 && y == y_init+120){
                regiao[2].unlock();
            }

            break;
        case 2: //Trem 2
            if(x == x_init + 110 && y == y_init + 120){
                test1 = regiao[3].try_lock();
                if(test1){
                    test2 = regiao[0].try_lock();
                    if(!test2){
                        regiao[3].unlock();
                        parado = true;
                    }else
                        parado = false;
                 }else
                    parado = true;
            }
            else if(x == x_init + 10 && y == y_init + 120){
                regiao[3].unlock();
            }
            else if(x == x_init + 10 && y == y_init){
                regiao[0].unlock();
            }
            break;
        case 4: //Trem 4
            if(x == x_init && y == y_init + 10){
                test1 = regiao[2].try_lock();
                if(test1){
                    test2 = regiao[3].try_lock();
                    if(!test2){
                        regiao[2].unlock();
                        parado = true;
                    }else
                        parado = false;
                }else
                    parado = true;
            }
            else if(x == x_init+110 && y == y_init ){
                regiao[2].unlock();
            }else if(x == x_init +220 && y == y_init +10){
                regiao[3].unlock();
            }break;
        default:
            break;
        }

        //Movimentação
        if(parado == false && velocidade<200){
            if (y == y_init && x < x_init+220)
                x+=10;
            else if (x == x_init+220 && y < y_init+120)
                y+=10;
            else if (x > x_init && y == y_init+120)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
        }
        msleep(velocidade);
    }
}

void Trem::setVelocidade(int velocidade){
    this->velocidade = velocidade;
}
