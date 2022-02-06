#include <snakegame.h>
#include <QApplication>

int main(int argc, char* argv[]){
    QApplication app(argc, argv);

    snakegame snakegame;
    snakegame.show();



    return app.exec();
}
