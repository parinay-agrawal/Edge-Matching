#include "mainwindow.h"
#include <QApplication>
#include <unistd.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    while(true) {
        a.processEvents();
        if (w.isNchanged()) {
            int prevN = w.grid.size();
            w.grid.resize(w.getN());
            for (int i=0;i<w.getN();i++) {
                w.grid[i].resize(w.getN());
            }
            if (prevN < w.getN()) {
                for (int i=prevN;i<w.getN();i++) {
                    for (int j=prevN;j<w.getN();j++) {
                        w.grid[i][j].top = 0;
                        w.grid[i][j].left=0;
                        w.grid[i][j].right = 0;
                        w.grid[i][j].bottom = 0;
                    }
                }
            }
        }
        w.repaint();
        usleep(1000);
    }
    //return a.exec();
}
