#include "trem.h"
#include <QtCore>
#include <QSemaphore>

#define THINKING 0
#define HUNGRY 1
#define EATING 2

static QMutex trens[6];
static QMutex regiaoCritica;
static int estados[8] = {0};

using namespace  std;
//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x_init = x;
    this->y = y_init = y;
    velocidade = 30;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1: //Trem 1
            if(x == x_init + 220 && y == y_init)
                estados[1] = HUNGRY;
            else if(x == x_init + 110 && y == y_init+120)
                estados[1] = THINKING;

            if(estados[1] == HUNGRY){
                regiaoCritica.lock();
                if(estados[2] != EATING && estados[4] != EATING)
                   estados[1] = EATING;
                regiaoCritica.unlock();
            }
            break;
        case 2: //Trem 2
            if(x == x_init + 110 && y == y_init + 120)
                estados[2] = HUNGRY;
            else if(x == x_init + 10 && y == y_init)
                estados[2] = THINKING;

            if(estados[2] == HUNGRY){
                regiaoCritica.lock();
                if(estados[1] != EATING && estados[4] != EATING)
                   estados[2] = EATING;
                regiaoCritica.unlock();
            }
            break;
        case 4: //Trem 4
            if(x == x_init && y == y_init + 10)
                estados[4] = HUNGRY;
            else if(x == x_init + 220 && y == y_init + 10)
                estados[4] = THINKING;

            if(estados[4] == HUNGRY){
                regiaoCritica.lock();
                if(estados[1] != EATING && estados[2] != EATING)
                   estados[4] = EATING;
                regiaoCritica.unlock();
            }
            break;
        default:
            break;
        }

        //Movimentação
        if(estados[ID] != HUNGRY && velocidade<200){
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
