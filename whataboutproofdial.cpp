#include "whataboutproofdial.h"
#include "ui_whataboutproofdial.h"

WhatAboutProofDial::WhatAboutProofDial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WhatAboutProofDial)
{
    ui->setupUi(this);
}

WhatAboutProofDial::~WhatAboutProofDial()
{
    delete ui;
}
