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

void Filter::blur(const QImage& image, const QRect& rect, int radius, bool alphaOnly) {

    int tab[] = { 14, 10, 8, 6, 5, 5, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2 };
        int alpha = (radius < 1)  ? 16 : (radius > 17) ? 1 : tab[radius-1];

        QImage result = image.convertToFormat(QImage::Format_ARGB32_Premultiplied);
        int r1 = rect.top();
        int r2 = rect.bottom();
        int c1 = rect.left();
        int c2 = rect.right();

        int bpl = result.bytesPerLine();
        int rgba[4];
        unsigned char* p;

        int i1 = 0;
        int i2 = 3;

        if (alphaOnly)
            i1 = i2 = (QSysInfo::ByteOrder == QSysInfo::BigEndian ? 0 : 3);

        for (int col = c1; col <= c2; col++) {
            p = result.scanLine(r1) + col * 4;
            for (int i = i1; i <= i2; i++)
                rgba[i] = p[i] << 4;

            p += bpl;
            for (int j = r1; j < r2; j++, p += bpl)
                for (int i = i1; i <= i2; i++)
                    p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
        }

        for (int row = r1; row <= r2; row++) {
            p = result.scanLine(row) + c1 * 4;
            for (int i = i1; i <= i2; i++)
                rgba[i] = p[i] << 4;

            p += 4;
            for (int j = c1; j < c2; j++, p += 4)
                for (int i = i1; i <= i2; i++)
                    p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
        }

        for (int col = c1; col <= c2; col++) {
            p = result.scanLine(r2) + col * 4;
            for (int i = i1; i <= i2; i++)
                rgba[i] = p[i] << 4;

            p -= bpl;
            for (int j = r1; j < r2; j++, p -= bpl)
                for (int i = i1; i <= i2; i++)
                    p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
        }

        for (int row = r1; row <= r2; row++) {
            p = result.scanLine(row) + c2 * 4;
            for (int i = i1; i <= i2; i++)
                rgba[i] = p[i] << 4;

            p -= 4;
            for (int j = c1; j < c2; j++, p -= 4)
                for (int i = i1; i <= i2; i++)
                    p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
        }
        filterPicture = filterPicture.fromImage(result);
}
