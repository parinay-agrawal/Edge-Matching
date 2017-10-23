#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include <QColorDialog>
#include <vector>
#include <map>
#include "settingsdialog.h"
#include <stdio.h>
#include <stdlib.h>
#include <set>

namespace Ui {
class MainWindow;
}

typedef struct node {
    int top;
    int left;
    int bottom;
    int right;
} square;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void drawGrid();

    ~MainWindow();

private slots:
    void on_actionReset_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_as_triggered();

    void on_actionExit_triggered();

    void on_actionpick_color_triggered();

    void on_actionAbout_triggered();

    void on_actionSave_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionNew_triggered();

    void on_actionset_N_triggered();

public:
    QString getFileName();

    void setFileName(QString);

    QColor getCurColor();

    void setCurColor(QColor);

    bool isNchanged();

    int getN();

    void addColor(int);

    SettingsDialog *getSettingsDialog();

    bool inside(QPoint, QPoint, QPoint, QPoint);

private:
    Ui::MainWindow *ui;
    QString fileName;

    int numcolors=0;

    QColor curColor = Qt::white;
    SettingsDialog *setNdialog;
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
public:
    std::map<int, QString> mappingBack;
    std::map<QString, int> mappingFront;
    std::vector<std::vector<square> > grid;
};

#endif // MAINWINDOW_H
