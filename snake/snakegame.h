#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QKeyEvent>


class snakegame : public QWidget
{

        Q_OBJECT
public:
    snakegame();

protected:
    void timerEvent(QTimerEvent*) override;
    void keyPressEvent(QKeyEvent *) override;
    void paintEvent(QPaintEvent *) override;

    // here we spesify the demonsions of the game's windows
private:
    static const int WIDTH = 20;
    static const int LENGHT = 20; // deviding into cells
    static const int FEILD_WIDTH = 40;
    static const int FEILD_LENGHT = 30;
    static const int DELAY = 100;

    void doDraw();
    void localTfaha();
    void move();
    void check_feild();
    void gameOver();
    void check_tfaha();

    int timeID;

    QPoint n_tfaha;
    enum Directions{
        Left, right, up, down
    };

    Directions n_dir;

    bool n_inGame;
    QVector<QPoint> n_dots;

    void initGame();
};

#endif // SNAKEGAME_H
