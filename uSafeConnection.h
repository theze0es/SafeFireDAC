//---------------------------------------------------------------------------
//Copyrighted by Luca Cavalleri e Matteo Cavalleri
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#ifndef uSafeConnectionH
#define uSafeConnectionH
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
#include "uSafeQuery.h"
#include <memory>
#include <unordered_set>

/*
MC:
Classe che istanza una TFDConnection "safe".
Può generare una versione "safe" di TFDQuery mediante MakeNewQuery();
*/

class TSafeQuery;

class TSafeConnection : public std::enable_shared_from_this<TSafeConnection>
{
friend class TSafeQuery;
public:

	__fastcall ~TSafeConnection();
	__fastcall TSafeConnection();
	std::shared_ptr<TSafeQuery> MakeNewQuery(const UnicodeString & ASQL, bool AActivateNow = false, UnicodeString AName="");
	std::shared_ptr<TSafeQuery> MakeNewQuery();
	TFDConnection* const Connection;
private:
	std::unordered_set<TSafeQuery*> _Queries;
};

using TSharedSafeConnection = std::shared_ptr<TSafeConnection>;
#define MakeSharedSafeConnection std::make_shared<TSafeConnection>()

#endif
