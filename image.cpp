#include "image.h"
#include "ui_image.h"

Image::Image(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Image)
{
    ui->setupUi(this);
}

Image::~Image()
{
    delete ui;
}

void Image::loadImage() {

    QGraphicsScene image;
    image.addPixmap(QPixmap("IMG_0348.PNG"));
    QGraphicsView view(&image);

    //QGraphicsPixmapItem item(QPixmap("IMG_0348.PNG"));
    //image.addItem(&item);
    view.show();
}
