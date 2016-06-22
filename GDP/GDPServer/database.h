#pragma once

#include <mutex>
#include <sqlite3.h>
#include <string>

namespace gdpserver
{
	typedef int (*SqlCallback)(void*, int, char**, char**);
	class sDatabase
	{
	public:
		sDatabase();
		~sDatabase();

		bool ExecuteSQL(const std::string& sql);
		bool ExecuteSQLCallback(const std::string& sql, SqlCallback functionCallBack, void* pOwner);

		int SqlCBUsersExists(int argc, char **argv, char **azColName);
	private:
		void Open();
		void Close();
		sqlite3*	m_connection;
		std::mutex	m_mutex;
	};
}