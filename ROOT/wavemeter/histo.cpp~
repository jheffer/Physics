#include <mysql.h>
//#include <iostream>
#include <vector>
#include "TH1I.h"
#include "classes.h"

void histo(){

	mysql();

	//vector<result> myResults;

	/* Doesn't work.
		myClass bob;
		cout << bob.show() << endl;

		vector<myClass*> myVector;
	*/

	/* This works.
		vector<int> myInts;

		myInts.push_back(1);
		myInts.push_back(44);
		myInts.push_back(3);

		vector<int>::iterator iter;
		for(iter = myInts.begin(); iter<myInts.end(); ++iter)
			cout << *iter << endl;
	*/

	// Create results
	/*
	for(int i = 0; i<numResults; i++)
	{
		results[i] = new result(1366622900 + i, 0, rand() % 10, rand() % 10);
	}
	*/

	//results[0] = new result(1366622900, 0, 1134);
	//results[0]->show();
	//results.push_back(result(1366622900, 0, 1134));

	/* Connect to MySQL database */

	// Useful variables for MySQL handling

	TSQLRow * row;
	TSQLResult * res;	// pointer: memory address of a TSQLResult
	char * sql = new char [BUFSIZE];	// pointer to first letter of array of type 'char'
	const int BUFSIZE = 4096;	

	// Settings
	const char * url = "mysql://hep.ph.liv.ac.uk:3306/Interferometry";
	const char * user = "interf"; //"interfview";
	const char * pass = "5mo-5NPJp8"; //"klPoI1lCZM";
	const char * db = "Interferometry";
	const char * tab = "wavemeter";
	const int BUFSIZE = 4096;

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

	/* Get results from table and fill histogram */

	// Create histograms

	TH1I * hist1 = new TH1I("hist1",
		"HeNe laser;Number of fringes;Frequency",
		10, 631996, 632004);
	TH1I * hist2 = new TH1I("hist2",
		"Unknown laser;Number of fringes;Frequency",
		10, 779996, 780004);

	// Retrieve and process data

	sprintf(sql, "%s", "SELECT * FROM wavemeter");
	res = con->Query(sql);
	errChk(res);
	//const int numResults = 4;
	//result * myResults[numResults];
	while(row = res->Next())
	{
		hist1->Fill(atoi(row->GetField(3)));	// atof to convert char to double
		hist2->Fill(atoi(row->GetField(4)));
		//printf("%s", row->GetField(1));
		//printf("\t%s", row->GetField(3));
		//printf("\t%s\n", row->GetField(4));
		//printf("\t%s\n", row->GetField(4));
		//result r1(time(0), row->getField(0), row->getField(1), row->getField(1));
		//r1.show();
	}

	/* Draw histograms */

	// Draw HeNe histogram
	
	hist1->SetStats(kTRUE);	// disable histogram statistics box
	hist1->SetFillColor(44);
	hist1->SetLineColor(1);
	TAxis * axis1 = hist1->GetXaxis();
	axis1->SetNoExponent(kTRUE);
	axis1->SetNdivisions(10);
//	axis1->SetLabelOffset(0);
//	axis1->SetTitleOffset(0);
	hist1->Draw();


	/*
	// legend

	Double_t xl1=0.78, yl1=0.85, xl2=xl1+.2, yl2=yl1+.1;
	TLegend * leg = new TLegend(xl1,yl1,xl2,yl2);
	leg->AddEntry(hist1,"HeNe laser","F");
	leg->AddEntry(hist2,"Unknown laser","F");
	leg->Draw();
	*/

	// export to jpg file

	c1->SaveAs("histHeNe.jpg");	// c1 is the default canvas

	// Draw laser histogram

	hist2->SetStats(kTRUE);
	hist2->SetFillColor(36);
	hist2->SetLineColor(1);
	TAxis * axis2 = hist2->GetXaxis();
	axis2->SetNoExponent(kTRUE);
	axis2->SetNdivisions(10);
	hist2->Draw();

	// export to jpg file

	c1->SaveAs("histTest.jpg");

	// clean up dynamic memory allocation
	delete con;
	delete sql;
   	delete res;
	delete row;
	delete axis1;
	delete axis2;
	delete hist1;
	delete hist2;
}

