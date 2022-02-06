#include "snakegame.h"

#include <QDebug>
#include <QPainter>
#include <QTime>
#include <QRandomGenerator>
#include<QMessageBox>


snakegame::snakegame()
{
    this->resize(WIDTH + FEILD_WIDTH, LENGHT + FEILD_LENGHT);
    this->setWindowTitle("SNAKE GAME");

    initGame();
}

void snakegame::timerEvent(QTimerEvent *e){
    Q_UNUSED(e);

    if(n_inGame){
        check_tfaha();
        move();
        check_feild();
    }
    this->repaint();
}

// the key press function
void snakegame::keyPressEvent(QKeyEvent *e){
    int key = e->key();
    if(key == Qt::Key_Left     && n_dir != Directions::right){ n_dir = Directions::Left;}
    if(key == Qt::Key_Right    && n_dir != Directions::Left){ n_dir = Directions::right;}
    if(key == Qt::Key_Up       && n_dir != Directions::down){ n_dir = Directions::up;}
    if(key == Qt::Key_Down     && n_dir != Directions::up){ n_dir = Directions::down;}

}

void snakegame::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    doDraw();
}

void snakegame::doDraw(){

    QPainter qp(this);

    if(n_inGame){

    qp.setBrush(Qt::red);
    // qp.setPen();
    qp.drawEllipse(n_tfaha.x() * WIDTH, n_tfaha.y() * LENGHT, WIDTH, LENGHT);

    for (int i= 0; i < n_dots.size(); ++i ) {
        if(i == 0){
            qp.setBrush(Qt::white);
            qp.drawEllipse(n_dots[i].x() * WIDTH, n_dots[i].y() * LENGHT, WIDTH, LENGHT);
        }else{
            qp.setBrush(Qt::green);
            qp.drawEllipse(n_dots[i].x() * WIDTH, n_dots[i].y() * LENGHT, WIDTH, LENGHT);
        }
    }

    }else{

        gameOver();

    }
}

void snakegame::localTfaha()
{
    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());
    n_tfaha.rx() = qrand() % WIDTH;
    n_tfaha.ry() = qrand() % LENGHT;
}

void snakegame::move()
{

    for (int i = n_dots.size()-1; i > 0 ; --i ) {
        n_dots[i] = n_dots[i+1];
    }

    switch(n_dir){
    case Left:      {n_dots[0].rx() -= 1; break;}
    case right:     {n_dots[0].rx() += 1; break;}
    case up:        {n_dots[0].ry() -= 1; break;}
    case down:      {n_dots[0].ry() += 1; break;}

    }

}

void snakegame::check_feild()
{
    if(n_dots.size() > 4){
        for(int i = 1; i <n_dots.size(); ++i){
            if(n_dots[0] == n_dots[i]){
                n_inGame = false;
            }
        }
    }
    if(n_dots[0].x() >= FEILD_WIDTH){n_inGame = false;}
    if(n_dots[0].x() < 0 )          {n_inGame = false;}
    if(n_dots[0].y() >= FEILD_WIDTH){n_inGame = false;}
    if(n_dots[0].y() < 0)           {n_inGame = false;}

    if(!n_inGame){
        killTimer(timeID);
    }
}

void snakegame::gameOver()
{
    QMessageBox msgb;
    msgb.setText("GAME OVER");
    msgb.exec();

    initGame();
}

void snakegame::check_tfaha(){

    if (n_tfaha == n_dots[0]){
         n_dots.push_back(QPoint(0,0));
         localTfaha();
         }
}

void snakegame::initGame(){
    n_inGame = true;
    n_dir = right;

    n_dots.resize(3);

    for (int i = 0; i< n_dots.size(); ++i ) {
        n_dots[i].rx() = n_dots.size() - i -1;
        n_dots[i].ry() = 0;
    }

    timeID = startTimer(DELAY);
}


