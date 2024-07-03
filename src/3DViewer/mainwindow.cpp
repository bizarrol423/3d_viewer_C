#include "mainwindow.h"
//#include "myopenglwidget.h"
#include "qgifimage/qgifimage.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  numb = 0;
  numb = 0;
  tmr = new QTimer();     // создание таймера
  tmr->setInterval(100);  //установка интервала
  // уставновка сигнала на создание скриншота
  numb = 0;
  numb = 0;
  tmr = new QTimer();     // создание таймера
  tmr->setInterval(100);  //установка интервала
  connect(
      tmr, SIGNAL(timeout()), this,
      SLOT(create_screenshot()));  // уставновка сигнала на создание скриншота

  setWindowTitle("3D_Viewer");

  connect(this, &MainWindow::download_file, ui->MyWidget,
          &MyOpenGLWidget::input_name);
  connect(ui->MyWidget, &MyOpenGLWidget::setSettingsOnForm, this,
          &MainWindow::set_settings_on_form);
}

MainWindow::~MainWindow() { delete ui; }

//отсылка сигнала, что нужно загузить файл на виджет, и вставка его имени в
//текстовое поле
void MainWindow::on_download_file_clicked() {
  emit download_file();
  ui->box_file_name->setText(m_filePath);
}

// Цвет фона
void MainWindow::on_But_color_back_clicked() {
  ui->MyWidget->colorElement.colorBack =
      QColorDialog::getColor(QColor(0, 0, 0, 255));
  if (!ui->MyWidget->colorElement.colorBack.isValid()) {
    qDebug() << "Выбор цвета фона отменён!";
  } else {
    ui->MyWidget->colorElement.colorBackRed =
        ui->MyWidget->colorElement.colorBack.redF();
    ui->MyWidget->colorElement.colorBackGreen =
        ui->MyWidget->colorElement.colorBack.greenF();
    ui->MyWidget->colorElement.colorBackBlue =
        ui->MyWidget->colorElement.colorBack.blueF();
    ui->MyWidget->colorElement.colorBackAlpha =
        ui->MyWidget->colorElement.colorBack.alphaF();
    // Раскраска квадратика-индикатора
    show_color(ui->MyWidget->colorElement.colorBack, ui->show_color_back);
  }
}

// Выбор цвета линий
void MainWindow::on_But_color_line_clicked() {
  ui->MyWidget->colorElement.colorLine =
      QColorDialog::getColor(QColor(38, 38, 38, 255));
  if (!ui->MyWidget->colorElement.colorLine.isValid()) {
    qDebug() << "Выбор цвета фона отменён!";
  } else {
    ui->MyWidget->colorElement.colorLineRed =
        ui->MyWidget->colorElement.colorLine.redF();
    ui->MyWidget->colorElement.colorLineGreen =
        ui->MyWidget->colorElement.colorLine.greenF();
    ui->MyWidget->colorElement.colorLineBlue =
        ui->MyWidget->colorElement.colorLine.blueF();
    ui->MyWidget->colorElement.colorLineAlpha =
        ui->MyWidget->colorElement.colorLine.alphaF();
    // Раскраска квадратика-индикатора
    show_color(ui->MyWidget->colorElement.colorLine, ui->show_color_line);
  }
}

// Выбор цвета вершин
void MainWindow::on_But_color_vertex_clicked() {
  ui->MyWidget->colorElement.colorVertex =
      QColorDialog::getColor(QColor(38, 38, 38, 255));
  if (!ui->MyWidget->colorElement.colorVertex.isValid()) {
    qDebug() << "Выбор цвета фона отменён!";
  } else {
    ui->MyWidget->colorElement.colorVertexRed =
        ui->MyWidget->colorElement.colorVertex.redF();
    ui->MyWidget->colorElement.colorVertexGreen =
        ui->MyWidget->colorElement.colorVertex.greenF();
    ui->MyWidget->colorElement.colorVertexBlue =
        ui->MyWidget->colorElement.colorVertex.blueF();
    ui->MyWidget->colorElement.colorVertexAlpha =
        ui->MyWidget->colorElement.colorVertex.alphaF();
    // Раскраска квадратика-индикатора
    show_color(ui->MyWidget->colorElement.colorVertex, ui->show_color_vertex);
  }
}

// Аттрибуты линий
void MainWindow::on_line_attribute_activated(int index) {
  switch (index) {
    case 0:  // нет отображения линий
      ui->MyWidget->typeLine = 0;
      break;
    case 1:  // сплошные линии
      ui->MyWidget->typeLine = 1;
      break;
    case 2:  // пунктирные линии
      ui->MyWidget->typeLine = 2;
      break;
  }
  ui->MyWidget->repaint();
}

void MainWindow::on_size_line_valueChanged(int arg1) {
  ui->MyWidget->sizeLine = arg1;
  ui->MyWidget->repaint();
}

// Атрибуты вершин
void MainWindow::on_vertex_attribute_activated(int index) {
  switch (index) {
    case 0:  // нет отображения вершин
      ui->MyWidget->typeVertex = 0;
      break;
    case 1:  // круг
      ui->MyWidget->typeVertex = 1;
      break;
    case 2:  // квадрат
      ui->MyWidget->typeVertex = 2;
      break;
  }
  ui->MyWidget->repaint();
}

void MainWindow::on_size_vertex_valueChanged(int arg1) {
  ui->MyWidget->sizeVertex = arg1;
  ui->MyWidget->repaint();
}

// Перемещение
void MainWindow::on_spin_mov_X_valueChanged(int arg1) {
  ui->MyWidget->mov_x = arg1;
  ui->slider_mov_X->setSliderPosition(arg1);
  ui->MyWidget->repaint();
}

void MainWindow::on_slider_mov_X_valueChanged(int value) {
  ui->MyWidget->mov_x = value;
  ui->spin_mov_X->setValue(value);
  ui->MyWidget->repaint();
}

void MainWindow::on_spin_mov_Y_valueChanged(int arg1) {
  ui->MyWidget->mov_y = arg1;
  ui->slider_mov_Y->setSliderPosition(arg1);
  ui->MyWidget->repaint();
}

void MainWindow::on_slider_mov_Y_valueChanged(int value) {
  ui->MyWidget->mov_y = value;
  ui->spin_mov_Y->setValue(value);
  ui->MyWidget->repaint();
}

void MainWindow::on_spin_mov_Z_valueChanged(int arg1) {
  ui->MyWidget->mov_z = arg1;
  ui->slider_mov_Z->setSliderPosition(arg1);
  ui->MyWidget->repaint();
}

void MainWindow::on_slider_mov_Z_valueChanged(int value) {
  ui->MyWidget->mov_z = value;
  ui->spin_mov_Z->setValue(value);
  ui->MyWidget->repaint();
}

// Вращение
void MainWindow::on_dial_rot_X_valueChanged(int value) {
  ui->MyWidget->rot_x = value;
  ui->spin_rot_X->setValue(value);
  ui->MyWidget->repaint();
}

void MainWindow::on_spin_rot_X_valueChanged(int arg1) {
  ui->MyWidget->rot_x = arg1;
  ui->dial_rot_X->setValue(arg1);
  ui->MyWidget->repaint();
}

void MainWindow::on_dial_rot_Y_valueChanged(int value) {
  ui->MyWidget->rot_y = value;
  ui->spin_rot_Y->setValue(value);
  ui->MyWidget->repaint();
}

void MainWindow::on_spin_rot_Y_valueChanged(int arg1) {
  ui->MyWidget->rot_y = arg1;
  ui->dial_rot_Y->setValue(arg1);
  ui->MyWidget->repaint();
}

void MainWindow::on_dial_rot_Z_valueChanged(int value) {
  ui->MyWidget->rot_z = value;
  ui->spin_rot_Z->setValue(value);
  ui->MyWidget->repaint();
}

void MainWindow::on_spin_rot_Z_valueChanged(int arg1) {
  ui->MyWidget->rot_z = arg1;
  ui->dial_rot_Z->setValue(arg1);
  ui->MyWidget->repaint();
}

// Выбор типа проекции
void MainWindow::on_projection_type_activated(int index) {
  switch (index) {
    case 0:  // Центральная
      ui->MyWidget->modelProjection = 0;
      break;
    case 1:  // Параллельная
      ui->MyWidget->modelProjection = 1;
      break;
    default:
      break;
  }
  ui->MyWidget->repaint();
}

// Масштаб
void MainWindow::on_spin_scale_valueChanged(double arg1) {
  ui->MyWidget->scaleModel = arg1;
  ui->MyWidget->repaint();
}

// Сброс настроек к дефолтным
void MainWindow::on_reset_clicked() {
  ui->MyWidget->typeLine = 1;
  ui->line_attribute->setCurrentIndex(1);

  ui->MyWidget->sizeLine = 1;
  ui->size_line->setValue(1);

  ui->MyWidget->typeVertex = 1;
  ui->vertex_attribute->setCurrentIndex(1);

  ui->MyWidget->sizeVertex = 1;
  ui->size_vertex->setValue(1);

  ui->MyWidget->mov_x = 0;
  ui->spin_mov_X->setValue(0);

  ui->MyWidget->mov_y = 0;
  ui->spin_mov_Y->setValue(0);

  ui->MyWidget->mov_z = 0;
  ui->spin_mov_Z->setValue(0);

  ui->MyWidget->rot_x = 0;
  ui->dial_rot_X->setValue(0);
  ui->spin_rot_X->setValue(0);

  ui->MyWidget->rot_y = 0;
  ui->dial_rot_Y->setValue(0);
  ui->spin_rot_Y->setValue(0);

  ui->MyWidget->rot_z = 0;
  ui->dial_rot_Z->setValue(0);
  ui->spin_rot_Z->setValue(0);

  ui->MyWidget->scaleModel = 1;
  ui->spin_scale->setValue(1);

  ui->MyWidget->colorElement.colorVertexRed = 1;
  ui->MyWidget->colorElement.colorVertexGreen = 0;
  ui->MyWidget->colorElement.colorVertexBlue = 0;

  ui->MyWidget->colorElement.colorLineRed = 0;
  ui->MyWidget->colorElement.colorLineGreen = 1;
  ui->MyWidget->colorElement.colorLineBlue = 0;

  ui->MyWidget->colorElement.colorBackRed = 0;
  ui->MyWidget->colorElement.colorBackGreen = 0;
  ui->MyWidget->colorElement.colorBackBlue = 0;

  ui->MyWidget->modelProjection = 0;
  ui->projection_type->setCurrentIndex(0);

  ui->MyWidget->colorElement.colorBack =
      ui->MyWidget->colorElement.colorBack.fromRgbF(
          ui->MyWidget->colorElement.colorBackRed,
          ui->MyWidget->colorElement.colorBackGreen,
          ui->MyWidget->colorElement.colorBackBlue, 1);
  ui->MyWidget->colorElement.colorVertex =
      ui->MyWidget->colorElement.colorVertex.fromRgbF(
          ui->MyWidget->colorElement.colorVertexRed,
          ui->MyWidget->colorElement.colorVertexGreen,
          ui->MyWidget->colorElement.colorVertexBlue, 1);
  ui->MyWidget->colorElement.colorLine =
      ui->MyWidget->colorElement.colorLine.fromRgbF(
          ui->MyWidget->colorElement.colorLineRed,
          ui->MyWidget->colorElement.colorLineGreen,
          ui->MyWidget->colorElement.colorLineBlue, 1);

  show_color(ui->MyWidget->colorElement.colorBack, ui->show_color_back);
  show_color(ui->MyWidget->colorElement.colorVertex, ui->show_color_vertex);
  show_color(ui->MyWidget->colorElement.colorLine, ui->show_color_line);

  ui->MyWidget->repaint();
}

void MainWindow::on_screenshot_button_clicked()  // создание скриншота
{
  QString filename = QFileDialog::getSaveFileName(
      0, "Open Dialog", "",
      tr("Images (*.jpeg *.bmp )"));  // сохранение файла и изменение расширения
  ui->MyWidget->grab().save(filename);  // захват виджета и сохранение
}

void MainWindow::on_create_gif_clicked() {
  tmr->start();  // запуск таймера
  QDir dir("./screenshot_gif/");  //проверка и создание папки если её нет
  if (!dir.exists()) {
    dir.mkpath(".");  // создание папки если её нет
  }
}

void MainWindow::create_screenshot() {
  if (numb < 50) {  // пока не созданны все кадры
    ui->MyWidget->grab().scaled(640, 480).save(
        "./screenshot_gif/" + QString::number(numb) +
        ".png");  // захват виджета и сохранение
    numb++;       // добавление 1 к имени файла
    ui->gif_progress->setValue(numb);
    if (numb == 49) {  // как только все 49 кадров созданны можно создавать gif
      create_gif("./screenshot_gif/");
    }
  }
}

void MainWindow::create_gif(QString folder_screeenshot) {  // создание gif
  QString filename = QFileDialog::getSaveFileName(
      0, "Open Dialog", "",
      tr("Images (*.gif )"));  // сохранение файла и изменение расширенияы
  QDir dir_screenshot(folder_screeenshot);  //папка с скриншотами
  QString name = "";                        // имя фотки
  QGifImage gif(QSize(640, 480));  // определение размера
  gif.setDefaultDelay(100);  // задержка анимации между картинками 0.1 секунда
  QImage image(640, 480, QImage::Format_RGB32);  // обьявление изображения
  for (int i = 0; i < numb;
       i++) {  // проходиться по изображениям и создавать из них gif
    name = folder_screeenshot + "/" + QString::number(i) +
           ".png";  //проходимся по каждой фотке
    image.load(name, "PNG");  // загрузка
    gif.addFrame(image);      //добавление в гиф формат
  }
  gif.save(filename);                  //сохранение гифки
  dir_screenshot.removeRecursively();  // удаление папки с скриншотами
  numb = 0;  // обнуляем переменную после окончания
  ui->gif_progress->setValue(numb);
  tmr->stop();  // останавливаем таймер скриншотов
}

// Установка значений из конфига на форму
void MainWindow::set_settings_on_form() {
  ui->line_attribute->setCurrentIndex(ui->MyWidget->typeLine);
  ui->size_line->setValue(ui->MyWidget->sizeLine);
  ui->vertex_attribute->setCurrentIndex(ui->MyWidget->typeVertex);
  ui->size_vertex->setValue(ui->MyWidget->sizeVertex);
  ui->projection_type->setCurrentIndex(ui->MyWidget->modelProjection);

  // Конвертация закружаемых значений RGB в QColor
  ui->MyWidget->colorElement.colorBack =
      ui->MyWidget->colorElement.colorBack.fromRgbF(
          ui->MyWidget->colorElement.colorBackRed,
          ui->MyWidget->colorElement.colorBackGreen,
          ui->MyWidget->colorElement.colorBackBlue, 1);
  ui->MyWidget->colorElement.colorVertex =
      ui->MyWidget->colorElement.colorVertex.fromRgbF(
          ui->MyWidget->colorElement.colorVertexRed,
          ui->MyWidget->colorElement.colorVertexGreen,
          ui->MyWidget->colorElement.colorVertexBlue, 1);
  ui->MyWidget->colorElement.colorLine =
      ui->MyWidget->colorElement.colorLine.fromRgbF(
          ui->MyWidget->colorElement.colorLineRed,
          ui->MyWidget->colorElement.colorLineGreen,
          ui->MyWidget->colorElement.colorLineBlue, 1);

  show_color(ui->MyWidget->colorElement.colorBack, ui->show_color_back);
  show_color(ui->MyWidget->colorElement.colorVertex, ui->show_color_vertex);
  show_color(ui->MyWidget->colorElement.colorLine, ui->show_color_line);
}

// Раскраска квадратика-индикатора в выбранный цвет
void MainWindow::show_color(QColor color, QLabel *label) {
  QVariant variant = color;
  QString colorString = variant.toString();
  label->setStyleSheet("QLabel {background-color:" + colorString + ";}");
}
