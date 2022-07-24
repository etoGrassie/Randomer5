//
// Created by Grassie on 2022/7/21.
//

#ifndef RD5_RD5DIALOG_H
#define RD5_RD5DIALOG_H

#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QListWidget>
#include <QTextBrowser>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

namespace RD5Dlg {
    class dlgRange : public QDialog {

    Q_OBJECT

    public:
        dlgRange();

    public:
        QSpinBox *spBoxMin;
        QSpinBox *spBoxMax;
    private: // Private pointers
        QVBoxLayout *vlCentral;
        QLabel *lbLabel;
        QHBoxLayout *hlMin;
        QLabel *lbMin;
        QHBoxLayout *hlMax;
        QLabel *lbMax;
        QDialogButtonBox *btnBox;

    private: // Private functions
        void setupUi();

        void setupEvent();
    };

    class dlgTemps : public QDialog {

    Q_OBJECT

    public:
        dlgTemps();

    public:
        int currentSelection;

    public:
        QVBoxLayout *vlCentral;
        QHBoxLayout *hlTempsMenu;
        QVBoxLayout *vlMenu;
        QLabel *lbMenu;
        QListWidget *lstMenu;
        QLabel *lbLabel;
        QDialogButtonBox *btnBox;
        QLabel *lbDesc;

    private:
        void setupUi();

        void setupEvent();

    private slots:

        void detectItemSelection();

    };

    class dlgRandomResult : public QDialog {

    Q_OBJECT

    public:
        dlgRandomResult(bool protected_);

    public:
        QTextBrowser *txtBrowResult;

    private:
        QVBoxLayout *vlCentral;
        QLabel *lbLabel;
        QDialogButtonBox *btnBox;

    private:
        void setupUi();

        void setupEvent();

    private slots:

        void saveResult();

    private:
        bool protected_;
    };
}

#endif //RD5_RD5DIALOG_H
