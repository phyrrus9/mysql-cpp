/*
	parses a mysql query to organize the result
	into either a namedArray
*/

#include "mySQLResult.h"

mySQLResult::mySQLResult(MYSQL *inst)
{
	mp_results = new namedArray< namedArray<string> >;
	m_errval = 0; //clear all bits
	MYSQL_RES *result = mysql_store_result(inst);
	if (result != (MYSQL_RES *)NULL)
	{
		MYSQL_FIELD *fields = mysql_fetch_fields(result);
		MYSQL_ROW row;
		unsigned int col_count = mysql_field_count(inst); //get the fields
		vector<string> *cols = new vector<string>;
		//populate cols
		for (unsigned int i = 0; i < col_count; i++)
			cols->push_back(string(fields[i].name));
		//loop through results and insert as we go
		while ((row = mysql_fetch_row(result)) != (MYSQL_ROW)NULL)
		{
			namedArray<string> tmp_result;
			for (unsigned int i = 0; i < col_count; i++) //get the contents
			{
				tmp_result.insert(string(row[i] != NULL ? row[i] : "NULL"),
					cols->at(i));
			}
			mp_results->insert(tmp_result); //add it
		}
		//free memory
		delete cols;
		mysql_free_result(result);
	}
	else if (result == (MYSQL_RES *)NULL && mysql_errno(inst) == 0); //did not return a value do nothing
	else
		m_errval |= E_NORESULT;
}

mySQLResult::~mySQLResult()
{ delete mp_results; }

unsigned int mySQLResult::getError() const { return m_errval; }

bool mySQLResult::multiple() const { return m_multiresult; }

bool mySQLResult::single() const { return m_errval & ~E_NORESULT; }

namedArray<string> mySQLResult::operator[](unsigned int index) const
{ return get(index); }

namedArray<string> mySQLResult::get(unsigned int index) const
{ return mp_results->get(index); }

double mySQLResult::toDouble(string in)
{
	char *c = (char *)in.c_str();
	double ret;
	sscanf(c, "%lf", &ret);
	return ret;
}

int mySQLResult::toInt(string in)
{
	char *c = (char *)in.c_str();
	int ret;
	sscanf(c, "%d", &ret);
	return ret;
}
