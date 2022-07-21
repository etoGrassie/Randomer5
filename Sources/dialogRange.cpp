/********************************************************************************
** Form generated from reading UI file 'dialogRange.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DIALOGRANGE_H
#define DIALOGRANGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_dlgRange
{
public:
    QVBoxLayout *vlCentral;
    QLabel *lbLabel;
    QHBoxLayout *hlMin;
    QLabel *lbMin;
    QSpinBox *spBoxMin;
    QHBoxLayout *hlMax;
    QLabel *lbMax;
    QSpinBox *spBoxMax;
    QDialogButtonBox *btnBox;

    void setupUi(QDialog *dlgRange)
    {
        if (dlgRange->objectName().isEmpty())
            dlgRange->setObjectName(QString::fromUtf8("dlgRange"));
        dlgRange->resize(357, 147);
        vlCentral = new QVBoxLayout(dlgRange);
        vlCentral->setObjectName(QString::fromUtf8("vlCentral"));
        lbLabel = new QLabel(dlgRange);
        lbLabel->setObjectName(QString::fromUtf8("lbLabel"));

        vlCentral->addWidget(lbLabel);

        hlMin = new QHBoxLayout();
        hlMin->setObjectName(QString::fromUtf8("hlMin"));
        lbMin = new QLabel(dlgRange);
        lbMin->setObjectName(QString::fromUtf8("lbMin"));

        hlMin->addWidget(lbMin);

        spBoxMin = new QSpinBox(dlgRange);
        spBoxMin->setObjectName(QString::fromUtf8("spBoxMin"));

        hlMin->addWidget(spBoxMin);


        vlCentral->addLayout(hlMin);

        hlMax = new QHBoxLayout();
        hlMax->setObjectName(QString::fromUtf8("hlMax"));
        lbMax = new QLabel(dlgRange);
        lbMax->setObjectName(QString::fromUtf8("lbMax"));

        hlMax->addWidget(lbMax);

        spBoxMax = new QSpinBox(dlgRange);
        spBoxMax->setObjectName(QString::fromUtf8("spBoxMax"));

        hlMax->addWidget(spBoxMax);


        vlCentral->addLayout(hlMax);

        btnBox = new QDialogButtonBox(dlgRange);
        btnBox->setObjectName(QString::fromUtf8("btnBox"));
        btnBox->setOrientation(Qt::Horizontal);
        btnBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        vlCentral->addWidget(btnBox);


        retranslateUi(dlgRange);
        QObject::connect(btnBox, SIGNAL(accepted()), dlgRange, SLOT(accept()));
        QObject::connect(btnBox, SIGNAL(rejected()), dlgRange, SLOT(reject()));

        QMetaObject::connectSlotsByName(dlgRange);
    } // setupUi

    void retranslateUi(QDialog *dlgRange)
    {
        dlgRange->setWindowTitle(QCoreApplication::translate("dlgRange", "Dialog", nullptr));
        lbLabel->setText(QString());
        lbMin->setText(QString());
        lbMax->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class dlgRange: public Ui_dlgRange {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DIALOGRANGE_H
