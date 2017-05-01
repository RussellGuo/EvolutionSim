#ifndef __POOL_H
#define __POOL_H

#include <QtCore>
#include <QBitArray>
#include <QHash>
#include <QSet>
#include "Random.h"
#include "bacterium.h"

class TPool
{
public:
    TPool(qint32 width, qint32 height):
        Width(width), Height(height),
        set()
    {
        Q_ASSERT(Width  > 10 && Width  < ( 1L<<15 ) );
        Q_ASSERT(Height > 10 && Height < ( 1L<<15 ) );
    }
    TPool(const TPool &) = delete;
    TPool& operator = (const TPool &) = delete;
    quint32 getWidth() const
    {
        return Width;
    }

    quint32 getHeight() const
    {
        return Height;
    }
    bool hasBacteriumAt(qint32 x, qint32 y) const {
        qint32 _x = x, _y = y;
        modWidth (_x);
        modHeight(_y);
        TBacterium Bacterium(_x, _y);
        bool ret = set.contains(Bacterium);
        return ret;
    }
    bool cleanBacteriumAt(qint32 x, qint32 y) {
        qint32 _x = x, _y = y;
        modWidth (_x);
        modHeight(_y);
        TBacterium Bacterium(_x, _y);
        bool ret = set.remove(Bacterium);
        return ret;
    }

    quint32 BacteriaCount() const {
        quint32 sum = set.count();
        return sum;
    }

    void addBacteriaRandomly(qint32 n) {
        for (qint32 i = 0; i < n; i++) {
            qint32 x = Random::Random();
            qint32 y = Random::Random();
            modWidth (x);
            modHeight(y);
            TBacterium Bacterium(x, y);
            set.insert(Bacterium);
        }
    }

    void addBacteriaIntoCircle(qint32 n, qint32 x0, qint32 y0, qint32 r) {
        Q_ASSERT(r >= 0);

        for (qint32 i = 0; i < n; i++) {
            qint32 dx, dy; // found a point vs (-r, -r)
            qint32 rx, ry; // same point vs (0,0)
            //
            for(;;) {
                dx = Random::Random() % ( r * 2 + 1);
                dy = Random::Random() % ( r * 2 + 1);
                rx = dx - r;
                ry = dy - r;
                if (rx*rx + ry*ry <= r*r) {
                    break;
                }
            }
            qint32 x = x0 + rx, y = y0 + ry;
            modWidth (x);
            modHeight(y);
            TBacterium Bacterium(x, y);
            set.insert(Bacterium);
        }
    }

    void modWidth(qint32 &x) const {
        x %= Width;
        if (x < 0) {
            x += Width;
        }
    }
    void modHeight(qint32 &y) const {
        y %= Height;
        if (y < 0) {
            y += Height;
        }
    }

    const QSet<TBacterium> getBacteria() const
    {
        return set;
    }

private:
    const qint32 Width, Height;
    QSet<TBacterium> set;

};

#endif // __POOL_H
