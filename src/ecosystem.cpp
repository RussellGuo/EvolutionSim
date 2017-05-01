#include "ecosystem.h"

TEcosystem::TEcosystem(QObject *parent) :
    QObject(parent)
{
}

const QSet<TBacterium> TEcosystem::getBacteria() const
{
    auto ret = Pool.getBacteria();
    return ret;
}

void TEcosystem::tick()
{
    if (!inRunning) {
        Initial();
        inRunning = true; // to prevent changging paramters of Ecosystem.
    }

    // new turn, bacteria adding in the pool...
    RemainderBacterium += IncreaseBacteriumEachForPool;
    qint32 totalBacteriaForPool = qint32(RemainderBacterium);
    RemainderBacterium -= totalBacteriaForPool;
    Pool.addBacteriaRandomly(totalBacteriaForPool);

    // Eden, more bacteria
    RemainderBacteriumForEden += IncreaseBacteriumEachForEden;
    qint32 totalBacteriaForEden = qint32(RemainderBacteriumForEden);
    RemainderBacteriumForEden -= totalBacteriaForEden;
    Pool.addBacteriaIntoCircle(totalBacteriaForEden, 100, -100, EdenRadius);


    // for each bug...
    auto it = BugList.begin();
    while (it != BugList.end()) {
        TBug *bug = *it;
        bug->tick();
        TBug::TState State = bug->getState();
        switch (State) {
        case TBug::LIVING:
            ++it;
            break;

        case TBug::DEAD:
        case TBug::READY_TO_REPRODUCE:
            it = BugList.erase(it);
            if (State == TBug::READY_TO_REPRODUCE) {
                for (const auto MutantType :{TBug::INCREASE, TBug::DECREASE}) {
                    TBug *Child = new TBug(bug, MutantType);
                    if (Child == 0) {
                        qFatal("not enough memory for the born bugs");
                    }
                    BugList.append(Child);
                }
                ReporductedBudCount++;
            } else {
                DeadBugCount++;
            }
            delete bug;
            break;
        default:
            qFatal("unknown bug state: %d", qint32(State));
        }
    }
    emit updated();
    {
        static int count;
        if (++count % 0x1000 == 0) {
            qDebug("%12d %12d %12d %12d", DeadBugCount, ReporductedBudCount, BugList.count(), Pool.BacteriaCount());
            count = 0;
        }
    }
}

void TEcosystem::Initial()
{
    if (inRunning) {
        qFatal("Initial more than once");
        return;
    }
    Pool.addBacteriaRandomly(InitBacteriumNumber);
    for (qint32 i = 0; i < InitBugNumber; i++) {
        TBug *bug = new TBug(&Pool);
        if (bug == 0) {
            qFatal("not enough memory for the initial-bugs");
        }
        BugList.append(bug);
    }
}

void TEcosystem::toPreventModifyParamtersAfterRunning() const
{
    if (inRunning) {
        qFatal("parameters cannot updated in running");
    }
}

void TEcosystem::setEdenRadius(const int &value)
{
    toPreventModifyParamtersAfterRunning();
    EdenRadius = value;
}

void TEcosystem::setIncreaseBacteriumEachForEden(const double &value)
{
    toPreventModifyParamtersAfterRunning();
    IncreaseBacteriumEachForEden = TBacteriumIncreasedNumber(value);
}

void TEcosystem::setIncreaseBacteriumEachForPool(const double &value)
{
    toPreventModifyParamtersAfterRunning();
    IncreaseBacteriumEachForPool = TBacteriumIncreasedNumber(value);
}

void TEcosystem::setInitBacteriumNumber(const int &value)
{
    toPreventModifyParamtersAfterRunning();
    InitBacteriumNumber = value;
}

void TEcosystem::setInitBugNumber(const int &value)
{
    toPreventModifyParamtersAfterRunning();
    InitBugNumber = value;
}

const TEcosystem::TBugList TEcosystem::getBugList() const
{
    return BugList;
}
