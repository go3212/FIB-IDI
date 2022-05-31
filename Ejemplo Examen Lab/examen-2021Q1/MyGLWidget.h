#include "ExamGLWidget.h"

class MyGLWidget:public ExamGLWidget
{
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) 
    : ExamGLWidget(parent)
    , patr_cub(1)
    , cubes_visible(true)
    , light_yellow(false)
    , cube_offset(0)
    {}
    ~MyGLWidget();

  public Q_SLOTS:
    void setCube(int cube)
    {
      makeCurrent();
      patr_cub = cube;
      update();
    }
    void setPerspectiveCamera(bool x)
    {
      makeCurrent();
      camPlanta = x;
      update();
    }

  Q_SIGNALS:
    void changedPerspectiveCamera(bool);
    void changedCube(int);

  protected:
    virtual void paintGL ();
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void modelTransformCub (float escala, float angle);
    virtual void modelTransformPatricio (int cub);
    virtual void projectTransform ();
    virtual void viewTransform ();

  private:
    int printOglError(const char file[], int line, const char func[]);
    int patr_cub;

    bool cubes_visible;
    bool light_yellow;
    int  cube_offset;
};
