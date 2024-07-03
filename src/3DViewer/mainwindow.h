#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QStatusBar>
#include <QTimer>

extern "C" {
#include "../Back/s_object.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  QString m_filePath;

 private slots:
  void on_download_file_clicked();

  void on_But_color_line_clicked();

  void on_But_color_back_clicked();

  void on_But_color_vertex_clicked();

  void on_line_attribute_activated(int index);

  void on_vertex_attribute_activated(int index);

  void on_size_line_valueChanged(int arg1);

  void on_size_vertex_valueChanged(int arg1);

  void on_spin_mov_X_valueChanged(int arg1);

  void on_spin_mov_Y_valueChanged(int arg1);

  void on_spin_mov_Z_valueChanged(int arg1);

  void on_reset_clicked();

  void on_dial_rot_X_valueChanged(int value);

  void on_spin_rot_X_valueChanged(int arg1);

  void on_dial_rot_Y_valueChanged(int value);

  void on_spin_rot_Y_valueChanged(int arg1);

  void on_dial_rot_Z_valueChanged(int value);

  void on_spin_rot_Z_valueChanged(int arg1);

  void on_projection_type_activated(int index);

  void on_spin_scale_valueChanged(double arg1);

  void on_screenshot_button_clicked();

  void on_create_gif_clicked();

  void create_screenshot();

  void on_slider_mov_X_valueChanged(int value);

  void on_slider_mov_Y_valueChanged(int value);

  void on_slider_mov_Z_valueChanged(int value);

  void show_color(QColor color, QLabel *label);

 public slots:
  void set_settings_on_form();

 private:
  Ui::MainWindow *ui;
  void create_gif(QString folder_screeenshot);
  int numb;     // количество скринов
  QTimer *tmr;  // таймер для скриншота

 signals:
  void download_file();
};
#endif  // MAINWINDOW_H
