//---------------------------------------------------------------------------
//Copyrighted by Luca Cavalleri e Matteo Cavalleri
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#pragma hdrstop

#include "uSafeQuery.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void TSafeQuery::AssignConnection(const std::shared_ptr<TSafeConnection>& ASafeConn) {
	RemoveConnection();
	TFDQuery::Connection = ASafeConn->Connection;
	_SharedConnection = ASafeConn;
	};
//---------------------------------------------------------------------------
	void TSafeQuery::AssignConnection(std::shared_ptr<TSafeConnection>&& ASafeConn) {
	RemoveConnection();
	TFDQuery::Connection = ASafeConn->Connection;
	_SharedConnection = std::move(ASafeConn);
	};
//---------------------------------------------------------------------------
void TSafeQuery::RemoveConnection() {
	if(TFDQuery::Connection)_SharedConnection->_Queries.erase(this);
	TFDQuery::Connection = nullptr;
	_SharedConnection.reset();
	};
//---------------------------------------------------------------------------
__fastcall TSafeQuery::~TSafeQuery() {
	RemoveConnection();
	};
//---------------------------------------------------------------------------




