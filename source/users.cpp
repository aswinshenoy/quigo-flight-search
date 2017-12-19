/*
	FILENAME : USERS.CPP
	DESCRIPTION: The file managing user/admin credentials
*/

/************************************************
*			   CLASS DEFINITION 	 			*
*				NAME : USER						*	
*		 		FILE : USERS.BIN				*
************************************************/
class user
{
	char username[25], password[35];
	public:
	char* returnuser(){ return username; }
	char* returnpass(){ return password; }
	void enter();
	void update(char* us, char* ps) { strcpy(username,us); strcpy(password,ps); }
};

user current_user; //holds for current user

void user::enter()
{
	   cout<<"Username: "; cin>>username;
	   cout<<"Password: "; getpass(password);
}

void add_user()
{
	ofstream fout;
	user s;
	fout.open("users.bin",ios::binary|ios::app);
	s.enter();
	fout.write((char*)&s,sizeof(user));
	fout.close();
}

void edit_user()
{
	fstream file;
	user u; int rec=0;
	char username[25];
	file.open("users.bin",ios::in|ios::out|ios::binary);
	cout<<"Enter Username: "; cin>>username;
	while(file.read((char*)&u,sizeof(u)))
	{
		if(strcmpi(u.returnuser(),username)==0)
		{
			u.enter();
			file.seekg(rec*sizeof(u),ios::beg);
			file.write((char*)&u,sizeof(u));
			cout<<"User Successfully Updated!"; getch();
		}
		rec++;
	}
	file.close();
}

void remove_user()
{
	ifstream fin;
	ofstream temp;
	user u;  char username[35];
	fin.open("users.bin",ios::in|ios::binary);
	temp.open("temp.bin",ios::out|ios::binary);
	cout<<"Enter Username: "; cin>>username;
	while(fin.read((char*)&u,sizeof(u)))
	{
		char *name = u.returnuser();
		if(strcmpi(name,username)==0)
		{	cout<<"Removed "<<username<<" successfully"; getch(); }
		else
			temp.write((char*)&u,sizeof(u));
	}
	temp.close();
	fin.close();
	remove("users.bin");
	rename("temp.bin", "users.bin");
}

//Function to check username
int check_user(char *un)
{
	ifstream fin;
	user s;
	fin.open("users.bin",ios::binary|ios::in);
	while(fin.read((char*)&s,sizeof(user)))
	{
		if(strcmpi(s.returnuser(),un)==0)
		return 1; //user exists
	}
	fin.close();
	return 0; //user not found
}

//Function to check password
int check_pass(char *un, char *pass)
{
	ifstream fin;
	user s;
	fin.open("users.bin",ios::binary|ios::in);
	while(fin.read((char*)&s,sizeof(user)))
	{
		if(strcmpi(s.returnuser(),un)==0)
			if(strcmp(s.returnpass(),pass)==0)
				return 1; //valid password
	}
	fin.close();
	return 0; //invalid password
}

/* FUNCTION TO ALLOW LOGIN TO ADMIN AREA */
user login()
{
    clrscr();
	user u;
	int uscheck=0, pscheck=0;
    char username[30], password[45];
    txy("LOGIN INTO QUIGO",maxx/2,10,50,1);
    do{
		clrln(12);
		txy("USERNAME: ",maxx/2,12,0,2);
		cin>>username;
		//checks username
		if(check_user(username))
		{
			uscheck=1; 
			do{
				clrln(12);
				txy("PASSWORD: ",maxx/2,12,0,2);
				getpass(password);
				//checks password
				if(check_pass(username,password))
				{
					pscheck=1;
					clrln(12); txy("LOGIN SUCCESSFUL!",maxx/2,12,50,1); delay(320);
					clrln(12); txy(strcat("Hello ",username),maxx/2,12,50,1); delay(320);
				}
				else { clrln(12); txy("INVALID PASSWORD!", maxx/2,12,60,1); getch(); }
			}while(pscheck!=1);
		}
		else { clrln(12); txy("INVALID USERNAME",maxx/2,12,60,1); getch(); }
    }while(uscheck!=1);
    getch();
	return u; //returns current user
}

/* Function to set up the first user */
void quigo_setup()
{
	ifstream file("users.bin");
	if(!file) //checks if any user exists
	{
		remove("flights.bin"); //protects data from unauthorised access
		clrscr();
		cout<<"QUIGO - SET UP\n\\n"
		cout<<"ENTER ADMIN DETAILS";
		add_user();
	}
	else
		file.close();
}

/* ADMIN AREA FUNCTIONS */
void admin_menu()
{
    int op;
    do{
	clrscr();
	txy("QUIGO - ADMIN AREA", maxx/2,7,45,1);
	txy("Add Flights",maxx/4,9,10);
	txy("Edit Flights",maxx/4,10,10);
	txy("Remove Flights",maxx/4,11,10);
	txy("View Flights",maxx/4,12,10);
	txy("Reset Flights",maxx/4,13,10);
	txy("Add User",maxx/4,14,10);
	txy("Edit User",maxx/4,15,10);
	txy("Remove User",maxx/4,16,10);
	txy("Log Out",maxx/4,17,10);
	op = selopy(maxx/4-3,9,17);
	clrscr();
	switch(op)
	{
		case 1: add_flight(); break;
		case 2: edit_flight(); break;
		case 3: remove_flight(); break;
		case 4: display_flights(); break;
		case 5: reset_flights(); break;
		case 6: add_user(); break;
		case 7: edit_user(); break;
		case 8: remove_user(); break;
		case 9: clrscr();
			txy("YOU HAVE BEEN LOGGED OUT!",maxx/2,maxy/2,60,1);
			getch();
			break;
	}
    }while(op!=9);
}
