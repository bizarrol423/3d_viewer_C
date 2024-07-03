#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#define GL_SILENCE_DEPRECATION
#include <QColor>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QSettings>
#include <iostream>

#include "mainwindow.h"

typedef struct colorStruct {
  QColor colorVertex;
  QColor colorLine;
  QColor colorBack;

  double colorVertexRed;
  double colorVertexGreen;
  double colorVertexBlue;
  double colorVertexAlpha = 255;

  double colorLineRed;
  double colorLineGreen;
  double colorLineBlue;
  double colorLineAlpha = 255;

  double colorBackRed;
  double colorBackGreen;
  double colorBackBlue;
  double colorBackAlpha = 255;
} colorData;

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
 public:
  MyOpenGLWidget(QWidget *parent = nullptr);
  ~MyOpenGLWidget();

  colorData colorElement;

  QString file_name_Q;
  model s;

  int error;
  int created;

  // размеры окна
  int sizeMyWidgetW;
  int sizeMyWidgetH;

  // Атрибуты линий и вершин
  int sizeLine;
  int typeLine;
  int sizeVertex;
  int typeVertex;

  // перемещение и вращение
  double mov_x;
  double mov_y;
  double mov_z;

  double rot_x;
  double rot_y;
  double rot_z;

  // масштаб
  double scaleModel;

  // проекция
  int modelProjection;

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

 private:
  void drawCube();
  void model_centering();
  void affin_trnsf(double *arr_copy);
  void Check_Projection(double max_lngth);
  void config_params_save();
  void config_params_load();

  float xRot, yRot, zRot;
  QPoint mPos;
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;

 public slots:
  void input_name();

 signals:
  void setSettingsOnForm();
};

#endif  // MYOPENGLWIDGET_H
