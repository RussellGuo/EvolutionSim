#include "bug.h"
#include <stdlib.h>

#include "Random.h"
#include "pool.h"
#include "bacterium.h"

quint32 TBug::SequeueOfBugID = 0;
TBug::TBug(TPool *pool):
    Pool(pool),
    ParentID(0),
    Generation(1),
    DNA(),
    DNA_CDF(DNA),
    Energy(ENERGY_1ST_GENERATION_BUG),
    Direction(Random::Random() % DNA_NUM),
    x(Random::Random() % Pool->getWidth()),
    y(Random::Random() % Pool->getHeight())

{
}

TBug::TBug(const TBug *_parent, TMutantType MutantType):
    Pool(_parent->Pool),
    ParentID(_parent->ID),
    Generation(_parent->Generation + 1),
    DNA(&(_parent->DNA), MutantType),
    // bug's every ancestry's DNA will stored in AncestralDNA if uncomment next statement. see it in the IDE while debugging.
    // AncestralDNA(_parent->AncestralDNA + QVector<TDNA>({_parent->DNA})),
    DNA_CDF(DNA),
    Energy(_parent->Energy/2),
    Direction(Random::Random() % DNA_NUM),
    x(_parent->x),
    y(_parent->y)
{

}

quint32 TBug::GetGeneration() const
{
    return Generation;
}

void TBug::tick()
{
    if (State != LIVING || Energy <= 0) {
        qFatal("found a bug who should not exist");
        return;
    }
    Energy--;
    if (Energy <= 0) {
        State = DEAD;
        return;
    }
    Age++;
    move();
    eat();
    if (Energy >= ENERGY_READY_TO_REPRODUCE && Age >= REPRODUCTION_AGE) {
        State = READY_TO_REPRODUCE;
    }
}

void TBug::eat()
{
    for (qint32 dx = -1; dx <= 1; dx++) {
        for (qint32 dy = -1; dy <= 1; dy ++) {
            bool ateBacterium = Pool->cleanBacteriumAt(x + dx, y + dy);
            if (ateBacterium) {
                Energy += ENERGY_BACTERIUM;
            }
        }
    }
    if (Energy > ENERGY_MAX) {
        Energy = ENERGY_MAX;
    }
}

void TBug::move()
{
    Direction += DNA_CDF.NextTurn();
    Direction %= DNA_NUM;
    if (Direction < 0) {
        Direction += DNA_NUM;
    }
    static const struct {
        qint32 dx, dy;
    } moveTab[DNA_NUM] = { {0, 2}, {2, 1}, {2, -1}, { 0, -2}, {-2, 1}, { -2, -1} };
    x += moveTab[Direction].dx;
    y += moveTab[Direction].dy;
    Pool->modWidth(x);
    Pool->modHeight(y);
}

qint32 TBug::getY() const
{
    return y;
}

qint32 TBug::getX() const
{
    return x;
}

quint32 TBug::getID() const
{
    return ID;
}

qint32 TBug::getEnergy() const
{
    return Energy;
}

TBug::TState TBug::getState() const
{
    return State;
}

TBug::~TBug(){}

TBug::TDNA::TDNA(const TDNA *parentDNA, TMutantType MutantType)
{
    if (parentDNA == 0) {
        // 1st generation bug, it has random gene.
        for (quint32 i = 0; i < DNA_NUM; i++) {
            DNA[i] = Random::Random() % 10;
        }
    } else {
        memcpy(DNA, parentDNA, sizeof DNA);
        quint32 mutatedPos =  Random::Random() % DNA_NUM;
        switch(MutantType) {
        case INCREASE:
            DNA[mutatedPos]++;
            break;
        case DECREASE:
            DNA[mutatedPos]--;
            break;
        }

    }

    // 1: normalize DNA
    qint32 tmpDNA[DNA_NUM];
    memcpy(tmpDNA, DNA, sizeof DNA);

    // DNA cannot large than 28, to avoid overflow
    qint32 maxDNA = tmpDNA[0];
    for(qint32 i = 1; i < DNA_NUM; i++) {
        if (tmpDNA[i] > maxDNA) {
            maxDNA = tmpDNA[i];
        }
    }

    for(qint32 i = 0; i < DNA_NUM; i++) {
        tmpDNA[i] += (28 -maxDNA);
        if (tmpDNA[i] < 0) {
            tmpDNA[i] = 0;
        }
    }

    // let minDNA be 0, easy to understand.
    qint32 minDNA = tmpDNA[0];
    for(qint32 i = 1; i < DNA_NUM; i++) {
        if (tmpDNA[i] < minDNA) {
            minDNA = tmpDNA[i];
        }
    }
    for(qint32 i = 0; i < DNA_NUM; i++) {
        tmpDNA[i] -= minDNA;
        DNA[i] = tmpDNA[i];
    }

    // DNA normalized

}

//  Choose index at random from distribution dna_cdf
qint32 TBug::TDNA_CDF::NextTurn() const
{
    qint32 index = 0;
    qint32 Rand = Random::Random() % DNA_CDF[DNA_NUM - 1];
    for (index = 0; index < DNA_NUM; index++) {
        if (Rand < DNA_CDF[index]) {
            return index;
        }
    }
    return DNA_NUM - 1;
}


TBug::TDNA_CDF::TDNA_CDF(const TBug::TDNA &DNA)
{
    qint32 sum = 0;
    for(qint32 i = 0; i < DNA_NUM; i++) {
        sum += (1 << DNA.DNA[i]);
        DNA_CDF[i] = sum;
    }
}
