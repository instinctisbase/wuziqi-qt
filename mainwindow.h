#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Item.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define CHESS_ROWS 15
#define CHESS_COLUMES 15
#define RECT_WIDTH 50
#define RECT_HEIGHT 50

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    void DrawChessboard();
    void DrawItems();
    void DrawItemWithMouse();

    void DrawChessAtPoint(QPainter& painter,QPoint& pt);
    int CountNearItem(Item item,QPoint ptDirection);


private:
    Ui::MainWindow *ui;

    QVector<Item>mItems;

    bool mIsBlackTurn;//当前该黑棋下
};
#endif // MAINWINDOW_H
