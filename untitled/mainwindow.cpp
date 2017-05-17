#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QGraphicsObject"
#include <QString>
#include <QImage>
#include <QDebug>
#include <QPoint>
#include <QColor>
#include <QRgb>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    image=new QImage;
    image->load("2.jpg");
    for(int i=0;i<300;i++)
        for(int j=0;j<300;j++)
            q[i][j]=qGray(image->pixelColor(i,j).rgba())&240;
    for(int i=0;i<300;i++)
        for(int j=0;j<300;j++)
            image->setPixelColor(i,j,QColor::fromRgb(q[i][j],q[i][j],q[i][j]));
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(*image));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->resize(310, 310);
    ui->graphicsView->show();
   t[0]=0.400001;
   for(int i=1;i<=90000;i++)
        t[i]=1-2.0*t[i-1]*t[i-1];
  for(int i = 0; i < 17; i++)
       ui->tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
  int a[16];
  for(int i=0;i<16;i++)a[i]=0;
  for(int i=0;i<300;i++)
      for(int j=0;j<300;j++)
          a[qGray(image->pixelColor(i,j).rgba())>>4]++;
  ui->tableWidget->setItem(0,0,new QTableWidgetItem(QString::number(0)));
  for(int i=0;i<16;i++)ui->tableWidget->setItem(0,i+1,new QTableWidgetItem(QString::number(a[i])));
  ui->tableWidget->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
int cnt = 0;
void MainWindow::on_pushButton_clicked()
{
    cnt++;
    ui->label->setText(QString::number(cnt));
    QImage ti=*image;
    for(int i=0;i<300;i++)
        for(int j=0;j<300;j++)
            ti.setPixelColor((i+j)%300,(i+2*j)%300,image->pixelColor(i,j));
    for(int i=0;i<300;i++)
        for(int j=0;j<300;j++)
        {
            q[i][j]=(((int)(floor)(t[(i-1)*300+j]*1000)+q[i][j])%256+256)%256;
            ti.setPixelColor(i,j,QColor::fromRgb(q[i][j],q[i][j],q[i][j]));
        }
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(ti));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->resize(310, 310);
    ui->graphicsView->show();
    (*image)=ti;
    int a[16];
    for(int i=0;i<16;i++)a[i]=0;
    for(int i=0;i<300;i++)
        for(int j=0;j<300;j++)
            a[qGray(image->pixelColor(i,j).rgba())>>4]++;
    ui->tableWidget->setItem(0,0,new QTableWidgetItem(QString::number(cnt)));
    for(int i=0;i<16;i++)ui->tableWidget->setItem(0,i+1,new QTableWidgetItem(QString::number(a[i])));
    ui->tableWidget->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    QImage *tmp = new QImage;
    tmp->load("1.jpg");
    for(int i=0;i<300;i++)
        for(int j=0;j<300;j++)
        {
            int x=(qGray(tmp->pixelColor(i,j).rgb())&240)+(qGray((image->pixelColor(i,j).rgb()))>>4);
            tmp->setPixelColor(i,j,QColor::fromRgb(x,x,x));
        }
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(*tmp));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->resize(310, 310);
    ui->graphicsView->show();
}
