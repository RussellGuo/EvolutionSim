#ifndef __ECOSYSTEM_WIDGHT_H_
#define __ECOSYSTEM_WIDGHT_H_

#include <QWidget>

class TEcosystem;
class TEcosystemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TEcosystemWidget(const TEcosystem *_ecosystem,  QWidget *parent = 0);

signals:

public slots:
private:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    const TEcosystem *const Ecosystem;

    quint32 selectedBugID;
};

#endif // __ECOSYSTEM_WIDGHT_H_
