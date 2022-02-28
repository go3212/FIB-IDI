#include <QApplication>
#include "MyForm.h"

int main(int argc, char** argv)
{
    QApplication qtapp(argc, argv);

    QSurfaceFormat f;
    f.setVersion(3,3);
    f.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(f);

    MyForm myform;
    myform.show();


    return qtapp.exec();
}