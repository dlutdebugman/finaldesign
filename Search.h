#ifndef SEARCH_H
#define SEARCH_H


#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QSqlRecord>
#include <QMessageBox>
#include <QDebug>
#include <QVector>
#include "public.h"

#define  MAX_SEARCH_NUM  (5000)
#define  MAX_SERCH_DAY   (31)

class Search : public QWidget
{
public:
    Search();
    ~Search();

private:
    bool initSQL();
    bool createTabale();
    bool tableExist(QString _tableName);

public :
    void storePlotData(char _id[], char _data[],int checkNUm);
    bool searchDatabyID(QString _IDorDate,QString _mainTableDateName,bool isIDSearch = true);

public:
    void getData(login_info *_Data);

private:
    QSqlDatabase m_db;
    QString m_mainTableDateName;
    QString m_plotData;

    login_info m_Data;
};

#endif // SEARCH_H
