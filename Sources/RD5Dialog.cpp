//
// Created by Grassie on 2022/7/21.
//

#include "../Headers/RD5Dialog.h"
#include <iostream>

namespace RD5Dlg {
    // Dialog Range
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


    // Dialog Temps
    dlgTemps::dlgTemps() {
        setupUi();
        setupEvent();
        detectItemSelection();
    }

    void dlgTemps::setupUi() {
        lbLabel = new QLabel;
        lbMenu = new QLabel;
        lstMenu = new QListWidget;
        vlMenu = new QVBoxLayout;
        vlMenu->addWidget(lbLabel);
        vlMenu->addWidget(lstMenu);

        lbDesc = new QLabel;
        lbDesc->setTextFormat(Qt::MarkdownText);
        hlTempsMenu = new QHBoxLayout;
        hlTempsMenu->addLayout(vlMenu);
        hlTempsMenu->addWidget(lbDesc);
        hlTempsMenu->setStretch(0, 3);
        hlTempsMenu->setStretch(1, 4);

        btnBox = new QDialogButtonBox;
        btnBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        vlCentral = new QVBoxLayout;
        vlCentral->addLayout(hlTempsMenu);
        vlCentral->addWidget(btnBox);

        this->setLayout(vlCentral);

        // List
        QStringList items;
        items << "[福建]七年级" << "[福建]八年级" << "[福建]九年级";
        lstMenu->addItems(items);
        lstMenu->setCurrentRow(0);

        // Policy
        this->setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);

        // Text
        this->setWindowTitle("学科模板");
        lbMenu->setText("年级");
        lbLabel->setText("学科模板");
    }

    void dlgTemps::setupEvent() {
        connect(lstMenu, SIGNAL(itemSelectionChanged()), this, SLOT(detectItemSelection()));

        connect(btnBox, SIGNAL(accepted()), this, SLOT(accept()));
        connect(btnBox, SIGNAL(rejected()), this, SLOT(reject()));
    }

    void dlgTemps::detectItemSelection() {
        int selection = this->lstMenu->currentRow();
        switch (selection) {
            case 0:
                this->lbDesc->setText("### [福建]七年级 学科模板\n"
                                      "#### 共包含7个科目\n"
                                      "* 语文\n"
                                      "* 数学\n"
                                      "* 英语\n"
                                      "* 历史\n"
                                      "* 生物\n"
                                      "* 地理\n"
                                      "* 政治");
                break;
            case 1:
                this->lbDesc->setText("### [福建]八年级 学科模板\n"
                                      "#### 共包含8个科目\n"
                                      "* 语文\n"
                                      "* 数学\n"
                                      "* 英语\n"
                                      "* 历史\n"
                                      "* 生物\n"
                                      "* 物理\n"
                                      "* 地理\n"
                                      "* 政治");
                break;
            case 2:
                this->lbDesc->setText("### [福建]八年级 学科模板\n"
                                      "#### 共包含7个科目\n"
                                      "* 语文\n"
                                      "* 数学\n"
                                      "* 英语\n"
                                      "* 历史\n"
                                      "* 化学\n"
                                      "* 物理\n"
                                      "* 政治");
                break;
        }
        currentSelection = selection;
    }
}
