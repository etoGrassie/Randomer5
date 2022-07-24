//
// Created by Grassie on 2022/7/20.
//

#ifndef RD5_RD5WINDOW_H
#define RD5_RD5WINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QCheckBox>
#include <QCommandLinkButton>
#include <QLabel>
#include <QMessageBox>
#include <QCloseEvent>
#include <QSpinBox>
#include "RD5Dialog.h"

namespace Window {
    class RD5Window : public QMainWindow {

    Q_OBJECT

    public: // Public Functions
        RD5Window();

    static bool isIn(int number, const int *array, int size);

    private: // Private Pointers

        QWidget *widCentral;
        QVBoxLayout *vlCentral;
        QHBoxLayout *hlLists;
        QHBoxLayout *hlOptions;
        QHBoxLayout *hlRandomTimes;
        QGridLayout *glNames;
        QGridLayout *glSubs;
        QVBoxLayout *vlNames;
        QVBoxLayout *vlSubs;
        QPushButton *btnNamesAdd;
        QPushButton *btnNamesDel;
        QPushButton *btnNamesRange;
        QPushButton *btnNamesClear;
        QPushButton *btnSubsAdd;
        QPushButton *btnSubsDel;
        QPushButton *btnSubsTemps;
        QPushButton *btnSubsClear;
        QPushButton *btnDebug;
        QListWidget *lstNames;
        QListWidget *lstSubs;
        QCommandLinkButton *cmdBtnStart;
        QCheckBox *chkBtnProtected;
        QLabel *lbNames;
        QLabel *lbSubs;
        QLabel *lbTimes;
        QSpinBox *spBoxRandomTimes;

    private: // Private Functions

        void setupUi();

        void setupEvents();

        void closeEvent(QCloseEvent *event);

    private: // Private Variables

        int closeButtonClicked = 0;

        bool protected_ = false;

        int Names = 0;

        int Subjects = 0;

        RD5Dlg::dlgRange dlgRange;

    private slots:

        void protectModeEvent();

        void funcAdd();

        void funcDel();

        void funcClear();

        void funcNamesRange();

        void funcSubsTemps();

        void funcRandom();

        void itemDoubleClicked(QListWidgetItem *item);

    };
}

#endif //RD5_RD5WINDOW_H
