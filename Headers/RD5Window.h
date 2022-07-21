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

namespace Window {
    class RD5Window : public QMainWindow {

    Q_OBJECT

    public: // Public Functions
        RD5Window();

    private: // Private Pointers

        QWidget *widCentral;
        QVBoxLayout *vlCentral;
        QHBoxLayout *hlLists;
        QHBoxLayout *hlOptions;
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
        QListWidget *lstNames;
        QListWidget *lstSubs;
        QCommandLinkButton *cmdBtnStart;
        QCheckBox *chkBtnProtected;
        QLabel *lbNames;
        QLabel *lbSubs;

    private: // Private Functions

        void setupUi();

        void setupEvents();

        void closeEvent(QCloseEvent *event);

    private: // Private Variables

        int closeButtonClicked = 0;

        bool protected_ = false;

        int Names = 0;

        int Subjects = 0;

    private slots:

        void protectModeEvent();

        void funcAdd();

        void funcDel();

        void funcClear();

        void funcNamesRange();

        void funcSubsTemps();

        void itemDoubleClicked(QListWidgetItem *item);

    };
}

#endif //RD5_RD5WINDOW_H
