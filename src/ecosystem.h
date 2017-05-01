#ifndef TECOSYSTEM_H
#define TECOSYSTEM_H

#include <QObject>
#include <QLinkedList>
#include <QVector>

#include "bug.h"
#include "pool.h"

class TEcosystem : public QObject
{
    Q_OBJECT
public:

    typedef double TBacteriumIncreasedNumber;

    static const qint32 POOL_WIDTH  = 512;
    static const qint32 POOL_HEIGHT = POOL_WIDTH * 3 / 4;

    explicit TEcosystem(QObject *parent = 0);
    TEcosystem(const TEcosystem&) = delete;
    TEcosystem &operator = (const TEcosystem&) = delete;

    typedef QLinkedList<TBug *> TBugList;
    const TBugList getBugList() const;
    const QSet<TBacterium> getBacteria() const;

signals:
    void updated();

public slots:
    void tick();
    void setInitBugNumber(const int &value);
    void setInitBacteriumNumber(const int &value);
    void setIncreaseBacteriumEachForPool(const double &value);
    void setIncreaseBacteriumEachForEden(const double &value);
    void setEdenRadius(const int &value);

private:
    TPool Pool{POOL_WIDTH, POOL_HEIGHT};

    TBugList   BugList;

    quint32 DeadBugCount = 0, ReporductedBudCount = 0;
    TBacteriumIncreasedNumber RemainderBacterium = 0, RemainderBacteriumForEden = 0;
    bool inRunning = false;

    void Initial();
    void toPreventModifyParamtersAfterRunning() const;

    qint32 InitBugNumber = 10;
    qint32 InitBacteriumNumber = POOL_WIDTH * POOL_HEIGHT / 100;
    TBacteriumIncreasedNumber IncreaseBacteriumEachForPool = 0.8;
    TBacteriumIncreasedNumber IncreaseBacteriumEachForEden = 0.5;
    qint32 EdenRadius = 90;
};

#endif // TECOSYSTEM_H
