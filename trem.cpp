#include "trem.h"
#include <QtCore>
#include <QSemaphore>
#include <iostream>

#define THINKING 0
#define HUNGRY 1
#define EATING 2

static QMutex regiaoCritica;
static QMutex regiao[7];
static QSemaphore area1(2);
static QSemaphore area2(2);
static QSemaphore area3(2);
static QSemaphore conjunto1(3);
static QSemaphore conjunto2(3);
static QSemaphore geral(4);

using namespace  std;
//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x_init = x;
    this->y = y_init = y;
    velocidade = 200;
    parado = false;
    area_atual=-1;
    if(ID == 4){//Trem 4 ja começa na região 2 que implica estar no conjunto 1 e na area 1 e 2
        geral.acquire(1);
        conjunto1.acquire(1);
        area1.acquire(1);
        area2.acquire(1);
        regiao[2].lock();
    }
    else if(ID == 5){//Trem 5 ja começa na regiao 4 o que implica estar no conjunto 2 e na area 3
        geral.acquire(1);
        conjunto2.acquire(1);
        area3.acquire(1);
        regiao[4].lock();
    }
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){

        iarea1 = 2-area1.available();
        iarea2 = 2-area2.available();
        iarea3 = 2-area3.available();
        iconjunto1 = 3-conjunto1.available();
        iconjunto2 = 3-conjunto1.available();
        igeral = 4-conjunto1.available();

        switch(ID){
        case 1: //Trem 1
            if(x == x_init + 220 && y == y_init){//Entrando na região 0
                regiaoCritica.lock();//Trava

                test1 = geral.tryAcquire(1);
                if(test1){
                    test2 = conjunto1.tryAcquire(1);
                    if(test2){
                        test3 = conjunto2.tryAcquire(1);
                        if(test3){
                            test4 = area1.tryAcquire(1);
                            if(test4){
                                test5 = regiao[0].try_lock();
                                if(test5){
                                    parado = false;
                                }else{
                                    if(geral.available() < 4)
                                        geral.release(1);
                                    if(area1.available() < 2)
                                        area1.release(1);
                                    if(conjunto1.available() < 3)
                                        conjunto1.release(1);
                                    if(conjunto2.available() < 3)
                                        conjunto2.release(1);
                                    parado = true;
                                }
                            }else{
                                if(geral.available() < 4)
                                    geral.release(1);
                                if(conjunto2.available() < 3)
                                    conjunto2.release(1);
                                if(conjunto1.available() < 3)
                                    conjunto1.release(1);
                                parado = true;
                            }
                        }else{
                            if(geral.available() < 4)
                                geral.release(1);
                            if(conjunto1.available() < 3)
                                conjunto1.release(1);
                            parado = true;
                        }
                    }else{
                        if(geral.available() < 4)
                            geral.release(1);
                        parado = true;
                    }
                }else
                    parado = true;

                regiaoCritica.unlock();//Trava
            }
            else if(x == x_init + 220 && y == y_init + 110){//Entrando na região 2
                regiaoCritica.lock();//Trava

                test1 = area2.tryAcquire(1);
                if(test1){
                    test2 = regiao[2].try_lock();
                    if(test2){
                        regiao[0].unlock();
                        area_atual=2;
                        parado = false;
                    }else{
                        if(area2.available() < 2)
                            area2.release(1);
                        parado = true;
                    }
                }else
                    parado = true;

                regiaoCritica.unlock();//Trava
            }
            else if(x == x_init + 110 && y == y_init+120){//Entrando na região 1
                regiao[1].lock();
                area_atual=1;
                regiao[2].unlock();

                regiaoCritica.lock();
                if(area1.available() < 2)
                    area1.release(1);
                regiaoCritica.unlock();
            }
            else if(x == x_init && y == y_init+120){//Saindo da ultima região (1)
                regiao[1].unlock();

                regiaoCritica.lock();
                if(geral.available() < 4)
                    geral.release(1);
                if(area2.available() < 2)
                    area2.release(1);
                if(conjunto2.available() < 3)
                    conjunto2.release(1);
                if(conjunto1.available() < 3)
                    conjunto1.release(1);
                regiaoCritica.unlock();            }

            break;
        case 2: //Trem 2
            if(x == x_init + 220 && y == y_init + 120){//Entrando na região 4
                regiaoCritica.lock();//Trava

                test1 = geral.tryAcquire(1);
                if(test1){
                    test2 = conjunto2.tryAcquire(1);
                    if(test2){
                        test3 = area3.tryAcquire(1);
                        if(test3){
                            test4 = regiao[4].try_lock();
                            if(test4){
                                area_atual = 4;
                                parado = false;
                            }else{
                                if(geral.available() < 4)
                                    geral.release(1);
                                if(area3.available() < 2)
                                    area3.release(1);
                                if(conjunto2.available() < 3)
                                    conjunto2.release(1);
                                parado = true;
                            }
                        }else{
                            if(geral.available() < 4)
                                geral.release(1);
                            if(conjunto2.available() < 3)
                                conjunto2.release(1);
                            parado = true;
                        }
                    }else{
                        if(geral.available() < 4)
                            geral.release(1);
                        parado = true;
                    }
                }else
                    parado = true;
                regiaoCritica.unlock();//Trava
            }
            else if(x == x_init + 110 && y == y_init + 120){//Entrando na região 3
                regiaoCritica.lock();//Trava

                test1 = conjunto1.tryAcquire(1);
                if(test1){
                    test2 = area1.tryAcquire(1);
                    if(test2){
                        test3 = regiao[3].try_lock();
                        if(test3){
                            area_atual=3;
                            regiao[4].unlock();
                            parado = false;
                        }else{
                            if(area1.available() < 2)
                                area1.release(1);
                            if(conjunto1.available() < 3)
                                conjunto1.release(1);
                            parado = true;
                        }
                    }else{
                        if(conjunto1.available() < 3)
                            conjunto1.release(1);
                        parado = true;
                    }
                }else
                    parado = true;

                regiaoCritica.unlock();//Trava
            }
            else if(x == x_init + 10 && y == y_init + 120){//Entrando na região 0
                regiao[0].lock();
                area_atual=0;
                regiao[3].unlock();

                regiaoCritica.lock();
                if(area3.available() < 2)
                    area3.release(1);
                regiaoCritica.unlock();
            }
            else if(x == x_init && y == y_init + 10){//Saindo da ultima região (0)
                regiao[0].unlock();

                regiaoCritica.lock();
                if(geral.available() < 4)
                    geral.release(1);
                if(area1.available() < 2)
                    area1.release(1);
                if(conjunto1.available() < 3)
                    conjunto1.release(1);
                if(conjunto2.available() < 3)
                    conjunto2.release(1);
                regiaoCritica.unlock();
            }
            break;
        case 3: //Trem 3
            if(x == x_init+110 && y == y_init){//Entrando regiao 1
                regiaoCritica.lock();//Trava

                test1 = geral.tryAcquire(1);
                if(test1){
                    test2 = conjunto1.tryAcquire(1);
                    if(test2){
                        test3 = area2.tryAcquire(1);
                        if(test3){
                            test4 = regiao[1].try_lock();
                            if(test4){
                                area_atual=1;
                                parado = false;
                            }else{
                                if(geral.available() < 4)
                                    geral.release(1);
                                if(area2.available() < 2)
                                    area2.release(1);
                                if(conjunto1.available() < 3)
                                    conjunto1.release(1);
                                parado = true;
                            }
                        }else{
                            if(geral.available() < 4)
                                geral.release(1);
                            if(conjunto1.available() < 3)
                                conjunto1.release(1);
                            parado = true;
                        }
                    }else{
                        if(geral.available() < 4)
                            geral.release(1);
                        parado = true;
                    }
                }else
                    parado = true;

                regiaoCritica.unlock();//Trava
            }
            else if(x == x_init+220 && y == y_init ){//Entrando na região 5
                regiao[5].lock();
                area_atual=5;
                regiao[1].unlock();
            }else if(x == x_init +220 && y == y_init +120){//Saindo da ultima região (5)
                regiao[5].unlock();

                regiaoCritica.lock();
                if(geral.available() < 4)
                    geral.release(1);
                if(area2.available() < 2)
                    area2.release(1);
                if(conjunto1.available() < 3)
                    conjunto1.release(1);
                regiaoCritica.unlock();
            }break;

        case 4: //Trem 4
            if(x == x_init && y == y_init+120){//Entrando na região 5
                regiaoCritica.lock();//Trava

                test1 = geral.tryAcquire(1);
                if(test1){
                    test1 = conjunto1.tryAcquire(1);
                    if(test1){
                        test2 = area2.tryAcquire(1);
                        if(test2){
                            test3 = regiao[5].try_lock();
                            if(test3){
                                area_atual=5;
                                parado = false;
                            }else{
                                if(geral.available() < 4)
                                    geral.release(1);
                                if(area2.available() < 2)
                                    area2.release(1);
                                if(conjunto1.available() < 3)
                                    conjunto1.release(1);
                                parado = true;
                            }
                        }else{
                            if(geral.available() < 4)
                                geral.release(1);
                            if(conjunto1.available() < 3)
                                conjunto1.release(1);
                            parado = true;
                        }
                    }else{
                        if(geral.available() < 4)
                            geral.release(1);
                        parado = true;
                    }
                }else
                    parado = true;

                std::cout<<parado<<endl;
                regiaoCritica.unlock();//Trava
            }
            else if(x == x_init && y == y_init + 10){//Entrando na região 2
                regiaoCritica.lock();//Trava

                test1 = conjunto2.tryAcquire(1);
                if(test1){
                    test2 = area1.tryAcquire(1);
                    if(test2){
                        test3 = regiao[2].try_lock();
                        if(test3){
                            area_atual=2;
                            regiao[5].unlock();
                            parado = false;
                        }else{
                            if(conjunto2.available() < 2)
                                conjunto2.release(1);
                            if(area1.available() < 2)
                                area1.release(1);
                            parado = true;
                        }
                    }else{
                        if(conjunto2.available() < 2)
                            conjunto2.release(1);
                        parado = true;
                    }
                }else
                    parado = true;
                regiaoCritica.unlock();//Trava
            }
            else if(x == x_init+110 && y == y_init){//Entrando região 3
                regiaoCritica.lock();//Trava

                test1 = area3.tryAcquire(1);
                if(test1){
                    test2 = regiao[3].try_lock();
                    if(test2){
                        area_atual=3;
                        regiao[2].unlock();
                        if(area2.available() < 2)
                            area2.release(1);
                        parado = false;
                    }else{
                        if(area3.available() < 2)
                            area3.release(1);
                        parado = true;
                    }
                }else
                    parado = true;

                regiaoCritica.unlock();//Trava
            }else if(x == x_init +220 && y == y_init +10){//Entrando na regiao 6
                regiao[6].lock();
                area_atual=6;
                regiao[3].unlock();

                regiaoCritica.lock();
                if(area1.available() < 2)
                    area1.release(1);
                if(conjunto1.available() < 3)
                    conjunto1.release(1);
                regiaoCritica.unlock();
            }else if(x == x_init +220 && y == y_init +120){//Saindo da ultima regiao (6)
                regiao[6].unlock();

                regiaoCritica.lock();
                if(geral.available() < 4)
                    geral.release(1);
                if(area3.available() < 2)
                    area3.release(1);
                if(conjunto2.available() < 3)
                    conjunto2.release(1);
                regiaoCritica.unlock();
            }break;

        case 5: //Trem 5
            if(x == x_init && y == y_init+120){//Entrando na região 6
                regiaoCritica.lock();//Trava

                test1 = geral.tryAcquire(1);
                if(test1){
                    test1 = conjunto2.tryAcquire(1);
                    if(test1){
                        test2 = area3.tryAcquire(1);
                        if(test2){
                            test3 = regiao[6].try_lock();
                            if(test3){
                                area_atual=6;
                                parado = false;
                            }else{
                                if(geral.available() < 4)
                                    geral.release(1);
                                if(area3.available() < 2)
                                    area3.release(1);
                                if(conjunto2.available() < 3)
                                    conjunto2.release(1);
                                parado = true;
                            }
                        }else{
                            if(geral.available() < 4)
                                geral.release(1);
                            if(conjunto2.available() < 3)
                                conjunto2.release(1);
                            parado = true;
                        }
                    }else{
                        if(geral.available() < 4)
                            geral.release(1);
                        parado = true;
                    }
                }else
                    parado = true;

                regiaoCritica.unlock();//Trava
            }
            else if(x == x_init && y == y_init +10){//Entrando na região 4
                regiao[4].lock();
                area_atual=4;
                regiao[6].unlock();
            }else if(x == x_init +110 && y == y_init){//Saindo da ultima região (4)
                regiao[4].unlock();

                regiaoCritica.lock();
                if(geral.available() < 4)
                    geral.release(1);
                if(area3.available() < 2)
                    area3.release(1);
                if(conjunto2.available() < 3)
                    conjunto2.release(1);
                regiaoCritica.unlock();
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
