includePath#ifndef __INTELLISENSE__ // code that generates an error squiggle 
#include "ui_myform.h"
#include <QSurfaceFormat>

class MyForm : public QWidget
{
  	Q_OBJECT

  	public:
    	MyForm (QWidget* parent=0);
  
	private:
		Ui::myform ui;
};
#endif