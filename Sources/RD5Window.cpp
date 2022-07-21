//
// Created by Grassie on 2022/7/20.
//

#include <iostream>
#include <QInputDialog>
#include <QDebug>
#include "../Headers/RD5Window.h"
#include "../Headers/RD5Dialog.h"


namespace Window {
    RD5Window::RD5Window() {
        setupUi();
        setupEvents();
    }

    void RD5Window::setupUi() {
        this->resize(600, 800);
        this->setWindowTitle("Randomer 4");

        vlNames = new QVBoxLayout;
        lbNames = new QLabel();
        lstNames = new QListWidget;
        glNames = new QGridLayout;
        btnNamesAdd = new QPushButton;
        btnNamesClear = new QPushButton;
        btnNamesDel = new QPushButton;
        btnNamesRange = new QPushButton;

        glNames->addWidget(btnNamesAdd, 0, 0);
        glNames->addWidget(btnNamesDel, 0, 1);
        glNames->addWidget(btnNamesRange, 1, 0);
        glNames->addWidget(btnNamesClear, 1, 1);
        vlNames->addWidget(lbNames);
        vlNames->addWidget(lstNames);
        vlNames->addLayout(glNames);

        vlSubs = new QVBoxLayout;
        lbSubs = new QLabel();
        lstSubs = new QListWidget;
        glSubs = new QGridLayout;
        btnSubsAdd = new QPushButton;
        btnSubsDel = new QPushButton;
        btnSubsTemps = new QPushButton;
        btnSubsClear = new QPushButton;

        glSubs->addWidget(btnSubsAdd, 0, 0);
        glSubs->addWidget(btnSubsDel, 0, 1);
        glSubs->addWidget(btnSubsTemps, 1, 0);
        glSubs->addWidget(btnSubsClear, 1, 1);
        vlSubs->addWidget(lbSubs);
        vlSubs->addWidget(lstSubs);
        vlSubs->addLayout(glSubs);

        hlLists = new QHBoxLayout;
        hlLists->addLayout(vlNames);
        hlLists->addLayout(vlSubs);

        cmdBtnStart = new QCommandLinkButton;
        chkBtnProtected = new QCheckBox;
        hlOptions = new QHBoxLayout;
        hlOptions->addWidget(cmdBtnStart);
        hlOptions->addWidget(chkBtnProtected);

        widCentral = new QWidget;
        vlCentral = new QVBoxLayout;
        vlCentral->addLayout(hlLists);
        vlCentral->addLayout(hlOptions);
        widCentral->setLayout(vlCentral);
        this->setCentralWidget(widCentral);

        // Policy
        lstNames->setSelectionMode(QAbstractItemView::ExtendedSelection);
        lstSubs->setSelectionMode(QAbstractItemView::ExtendedSelection);
        lstNames->setEditTriggers(QListWidget::DoubleClicked);
        lstSubs->setEditTriggers(QListWidget::DoubleClicked);

        // Text
        lbNames->setText("号数列表");
        lbSubs->setText("科目列表");

        btnNamesAdd->setText("增加");
        btnNamesDel->setText("删除");
        btnNamesRange->setText("数列");
        btnNamesClear->setText("清空");

        btnSubsAdd->setText("增加");
        btnSubsDel->setText("删除");
        btnSubsTemps->setText("模板");
        btnSubsClear->setText("清空");

        cmdBtnStart->setText("开始抽取");
        chkBtnProtected->setText("启用保护模式");
    }

    void RD5Window::closeEvent(QCloseEvent *event) {
        if (protected_) {
            closeButtonClicked++;
            if (closeButtonClicked < 2) {
                event->ignore();
                return;
            } else {
                closeButtonClicked = 0;
                event->accept();
                return;
            }
        }

        QMessageBox::StandardButton result = QMessageBox::question(this, "Randomer 5",
                                                                   "确认要退出吗？",
                                                                   QMessageBox::Yes | QMessageBox::No,
                                                                   QMessageBox::No);

        if (result == QMessageBox::Yes) {
            event->accept();
        } else {
            event->ignore();
        }
    }

    void RD5Window::setupEvents() {
        // Check Boxes Event
        connect(chkBtnProtected, SIGNAL(stateChanged(int)), this, SLOT(protectModeEvent()));
        // Buttons Event
        connect(btnNamesAdd, SIGNAL(clicked(bool)), this, SLOT(funcAdd()));
        connect(btnSubsAdd, SIGNAL(clicked(bool)), this, SLOT(funcAdd()));
        connect(btnNamesDel, SIGNAL(clicked(bool)), this, SLOT(funcDel()));
        connect(btnSubsDel, SIGNAL(clicked(bool)), this, SLOT(funcDel()));
        connect(btnNamesRange, SIGNAL(clicked(bool)), this, SLOT(funcNamesRange()));
        connect(btnSubsTemps, SIGNAL(clicked(bool)), this, SLOT(funcSubsTemps()));
        connect(btnNamesClear, SIGNAL(clicked(bool)), this, SLOT(funcClear()));
        connect(btnSubsClear, SIGNAL(clicked(bool)), this, SLOT(funcClear()));
        // List Item Event
        connect(lstNames, SIGNAL(itemDoubleClicked(QListWidgetItem * )), this,
                SLOT(itemDoubleClicked(QListWidgetItem * )));
        connect(lstSubs, SIGNAL(itemDoubleClicked(QListWidgetItem * )), this,
                SLOT(itemDoubleClicked(QListWidgetItem * )));
    }

    void RD5Window::protectModeEvent() {
        closeButtonClicked = 0;
        if (chkBtnProtected->isChecked()) {
            protected_ = true;
        } else if (!chkBtnProtected->isChecked()) {
            protected_ = false;
        }
    }

    void RD5Window::funcAdd() {
        if (this->sender() == btnNamesAdd) {
            lstNames->addItem("新项");
            Names++;
        } else if (this->sender() == btnSubsAdd) {
            lstSubs->addItem("新项");
            Subjects++;
        }
    }

    void RD5Window::funcDel() {
        if (this->sender() == btnNamesDel) {
                    foreach (auto *item, lstNames->selectedItems()) {
                    lstNames->takeItem(lstNames->row(item));
                    Names--;
                }
        } else if (this->sender() == btnSubsDel) {
                    foreach (auto *item, lstSubs->selectedItems()) {
                    lstSubs->takeItem(lstSubs->row(item));
                    Subjects--;
                }
        }
    }

    void RD5Window::funcClear() {
        if (this->sender() == btnNamesClear) {
            lstNames->clear();
            Names = 0;
        } else if (this->sender() == btnSubsClear) {
            lstSubs->clear();
            Subjects = 0;
        }
    }

    void RD5Window::funcNamesRange() {
        auto *dialog = new RD5Dlg::dlgRange;
        dialog->setAttribute(Qt::WA_DeleteOnClose, true);
        if (dialog->exec() == 1) {
            int rangeMin = dialog->spBoxMin->value();
            int rangeMax = dialog->spBoxMax->value();
            for (int num = rangeMin; num <= rangeMax; num++) {
                lstNames->addItem(QString::number(num));
            }
        }
    }

    void RD5Window::funcSubsTemps() {
        auto *dialog = new RD5Dlg::dlgTemps;
        dialog->setAttribute(Qt::WA_DeleteOnClose, true);
        if (dialog->exec() == 1) {
            int selection = dialog->currentSelection;
            QStringList subjects;
            switch (selection) {
                case 0:
                    subjects << "语文" << "数学" << "英语" << "历史" << "生物" << "地理" << "政治";
                    break;
                case 1:
                    subjects << "语文" << "数学" << "英语" << "历史" << "生物" << "物理" << "地理" << "政治";
                    break;
                case 2:
                    subjects << "语文" << "数学" << "英语" << "历史" << "化学" << "物理" << "政治";
                    break;
            }
            lstSubs->addItems(subjects);
        }
    }

    void RD5Window::itemDoubleClicked(QListWidgetItem *item) {
        item->setFlags(item->flags() | Qt::ItemIsEnabled | Qt::ItemIsEditable);
    }
}