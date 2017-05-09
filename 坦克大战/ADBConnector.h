/*

Athena Classes Library For Microsoft Visual C++

Copyright @2016 CDU INnoVation Studio
All rights reserved.

文件名称：ADBConnector.h
摘要：
1.本文件含有MySQL数据库操作类的声明，实现在ADBConnector.cpp中。
2.ADBConnector类的对象能实现连接MySQL数据库，并执行相关的操作。
3.所有的功能均是对MySQL提供C API的封装。
4.通过ADBConnector来访问数据库并不会比纯C API慢，因为数据库的性能瓶颈在于数据库本身以及硬盘。

当前版本：V1.0
作者：余悦
e-mail：1397011447@qq.com
创建日期：2016年12月03日
更新日期：2016年12月26日

修正日志：

*/

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "ACore.h"

struct st_mysql;
typedef struct st_mysql MYSQL;

ATHENA_BEGIN

struct connectorData;
struct queryData;

using DBString=std::string;
using DBStringList = std::vector<DBString>;

class AQuery final
{
public:
	friend class ADBConnector;
public:
	AQuery();
	AQuery(const AQuery &)=delete;
	AQuery(AQuery &&);
	~AQuery();
	AQuery &operator=(const AQuery &) = delete;
	AQuery &operator=(AQuery &&);
	bool next();
	bool previous();
	bool seek(int pos);
	int tell() const;
	int rowNum() const;
	int fieldNum() const;
	DBString operator[](int index) const;
	DBString operator[](const DBString &field) const;
	DBString getValueByField(const DBString &field) const;
	DBStringList getAllFields() const;
protected:
	std::unique_ptr<queryData> data;
};

class ADBConnector final
{
public:
	ADBConnector();
	ADBConnector(const  DBString &hostName,const DBString &dbName,const DBString &userName,const DBString &password,unsigned int port=0);
	ADBConnector(const ADBConnector &);
	ADBConnector(ADBConnector &&);
	~ADBConnector();

	ADBConnector& operator=(const ADBConnector &);
	ADBConnector& operator=(ADBConnector &&);

	bool isConnected() const;//
	bool connectToDefault();
	bool connectTo(const DBString &hostName, const DBString &dbName, const DBString &userName, const DBString &password, unsigned int port = 0);//
	bool changeUser(const DBString &dbName, const DBString &userName, const DBString &password);
	bool createDataBase(const DBString &dbName);
	bool dropDataBase(const DBString &dbName);
	bool setCharacterSet(const DBString &charactorName);//
	bool selectDataBase(const DBString &dbName);

	void setHostName(const DBString hostName);
	void setDBName(const DBString dbName);
	void setUserName(const DBString userName);
	void setPassword(const DBString password);
	void setPort(unsigned int port=0);

	const DBString & getHostName() const;
	const DBString & getDBName() const;
	const DBString & getUserName() const;
	const DBString & getPassword() const;

	DBString getClientInfo() const;
	DBString getHostInfo() const;
	DBString getServerInfo() const;
	DBString getClientVersion() const;
	DBString getServerVersion() const;
	DBString getCharacterSet() const;

	DBStringList getAllDataBases(const DBString &wild=DBString()) const;
	DBStringList getAllTables(const DBString &wild = DBString()) const;
	DBStringList getAllFields(const DBString &table,const DBString &wild = DBString()) const;

	AQuery query(const DBString &) const;//

	unsigned int getPort() const;
	MYSQL *origin() const;
protected:
	std::unique_ptr<connectorData> data;
};

ATHENA_END
