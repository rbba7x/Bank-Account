//Ryan Beebe 
//2018
//This project reads from a text file and creates a RAF file with bank account information

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Function prototypes
void DisplayRAF(string fname);
void copy_to_array();
void array_to_raf();
int display_menu();
void call_function(int choose);
void DisplayID(string fname);
void deposit_to_ID(string fname);
void withdrawl_from_ID(string fname);
void close_account();
void RAF_to_txt(string fname);

//Person structure has id, name, and balance
struct PERSON
{
	int ID;         //4 bytes
	string name;	//4 bytes
	float Balance;  //4 bytes 
};

PERSON st = { 0, "bbbb", 0.0 };
PERSON a[10];
fstream f;

//Displays the RAF file
void DisplayRAF(string fname)
{
	f.open(fname, ios::in |  ios :: out | ios::binary);
	cout << endl << "This is the content of " << fname << " file\n";
	f.read((char *)&st, sizeof(st));
	while (true)
	{
		cout << st.ID << "\t" << st.name << "\t" << st.Balance << endl;
		f.read((char *)&st, sizeof(st));
		
		if (st.ID == 0)
		{
			st.name = "bbbbbbbbbbbbbbb";
			st.Balance = 0.0;
		}
		if (f.fail()) break;
	}
	f.close();
}

//Displays the RAF file
void DisplayRAF1(string fname)
{
	f.open(fname, ios::in | ios::out | ios::binary);
	cout << endl << "This is the content of " << fname << " file\n";
	f.read((char *)&st, sizeof(st));
	while (true)
	{
		cout << st.ID << "\t" << st.name << "\t" << st.Balance << endl;
		f.read((char *)&st, sizeof(st));
		if (f.fail()) break;
	}
	f.close();
}

//Copies the txt file to an array
void copy_to_array()
{
	fstream g;
	g.open("input_file.txt", ios::in);
	
	for (int i = 0; i < 10; ++i)
	{
		g >> a[i].ID;
		g >> a[i].name;
		g >> a[i].Balance;

		if (a[i].ID == 0)
		{
			a[i].ID = 0;
			a[i].name = "bbbb";
			a[i].Balance = 0;
		}
	}
}

//Transfer data from the array to the raf
void array_to_raf()
{
	int pos;

	//copy data from array a into RAF. Use ID as a key value
	//fstream f;
	f.open("file.raf", ios::out | ios::binary);
	for (int i = 0; i < 10; ++i)
	{
		pos = (a[i].ID / 10 - 1) * sizeof(a[i]);//find the insertion position
		f.seekp(pos, ios::beg); // find the insertion position
		f.write((char *)&a[i], sizeof(a[i]));
	}
	f.close();
}

//Displays the menu and returns what option is chosen
int display_menu()
{
	int option;
	cout << "---------------------Bank of Americana-----------------" << endl;
	cout << "1.	Display all records from the RAF\n2.	Display a record when ID is given\n3.	Deposit in an account with a given ID";
	cout << "\n4.	Withdraw from an account with a given ID\n5.	Close an account for a given ID\n6.	Exit (copy the RAF into a text file)"<<endl;
	cin >> option;

	return option;
}

//Determines what function to call based off of user input
void call_function(int choose)
{
	switch (choose)
	{
	case 1: DisplayRAF("file.raf");
		break;
	case 2: DisplayID("file.raf");
		break;
	case 3: deposit_to_ID("file.raf");
		break;
	case 4: withdrawl_from_ID("file.raf");
		break;
	case 5: close_account();
		break;
	case 6: RAF_to_txt("file.raf");
		break;
	}
}

//Displays information for a user-entered ID
void DisplayID(string fname)
{
	int byteofset, id;

	cout << "Enter and ID to search for: ";
		cin >> id;
		
	f.open("file.raf", ios::in | ios::out | ios::binary);
	byteofset = ((id/ 10) - 1) * sizeof(st);
	f.seekg(byteofset, ios::beg); //Point to beginning
	f.read((char*)&st, sizeof(st));
	cout << st.ID << "\t" << st.name << "\t" << st.Balance << endl;
}

//Allows a deposit to an account
void deposit_to_ID(string fname)
{
	int byteofset, id;
	float deposit_amount;

	cout << "Enter and ID to search for: ";
		cin >> id;
	cout << "Enter the amount to deposit: ";
		cin >> deposit_amount;

	f.open("file.raf", ios::in | ios::out | ios::binary);
	byteofset = ((id / 10) - 1) * sizeof(st);
	f.seekg(byteofset, ios::beg); //Point to beginning
	f.read((char*)&st, sizeof(st));

	st.Balance = st.Balance + deposit_amount;

	cout << "Information for account #" << id << " had been updated and is displayed below." << endl;
	cout << st.ID << "\t" << st.name << "\t" << st.Balance << endl;
}

//Allows a withdrawl from an account
void withdrawl_from_ID(string fname)
{
	int byteofset, id;
	float withdrawl_amount;

	cout << "Enter and ID to search for: ";
	cin >> id;
	cout << "Enter the amount to withdrawl: ";
	cin >> withdrawl_amount;

	f.open("file.raf", ios::in | ios::out | ios::binary);
	byteofset = ((id / 10) - 1) * sizeof(st);
	f.seekg(byteofset, ios::beg); //Point to beginning
	f.read((char*)&st, sizeof(st));

	st.Balance = st.Balance - withdrawl_amount;

	cout << "Information for account #" << id << " had been updated and is displayed below." << endl;
	cout << st.ID << "\t" << st.name << "\t" << st.Balance << endl;
}

//Closes an account
void close_account()
{
	int byteofset, id;

	cout << "Enter the id of the account you wish to close: ";
	cin >> id;

	f.open("file.raf", ios::in | ios::out | ios::binary);
	byteofset = ((id / 10) - 1) * sizeof(st);
	f.seekg(byteofset, ios::beg); //Point to beginning
	f.read((char*)&st, sizeof(st));

	st.ID = 0;
	st.name = "bbbb";
	st.Balance = 0.0;

	cout << "Information for account #" << id << " had been updated and is displayed below." << endl;
	cout << st.ID << "\t" << st.name << "\t" << st.Balance << endl;
}

//Transfers data from the raf to the txt file
void RAF_to_txt(string fname)
{
	ofstream myfile;
	myfile.open("output_file.txt");

	f.open(fname, ios::in | ios::binary);
	myfile << endl << "This is the content of " << fname << " file\n";
	f.read((char *)&st, sizeof(st));
	while (true)
	{
		myfile << st.ID << "\t" << st.name << "\t" << st.Balance << endl;
		f.read((char *)&st, sizeof(st));
		if (f.fail()) break;

		else if (st.ID == 0)
		{
			st.name = "bbbbbbbbbbbbbbb";
			st.Balance = 0.0;
		}
	}
	f.close();
	myfile.close();
}

int main()
{
	int pos, choice;

	//Initialize file “file.raf” with dummy record st to hold 10 records
	fstream f;
	f.open("file.raf", ios::out | ios::binary); //open the file to write dummy record

	for (int i = 0; i <= 10; ++i)
	{
		f.write((char*)& st, sizeof(st));
	}
	f.close();
		
	DisplayRAF1("file.raf");

	for (int i = 0; i < 7; ++ i) {
		copy_to_array(); //Copy data from txt file to array
		array_to_raf();  //Copy data from array to raf
		choice = display_menu();
		call_function(choice);
	}
	system("pause");
	return 0;
}

/*------------------Output--------------------------
This is the content of file.raf file
0       bbbb    0
0       bbbb    0
0       bbbb    0
0       bbbb    0
0       bbbb    0
0       bbbb    0
0       bbbb    0
0       bbbb    0
0       bbbb    0
0       bbbb    0
0       bbbb    0
---------------------Bank of Americana-----------------
1.      Display all records from the RAF
2.      Display a record when ID is given
3.      Deposit in an account with a given ID
4.      Withdraw from an account with a given ID
5.      Close an account for a given ID
6.      Exit (copy the RAF into a text file)
1

This is the content of file.raf file
10      Nixon,Kathy     100.1
20      Reagan,Ron      200.2
30      Clinton,Bill    300.3
40      Bush,Barbra     400.4
50      Carter,Jimmy    500.5
60      Bush,George     600.6
0       bbbbbbbbbbbbbbb        0
0       bbbbbbbbbbbbbbb        0
90      Obama,Barack    900.9
---------------------Bank of Americana-----------------
1.      Display all records from the RAF
2.      Display a record when ID is given
3.      Deposit in an account with a given ID
4.      Withdraw from an account with a given ID
5.      Close an account for a given ID
6.      Exit (copy the RAF into a text file)
1

This is the content of file.raf file
10      Nixon,Kathy     100.1
20      Reagan,Ron      200.2
30      Clinton,Bill    300.3
40      Bush,Barbra     400.4
50      Carter,Jimmy    500.5
60      Bush,George     600.6
0       bbbbbbbbbbbbbbb        0
0       bbbbbbbbbbbbbbb        0
90      Obama,Barack    900.9
---------------------Bank of Americana-----------------
1.      Display all records from the RAF
2.      Display a record when ID is given
3.      Deposit in an account with a given ID
4.      Withdraw from an account with a given ID
5.      Close an account for a given ID
6.      Exit (copy the RAF into a text file)
2
Enter and ID to search for: 30
30      Clinton,Bill    300.3
---------------------Bank of Americana-----------------
1.      Display all records from the RAF
2.      Display a record when ID is given
3.      Deposit in an account with a given ID
4.      Withdraw from an account with a given ID
5.      Close an account for a given ID
6.      Exit (copy the RAF into a text file)
3
Enter and ID to search for: 10
Enter the amount to deposit: 99.91
Information for account #10 had been updated and is displayed below.
10      Nixon,Kathy     200.01
---------------------Bank of Americana-----------------
1.      Display all records from the RAF
2.      Display a record when ID is given
3.      Deposit in an account with a given ID
4.      Withdraw from an account with a given ID
5.      Close an account for a given ID
6.      Exit (copy the RAF into a text file)
4
Enter and ID to search for: 90
Enter the amount to withdrawl: 900.89
Information for account #90 had been updated and is displayed below.
90      Obama,Barack    0.0100098
---------------------Bank of Americana-----------------
1.      Display all records from the RAF
2.      Display a record when ID is given
3.      Deposit in an account with a given ID
4.      Withdraw from an account with a given ID
5.      Close an account for a given ID
6.      Exit (copy the RAF into a text file)
5
Enter the id of the account you wish to close: 50
Information for account #50 had been updated and is displayed below.
0       bbbb    0
-------------------- - Bank of Americana---------------- -
1.      Display all records from the RAF
2.      Display a record when ID is given
3.      Deposit in an account with a given ID
4.      Withdraw from an account with a given ID
5.      Close an account for a given ID
6.      Exit(copy the RAF into a text file)
6

Output_fle.txt:
This is the content of file.raf file
10	Nixon,Kathy	100.1
20	Reagan,Ron	200.2
30	Clinton,Bill	300.3
40	Bush,Barbra	400.4
50	Carter,Jimmy	500.5
60	Bush,George	600.6
0	bbbbbbbbbbbbbbb	0
0	bbbbbbbbbbbbbbb	0
90	Obama,Barack	900.9
*/