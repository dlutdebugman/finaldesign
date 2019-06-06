#include <QDateTime>
#include <QMessageBox>
#include <QApplication>

#include "Search.h"

Search::Search()
{
    initSQL();
}

Search::~Search()
{
    m_db.close();
    QSqlDatabase::removeDatabase("QSQLITE");
}
/*!
*@brief：
*/
bool Search::initSQL()
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        m_db = QSqlDatabase::database("qt_sql_default_connection");
        m_db.setDatabaseName("database.db");
    }
    else
    {
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName("database.db");
    }

    if (!m_db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection."
                                       ), QMessageBox::Cancel);
        return false;
    }
    createTabale();
    return true;
}
/*!
*@brief:创建数据库
*/
bool Search::createTabale()
{
    m_mainTableDateName.clear();
    m_mainTableDateName = "login" ;
    QSqlQuery query(m_db);
    query.exec(QString("select count(*) from sqlite_master where type='table' and name='%1'").arg(m_mainTableDateName));
    if(query.next())
    {
        if(!query.value(0).toInt() == 0)
        {
            return true;
        }
    }
    QString tableName = "create table " + m_mainTableDateName +" (" + "id CHAR primary key,"
                                                                      "check_num  CHAR(200),"
                                                                      "password   CHAR(200)" +")";

    query.exec(tableName);

    return true;
}

/*!
*@brief: 获取主表数据(不检索plot数据，具有日期)
*/
void Search::getData(login_info *_Data)
{
    memcpy(_Data , &m_Data ,sizeof(login_info));
}

/**
* @brief:save user_name and password
* @param:_id[in]id   _data[in]password
* @return:
*/
void Search::storePlotData(char _id[], char _data[],int checkNUm)
{
	createTabale();
    QString refer = "insert into "+ m_mainTableDateName +" values (:id,:password,:check_num)";
    QSqlQuery query;
    query.prepare(refer);
    query.bindValue(":id",_id);
    query.bindValue(":check_num",checkNUm);
    query.bindValue(":password",_data);
    query.exec();
}
/*!
*@brief: search by ID
*/
bool Search::searchDatabyID(QString _IDorDate,QString _TableDateName,bool isIDSearch)
{
    QSqlQuery query;
    memset(&m_Data, 0x00, sizeof(login_info));


    if(isIDSearch && tableExist(_TableDateName))
    {
        QString plot_refer = "select check_num,password from " + m_mainTableDateName + " where id = '%1'";
        query.exec(QString(plot_refer).arg(_IDorDate));
        query.next();
        QString plotData = query.value(0).toString();
        QString _check_num = query.value(1).toString();

        strcpy(m_Data.password, plotData.toLatin1());
        strcpy(m_Data.check_num, _check_num.toLatin1());
        if(plotData.isEmpty())
        {
            //MyMessageBox::showMyMessageBox(this, QStringLiteral("友情提醒"), QStringLiteral("没有检索到相关数据!"), MESSAGE_WARNNING, BUTTON_OK, true);
            return false;
        }
        else
        {
            return true;
        }
    }
    else 
    {
        return false;
    }
    return true;
}

 /*!
*@brief: 判断表是否存在
*/
bool Search::tableExist(QString _tableName)
{
	QSqlQuery query(m_db);
    query.exec(QString("select count(*) from sqlite_master where type='table' and name='%1'").arg(_tableName));
    if(query.next())
    {
        if(!query.value(0).toInt() == 0)
        {
            return true;
        }
		else
		{
			return false;
		}
    }
	return true;
}
