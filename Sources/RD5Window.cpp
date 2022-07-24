//
// Created by Grassie on 2022/7/20.
//

#include <iostream>
#include <QInputDialog>
#include <QDebug>
#include "../Headers/RD5Window.h"
#include <cstdlib>
#include <ctime>
// #include "../Headers/RD5Dialog.h"


namespace Window {
    RD5Window::RD5Window() {
        setupUi();
        setupEvents();
    }

    bool RD5Window::isIn(int number, const int *array) {
        std::cout << "the length of array is " << sizeof(array) / sizeof(int) << std::endl;
        for (int time = 0; time < sizeof(array) / sizeof(int); time++) {
            if (number == array[time]) {
                return true;
            }
        }
        return false;
    }

    void RD5Window::setupUi() {
        this->resize(600, 800);
        this->setWindowTitle("Randomer 5");

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

        lbTimes = new QLabel;
        spBoxRandomTimes = new QSpinBox;
        hlRandomTimes = new QHBoxLayout;
        hlRandomTimes->addWidget(lbTimes);
        hlRandomTimes->addWidget(spBoxRandomTimes);

        cmdBtnStart = new QCommandLinkButton;
        chkBtnProtected = new QCheckBox;
        btnDebug = new QPushButton;
        hlOptions = new QHBoxLayout;
        hlOptions->addWidget(cmdBtnStart);
        hlOptions->addLayout(hlRandomTimes);
        hlOptions->addWidget(chkBtnProtected);
        hlOptions->addWidget(btnDebug);

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

        spBoxRandomTimes->setMinimum(1);

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
        lbTimes->setText("抽取次数：");
        chkBtnProtected->setText("启用保护模式");
        btnDebug->setText("Debug");
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
        connect(btnDebug, SIGNAL(clicked(bool)), this, SLOT(funcRandom()));
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
        if (dlgRange.exec() == QDialog::Accepted) {
            for (int times = dlgRange.spBoxMin->value(); times <= dlgRange.spBoxMax->value(); times++) {
                lstNames->addItem(QString::number(times));
                Names++;
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

    void RD5Window::funcRandom() {
        if (Names < 1) {
            return;
        }
        srand(unsigned(time(nullptr)));
        int randomResult[spBoxRandomTimes->value()];
        for (int time = 0; time < spBoxRandomTimes->value(); time++) {
            int randNum = rand() % Names;
            if (isIn(randNum, randomResult)) {
                time--;
            }
            else {
                randomResult[time] = randNum;
            }
        }

        for (int time = 0; time < spBoxRandomTimes->value(); time++) {
            std::cout << randomResult[time] << std::endl;
        }
    }
}