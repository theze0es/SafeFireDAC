# SafeFireDAC
A couple of classes that enables the use of smart pointers with FireDAC in C++ (TFDConnection and TFDQuery) 

Put a connection on the stack

	TSharedSafeConnection sf=MakeSharedSafeConnection;
	sf->Connection->DriverName="PG";
	sf->Connection->LoginPrompt=false;
	sf->Connection->ConnectionDefName="mydb";
	sf->Connection->Params->Password="password-example";
	sf->Connection->Params->UserName="postgres";
	sf->Connection->Connected=true;

Quick and simple use:

	{
	//executes a query on the stack
	TSharedSafeQuery q4 = sf->MakeNewQuery("select count(*) as cnt from cdr.utenti",true);
	ShowMessage(q4->FieldByName("cnt")->AsString+" con q4");
	}
	//now q4 does not exists anymore.

Quick and simple use with some SQL parameters:

	TSharedSafeQuery q3 = sf->MakeNewQuery("select count(*) as cnt from cdr.utenti where username=:user");
	q3->UpdateOptions->AutoIncFields="key_operatore";
	q3->ParamByName("user")->AsString="Bob";
	q3->Active=true;
	ShowMessage(q3->FieldByName("cnt")->AsString+" con q3");

That is. 
If you're interested in a less direct way:

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


Or even a more indirect way:

	std::shared_ptr<TSafeQuery> q2 (new TSafeQuery(nullptr));
	q2->AssignConnection(c);
	q2->SQL->Add("select count(*) as cnt from cdr.utenti");
	q2->Active=true;
	ShowMessage(q2->FieldByName("cnt")->AsString+" con q2");

