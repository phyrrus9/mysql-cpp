/*
	class to manage a mysql connection. pretty simple.
*/

#include <string>
#include <mysql/mysql.h>
#include "mySQLResult.h" //so we can return from a query

#ifndef MYSQLCON_H
#define MYSQLCON_H

using std::string;

enum mySQLConError {
			E_INITFAIL	=	0x00000001,
			E_CONNECTFAIL	=	0x00000002,
			E_QUERYFAIL	=	0x00000004};

class mySQLCon
{
private:
	bool m_connected;
	unsigned int m_errval;
	MYSQL *mp_srvhandle;
public:
	unsigned int getError() const;
	mySQLCon();
	~mySQLCon();
	bool connect(string host, string user, string pass);
	bool connect(string host, string user, string pass, string db);
	bool connect(char *host, char *user, char *pass, char *db = NULL, int port = 0);
	void close();
	mySQLResult *query(string query);
	mySQLResult *query(char *query);
};

#endif
