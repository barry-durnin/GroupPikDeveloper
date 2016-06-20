#include "database.h"

#include <iostream>

namespace gdpserver
{
	namespace
	{
		void SQLiteErrorLogCallback(void *pArg, int iErrCode, const char *zMsg)
		{
			printf("(%d) %s\n", iErrCode, zMsg);
		}
	}

	sDatabase::sDatabase()
		: m_connection(nullptr)
	{
		Open();
	}

	sDatabase::~sDatabase()
	{
		Close();
	}

	bool sDatabase::ExecuteSQL(const std::string& sql)
	{
		std::unique_lock<std::mutex> l(m_mutex);

		char* error = nullptr;
		if (sqlite3_exec(m_connection, sql.c_str(), nullptr, nullptr, &error) != SQLITE_OK)
		{
			if (error)
			{
				std::cout << "SQL Error: " << error << "\n";
				sqlite3_free(error);
			}
			else
			{
				std::cout << "SQL Error: Unknown\n";
			}

			return false;
		}
		else
		{
			std::cout << "SQL success\n";
		}

		return true;
	}

	void sDatabase::Open()
	{
		sqlite3_open("gdpserver.db", &m_connection);
		sqlite3_config(SQLITE_CONFIG_LOG, SQLiteErrorLogCallback, this);

		// Obviously total nonsense.
		if (ExecuteSQL("create table user (name varchar(255), password varchar(255));"))
		{
			// Add some dummy data
			ExecuteSQL("insert into user (name, password) values (\"barry\", \"123\")");
			ExecuteSQL("insert into user (name, password) values (\"rob\", \"123\")");
		}
	}
	
	void sDatabase::Close()
	{
		sqlite3_close(m_connection);
		m_connection = nullptr;
	}
}