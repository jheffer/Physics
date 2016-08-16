class result {

public:

	// Member variables

	unsigned long int timestamp;	// unix timestamp (integer, length 10)
	unsigned short int direction;	// direction flag
	unsigned long int countRef;	// number of fringes for each laser
	unsigned long int countTest;
	
	// Default constructor

	result()
	{
		timestamp = 0;
		direction = 0;
		countRef = 0;
		countTest = 0;
		cout << "Creating result at t = " << timestamp << endl;
	}

	// Parameterized constructor

	result(int a, int b, int c, int d)
	{
		timestamp = a;
		direction = b;
		countRef = c;
		countTest = d;
		cout << "Creating result at t = " << timestamp << endl;
	}

	// Destructor

	~result()
	{
		cout << "Destroying result with t = " << timestamp << endl;
	}

	// Echo the number of fringes

	void show()
	{
		cout << "Result (t = " << timestamp << "):" << endl;
		cout << "\tDirection: " << direction << endl;
		cout << "\tHeNe fringes: " << countRef << endl;
		cout << "\tTest laser fringes: " << countTest << endl;
	}

	/*
	int retRef() {return countRef;}
	int retTest() {return countTest;}
	int dir() {return direction;}
	*/

	/*
	// Method to a create a MySQL query string to insert a result to the database
	char insert()
	{
		char x [4096];
		sprintf(x, "%s", "INSERT INTO wavemeter `dir`=1, `count-ref`=countRef. `count-test`=CountTest");	
		return x;
	}
	*/
};
