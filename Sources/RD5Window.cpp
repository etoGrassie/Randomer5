#include <QInputDialog>
#include <QDateTime>
#include <cstdlib>
#include <ctime>
#include "../Headers/RD5Window.h"

namespace Window {
    RD5Window::RD5Window() {
        setupUi();
        setupEvents();
    }

    bool RD5Window::isIn(int number, const int *array, int size) {
        for (int time = 0; time < size; time++) {
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
                    Subjects += 7;
                    break;
                case 1:
                    subjects << "语文" << "数学" << "英语" << "历史" << "生物" << "物理" << "地理" << "政治";
                    Subjects += 8;
                    break;
                case 2:
                    subjects << "语文" << "数学" << "英语" << "历史" << "化学" << "物理" << "政治";
                    Subjects += 7;
                    break;
            }
            lstSubs->addItems(subjects);
        }
    }

    void RD5Window::itemDoubleClicked(QListWidgetItem *item) {
        item->setFlags(item->flags() | Qt::ItemIsEnabled | Qt::ItemIsEditable);
    }

    void RD5Window::funcRandom() {
        int randomTimes = spBoxRandomTimes->value();
        // 检测抽取基本条件，如果满足下列条件之一，则无法抽取
        // 1) 号数为0（没有结果）
        // 2) 号数小于抽取次数（必定会有重复）
        if (Names < 1) {
            QMessageBox::critical(this, "无法抽取", "没有号数可以抽取！",
                                  QMessageBox::Cancel);
            return;
        } else if (Names < randomTimes) {
            QMessageBox::critical(this, "无法抽取", "号数少于抽取次数！（必定会重复）",
                                  QMessageBox::Cancel);
            return;
        }

        srand(unsigned(time(nullptr)));
        // 随机座号，不重复
        // 即 每次抽取都检测是否有抽过的（是否在已抽数字列表中，isIn(int num, int *array, int size)）
        // 是则重抽，否则添加到已抽数字列表
        int randomNames[randomTimes];
        for (int times = 0; times < randomTimes; times++) {
            int randNum = rand() % Names;
            if (isIn(randNum, randomNames, randomTimes)) {
                times--;
                continue;
            }
            randomNames[times] = randNum;
        }

        // 抽取科目，可能重复
        // 科目可以为空，为空则不抽取科目
        int randomSubs[randomTimes];
        if (Subjects > 0) {
            for (int times = 0; times < randomTimes; times++) {
                int randSub = rand() % Subjects;
                randomSubs[times] = randSub;
            }
        } else {
            for (int times = 0; times < randomTimes; times++) {
                randomSubs[times] = 0;
            }
        }
        // 获取当前时间和日期并保存到QString当中
        QString currenTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        RD5Dlg::dlgRandomResult dlgResult(protected_);

        /* 输出格式为Markdown
         * 首行是 "{randomTimes}/{Names} 抽取结果"
         * 第二行是 "时间: {currentTime}"
         * 接下来是抽取结果，格式为 "{列表项目文字} --> {科目}"
         */

        dlgResult.txtBrowResult->setMarkdown(
                QString("# %1/%2 抽取结果\n").arg(randomTimes).arg(Names) +
                QString("#### 时间: %1\n").arg(currenTime)
        );
        for (int times = 0; times < randomTimes; times++) {
            dlgResult.txtBrowResult->setMarkdown(
                    dlgResult.txtBrowResult->toMarkdown() +
                    QString("### %1 %2\n\n").arg(lstNames->item(randomNames[times])->text()).arg(
                            Subjects > 1 ? "--> " + lstSubs->item(randomSubs[times])->text() : "")
            );
        }
    }
}