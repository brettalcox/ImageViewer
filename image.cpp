#include "image.h"
#include "ui_image.h"
#include "zoom.h"
#include <QFile>
#include <QFileDialog>
#include <fstream>
#include <sstream>
#include <math.h>
#include <QGraphicsPixmapItem>

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

void Image::on_rotateButton_clicked()
{
    /*
    scene.clear();
    //ui->graphicsView->rotate(90);
    QPixmap p(picture);
    auto item = new QGraphicsPixmapItem(picture);
    item->setTransformOriginPoint(p.rect().center());
    item->setRotation(90);

    scene.addItem(item);
    pictureRotate = item->pixmap();
    scene.addPixmap(pictureRotate);
    */
    //auto sceneRotate = new QGraphicsScene;

    /*

    QMatrix rm;
    rm.rotate(90);
    picture = picture.transformed(QPixmap::trueMatrix(rm,picture.width(), picture.height()));
    scene.clear();
    ui->graphicsView->setScene(&scene);
    scene.addPixmap(picture);
    */

    QPixmap rotatedPixmap(picture.height(), picture.width());
    QPainter p(&rotatedPixmap);
    QSize size = picture.size();
    p.translate(size.height()/2, size.height()/2);
    p.rotate(90);
    p.translate(-size.height()/2, -size.height()/2);
    p.drawPixmap(0, 0, picture);
    p.end();
    picture = rotatedPixmap;
    scene.clear();
    scene.addPixmap(picture);
}

void Image::on_dial_valueChanged(int value)
{
    int difference = previousValue - value;
    if (value == 0) {
        if (previousValue == 35) {
            ui->graphicsView->rotate(10);
        }
        else {
            ui->graphicsView->rotate(350);
        }
    }
    else if (value == 35) {
        if (previousValue == 0) {
            ui->graphicsView->rotate(350);
        }
        else {
            ui->graphicsView->rotate(10);
        }
    }
    else {
        if (difference > 0) {
            ui->graphicsView->rotate(350);
        }
        else if (difference < 0) {
            ui->graphicsView->rotate(10);
        }
    }
    previousValue = value;

}

void Image::on_saveButton_clicked()
{
    scene.clear();
    QImage image = picture.toImage();
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    scene.render(&painter);
    painter.end();
    image.save("pic.png");
    scene.addPixmap(picture);


/*
    QPixmap output = QPixmap::grabWidget(ui->graphicsView);
    QImage image = output.toImage();
    image.save("pic.png");
*/
}
