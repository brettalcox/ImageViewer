#ifndef IMAGE_H
#define IMAGE_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>

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

private slots:
    void on_pushButton_clicked();

    void on_actionClose_Image_triggered();

private:
    Ui::Image *ui;
    QPixmap picture;
    QGraphicsScene scene;
    QString filename;


};

#endif // IMAGE_H
