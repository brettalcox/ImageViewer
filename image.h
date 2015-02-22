#ifndef IMAGE_H
#define IMAGE_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QMenu>
#include <QLabel>

namespace Ui {
class Image;
}

class Image : public QMainWindow
{
    Q_OBJECT

public:
    explicit Image(QWidget *parent = 0);
    ~Image();
    void loadImage();
    void cropImage();
    void colorFilter();

private slots:
    void on_loadButton_clicked();
    void on_actionClose_Image_triggered();
    void on_actionOpen_Image_triggered();
    void on_closeButton_clicked();
    void on_actionQuit_triggered();
    void on_rotateButton_clicked();
    void on_dial_valueChanged(int value);
    void on_saveButton_clicked();
    void on_selectButton_clicked();
    void on_cropButton_clicked();
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void on_resetButton_clicked();
    void on_brightnessSlider_sliderMoved(int value);

private:
    Ui::Image *ui;
    QPixmap picture;
    QPixmap originalPicture;
    QGraphicsScene scene;
    QString filename;
    int previousValue = 1;
    int brightnessPrev = 0;
    QString filterSelection;

};

#endif // IMAGE_H
