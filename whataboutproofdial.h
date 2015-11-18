#ifndef WHATABOUTPROOFDIAL_H
#define WHATABOUTPROOFDIAL_H

#include <QDialog>

namespace Ui {
class WhatAboutProofDial;
}

class WhatAboutProofDial : public QDialog
{
    Q_OBJECT

public:
    explicit WhatAboutProofDial(QWidget *parent = 0);
    ~WhatAboutProofDial();

private:
    Ui::WhatAboutProofDial *ui;
};

#endif // WHATABOUTPROOFDIAL_H
