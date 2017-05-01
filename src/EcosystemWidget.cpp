#include "EcosystemWidget.h"
#include "ecosystem.h"
#include <QPainter>
#include <QMouseEvent>

TEcosystemWidget::TEcosystemWidget(const TEcosystem *_ecosystem, QWidget *parent) :
    QWidget(parent),
    Ecosystem(_ecosystem),
    selectedBugID(0)
{
    QSize rect(512, 384);
    resize(rect);
    setMinimumSize(rect);
    setMaximumSize(rect);

    connect(Ecosystem, SIGNAL(updated()), this, SLOT(update()));

}

void TEcosystemWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QBrush BrushPool(QColor(0x7F, 0x7F, 0x7F));
    painter.fillRect(0, 0, width(), height(), BrushPool);

    for (auto &bug: Ecosystem->getBugList()) {
        qint32 health = bug->getEnergy();
        qint32 color;
        // for a bug, use color to indicate that health
        if (health > 200) {
            color = 0xFF;
        } else if (health < 100){
            color = 0x7F;
        } else {
            color = 0x7F + (health - 100) * (0xFF - 0x7F) / 100;
        }

        if (bug->getID() == selectedBugID) {
            painter.fillRect(bug->getX() - 2, bug->getY() - 2, 5, 5, QColor(255, 0, 0));
        }
        painter.fillRect(bug->getX() - 1, bug->getY() - 1, 3, 3, QColor(0, color, 0));
        //painter.drawText(bug->getX() - 20, bug->getY() + 10, QString("%1").arg(bug->getID()));
    }

    QPen PenBacterium(QColor(0x00, 0x00, 0xFF));
    painter.setPen(PenBacterium);
    for (auto &bacterium: Ecosystem->getBacteria()) {
        painter.drawPoint(bacterium.x, bacterium.y);
    }
}

void TEcosystemWidget::mousePressEvent(QMouseEvent *e)
{
    selectedBugID = 0;
    quint32 closestDistSquare = (1U<<31);
    for (auto &bug: Ecosystem->getBugList()) {
        qint32 dx = e->x() - bug->getX();
        qint32 dy = e->y() - bug->getY();
        quint32 distSquare = dx*dx + dy * dy;
        if (distSquare < closestDistSquare) {
            closestDistSquare = distSquare;
            selectedBugID = bug->getID();
        }
    }
    update();
}
