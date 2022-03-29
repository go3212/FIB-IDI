#include <QApplication>
#include "MyForm.h"


int main(int argc, char** argv)
{
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QApplication qtapp(argc, argv);


    QSurfaceFormat f;
    f.setVersion(3,3);
    f.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(f);

    MyForm myform;
    myform.show();


    return qtapp.exec();
}