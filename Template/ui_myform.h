/********************************************************************************
** Form generated from reading UI file 'myformBFYmFf.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MYFORMBFYMFF_H
#define MYFORMBFYMFF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myform
{
public:
    QOpenGLWidget *openGLWidget;

    void setupUi(QWidget *myform)
    {
        if (myform->objectName().isEmpty())
            myform->setObjectName(QString::fromUtf8("myform"));
        myform->resize(400, 300);
        openGLWidget = new QOpenGLWidget(myform);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(0, 0, 371, 271));

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

#endif // MYFORMBFYMFF_H
