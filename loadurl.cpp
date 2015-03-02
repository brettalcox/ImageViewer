#include "loadurl.h"
#include "ui_loadurl.h"

LoadUrl::LoadUrl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadUrl)
{
    ui->setupUi(this);
}

LoadUrl::~LoadUrl()
{
    delete ui;
}

void LoadUrl::downloadImageFile(QString url) {

    QNetworkAccessManager *m_WebCtrl = new QNetworkAccessManager;
    connect(m_WebCtrl, SIGNAL(finished(QNetworkReply*)), SLOT(imageDownloaded(QNetworkReply*)));
    QUrl theUrl = url;
    QNetworkRequest request(theUrl);
    m_WebCtrl->get(request);

}

void LoadUrl::imageDownloaded(QNetworkReply *pReply) {
    QByteArray downloadedImage = NULL;
    downloadedImage = pReply->readAll();
    emit downloaded();

    QPixmap urlImage;
    urlImage.loadFromData(downloadedImage);
    image = urlImage;



}

QPixmap LoadUrl::returnImage() {
    return image;
}
