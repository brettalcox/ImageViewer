#include "image.h"
#include "ui_image.h"
#include "zoom.h"

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

    filename = "IMG_0348.PNG";
    //QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView);
    //picture("IMG_0348.PNG");
    picture.load(filename);
    ui->graphicsView->setScene(&scene);
    scene.addPixmap(picture);
    Graphics_view_zoom* z = new Graphics_view_zoom(ui->graphicsView);
    z->set_modifiers(Qt::NoModifier);


}

void Image::on_pushButton_clicked()
{
    loadImage();
}

void Image::on_actionClose_Image_triggered()
{
    scene.clear();
}
