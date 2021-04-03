#pragma once
#include <QPoint>

class Item
{
public:
    Item(void);
    Item(QPoint pt,bool bBlack);
    ~Item(void);

    QPoint mPt;
    bool mBlack;
    bool operator==(const Item &t1)const
    {
        return ((mPt == t1.mPt ) && (mBlack == t1.mBlack));
    }


};
