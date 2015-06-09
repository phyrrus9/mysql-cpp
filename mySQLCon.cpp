/*
	class to manage a mysql connection. pretty simple.
*/

#include "mySQLCon.h"

unsigned int mySQLCon::getError() const { return m_errval; }

mySQLCon::mySQLCon()
{
	m_connected = false;
	m_errval = 0; //set to no error
	if ((mp_srvhandle = mysql_init((MYSQL *)NULL)) == NULL)
		m_errval |= E_INITFAIL;
}

mySQLCon::~mySQLCon()
{
	if (mp_srvhandle != (MYSQL *)NULL)
	{
		mysql_close(mp_srvhandle);
		mp_srvhandle = (MYSQL *)NULL;
	}
}

bool mySQLCon::connect(string host, string user, string pass)
{ return connect((char *)host.c_str(), (char *)user.c_str(), (char *)pass.c_str()); }

bool mySQLCon::connect(string host, string user, string pass, string db)
{ return connect((char *)host.c_str(), (char *)user.c_str(), (char *)pass.c_str(), (char *)db.c_str()); }

bool mySQLCon::connect(char *host, char *user, char *pass, char *db, int port)
{
	MYSQL *handle = (MYSQL *)NULL;
	if ((handle = mysql_real_connect(mp_srvhandle, host, user, pass, db, port, NULL, 0)
	    ) != mp_srvhandle)
	{
		m_errval &= ~E_CONNECTFAIL; //reset error flag
		if (handle == NULL)
			m_errval |= E_CONNECTFAIL;
		else if (m_connected)
		{
			m_errval |= E_CONNECTFAIL; //cannot hold two connections
			mysql_close(handle);
		}
		else
			mp_srvhandle = handle; //just replace it
	}
	m_connected = m_errval == 0;
	return m_connected;
}

void mySQLCon::close()
{
	if (!m_connected) return;
	mysql_close(mp_srvhandle);
	mp_srvhandle = (MYSQL *)NULL;
	m_connected = false;
}

mySQLResult *mySQLCon::query(string query)
{ return this->query((char *)query.c_str()); }

mySQLResult *mySQLCon::query(char *query)
{
	m_errval &= ~E_QUERYFAIL; //reset error flag
	mySQLResult *ret = (mySQLResult *)NULL;
	if (mysql_query(mp_srvhandle, (const char *)query) == 0)
		ret = new mySQLResult(mp_srvhandle);
	else
		m_errval |= E_QUERYFAIL;
	return ret;
}

