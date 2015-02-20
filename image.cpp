#include "image.h"
#include "ui_image.h"
#include "zoom.h"
#include <QFile>
#include <QFileDialog>
#include <fstream>
#include <sstream>

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

        scene.clear();
        ui->graphicsView->resetTransform();
        picture.load(filename);
        ui->graphicsView->setScene(&scene);
        scene.addPixmap(picture);

        Graphics_view_zoom* z = new Graphics_view_zoom(ui->graphicsView);
        z->set_modifiers(Qt::NoModifier);

}

void Image::on_loadButton_clicked()
{
    filename = QFileDialog::getOpenFileName(this,
         tr("Open Image"), "\\", tr("Image Files (*.png *.jpg *.bmp)"));
    loadImage();
}

void Image::on_actionClose_Image_triggered()
{
    scene.clear();
    ui->graphicsView->resetTransform();
}

void Image::on_actionOpen_Image_triggered()
{
    filename = QFileDialog::getOpenFileName(this,
         tr("Open Image"), "\\", tr("Image Files (*.png *.jpg *.bmp)"));
    loadImage();
}

void Image::on_closeButton_clicked()
{
    scene.clear();
    ui->graphicsView->resetTransform();
}

void Image::on_actionQuit_triggered()
{
    QApplication::quit();
}
