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

namespace RD5Dlg {
    class dlgRange : public QDialog {
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
}

#endif //RD5_RD5DIALOG_H
