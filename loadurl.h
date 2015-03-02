#ifndef LOADURL_H
#define LOADURL_H

#include <QWidget>
#include <QByteArray>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

namespace Ui {
class LoadUrl;
}

class LoadUrl : public QWidget
{
    Q_OBJECT

public:
    explicit LoadUrl(QWidget *parent = 0);
    ~LoadUrl();
    void downloadImageFile(QString);
    QPixmap returnImage();

signals:
    void downloaded();

private slots:
    void imageDownloaded(QNetworkReply* pReply);

private:
    Ui::LoadUrl *ui;
    QByteArray *m_DownloadedData;
    QPixmap image;
};

#endif // LOADURL_H
