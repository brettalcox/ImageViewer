#include "filter.h"

Filter::Filter(QPixmap original)
{
    unfiltered = original;
}

Filter::~Filter()
{

}

void Filter::setFilter(QPixmap picture) {
    filterPicture = picture;
}

QPixmap Filter::getFilter() {
    return filterPicture;
}

void Filter::normalFilter() {
    filterPicture = unfiltered;
}

void Filter::grayFilter() {
    filterPicture = unfiltered;
    QImage image = filterPicture.toImage();
    QRgb col;
    int gray;
    int width = filterPicture.width();
    int height = filterPicture.height();
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            col = image.pixel(i, j);
            gray = qGray(col);
            image.setPixel(i, j, qRgb(gray, gray, gray));
        }
    }
    filterPicture = filterPicture.fromImage(image);
}

void Filter::sepiaFilter() {
    filterPicture = unfiltered;
    QImage image = filterPicture.toImage();
    int sepiaH, sepiaS, sepiaL;
    QColor(162,128,101).getHsv( &sepiaH, &sepiaS, &sepiaL );
    int pixelLuminance;
    QRgb* rgb;
    QColor sepiaColor;
    uchar* scanLine;
    int width = filterPicture.width();
    int height = filterPicture.height();

    for (int i = 0; i < height; i++) {
        scanLine = image.scanLine(i);
        for (int j = 0; j < width; j++) {
            rgb = ((QRgb*)scanLine+j);
            pixelLuminance = (int) (0.2125*qRed(*rgb) + 0.7154*qGreen(*rgb) + 0.0721*qBlue(*rgb));
            sepiaColor.setHsv(sepiaH, sepiaS, pixelLuminance);
            *rgb = sepiaColor.rgb();
        }
    }
    filterPicture = filterPicture.fromImage(image);
}

void Filter::changeBrightness(int delta) {
    filterPicture = unfiltered;
    QImage newImage = filterPicture.toImage();
    QColor oldColor;
    int r,g,b;

        for (int x = 0; x < newImage.width(); x++){
            for (int y = 0; y < newImage.height(); y++){
                oldColor = QColor(filterPicture.toImage().pixel(x,y));

                r = oldColor.red() + delta;
                g = oldColor.green() + delta;
                b = oldColor.blue() + delta;

                r = qBound(0, r, 255);
                g = qBound(0, g, 255);
                b = qBound(0, b, 255);

                newImage.setPixel(x,y, qRgb(r,g,b));
            }
        }
        filterPicture = filterPicture.fromImage(newImage);
}
