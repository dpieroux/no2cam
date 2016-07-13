#ifndef SWEEPWIDGET_H
#define SWEEPWIDGET_H

#include "AbstractMainPane.h"

class QLineEdit;

class SweepingPane : public AbstractMainPane
{
    Q_OBJECT
public:
    explicit SweepingPane(QWidget *parent = 0);

signals:

public slots:

private:
    QLineEdit *wl1;
    QLineEdit *wl2;
    QLineEdit *wlDelta;
    QLineEdit *eet;
    QLineEdit *cooldown;
    QLineEdit *session;
};

#endif // SWEEPWIDGET_H
