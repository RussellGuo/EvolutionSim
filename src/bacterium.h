#ifndef __BACTERIUM_H_
#define __BACTERIUM_H_

#include <QtCore>

struct TBacterium {
    const qint16 x, y;
    TBacterium(const qint32 _x, const qint32 _y): x(_x), y(_y)  {
        Q_ASSERT( _x < (1L<<15) && _y < (1L<<15));
    }
    TBacterium(const TBacterium &other): x(other.x), y(other.y) { }
    TBacterium &operator =(const TBacterium &other) = delete;

    bool operator == (const TBacterium &other) const {
       bool ret = x == other.x && y == other.y;
       return ret;
    }
};
inline uint qHash(const TBacterium &Bacterium) {
    uint ret = (uint(Bacterium.x) ) << 16 | uint(Bacterium.y);
    return ret;
}

#endif // __BACTERIUM_H_
