/********************************************************************************
** Form generated from reading UI file 'myform.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYFORM_H
#define UI_MYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include "MyGLWidget.h"

QT_BEGIN_NAMESPACE

class Ui_myform
{
public:
    MyGLWidget *openGLWidget;

    void setupUi(QWidget *myform)
    {
        if (myform->objectName().isEmpty())
            myform->setObjectName(QString::fromUtf8("myform"));
        myform->setWindowModality(Qt::ApplicationModal);
        myform->resize(500, 500);
        openGLWidget = new MyGLWidget(myform);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(0, 0, 500, 500));

        retranslateUi(myform);

        QMetaObject::connectSlotsByName(myform);
    } // setupUi

    void retranslateUi(QWidget *myform)
    {
        myform->setWindowTitle(QCoreApplication::translate("myform", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class myform: public Ui_myform {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFORM_H
