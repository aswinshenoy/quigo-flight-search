/*
				   ____    _    _   _____    _____    ____  
				  / __ \  | |  | | |_   _|  / ____|  / __ \ 
				 | |  | | | |  | |   | |   | |  __  | |  | |
				 | |  | | | |  | |   | |   | | |_ | | |  | |
				 | |__| | | |__| |  _| |_  | |__| | | |__| |
				  \___\_\  \____/  |_____|  \_____|  \____/ 
																								
Project Name: Quigo - Flight Search
Project URI: https://github.com/aswinshenoy/quigo-flight-search
Author: Ashwin Shenoy
Author URI: http://aswinshenoy.com/

Version: 1.3
License: MIT License
Copyright (c) 2017 ASHWIN SHENOY

Description: 
Quigo is an advanced C++ based flight-search engine,
which lets you finds the cheapest, earliest, and fastest flights
including connection flights easily using arrow-key based simplified UI

This C++ project is licensed under the MIT License.
Use it to make something cool, have fun, and share what you've learned with others.
*/

/*
	FILENAME : QUIGO.CPP
	DESCRIPTION: The main-program file
*/

/* HEADER FILES */
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<dos.h>
#include<stdlib.h>

/* FUNCTION FILES (REQUIRED, in order) */
#include "core.cpp"
#include "flights.cpp"
#include "users.cpp"
#include "search.cpp"


/* DISPLAYS ATTACHED DOCUMENTATION FILE*/
void about_quigo()
{
	clrscr();
	ifstream fin("quigo.txt");
	char s[80];
	while(!fin.eof())
	{
		fin.getline(s,80);
		cout<<s<<endl;
	}
	getch();
	fin.close();
}

/* ACESS FUNCTION TO ADMIN AREA */
void admin_area()
{
	current_user = login();
	clrscr();
	admin_menu();
}

/* FUNCTION FOR MAIN MENU */
void main_menu()
{
	int op;
	do{
		clrscr();
		quigo_logo(maxx/2-22,8);
		txy("MAIN MENU",maxx/4-3,11);
		txy("Search Flights",maxx/4,12,30);
		txy("About Quigo",maxx/4,13,30);
		txy("Admin Area",maxx/4,14,30);
		txy("Exit",maxx/4,15,30);
		op = selopy(maxx/4-3,12,15);
		switch(op)
		{
			case 1: flight_search();  break;
			case 2: about_quigo(); break;
			case 3: admin_area();
		}
    }while(op!=4);	
}

/* THE MAIN FUNCTION */
void main()
{
	welcome_screen();
	quigo_setup();
	main_menu();
	exit_screen();
}
