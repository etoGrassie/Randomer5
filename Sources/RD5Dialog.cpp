//
// Created by Grassie on 2022/7/21.
//

#include "../Headers/RD5Dialog.h"
#include <iostream>

namespace RD5Dlg {
    dlgRange::dlgRange() {
        setupUi();
        setupEvent();
    }

    void dlgRange::setupUi() {
        this->resize(300, 200);
        lbLabel = new QLabel;

        hlMin = new QHBoxLayout;
        lbMin = new QLabel;
        spBoxMin = new QSpinBox;
        hlMin->addWidget(lbMin);
        hlMin->addWidget(spBoxMin);

        hlMax = new QHBoxLayout;
        lbMax = new QLabel;
        spBoxMax = new QSpinBox;
        hlMax->addWidget(lbMax);
        hlMax->addWidget(spBoxMax);

        btnBox = new QDialogButtonBox;
        btnBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        vlCentral = new QVBoxLayout;
        vlCentral->addWidget(lbLabel);
        vlCentral->addLayout(hlMin);
        vlCentral->addLayout(hlMax);
        vlCentral->addWidget(btnBox);
        this->setLayout(vlCentral);

        // Policy
        this->setWindowTitle("生成数列工具");
        this->setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);

        // Text
        lbLabel->setText("生成数列");
        lbMin->setText("最小值");
        lbMax->setText("最大值");

    }

    void dlgRange::setupEvent() {
        connect(btnBox, SIGNAL(accepted()), this, SLOT(accept()));
        connect(btnBox, SIGNAL(rejected()), this, SLOT(reject()));
    }
}
