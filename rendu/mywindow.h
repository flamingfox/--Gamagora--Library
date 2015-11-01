#ifndef MYWINDOW_H
#define MYWINDOW_H

#include "myGLWidget.h"
#include "lib/voxel.h"
#include <QImage>

class myWindow : public myGLWidget
{
    Q_OBJECT
public:
    explicit myWindow(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void keyPressEvent( QKeyEvent *keyEvent );
    void loadTexture(QString textureName);
    Voxel vox;

private:

    GLuint texture[1];
    float _fx;
    float _speed;
};

#endif // MYWINDOW_H
