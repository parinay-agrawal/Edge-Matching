#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setNdialog = new SettingsDialog(this);
    fileName = "Untitled";
    this->setWindowTitle("Untitled");

    on_actionReset_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionReset_triggered()
{
    setNdialog->setN(1);
    //other stuff
    numcolors = 0;
    mappingBack.clear();
    mappingFront.clear();

    mappingBack.insert(std::make_pair(0, QColor("white").name()));
    mappingFront.insert(std::make_pair(QColor("white").name(), 0));
    grid.clear();
    grid.resize(1);
    grid[0].resize(1);
    grid[0][0].left = 0;
    grid[0][0].top = 0;
    grid[0][0].bottom = 0;
    grid[0][0].right = 0;
}

void MainWindow::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, "Open a file");
    if (!file.isEmpty()) {
        //read file and take data, then paint is automatically called
        FILE *f = freopen(file.toStdString().c_str(), "r", stdin);
        int n;
        scanf("%d",&n);
        setNdialog->setN(n);
        grid.resize(n);
        for (int i=0;i<n;i++) {
            grid[i].resize(n);
            for (int j=0;j<n;j++) {
                scanf("%d", &grid[i][j].top);
                addColor(grid[i][j].top);
                scanf("%d", &grid[i][j].left);
                addColor(grid[i][j].left);
                scanf("%d", &grid[i][j].bottom);
                addColor(grid[i][j].bottom);
                scanf("%d", &grid[i][j].right);
                addColor(grid[i][j].right);
            }
        }
        int tmp;
        scanf("%d",&tmp);
        if (tmp != 0) {
            int id;
            std::string color;
            for (int i=0;i<tmp;i++) {
                std::cin>>id>>color;
                mappingBack[id] = QString::fromStdString(color);
                mappingFront[QString::fromStdString(color)] = id;
            }
        }

        fclose(f);
        fileName = file;
        this->setWindowTitle(file);
    }
}

void MainWindow::addColor(int color)
{
    if (mappingBack.find(color) != mappingBack.end()) return;
    else {
        if (color == 0) {
            mappingBack[0] = QColor("white").name();
            mappingFront[QColor("white").name()] = 0;
            return;
        }
        int r,g,b;
        do {
            r = rand()%256;
            g = rand()%256;
            b = rand()%256;
        }
        while (mappingFront.find(QColor(r,g,b).name()) != mappingFront.end());
        mappingBack.insert(std::make_pair(color, QColor(r,g,b).name()));
        mappingFront.insert(std::make_pair(QColor(r,g,b).name(), color));
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    QString file = QFileDialog::getSaveFileName(this, "Save as");
    if (!file.isEmpty()) {
        file.append(".txt");
        QString oldfile = fileName;
        fileName = file;
        on_actionSave_triggered();
        fileName = oldfile;
    }
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionpick_color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
    if (color.isValid()) {
        //change the brush color probably
        curColor = color;
    }
}

void MainWindow::on_actionAbout_triggered()
{
    //later
}

void MainWindow::on_actionSave_triggered()
{
    if (fileName.compare("Untitled") == 0) {
        QString file = QFileDialog::getSaveFileName(this, "Save as");
        if (file.isEmpty()) return;
        file.append(".txt");
        fileName = file;
        this->setWindowTitle(fileName);
    }
    FILE *f = freopen(fileName.toStdString().c_str(), "w", stdout);

        //write output to a file
        std::set<int> ids;
        ids.clear();
        if (f != NULL) {
            printf("%d\n",grid.size());
            for (int i=0;i<grid.size();i++) {
                for (int j=0;j<grid.size();j++) {
                    printf("%d %d %d %d\n", grid[i][j].top, grid[i][j].left, grid[i][j].bottom, grid[i][j].right);
                    if (grid[i][j].top != 0) ids.insert(grid[i][j].top);
                    if (grid[i][j].left != 0) ids.insert(grid[i][j].left);
                    if (grid[i][j].bottom != 0) ids.insert(grid[i][j].bottom);
                    if (grid[i][j].right != 0) ids.insert(grid[i][j].right);
                }
            }
            printf("%d\n",ids.size());
            for (std::set<int>::iterator it = ids.begin();it != ids.end();it++) {
                printf("%d %s\n",*it, mappingBack[*it].toStdString().c_str());
            }
            fclose(f);
        }

}

void MainWindow::on_actionUndo_triggered()
{
    //later
}

void MainWindow::on_actionRedo_triggered()
{
    //later
}

void MainWindow::on_actionNew_triggered()
{
    fileName = "Untitled";
    this->setWindowTitle("Untitled");
    on_actionReset_triggered();
}

void MainWindow::on_actionset_N_triggered()
{
    setNdialog->show();
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    QPen linepen(Qt::red);


    QPoint p1,p2;

    QPoint l1,l2,r1,r2;

    QRect winPos = this->geometry();
    QPoint topleft = winPos.topLeft();
    int height = winPos.height();
    int width = winPos.width();

    int n = this->setNdialog->getN();

    int xdiff, ydiff;
    xdiff = width/(n+3);
    ydiff = height/(n+3);
    if (xdiff > ydiff) xdiff = ydiff;
    else ydiff = xdiff;
    //std::cout << topleft.x() << " " << topleft.y() << std::endl;


        for(int i=0;i<=n;i++) {
            if (i!=n) {
                linepen.setWidth(1);
                painter.setPen(linepen);

                for (int j=0;j<n;j++)
                {
                    l1.setX(topleft.x()+xdiff*(j+1));
                    r2.setX(topleft.x()+xdiff*(j+2));
                    l1.setY(topleft.y()+ydiff*(i+1));
                    r2.setY(topleft.y()+ydiff*(i+2));

                    l2.setX(topleft.x()+xdiff*(j+1));
                    r1.setX(topleft.x()+xdiff*(j+2));
                    l2.setY(topleft.y()+ydiff*(i+2));
                    r1.setY(topleft.y()+ydiff*(i+1));


                    QPainterPath path1,path2,path3,path4;
                    path1.moveTo(l1);
                    path1.lineTo((l1.x()+r2.x())/2, (l1.y()+r2.y())/2);
                    path1.lineTo(r1);
                    path1.lineTo(l1);

                    painter.fillPath(path1, QBrush (QColor(mappingBack[grid[i][j].top])));

                    path2.moveTo(l1);
                    path2.lineTo((l1.x()+r2.x())/2, (l1.y()+r2.y())/2);
                    path2.lineTo(l2);
                    path2.lineTo(l1);
                    painter.fillPath(path2, QBrush (QColor(mappingBack[grid[i][j].left])));

                    path3.moveTo(l2);
                    path3.lineTo((l1.x()+r2.x())/2, (l1.y()+r2.y())/2);
                    path3.lineTo(r2);
                    path3.lineTo(l2);
                    painter.fillPath(path3, QBrush (QColor(mappingBack[grid[i][j].bottom])));

                    path4.moveTo(r2);
                    path4.lineTo((l1.x()+r2.x())/2, (l1.y()+r2.y())/2);
                    path4.lineTo(r1);
                    path4.lineTo(r2);
                    painter.fillPath(path4, QBrush (QColor(mappingBack[grid[i][j].right])));


                    painter.drawLine(l1,r2);

                    painter.drawLine(l2,r1);
                }
            }
            linepen.setWidth(2);
            painter.setPen(linepen);

            p1.setX(topleft.x()+xdiff);
            p2.setX(topleft.x()+xdiff*(n+1));
            p1.setY(topleft.y()+ydiff*(i+1));
            p2.setY(topleft.y()+(ydiff*(i+1)));
            painter.drawLine(p1,p2);
        }
        for(int i=0;i<=n;i++) {
            p1.setY(topleft.y()+ydiff);
            p2.setY(topleft.y()+ydiff*(n+1));
            p1.setX(topleft.x()+xdiff*(i+1));
            p2.setX(topleft.x()+(xdiff*(i+1)));
            painter.drawLine(p1,p2);
        }
}

QString MainWindow::getFileName() {
       return fileName;
}

void MainWindow::setFileName(QString file) {
    fileName = file;
}

void MainWindow::setCurColor(QColor color) {
    curColor = color;
}

QColor MainWindow::getCurColor() {
    return curColor;
}

SettingsDialog *MainWindow::getSettingsDialog() {
    return setNdialog;
}

bool MainWindow::getN()
{
    return setNdialog->getN();
}

bool MainWindow::isNchanged()
{
    return (getN() == grid.size());
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton){
        QPoint pos = event->pos();
        QPoint l1,l2,r1,r2;

        QRect winPos = this->geometry();
        QPoint topleft = winPos.topLeft();
        int height = winPos.height();
        int width = winPos.width();

        int n = this->setNdialog->getN();

        int xdiff, ydiff;
        xdiff = width/(n+3);
        ydiff = height/(n+3);
        if (xdiff > ydiff) xdiff = ydiff;
        else ydiff = xdiff;

        for (int i=0;i<n;i++) {
            for (int j=0;j<n;j++) {
                l1.setX(topleft.x()+xdiff*(j+1));
                r2.setX(topleft.x()+xdiff*(j+2));
                l1.setY(topleft.y()+ydiff*(i+1));
                r2.setY(topleft.y()+ydiff*(i+2));

                l2.setX(topleft.x()+xdiff*(j+1));
                r1.setX(topleft.x()+xdiff*(j+2));
                l2.setY(topleft.y()+ydiff*(i+2));
                r1.setY(topleft.y()+ydiff*(i+1));

                QPoint midp;
                midp.setX((l1.x()+r2.x())/2);
                midp.setY((l1.y()+r2.y())/2);

                if (mappingFront.find(curColor.name()) == mappingFront.end()) {
                    //add this color to the maps
                    //chnage numColors
                }

                if (inside(pos, l1, r1, midp)) {
                    grid[i][j].top = mappingFront[curColor.name()];
                    break;
                }
                if (inside(pos, l1, l2, midp)) {
                    grid[i][j].left = mappingFront[curColor.name()];
                    break;
                }
                if (inside(pos, l2, r2, midp)) {
                    grid[i][j].bottom = mappingFront[curColor.name()];
                    break;
                }
                if (inside(pos, r2, r1, midp)) {
                    grid[i][j].right = mappingFront[curColor.name()];
                    break;
                }
            }
        }
    }
}

bool MainWindow::inside(QPoint a, QPoint b, QPoint c, QPoint d) {
    //check if a is inside (b,c,d)
}

