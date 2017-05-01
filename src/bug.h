#ifndef BUG_H
#define BUG_H

#include <QtCore>
#include <QVector>

class TPool;

class TBug
{
public:
    static const qint32 DNA_NUM = 6;
    static const qint32 ENERGY_BACTERIUM = 40;
    static const qint32 ENERGY_1ST_GENERATION_BUG = 400;
    static const qint32 ENERGY_MAX = 1500;
    static const qint32 ENERGY_READY_TO_REPRODUCE = 1000;
    static const qint32 REPRODUCTION_AGE = 800;

    enum TState {
        LIVING,
        DEAD,
        READY_TO_REPRODUCE,
    };

    enum TMutantType {
        INCREASE,
        DECREASE,
    };

    // 1st generation bug
    TBug(TPool *pool);
    // reproduced bug
    TBug(const TBug *_parent, TMutantType MutantType);
    TBug(const TBug &) = delete;
    TBug &operator = (const TBug &) = delete;

    quint32 GetGeneration() const;
    void tick();

    virtual ~TBug();

    struct TDNA {
        TDNA(const TDNA *parentDNA = 0, TMutantType MutantType = INCREASE);
        qint32  DNA[DNA_NUM];
    };
    struct TDNA_CDF {
      TDNA_CDF(const TDNA &DNA);
      // Choose index at random from distribution dna_cdf
      qint32 NextTurn() const;

    private:

      qint32  DNA_CDF[DNA_NUM];
    };


    TState getState() const;

    qint32 getEnergy() const;

    quint32 getID() const;

    qint32 getX() const;

    qint32 getY() const;

private:
    void eat();
    void move();

    static quint32 SequeueOfBugID;
    TPool *const Pool;
    quint32 const ID = ++SequeueOfBugID;
    quint32 const ParentID;
    quint32 const Generation;
    const TDNA DNA;
    const QVector<TDNA>AncestralDNA;
    const TDNA_CDF DNA_CDF;
    quint32 Age = 0;
    qint32 Energy;
    qint32 Direction;
    qint32 x,y;
    TState State = LIVING;
};

#endif // BUG_H
