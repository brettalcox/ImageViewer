#include "image.h"
#include "ui_image.h"
#include "zoom.h"
#include "filter.h"
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
        originalPicture.load(filename);
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
    QPixmap blank;
    picture = blank;
    originalPicture = blank;
    ui->comboBox->setCurrentText("Filter");
}

void Image::on_actionQuit_triggered()
{
    QApplication::quit();
}

void Image::on_rotateButton_clicked()
{
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
    scene.addPixmap(picture);

    QString newName = QFileDialog::getSaveFileName(this, tr("Save image"), QDir::currentPath(), tr("Image (*.jpg *.png *.bmp)"));
    image.save(newName);
}

void Image::on_selectButton_clicked()
{
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
}

void Image::on_cropButton_clicked()
{
    QPixmap croppedImage = QPixmap::grabWidget(ui->graphicsView);
    scene.clear();
    picture = croppedImage;
    scene.addPixmap(picture);
}

void Image::on_comboBox_currentIndexChanged(const QString &arg1)
{
        filterSelection = arg1;
        colorFilter();
}

void Image::colorFilter() {
    Filter filteredImage(picture);

    if (filterSelection == "Normal") {
        scene.clear();
        scene.addPixmap(picture);
    }

    if (filterSelection == "Grayscale") {
        filteredImage.grayFilter();
        scene.clear();
        scene.addPixmap(filteredImage.getFilter());
        picture = filteredImage.getFilter();
    }

    if (filterSelection == "Sepia") {
        filteredImage.sepiaFilter();
        scene.clear();
        scene.addPixmap(filteredImage.getFilter());
        picture = filteredImage.getFilter();

    }
}

void Image::on_resetButton_clicked()
{
    picture = originalPicture;
    scene.clear();
    scene.addPixmap(picture);
    ui->comboBox->setCurrentText("Filter");
    ui->brightnessSlider->setSliderPosition(0);
}

void Image::on_brightnessSlider_sliderMoved(int value)
{
    Filter filteredImage(picture);

    int difference = brightnessPrev - value;
    if (value > 0) {
        if (value == 0) {
            if (brightnessPrev == 1) {
                filteredImage.changeBrightness(-value);
            }
            else if (brightnessPrev == -1) {
                filteredImage.changeBrightness(value);
            }
        }
        else {
            if (difference > 0) {
                filteredImage.changeBrightness(-value);
            }
            else if (difference < 0) {
                filteredImage.changeBrightness(value);
            }
        }
    }
    else if (value < 0) {
        if (value == 0) {
            if (brightnessPrev == 1) {
                filteredImage.changeBrightness(value);
            }
            else if (brightnessPrev == -1) {
                filteredImage.changeBrightness(-value);
            }
        }
        else {
            if (difference > 0) {
                filteredImage.changeBrightness(value);
            }
            else if (difference < 0) {
                filteredImage.changeBrightness(-value);
            }
        }
    }
    brightnessPrev = value;

    scene.clear();
    scene.addPixmap(filteredImage.getFilter());
    picture = filteredImage.getFilter();

}
