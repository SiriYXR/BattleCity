#include "ADBConnector.h"
#include "AFormat.h"
#include "mysql.h"
#include <map>

#pragma comment(lib,"libmysql")
#pragma warning(disable:4800)

ATHENA_BEGIN

template<class T,class U>
using DBMap = std::map<T,U>;

template<class T,class U>
using DBPair = std::pair<T, U>;

struct connectorData
{
	connectorData() :connection(nullptr),isOpen(false), port(0){}
	~connectorData()
	{
		if (connection != nullptr)
		{
			mysql_close(connection);
		}
	}
	DBString hostName;
	DBString dbName;
	DBString userName;
	DBString password;
	MYSQL *connection;
	unsigned int port;
	bool isOpen;
};

struct queryData
{
	queryData():currentRow(0),maxRow(0),row(nullptr),res(nullptr){}
	~queryData()
	{
		if (res)
		{
			mysql_free_result(res);
		}
	}
	DBMap<DBString, int> fieldToIndex;
	int currentRow;
	int maxRow;
	int fieldNum;
	MYSQL_ROW row;
	MYSQL_RES *res;
};

ADBConnector::ADBConnector()
{
	data = std::make_unique<connectorData>();
}

ADBConnector::ADBConnector(const DBString & hostName, const DBString & dbName, const DBString & userName, const DBString & password, unsigned int port)
{
	data = std::make_unique<connectorData>();
	connectTo(hostName,dbName,userName,password,port);
}

ADBConnector::ADBConnector(const ADBConnector &db)
{
	data = std::make_unique<connectorData>();
	*this = db;
}

ADBConnector::ADBConnector(ADBConnector &&db)
{
	data.swap(db.data);
}

void ADBConnector::setHostName(const DBString hostName)
{
	data->hostName = hostName;
}

void ADBConnector::setDBName(const DBString dbName)
{
	data->dbName = dbName;
}

void ADBConnector::setUserName(const DBString userName)
{
	data->userName = userName;
}

void ADBConnector::setPassword(const DBString password)
{
	data->password = password;
}

void ADBConnector::setPort(unsigned int port)
{
	data->port = port;
}

const DBString & ADBConnector::getHostName() const
{
	return data->hostName;
}

const DBString & ADBConnector::getDBName() const
{
	return data->dbName;
}

const DBString & ADBConnector::getUserName() const
{
	return data->userName;
}

const DBString & ADBConnector::getPassword() const
{
	return data->password;
}

DBString ADBConnector::getClientInfo() const
{
	return DBString(mysql_get_client_info());
}

DBString ADBConnector::getHostInfo() const
{
	return DBString(mysql_get_host_info(data->connection));
}

DBString ADBConnector::getServerInfo() const
{
	return DBString(mysql_get_server_info(data->connection));
}

DBString ADBConnector::getClientVersion() const
{
	int result = mysql_get_client_version();
	int major=result/10000;
	int release=(result/100)%100;
	int sub=result%100;
	
	char buffer[MSGLEN];
	format.printf(buffer,"%d.%d.%d",major,release,sub);

	return DBString(buffer);
}

DBString ADBConnector::getServerVersion() const
{
	int result = mysql_get_server_version(data->connection);
	int major = result / 10000;
	int release = (result / 100) % 100;
	int sub = result % 100;

	char buffer[MSGLEN];
	format.printf(buffer, "%d.%d.%d", major, release, sub);

	return DBString(buffer);
}

DBString ADBConnector::getCharacterSet() const
{
	return DBString(mysql_character_set_name(data->connection));
}

DBStringList ADBConnector::getAllDataBases(const DBString & wild) const
{
	auto result = mysql_list_dbs(data->connection,wild.c_str());

	if (result == nullptr)
	{
		return DBStringList();
	}

	int numOfResult = static_cast<int>(mysql_num_rows(result));
	DBStringList allDataBase(numOfResult);

	for (int i=0;i<numOfResult;i++)
	{
		allDataBase[i]=mysql_fetch_row(result)[0];
	}
	
	mysql_free_result(result);

	return allDataBase;
}

DBStringList ADBConnector::getAllTables(const DBString & wild) const
{
	auto result = mysql_list_tables(data->connection, wild.c_str());

	if (result == nullptr)
	{
		return DBStringList();
	}

	int numOfResult = static_cast<int>(mysql_num_rows(result));
	DBStringList allTable(numOfResult);

	for (int i = 0; i<numOfResult; i++)
	{
		allTable[i] = mysql_fetch_row(result)[0];
	}

	mysql_free_result(result);

	return allTable;
}

DBStringList ADBConnector::getAllFields(const DBString & table, const DBString & wild) const
{
	charBuffer buffer;
	format.printf(buffer.data(),"show columns from %s like \'%s\'",table.c_str(),wild.c_str());
	AQuery result=query(buffer.data());
	int num = result.rowNum();
	DBStringList allFields(num);
	for (int i = 0; i < num; i++)
	{
		result.next();
		allFields[i] = std::move(result[i]);
	}

	return allFields;
}

AQuery ADBConnector::query(const DBString &sql) const
{
	int result=mysql_query(data->connection, sql.c_str());
	if (result)
	{
		return AQuery();
	}

	AQuery query;
	query.data->res = mysql_store_result(data->connection);
	if (query.data->res == nullptr)
	{
		return query;
	}
	query.data->maxRow=static_cast<int>(mysql_num_rows(query.data->res));
	query.data->fieldNum = mysql_num_fields(query.data->res);
	MYSQL_FIELD *fields=mysql_fetch_fields(query.data->res);

	for (int i = 0; i < query.data->fieldNum; i++)
	{
		query.data->fieldToIndex.insert(DBPair<DBString,int>(fields[i].name,i));
	}

	return query;
}

unsigned int ADBConnector::getPort() const
{
	return data->port;
}

MYSQL * ADBConnector::origin() const
{
	return data->connection;
}

bool ADBConnector::isConnected() const
{
	return data->isOpen;
}

bool ADBConnector::connectToDefault()
{
	return connectTo(data->hostName,data->dbName,data->userName,data->password,data->port);
}

bool ADBConnector::connectTo(const DBString & hostName, const DBString & dbName, const DBString & userName, const DBString & password, unsigned int port)
{
	if (data->connection)
	{
		mysql_close(data->connection);
		data->connection = nullptr;
	}

	data->hostName = hostName;
	data->dbName = dbName;
	data->userName = userName;
	data->password = password;
	data->port = port;
	data->isOpen = false;

	data->connection = mysql_init(nullptr);
	if (data->connection != nullptr)
	{
		auto ok = mysql_real_connect(data->connection, data->hostName.c_str(),
			data->userName.c_str(), data->password.c_str(), data->dbName.c_str(), data->port, nullptr, 0);
		if (ok)
		{
			data->isOpen = true;
		}
	}

	return data->isOpen;
}

bool ADBConnector::changeUser(const DBString & dbName, const DBString & userName, const DBString & password)
{
	if (!data->isOpen)
	{
		return false;
	}

	return static_cast<bool>(mysql_change_user(data->connection, userName.c_str(), password.c_str(), dbName.c_str()));
}

bool ADBConnector::createDataBase(const DBString & dbName)
{
	if (data->isOpen)
	{
		DBString sql = "create database ";
		sql += dbName;
		return !mysql_query(data->connection,sql.c_str());
	}
	return false;
}

bool ADBConnector::dropDataBase(const DBString & dbName)
{
	if (data->isOpen)
	{
		DBString sql = "drop database ";
		sql += dbName;
		return !mysql_query(data->connection, sql.c_str());
	}
	return false;
}

bool ADBConnector::setCharacterSet(const DBString & charactorName)
{
	return !mysql_set_character_set(data->connection,charactorName.c_str());
}

bool ADBConnector::selectDataBase(const DBString & dbName)
{
	return !mysql_select_db(data->connection,dbName.c_str());
}

ADBConnector::~ADBConnector()
{

}

ADBConnector & ADBConnector::operator=(const ADBConnector &db)
{
	if (db.data->connection != nullptr)
	{
		connectTo(db.data->hostName, db.data->dbName, db.data->userName, db.data->password, db.data->port);
	}
	else
	{
		if (data->connection)
		{
			mysql_close(data->connection);
			data->connection = nullptr;
		}
		data->hostName = db.data->hostName;
		data->dbName = db.data->dbName;
		data->userName = db.data->userName;
		data->password = db.data->password;
		data->isOpen = db.data->isOpen;
		data->port = db.data->port;
	}

	return *this;
}

ADBConnector & ADBConnector::operator=(ADBConnector &&db)
{
	data.swap(db.data);
	return *this;
}

AQuery::AQuery()
{
	data = std::make_unique<queryData>();
}

AQuery::AQuery(AQuery &&db)
{
	data.swap(db.data);
}

AQuery::~AQuery()
{
}

AQuery & AQuery::operator=(AQuery &&db)
{
	data.swap(db.data);
	return *this;
}

bool AQuery::next()
{
	if (data->currentRow == data->maxRow)
	{
		return false;
	}

	data->row=mysql_fetch_row(data->res);
	data->currentRow++;

	return true;
}

bool AQuery::previous()
{
	if (data->currentRow == 0)
	{
		return false;
	}
	return seek(data->currentRow-1);
}

bool AQuery::seek(int pos)
{
	if (pos >= 0 && pos < data->maxRow)
	{
		mysql_data_seek(data->res,pos);
		data->row = mysql_fetch_row(data->res);
		data->currentRow = pos;
		return true;
	}

	return false;
}

int AQuery::tell() const
{
	return data->currentRow;
}

int AQuery::rowNum() const
{
	return data->maxRow;
}

int AQuery::fieldNum() const
{
	return data->fieldNum;
}

DBString AQuery::operator[](int index) const
{
	if (index < 0||index>=data->fieldNum)
	{
		throw AOutOfRange("AQuery::operator[](int):Index Out Of Range");
	}

	return DBString(data->row[index]);
}

DBString AQuery::operator[](const DBString & field) const
{
	return getValueByField(field);
}

DBString AQuery::getValueByField(const DBString & field) const
{
	auto result = data->fieldToIndex.find(field);
	if (result == data->fieldToIndex.end())
	{
		return DBString();
	}
	
	return DBString(data->row[result->second]);
}

DBStringList AQuery::getAllFields() const
{
	DBStringList result;
	result.reserve(data->fieldToIndex.size());

	for (auto &field : data->fieldToIndex)
	{
		result.push_back(field.first);
	}

	return result;
}

ATHENA_END

#pragma warning(default:4800)