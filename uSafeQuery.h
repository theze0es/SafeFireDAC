//---------------------------------------------------------------------------
//Copyrighted by Luca Cavalleri e Matteo Cavalleri
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#ifndef uSafeQueryH
#define uSafeQueryH
//---------------------------------------------------------------------------
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Phys.PG.hpp>
#include <FireDAC.Phys.PGDef.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Def.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FireDAC.Stan.Pool.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.VCLUI.Wait.hpp>
#include "uSafeConnection.h"
#include <memory>
#include <unordered_set>

/*
MC:
Classe che rappresenta la versione safe di TFDQuery.
Può essere ritornata da una TSafeConnection mediante MakeNewQuery() oppure
può essere istanzata indipendentemente e successivamente associata alla connessione
mediante AssignConnection()
*/


class TSafeConnection;

class TSafeQuery : public TFDQuery
{
public:
	using TFDQuery::TFDQuery;
	TSafeQuery() = delete;

	void AssignConnection(std::shared_ptr<TSafeConnection>&& ASafeConn);
	void AssignConnection(const std::shared_ptr<TSafeConnection>& ASafeConn);
	void RemoveConnection();
	__fastcall ~TSafeQuery();
	struct __null_type {}; __null_type Connection;

private:
	std::shared_ptr<TSafeConnection> _SharedConnection;
};

using TSharedSafeQuery = std::shared_ptr<TSafeQuery>;


#endif
