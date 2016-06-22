#include "database.h"

#include <iostream>

namespace gdpserver
{
	static int TestCallBack(void *param, int argc, char **argv, char **azColName)
	{
		sDatabase* pDB = reinterpret_cast<sDatabase*>(param);
		return pDB->SqlCBUsersExists(argc, argv, azColName);
	}

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

		return true;
	}

	bool sDatabase::ExecuteSQLCallback(const std::string& sql, SqlCallback functionCallBack, void *pOwner)
	{
		std::unique_lock<std::mutex> l(m_mutex);

		char* error = nullptr;
		if (sqlite3_exec(m_connection, sql.c_str(), functionCallBack, pOwner, &error) != SQLITE_OK)
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

		return true;
	}

	int sDatabase::SqlCBUsersExists(int argc, char **argv, char **azColName)
	{
		std::cout << "Test expected arg count is 2 Actual: " << argc << std::endl;
		for (int i = 0; i < argc; ++i)
		{
			std::cout << azColName[i] << std::endl;
			std::cout << argv[i] << std::endl;
		}
		return 0;
	}

	void sDatabase::Open()
	{
		sqlite3_open("gdpserver.db", &m_connection);
		sqlite3_config(SQLITE_CONFIG_LOG, SQLiteErrorLogCallback, this);

		


		if (!ExecuteSQL("create table if not exists user (name varchar(255), password varchar(255));"))
		{
			std::cout << "User tabled has not been created! Critical error" << std::endl;
			// Add some dummy data
			//ExecuteSQL("insert into user (name, password) values (\"barry\", \"123\")");
			//ExecuteSQL("insert into user (name, password) values (\"rob\", \"123\")");
		}
		else
		{
			if (!ExecuteSQLCallback("select * from user", TestCallBack, this))
			{
				std::cout << "Error!!!!!";
			}
		}
	}
	
	void sDatabase::Close()
	{
		sqlite3_close(m_connection);
		m_connection = nullptr;
	}
}