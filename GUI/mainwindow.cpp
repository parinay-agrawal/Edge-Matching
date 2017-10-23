#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setNdialog = new SettingsDialog(this);
    fileName = "Untitled";
    this->setWindowTitle("Edge Matching Creator - Untitled");

    on_actionReset_triggered();

    font.setPointSize(12);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionReset_triggered()
{
    for (int i=0;i<labels.size();i++) {
        for (int j=0;j<labels.size();j++) {
            if (labels[i][j] != NULL) {
                labels[i][j]->~QLabel();
                labels[i][j] = NULL;
            }
        }
    }
    labels.resize(1);
    labels[0].resize(1);
    labels[0][0] = NULL;
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
    getdatafromfile(file);
}

void MainWindow::getdatafromfile(QString file) {
    if (!file.isEmpty()) {
        //read file and take data, then paint is automatically called
        FILE *f = freopen(file.toStdString().c_str(), "r", stdin);
        int n;
        on_actionReset_triggered();
        scanf("%d",&n);
        setNdialog->setN(n);
        grid.resize(n);
        labels.resize(n);
        int nc=0;
        std::map<int,int> new_id;
        new_id.clear();
        new_id[0]=0;
        int tmp;
        for (int i=0;i<n;i++) {
            grid[i].resize(n);
            labels[i].resize(n);
            for (int j=0;j<n;j++) {
                labels[i][j] = new QLabel(this);
                scanf("%d", &tmp);
                if ((new_id.find(tmp)) == new_id.end()) {
                    new_id[tmp] = tmp;
                    nc++;
                }
                grid[i][j].top = new_id[tmp];
                scanf("%d", &tmp);
                if ((new_id.find(tmp)) == new_id.end()) {
                    new_id[tmp] = (tmp);
                    nc++;
                }
                grid[i][j].left = new_id[tmp];
                scanf("%d", &tmp);
                if ((new_id.find(tmp)) == new_id.end()) {
                    new_id[tmp] = (tmp);
                    nc++;
                }
                grid[i][j].bottom = new_id[tmp];
                scanf("%d", &tmp);
                if ((new_id.find(tmp)) == new_id.end()) {
                    new_id[tmp] = (tmp);
                    nc++;
                }
                grid[i][j].right = new_id[tmp];
            }
        }
        scanf("%d",&tmp);
        if (tmp != 0) {
            int id;
            std::string color;
            for (int i=0;i<tmp;i++) {
                std::cin>>id>>color;
                if (new_id.find(id) == new_id.end()) continue;
                if (id != 0) {
                    numcolors++;
                    mappingBack[new_id[id]] = QString::fromStdString(color);
                    mappingFront[QString::fromStdString(color)] = new_id[id];
                }
            }
        }
        else {
            for (int i=1;i<=nc;i++) {
                addColor(i);
            }
        }

        std::vector<std::pair<std::pair<std::pair<int, int>, std::pair<int, int> >, int> > data;
        for (int i=0;i<grid.size();i++) {
            for (int j=0;j<grid.size();j++) {
                auto p1 = std::make_pair(std::make_pair(std::make_pair(grid[i][j].top, grid[i][j].left), std::make_pair(grid[i][j].bottom, grid[i][j].right)), i*grid.size()+j);
                auto p2 = std::make_pair(std::make_pair(std::make_pair(grid[i][j].left, grid[i][j].bottom), std::make_pair(grid[i][j].right, grid[i][j].top)), i*grid.size()+j);
                auto p3 = std::make_pair(std::make_pair(std::make_pair(grid[i][j].bottom, grid[i][j].right), std::make_pair(grid[i][j].top, grid[i][j].left)), i*grid.size()+j);
                auto p4 = std::make_pair(std::make_pair(std::make_pair(grid[i][j].right, grid[i][j].top), std::make_pair(grid[i][j].left, grid[i][j].bottom)), i*grid.size()+j);
                if (p1>p2) p1=p2;
                if (p3>p4) p3=p4;
                if (p1>p3) p1=p3;
                data.push_back(p1);
            }
        }
        std::sort(data.begin(), data.end());
        for (int i=0;i<data.size();i++) {
            labels[data[i].second/grid.size()][data[i].second%grid.size()]->setText(QString::number(i+1));
        }
        fclose(f);
        fileName = file;
        this->setWindowTitle(QString("Edge Matching Creator - ").append(fileName));
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
        while (true) {
            r = ((rand()%256)*(rand()%256))%256;
            g = ((rand()%256)*(rand()%256))%256;
            b = ((rand()%256)*(rand()%256))%256;
            int diff = 1000000000;
            for (int i=0;i<=numcolors;i++) {
                int exr, exg, exb;
                QColor(mappingBack[i]).getRgb(&exr, &exg, &exb);
                diff = std::min(diff, (exr-r)*(exr-r) + (exg-g)*(exg-g) + (exb-b)*(exb-b));
            }
            if (diff > 10000) break;
        }
        mappingBack.insert(std::make_pair(color, QColor(r,g,b).name()));
        mappingFront.insert(std::make_pair(QColor(r,g,b).name(), color));
        numcolors++;
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    QString file = QFileDialog::getSaveFileName(this, "Save as");
    if (!file.isEmpty()) {
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
        fileName = file;
        this->setWindowTitle(QString("Edge Matching Creator - ").append(fileName));
    }
    FILE *f = freopen(fileName.toStdString().c_str(), "w", stdout);

        //write output to a file
        std::set<int> ids;
        ids.clear();
        std::map<int, int> new_id;
        new_id.clear();
        new_id[0] = 0;
        int nc=0;
        if (f != NULL) {
            printf("%d\n",grid.size());
            for (int i=0;i<grid.size();i++) {
                for (int j=0;j<grid.size();j++) {
                    if (new_id.find(grid[i][j].top) == new_id.end()) {
                        new_id[grid[i][j].top] = (grid[i][j].top);
                    }
                    if (new_id.find(grid[i][j].left) == new_id.end()) {
                        new_id[grid[i][j].left] = (grid[i][j].left);
                    }
                    if (new_id.find(grid[i][j].bottom) == new_id.end()) {
                        new_id[grid[i][j].bottom] = (grid[i][j].bottom);
                    }
                    if (new_id.find(grid[i][j].right) == new_id.end()) {
                        new_id[grid[i][j].right] = (grid[i][j].right);
                    }
                    printf("%d %d %d %d\n", new_id[grid[i][j].top], new_id[grid[i][j].left], new_id[grid[i][j].bottom], new_id[grid[i][j].right]);
                    if (grid[i][j].top != 0) ids.insert(grid[i][j].top);
                    if (grid[i][j].left != 0) ids.insert(grid[i][j].left);
                    if (grid[i][j].bottom != 0) ids.insert(grid[i][j].bottom);
                    if (grid[i][j].right != 0) ids.insert(grid[i][j].right);
                }
            }
            printf("%d\n",ids.size());
            for (std::set<int>::iterator it = ids.begin();it != ids.end();it++) {
                printf("%d %s\n",new_id[*it], mappingBack[*it].toStdString().c_str());
            }
            fclose(f);

            //reopen the file
            getdatafromfile(fileName);
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
    this->setWindowTitle("Edge Matching Creator - Untitled");
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

    int n = grid.size();

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

                    QPoint midp((l1.x()+r2.x())/2, (l1.y()+r2.y())/2);

                    if (labels[i][j] == NULL) {
                        labels[i][j] = new QLabel(this);
                        labels[i][j]->setText(QString::number(-1));
                    }
                    labels[i][j]->setGeometry(QRect(midp, r2));
                    labels[i][j]->setFont(font);
                    labels[i][j]->show();


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

int MainWindow::getN()
{
    return setNdialog->getN();
}

bool MainWindow::isNchanged()
{
    return !(getN() == grid.size());
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
        QPoint pos = event->pos();
        QPoint l1,l2,r1,r2;

        QRect winPos = this->geometry();
        QPoint topleft = winPos.topLeft();
        int height = winPos.height();
        int width = winPos.width();

        int n = grid.size();

        int xdiff, ydiff;
        xdiff = width/(n+3);
        ydiff = height/(n+3);
        if (xdiff > ydiff) xdiff = ydiff;
        else ydiff = xdiff;

        bool done=false;
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

                if (inside(pos, l1, r1, midp)) {
                    if (event->button() == Qt::LeftButton) {
                        if (mappingFront.find(curColor.name()) == mappingFront.end()) {
                            mappingFront.insert(std::make_pair(curColor.name(), ++numcolors));
                            mappingBack.insert(std::make_pair(numcolors, curColor.name()));
                        }
                        grid[i][j].top = mappingFront[curColor.name()];
                    }
                    else if (event->button() == Qt::RightButton) {
                        curColor = QColor(mappingBack[grid[i][j].top]);
                    }

                    done=true;
                    break;
                }
                if (inside(pos, l1, l2, midp)) {
                    if (event->button() == Qt::LeftButton) {
                        if (mappingFront.find(curColor.name()) == mappingFront.end()) {
                            mappingFront.insert(std::make_pair(curColor.name(), ++numcolors));
                            mappingBack.insert(std::make_pair(numcolors, curColor.name()));
                        }
                        grid[i][j].left = mappingFront[curColor.name()];
                    }
                    else if (event->button() == Qt::RightButton) {
                        curColor = QColor(mappingBack[grid[i][j].left]);
                    }

                    done=true;
                    break;
                }
                if (inside(pos, l2, r2, midp)) {
                    if (event->button() == Qt::LeftButton) {
                        if (mappingFront.find(curColor.name()) == mappingFront.end()) {
                            mappingFront.insert(std::make_pair(curColor.name(), ++numcolors));
                            mappingBack.insert(std::make_pair(numcolors, curColor.name()));
                        }
                        grid[i][j].bottom = mappingFront[curColor.name()];
                    }
                    else if (event->button() == Qt::RightButton) {
                        curColor = QColor(mappingBack[grid[i][j].bottom]);
                    }

                    done=true;
                    break;
                }
                if (inside(pos, r2, r1, midp)) {
                    if (event->button() == Qt::LeftButton) {
                        if (mappingFront.find(curColor.name()) == mappingFront.end()) {
                            mappingFront.insert(std::make_pair(curColor.name(), ++numcolors));
                            mappingBack.insert(std::make_pair(numcolors, curColor.name()));
                        }
                        grid[i][j].right = mappingFront[curColor.name()];
                    }
                    else if (event->button() == Qt::RightButton) {
                        curColor = QColor(mappingBack[grid[i][j].right]);
                    }

                    done=true;
                    break;
                }
            }
            if (done) break;
        }
}

bool MainWindow::inside(QPoint a, QPoint b, QPoint c, QPoint d)
{
    QPointF p = QPointF(a);
    QPointF p1 = QPointF(b);
    QPointF p2 = QPointF(c);
    QPointF p3 = QPointF(d);
    //check if a is inside (b,c,d)
    float alpha = ((p2.y() - p3.y())*(p.x() - p3.x()) + (p3.x() - p2.x())*(p.y() - p3.y())) /
            ((p2.y() - p3.y())*(p1.x() - p3.x()) + (p3.x() - p2.x())*(p1.y() - p3.y()));
    float beta = ((p3.y() - p1.y())*(p.x() - p3.x()) + (p1.x() - p3.x())*(p.y() - p3.y())) /
           ((p2.y() - p3.y())*(p1.x() - p3.x()) + (p3.x() - p2.x())*(p1.y() - p3.y()));
    float gamma = 1.0f - alpha - beta;
    if (alpha>0 && beta>0 && gamma>0) return true;
    else return false;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_R)
    {
        curColor = QColor(255,0,0);
    }
    else if(event->key() == Qt::Key_G)
    {
        curColor = QColor(0,255,0);
    }
    else if(event->key() == Qt::Key_B)
    {
        curColor = QColor(0,0,255);
    }
    else if (event->key() == Qt::Key_W)
    {
        curColor = QColor(255,255,255);
    }
    else if (event->key() == Qt::Key_Y)
    {
        curColor = QColor(255,255,0);
    }
    else if (event->key() == Qt::Key_C)
    {
        curColor = QColor(0,255,255);
    }
    else if (event->key() == Qt::Key_M)
    {
        curColor = QColor(255,0,255);
    }
}

