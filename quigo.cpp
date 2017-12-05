\*
Project Name: Quigo - Flight Search
Project URI: https://github.com/aswinshenoy/quigo-flight-search
Author: Ashwin Shenoy
Author URI: http://aswinshenoy.com/

Version: 1.2.1
License: MIT License
Copyright (c) 2017 ASHWIN SHENOY

Description: 
Quigo is an advanced C++ based flight-search engine,
which lets you finds the cheapest, earliest, and fastest flights
including connection flights easily using arrow-key based simplified UI

This C++ project is licensed under the MIT License.
Use it to make something cool, have fun, and share what you've learned with others.
*/

#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<dos.h>
#include<stdlib.h>

//Including Project Files
#include "gui.cpp"
#include "users.cpp"
#include "flights.cpp"
#include "search.cpp"

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

void admin_area()
{
	current_user = login();
	clrscr();
	if(current_user.returntype()==1)
		admin_menu();
	else { txy("You don't have permission to do this.", maxx/2, maxy/2); getch(); login();}
}

void main_menu()
{
	int op;
	do{
      clrscr();
      txy("QUIGO - FLIGHT SEARCH", maxx/4-4,10,45);
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

void main()
{
	clrscr();
	main_menu();
	getch();
}
