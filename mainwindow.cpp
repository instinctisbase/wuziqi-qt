#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include "QMouseEvent"
#include "qmessagebox.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize((CHESS_COLUMES+1)*RECT_WIDTH,(CHESS_ROWS+1)*RECT_HEIGHT);
    mIsBlackTurn = true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    DrawChessboard();
    DrawItems();
    DrawItemWithMouse();

    update();
}

void MainWindow::DrawChessboard()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
    painter.setBrush(Qt::darkYellow);
    painter.setPen(QPen(QColor(Qt::black),2));

    for (int i = 0; i < CHESS_COLUMES; i++){
        for (int j = 0; j<CHESS_ROWS; j++)
        {
            painter.drawRect((i+0.5)*RECT_WIDTH,(j+0.5)*RECT_HEIGHT,RECT_WIDTH,RECT_HEIGHT);
        }
    }

}

void MainWindow::DrawItems()
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(Qt::transparent)));

    for(int i =0;i<mItems.size(); i++)
    {
        Item item = mItems[i];
        if(item.mBlack){
            painter.setBrush(Qt::black);
        }
        else{
            painter.setBrush(Qt::white);
        }
        DrawChessAtPoint(painter,item.mPt);
    }

}

void MainWindow::DrawChessAtPoint(QPainter& painter,QPoint& pt)
{
    QPoint ptCenter((pt.x()+0.5)*RECT_WIDTH,(pt.y()+0.5)*RECT_HEIGHT);
    painter.drawEllipse(ptCenter,RECT_WIDTH/2,RECT_HEIGHT/2);

}

void MainWindow::DrawItemWithMouse()
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(Qt::transparent)));
    if(mIsBlackTurn)
    {
        painter.setBrush(Qt::black);

    }
    else{
        painter.setBrush((Qt::white));
    }

    painter.drawEllipse(mapFromGlobal(QCursor::pos()),RECT_WIDTH/2,RECT_HEIGHT/2);

}
void MainWindow::mousePressEvent(QMouseEvent* e)
{
    //求鼠标点击处的棋子点坐标
    QPoint pt;
    pt.setX( (e->pos().x())/RECT_WIDTH);
    pt.setY((e->pos().y())/RECT_HEIGHT);

    //如果已经存在棋子，则什么都不做
    for(int i = 0; i<mItems.size(); i++)
    {
        Item item = mItems[i];
        if(item.mPt == pt)
        {
            //棋子已存在
            return ;
        }
    }

    //不存在棋子，下一个
    Item item(pt,mIsBlackTurn);
    mItems.append(item);

    //统计四个方向是否五连子
    int nLeft = CountNearItem(item,QPoint(-1,0));
    int nLeftUp = CountNearItem(item,QPoint(-1,-1));
    int nUp = CountNearItem(item,QPoint(0,-1));
    int nRightUp =  CountNearItem(item,QPoint(1,-1));
    int nRight = CountNearItem(item,QPoint(1,0));
    int nRightDown = CountNearItem(item,QPoint(1,1));
    int nDown = CountNearItem(item,QPoint(0,1));
    int nLeftDown = CountNearItem(item, QPoint(-1,1));

    if((nLeft + nRight)>= 4 ||
        (nLeftUp + nRightDown)>=4 ||
            (nUp + nDown) >= 4||
            (nRightUp + nLeftDown) >= 4)
    {
        QString str = mIsBlackTurn?"Black":"White";
        QMessageBox::information(NULL,"GAME OVER", str,QMessageBox::Yes,QMessageBox::Yes);
        mItems.clear();
        return;

    }
    mIsBlackTurn = !mIsBlackTurn;

}
int MainWindow::CountNearItem(Item item,QPoint ptDirection)
{
    int nCount = 0;
    item.mPt += ptDirection;

    while(mItems.contains(item))
    {
        nCount++;
        item.mPt += ptDirection;
    }
    return nCount;
}
