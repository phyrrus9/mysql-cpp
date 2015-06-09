/*
	parses a mysql query to organize the result
	into either a namedArray
*/

#include <stdlib.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <mysql/mysql.h>
#include "namedArray.h"

#ifndef MYSQLRESULT_H
#define MYSQLRESULT_H

using std::string;
using std::vector;

enum mySQLResultError {
			E_NORESULT	= 0x00000001};

class mySQLResult
{
private:
	bool m_multiresult; //true if returned array
	unsigned int m_errval;
	namedArray< namedArray<string> > *mp_results;
public:
	mySQLResult(MYSQL *inst);
	~mySQLResult();
	unsigned int getError() const;
	bool multiple() const;
	bool single() const;
	namedArray<string> operator[](unsigned int index) const;
	namedArray<string> get(unsigned int index) const;
	double toDouble(string in);
	int toInt(string in);
};

#endif
