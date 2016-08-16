#include <TSQLServer.h>
//#include <TMySQLServer.h>
#include <TSQLResult.h>
#include <TSQLRow.h>
//#include <TList.h>
#include "classes.h"

// Check that a MySQL query was performed successfully.
void errChk(TSQLResult * x)
{
	if(x == 0)
	{
		cout << "Error (res = " << *x << "): query failed."<< endl;
	}
	else
	{
		//cout << "Query OK." << endl;
	}
}

/*
TSQLResult sqlQuery(TSQLServer * x, char * query)
{
	cout << "Flag A" << endl;
	TSQLResult * y = x->Query(query);
	cout << "Flag B" << endl;
	errChk(y);
	cout << "Flag C" << endl;
	return y;
}
*/

// Display a result with d columns
void showRes(TSQLResult * x, int d)
{
	TSQLRow * y;
	char z [4096];
	sprintf(z, "");
	while(y = x->Next())
	{
		for(unsigned short int i = 0; i < d; i++)
		{
			sprintf(z, "%s\t%s", z, y->GetField(i));	
		}
	cout << z << endl;
	sprintf(z, "");
	}
}

void mysql()
{
	// Settings
	const char * url = "mysql://hep.ph.liv.ac.uk:3306/Interferometry";
	const char * user = "interf"; //"interfview";
	const char * pass = "5mo-5NPJp8"; //"klPoI1lCZM";
	const char * db = "Interferometry";
	const char * tab = "wavemeter";
	const int BUFSIZE = 4096;

	// Connect to MySQL database
	TSQLServer * con = TSQLServer::Connect(url, user, pass);
	if(con == 0)
	{
		cout << "Error (con = " << con << "): failed to connect to MySQL database." << endl;
	}
	else
	{
		// Success: report server info
		printf("Connected to server \"%s\"", con->ServerInfo());
		printf(" on host %s\n", con->GetHost());
	}

	// Useful variables
	TSQLRow * row;
	TSQLResult * res;	// pointer: memory address of a TSQLResult
	char * sql = new char [BUFSIZE];	// pointer to first letter of array of type 'char'

	// List tables
   	cout << "Database \"" << db << "\" contains tables:" << endl;
	sprintf(sql, "%s", "SHOW TABLES");	// int sprintf (char * str, const char * format, ... );
	//res = sqlQuery(con, sql);	// con = address of connection. sql = address of first letter in array 'sql'
	res = con->Query(sql);
	errChk(res);
	showRes(res, 1);

	// List table info
   	cout << "Table 'wavemeter' info:" << endl;
	sprintf(sql, "%s", "DESCRIBE wavemeter");
	res = con->Query(sql);
	errChk(res);
	cout << "\tField\tType\tNULL\tKey\tDefault\tExtra" << endl;
	cout << "\t__________________________________________________________________" << endl;
	showRes(res, 3);	

	/*
	// Create a result
	result r1 = result(time(0), 1, 632000, 780001);

	// insert into database
	snprintf(sql, BUFSIZE-1,
		"INSERT INTO %s (dir, countRef, countTest) VALUES(%d, %d, %d)",
		tab, r1.direction, r1.countRef, r1.countTest);
	res = con->Query(sql);
	errChk(res);
	*/

	// Display contents of our table
	sprintf(sql, "%s", "SELECT * FROM wavemeter");
	res = con->Query(sql);
	errChk(res);
	cout << "\n\tid\ttime\t\t\tdir\t\HeNe\tUnknown" << endl;
	cout << "\t__________________________________________________________________" << endl;
	showRes(res, 5);

	// clean up
	delete con;
	delete sql;
   	delete res;
	delete row;
}
