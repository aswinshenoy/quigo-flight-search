class user
{
	char username[25], password[35];
	int type;
	public:
	char* returnuser(){ return username; }
	char* returnpass(){ return password; }
	int returntype(){ return type; }
	void enter();
	void update(char* us, char* ps) { strcpy(username,us); strcpy(password,ps); }
	void update(char* us, int t) { strcpy(username,us); type=t; }
	/* The above function is an example of function overloading */
};

user current_user;

void user::enter()
{
	   clrscr();
	   cout<<"Username: "; cin>>username;
	   cout<<"Password: "; getpass(password);
	   cout<<"Type: "; cin>>type;
}

void add_user()
{
	ofstream fout;
	user s;
	fout.open("user.dat",ios::binary|ios::app);
	s.enter();
	fout.write((char*)&s,sizeof(user));
	fout.close();
}

void edit_user()
{
	fstream file;
	user u; int rec=0;
	char username[25];
	file.open("users.dat",ios::in|ios::out|ios::binary);
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
	fin.open("users.dat",ios::in|ios::binary);
	temp.open("temp.dat",ios::out|ios::binary);
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
	remove("users.dat");
	rename("temp.dat", "users.dat");
}

int check_user(char *un)
{
	ifstream fin;
	user s;
	fin.open("user.dat",ios::binary|ios::in);
	while(fin.read((char*)&s,sizeof(user)))
	{
		if(strcmpi(s.returnuser(),un)==0)
		return 1;
	}
	fin.close();
	return 0;
}

int check_pass(char *un, char *pass)
{
	ifstream fin;
	user s;
	fin.open("user.dat",ios::binary|ios::in);
	while(fin.read((char*)&s,sizeof(user)))
	{
		if(strcmpi(s.returnuser(),un)==0)
			if(strcmp(s.returnpass(),pass)==0)
				return 1;
	}
	fin.close();
	return 0;
}

int get_type(char *un)
{
	ifstream fin;
	user s;
	fin.open("user.dat",ios::binary|ios::in);
	while(fin.read((char*)&s,sizeof(user)))
	{
		if(strcmpi(s.returnuser(),un)==0)
				return s.returntype();
	}
	fin.close();
	return -1;
}

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
		if(check_user(username))
		{
			uscheck=1;
			do{
				clrln(12);
				txy("PASSWORD: ",maxx/2,12,0,2);
				getpass(password);
				if(check_pass(username,password))
				{
					pscheck=1;
					clrln(12); txy("LOGIN SUCCESSFUL!",maxx/2,12,50,1); delay(320);
					clrln(12); txy(strcat("Hello ",username),maxx/2,12,50,1); delay(320);
					int type = get_type(username);
					u.update(username,type);
				}
				else { clrln(12); txy("INVALID PASSWORD!", maxx/2,12,60,1); getch(); }
			}while(pscheck!=1);
		}
		else { clrln(12); txy("INVALID USERNAME",maxx/2,12,60,1); getch(); }
    }while(uscheck!=1);
    getch();
	return u;
}
