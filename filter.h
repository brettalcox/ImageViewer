#ifndef FILTER_H
#define FILTER_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class Filter
{
public:
    Filter(QPixmap);
    ~Filter();
    void setFilter(QPixmap);
    QPixmap getFilter();
    void normalFilter();
    void grayFilter();
    void sepiaFilter();
    void changeBrightness(int);
    void blur(const QImage& image, const QRect& rect, int radius, bool alphaOnly);
    void warm(int);
    void cool(int);

private:
    QPixmap filterPicture;
    QPixmap unfiltered;
};

#endif // FILTER_H
