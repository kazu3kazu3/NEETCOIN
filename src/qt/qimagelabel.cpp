// Copyright (c) 2018 NEETCOIN Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <QtGui/QPainter>
#include <QtWidgets/QStyleOption>

#include "qimagelabel.h"

QImageLabel::QImageLabel(QWidget *parent) : QLabel(parent) {}

void QImageLabel::paintEvent(QPaintEvent *event) {
    // If pixmap is not set, call parent's method
    if (!this->pixmap() || this->pixmap()->isNull()) {
        QLabel::paintEvent(event);
        return;
    }

    QPainter painter(this);
    drawFrame(&painter);

    QSize scaledSize = this->size() * devicePixelRatioF();
    QImage *originalImage = new QImage(this->pixmap()->toImage());
    QImage scaledImage = originalImage->scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QPixmap *scaledPixmap = new QPixmap(QPixmap::fromImage(scaledImage));
    scaledPixmap->setDevicePixelRatio(devicePixelRatioF());

    int marginX = (this->width() - scaledPixmap->width()) / 2;
    int marginY = (this->height() - scaledPixmap->height()) / 2;

    painter.drawPixmap(marginX, marginY, *scaledPixmap);

    delete originalImage;
    delete scaledPixmap;
}
