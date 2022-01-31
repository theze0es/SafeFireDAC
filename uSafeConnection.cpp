//---------------------------------------------------------------------------
//Copyrighted by Luca Cavalleri e Matteo Cavalleri
//---------------------------------------------------------------------------


#pragma hdrstop

#include "uSafeConnection.h"
//---------------------------------------------------------------------------
__fastcall TSafeConnection::TSafeConnection() : Connection(new TFDConnection(nullptr)) {

}
//---------------------------------------------------------------------------

#pragma package(smart_init)
__fastcall TSafeConnection::~TSafeConnection() {
	for (auto i : _Queries) i->RemoveConnection();
	// M.M. 29/04/21
	delete Connection;

};
//---------------------------------------------------------------------------
std::shared_ptr<TSafeQuery> TSafeConnection::MakeNewQuery() {
		std::shared_ptr<TSafeQuery> newq (new TSafeQuery(nullptr));
		newq->AssignConnection(shared_from_this());
		return newq;
		};
//---------------------------------------------------------------------------
std::shared_ptr<TSafeQuery> TSafeConnection::MakeNewQuery(const UnicodeString & ASQL, bool AActivateNow , UnicodeString AName) {
	std::shared_ptr<TSafeQuery> newq=MakeNewQuery();
	newq->SQL->Add(ASQL);
	newq->Name=AName;
	if (AActivateNow) newq->Active=true;
	return newq;
}



