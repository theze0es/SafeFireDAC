# SafeFireDAC
A couple of classes that enables the use of smart pointers with FireDAC in C++ (TFDConnection and TFDQuery) 

Put a connection on the stack

	TSharedSafeConnection c2=MakeSharedSafeConnection;
	c2->Connection->DriverName="PG";
	c2->Connection->LoginPrompt=false;
	c2->Connection->ConnectionDefName="cdr";
	c2->Connection->Params->Password="password-example";
	c2->Connection->Params->UserName="postgres";
	c2->Connection->Connected=true;

How to use it:

	{
	//executes a query on the stack
	TSharedSafeQuery q4 = c2->MakeNewQuery("select count(*) as cnt from cdr.utenti",true);
	ShowMessage(q4->FieldByName("cnt")->AsString+" con q4");
	}
	//now q4 does not exists anymore.

Executing a query on the stack adjusting some parameters

	TSharedSafeQuery q3 = c2->MakeNewQuery("select count(*) as cnt from cdr.utenti");
	q3->UpdateOptions->AutoIncFields="key_operatore";
	q3->Active=true;
	ShowMessage(q3->FieldByName("cnt")->AsString+" con q3");


A less direct way:

	std::shared_ptr<TSafeConnection> c = std::make_shared<TSafeConnection>();
	c->Connection->DriverName="PG";
	c->Connection->LoginPrompt=false;
	c->Connection->ConnectionDefName="cdr";
	c->Connection->Params->Password="password-example";
	c->Connection->Params->UserName="postgres";
	c->Connection->Connected=true;

	std::shared_ptr<TSafeQuery> q1 = c->MakeNewQuery();
	q1->SQL->Add("select count(*) as cnt from cdr.utenti");
	q1->Active=true;
	ShowMessage(q1->FieldByName("cnt")->AsString+" con q1");


A more indirect way:

	std::shared_ptr<TSafeQuery> q2 (new TSafeQuery(nullptr));
	q2->AssignConnection(c);
	q2->SQL->Add("select count(*) as cnt from cdr.utenti");
	q2->Active=true;
	ShowMessage(q2->FieldByName("cnt")->AsString+" con q2");

