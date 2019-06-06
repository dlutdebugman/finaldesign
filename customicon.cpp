#include "customicon.h"

customIcon* customIcon::_instance = 0;
customIcon::customIcon(QObject *)
    : QObject(qApp)
{
    int fontId = QFontDatabase::addApplicationFont(":/Resources/image/fontawesome-webfont.ttf");
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    iconFont = QFont(fontName);
}

void customIcon::SetIcon(QLabel *lab, QChar c, int size)
{
    Q_UNUSED(c);
    iconFont.setPointSize(size);
    lab->setFont(iconFont);
}

void customIcon::SetIcon(QPushButton *btn, QChar c, int size)
{
    iconFont.setPointSize(size);
    btn->setFont(iconFont);
    btn->setText(c);
}

