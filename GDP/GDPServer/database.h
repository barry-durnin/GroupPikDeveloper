#pragma once

#include <mutex>
#include <sqlite3.h>
#include <string>

namespace gdpserver
{
	class sDatabase
	{
	public:
		sDatabase();
		~sDatabase();

		bool ExecuteSQL(const std::string& sql);

	private:
		void Open();
		void Close();

		sqlite3*	m_connection;
		std::mutex	m_mutex;
	};
}