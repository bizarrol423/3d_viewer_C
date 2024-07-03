#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
  sizeMyWidgetW = 0;
  sizeMyWidgetH = 0;
  file_name_Q = "";
  error = 0;
  created = 0;

  mov_x = 0.0;
  mov_y = 0.0;
  mov_z = 0.0;

  scaleModel = 1;
}

MyOpenGLWidget::~MyOpenGLWidget() { remove_model(&s); }

void MyOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  config_params_load();  // для функции самого виджета
}

void MyOpenGLWidget::paintGL() {
  glClearColor(colorElement.colorBackRed, colorElement.colorBackGreen,
               colorElement.colorBackBlue, 1);  // цвет и глубина фона
  glClear(GL_COLOR_BUFFER_BIT |
          GL_DEPTH_BUFFER_BIT);  // очистка буфера цвета и буфера глубины

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  double k = s.matrix_3d.Max_lngth;

  //  выбор проекции
  Check_Projection(k);

  // Центрирование
  model_centering();

  drawCube();
  config_params_save();
}

void MyOpenGLWidget::resizeGL(int w, int h) {
  sizeMyWidgetW = w;
  sizeMyWidgetH = h;
  glViewport(0, 0, sizeMyWidgetW, sizeMyWidgetH);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent *mo) { mPos = mo->pos(); }

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *mo) {
  xRot = 1 / M_PI * (mo->pos().y() - mPos.y());
  yRot = 1 / M_PI * (mo->pos().x() - mPos.x());
  update();
}

//обработка входящего сигнала
void MyOpenGLWidget::input_name() {
  //по сигналу открывается окно выбора файла
  QString file_path = QFileDialog::getOpenFileName(this, tr("Open file"), ".",
                                                   tr("Object files (*.obj)"));

  //отпраавка переменной в класс, который посылает сигнал
  MainWindow *m = qobject_cast<MainWindow *>(sender());
  m->m_filePath = file_path;

  //Перезагрузка данных модели из нового файла
  file_name_Q = file_path;

  if (created != 0) {  // проверка на пустоту модели
    remove_model(&s);
    std::string file_name_std = file_name_Q.toStdString();
    const char *file_name = file_name_std.c_str();
    error = create_model(&s, file_name);
  }

  // Вывод информации в статус бар
  std::string file_name_std = file_name_Q.toStdString();
  int comPos = file_name_std.rfind("/") + 1;
  int comEndPos = file_name_Q.indexOf(".obj", comPos);
  QString nameFile = file_name_Q.mid(comPos, comEndPos - comPos);
  QString countVertices = QString::number(s.count_of_vrtxs);
  QString countEdges = QString::number(s.count_of_vrtxs + s.count_of_fcts - 2);
  m->statusBar()->showMessage("  Name: " + nameFile + "   Vertices: " +
                              countVertices + "   Edges: " + countEdges);
}

void MyOpenGLWidget::drawCube() {
  if (error || !created) {
    std::string file_name_std = file_name_Q.toStdString();
    const char *file_name = file_name_std.c_str();
    error = create_model(&s, file_name);
    created = 1;
  }

  //Проверка что модель создалась
  if (!error) {
    // Вращение по мышке
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);

    reset_matrix(&s);
    affin_trnsf(s.matrix_3d.matrix);

    glVertexPointer(3, GL_DOUBLE, 0, s.matrix_3d.matrix);  // работает
    glEnableClientState(GL_VERTEX_ARRAY);

    //Отрисовка вершин
    glPointSize(sizeVertex);  // размер вершины в пикселях
    glColor3d(colorElement.colorVertexRed,
              colorElement.colorVertexGreen,  // по умолчанию альфа=1
              colorElement.colorVertexBlue);
    if (typeVertex != 0) {
      if (typeVertex == 1) {  // выбор формы отображения вершины
        glEnable(GL_POINT_SMOOTH);  // отображать вершины в форме круга
      } else if (typeVertex == 2) {
        glDisable(GL_POINT_SMOOTH);  //отображать вершины в форме квадрата
      }
      glDrawArrays(GL_POINTS, 1, s.count_of_vrtxs);  //работает
    }

    // Отрисовка линий
    glLineWidth(sizeLine);
    glColor3d(colorElement.colorLineRed, colorElement.colorLineGreen,
              colorElement.colorLineBlue);
    if (typeLine != 0) {
      if (typeLine == 1) {  // сплошная линия
        glDisable(GL_LINE_STIPPLE);  // отключение режима пунктирной линии
      } else if (typeLine == 2) {  // пунктирная линия
        glEnable(GL_LINE_STIPPLE);  // включение режима пунктирной линии
        glLineStipple(1, 0x00F0);
      }
      glDrawElements(GL_LINES, s.facet.size_v, GL_UNSIGNED_INT, s.facet.vrtxs);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
  } else if (!file_name_Q.isEmpty()) {
    fprintf(stderr, "ERROR DRAW = %d\n", error);
  }
}

// Пересчет для расположение модели в середине поля отрисовки (центрирование)
void MyOpenGLWidget::model_centering() {
  double z_tmp = s.matrix_3d.Max_lngth;
  z_tmp = (z_tmp < 2) ? 2 : z_tmp;
  glTranslatef(0, 0, -(z_tmp));
}

void MyOpenGLWidget::affin_trnsf(double *arr_copy) {
  // Перемещение
  if (mov_x != 0 || mov_y != 0 || mov_z != 0) {
    shift(arr_copy, s.matrix_3d.rows, mov_x, mov_y, mov_z);
  }
  // Вращение
  if (rot_x || rot_y || rot_z) {
    turn(arr_copy, s.matrix_3d.rows, rot_x, rot_y, rot_z);
  }
  // Масштаб
  if (scaleModel != 1 && scaleModel != 0) {
    scale(arr_copy, s.matrix_3d.rows, scaleModel);
  }
}

/* Проверка проекции отрисовки */
void MyOpenGLWidget::Check_Projection(double k) {
  double z_far = k * 6;
  double shift = fabs(mov_z) + fabs(mov_y) + fabs(mov_x);
  if (scaleModel > 1) {
    z_far *= scaleModel;
    shift *= scaleModel;
  }
  if (modelProjection == 0) {
    glFrustum(-1, 1, -1, 1, 1, z_far + shift);
  } else if (modelProjection == 1) {
    glOrtho(-k, k, -k, k, 0.0001, z_far * 2 + shift);
  }
}

// Запись в файл настроек
void MyOpenGLWidget::config_params_save() {
//  QSettings settings(QDir::currentPath()+"/3DViewer_settings.ini", QSettings::IniFormat);
    QSettings settings("3DViewer_settings.ini", "3D_Viewer");
  settings.beginGroup("Settings");
  settings.setValue("colorElement.colorBackRed", colorElement.colorBackRed);
  settings.setValue("colorElement.colorBackGreen", colorElement.colorBackGreen);
  settings.setValue("colorElement.colorBackBlue", colorElement.colorBackBlue);
  settings.setValue("colorElement.colorVertexRed", colorElement.colorVertexRed);
  settings.setValue("colorElement.colorVertexGreen",
                    colorElement.colorVertexGreen);
  settings.setValue("colorElement.colorVertexBlue",
                    colorElement.colorVertexBlue);
  settings.setValue("colorElement.colorLineRed", colorElement.colorLineRed);
  settings.setValue("colorElement.colorLineGreen", colorElement.colorLineGreen);
  settings.setValue("colorElement.colorLineBlue", colorElement.colorLineBlue);
  settings.setValue("sizeLine", sizeLine);
  settings.setValue("typeLine", typeLine);
  settings.setValue("sizeVertex", sizeVertex);
  settings.setValue("typeVertex", typeVertex);
  settings.setValue("modelProjection", modelProjection);
  settings.endGroup();
}

// Чтение данный из файла
void MyOpenGLWidget::config_params_load() {
//  QSettings settings(QDir::currentPath()+"/3DViewer_settings.ini", QSettings::IniFormat);
    QSettings settings("3DViewer_settings.ini", "3D_Viewer");
  settings.beginGroup("Settings");
  colorElement.colorBackRed =
      settings.value("colorElement.colorBackRed", 0).toDouble();
  colorElement.colorBackGreen =
      settings.value("colorElement.colorBackGreen", 0).toDouble();
  colorElement.colorBackBlue =
      settings.value("colorElement.colorBackBlue", 0).toDouble();
  colorElement.colorVertexRed =
      settings.value("colorElement.colorVertexRed", 1).toDouble();
  colorElement.colorVertexGreen =
      settings.value("colorElement.colorVertexGreen", 0).toDouble();
  colorElement.colorVertexBlue =
      settings.value("colorElement.colorVertexBlue", 0).toDouble();
  colorElement.colorLineRed =
      settings.value("colorElement.colorLineRed", 0).toDouble();
  colorElement.colorLineGreen =
      settings.value("colorElement.colorLineGreen", 1).toDouble();
  colorElement.colorLineBlue =
      settings.value("colorElement.colorLineBlue", 0).toDouble();
  sizeLine = settings.value("sizeLine", 1).toInt();
  typeLine = settings.value("typeLine", 1).toInt();
  sizeVertex = settings.value("sizeVertex", 1).toInt();
  typeVertex = settings.value("typeVertex", 1).toInt();
  modelProjection = settings.value("modelProjection", 0).toInt();
  settings.endGroup();
  emit setSettingsOnForm();
}
