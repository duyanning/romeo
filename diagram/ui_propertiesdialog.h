/********************************************************************************
** Form generated from reading UI file 'propertiesdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTIESDIALOG_H
#define UI_PROPERTIESDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PropertiesDialog
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *groupBox;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QSpinBox *xSpinBox;
    QSpacerItem *spacerItem;
    QLabel *label_2;
    QSpinBox *ySpinBox;
    QSpacerItem *spacerItem1;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLineEdit *textLineEdit;
    QLabel *label_4;
    QLabel *label_9;
    QLabel *textColorLabel;
    QPushButton *textColorButton;
    QLabel *label_5;
    QLabel *outlineColorLabel;
    QPushButton *outlineColorButton;
    QPushButton *backgroundColorButton;
    QLabel *backgroundColorLabel;
    QLabel *label_7;
    QSpacerItem *spacerItem2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PropertiesDialog)
    {
        if (PropertiesDialog->objectName().isEmpty())
            PropertiesDialog->setObjectName(QString::fromUtf8("PropertiesDialog"));
        PropertiesDialog->resize(322, 350);
        vboxLayout = new QVBoxLayout(PropertiesDialog);
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(9, 9, 9, 9);
        groupBox = new QGroupBox(PropertiesDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        hboxLayout = new QHBoxLayout(groupBox);
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(9, 9, 9, 9);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        hboxLayout->addWidget(label);

        xSpinBox = new QSpinBox(groupBox);
        xSpinBox->setObjectName(QString::fromUtf8("xSpinBox"));
        xSpinBox->setAlignment(Qt::AlignRight);
        xSpinBox->setMinimum(-1000);
        xSpinBox->setMaximum(1000);

        hboxLayout->addWidget(xSpinBox);

        spacerItem = new QSpacerItem(31, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        hboxLayout->addWidget(label_2);

        ySpinBox = new QSpinBox(groupBox);
        ySpinBox->setObjectName(QString::fromUtf8("ySpinBox"));
        ySpinBox->setAlignment(Qt::AlignRight);
        ySpinBox->setMinimum(-1000);
        ySpinBox->setMaximum(1000);

        hboxLayout->addWidget(ySpinBox);

        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem1);


        vboxLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(PropertiesDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(6);
        gridLayout->setVerticalSpacing(6);
        gridLayout->setContentsMargins(9, 9, 9, 9);
        textLineEdit = new QLineEdit(groupBox_2);
        textLineEdit->setObjectName(QString::fromUtf8("textLineEdit"));

        gridLayout->addWidget(textLineEdit, 0, 1, 1, 2);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 1, 0, 1, 1);

        textColorLabel = new QLabel(groupBox_2);
        textColorLabel->setObjectName(QString::fromUtf8("textColorLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textColorLabel->sizePolicy().hasHeightForWidth());
        textColorLabel->setSizePolicy(sizePolicy);
        textColorLabel->setFrameShape(QFrame::StyledPanel);
        textColorLabel->setFrameShadow(QFrame::Raised);
        textColorLabel->setScaledContents(true);

        gridLayout->addWidget(textColorLabel, 1, 1, 1, 1);

        textColorButton = new QPushButton(groupBox_2);
        textColorButton->setObjectName(QString::fromUtf8("textColorButton"));

        gridLayout->addWidget(textColorButton, 1, 2, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        outlineColorLabel = new QLabel(groupBox_2);
        outlineColorLabel->setObjectName(QString::fromUtf8("outlineColorLabel"));
        sizePolicy.setHeightForWidth(outlineColorLabel->sizePolicy().hasHeightForWidth());
        outlineColorLabel->setSizePolicy(sizePolicy);
        outlineColorLabel->setFrameShape(QFrame::StyledPanel);
        outlineColorLabel->setFrameShadow(QFrame::Raised);
        outlineColorLabel->setScaledContents(true);

        gridLayout->addWidget(outlineColorLabel, 2, 1, 1, 1);

        outlineColorButton = new QPushButton(groupBox_2);
        outlineColorButton->setObjectName(QString::fromUtf8("outlineColorButton"));

        gridLayout->addWidget(outlineColorButton, 2, 2, 1, 1);

        backgroundColorButton = new QPushButton(groupBox_2);
        backgroundColorButton->setObjectName(QString::fromUtf8("backgroundColorButton"));

        gridLayout->addWidget(backgroundColorButton, 3, 2, 1, 1);

        backgroundColorLabel = new QLabel(groupBox_2);
        backgroundColorLabel->setObjectName(QString::fromUtf8("backgroundColorLabel"));
        sizePolicy.setHeightForWidth(backgroundColorLabel->sizePolicy().hasHeightForWidth());
        backgroundColorLabel->setSizePolicy(sizePolicy);
        backgroundColorLabel->setFrameShape(QFrame::StyledPanel);
        backgroundColorLabel->setFrameShadow(QFrame::Raised);
        backgroundColorLabel->setScaledContents(true);

        gridLayout->addWidget(backgroundColorLabel, 3, 1, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 3, 0, 1, 1);


        vboxLayout->addWidget(groupBox_2);

        spacerItem2 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem2);

        buttonBox = new QDialogButtonBox(PropertiesDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

        vboxLayout->addWidget(buttonBox);

#if QT_CONFIG(shortcut)
        label->setBuddy(xSpinBox);
        label_2->setBuddy(ySpinBox);
        label_4->setBuddy(textLineEdit);
#endif // QT_CONFIG(shortcut)

        retranslateUi(PropertiesDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), PropertiesDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PropertiesDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(PropertiesDialog);
    } // setupUi

    void retranslateUi(QDialog *PropertiesDialog)
    {
        PropertiesDialog->setWindowTitle(QCoreApplication::translate("PropertiesDialog", "Edit Properties", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PropertiesDialog", "Position", nullptr));
        label->setText(QCoreApplication::translate("PropertiesDialog", "&X:", nullptr));
        label_2->setText(QCoreApplication::translate("PropertiesDialog", "&Y:", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("PropertiesDialog", "Attributes", nullptr));
        label_4->setText(QCoreApplication::translate("PropertiesDialog", "&Text:", nullptr));
        label_9->setText(QCoreApplication::translate("PropertiesDialog", "Text Color:", nullptr));
        textColorButton->setText(QCoreApplication::translate("PropertiesDialog", "Choose...", nullptr));
        label_5->setText(QCoreApplication::translate("PropertiesDialog", "Outline Color:", nullptr));
        outlineColorButton->setText(QCoreApplication::translate("PropertiesDialog", "Choose...", nullptr));
        backgroundColorButton->setText(QCoreApplication::translate("PropertiesDialog", "Choose...", nullptr));
        label_7->setText(QCoreApplication::translate("PropertiesDialog", "Background Color:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertiesDialog: public Ui_PropertiesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTIESDIALOG_H
