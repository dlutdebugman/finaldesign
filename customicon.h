#ifndef CUSTOMICON_H
#define CUSTOMICON_H

#include <QObject>
#include <QFont>
#include <QFontDatabase>
#include <QMutex>
#include <QLabel>
#include <QPushButton>
#include <QApplication>

class customIcon : public QObject
{
    Q_OBJECT
public:
    explicit customIcon(QObject *parent = 0);

    QFont iconFont;
    static customIcon* _instance;

public:
    static customIcon* Instance()
    {
        static QMutex mutex;
        if (!_instance) {
            QMutexLocker locker(&mutex);
            if (!_instance) {
                _instance = new customIcon;
            }
        }
        return _instance;
    }

    void SetIcon(QLabel* lab, QChar c, int size = 10);
    void SetIcon(QPushButton* btn, QChar c, int size = 10);
};

#endif // CUSTOMICON_H
