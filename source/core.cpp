/*
	FILENAME : CORE.CPP
	DESCRIPTION: The file containing core functions required for quigo
	
*/

//Display Properties (differs for different emulators)
int maxx = 80; 
int maxy = 25;

/* Function to clear current line */
void clrln(int y, int x=0)
{
  for(int i=x; i<maxx; i++)
  { gotoxy(i,y); cout<<" "; }
}

/* Function to print a line */
void prntln(int y, int x=0)
{
  for(int i=x+1; i<maxx; i++)
  { gotoxy(i,y); cout<<"-"; }
}

/* Function to accept password */
void getpass(char *pass, int l=35)
{
	char ch;
	int i=0;
	while(1) //runs until enter is entered
	{
		ch=getch();
		if(ch==13) //checks for enter key
		{
			pass[i]='\0'; //ends with a null ch
			break;
		}
		else if(ch==8) //checks for backspace
		{
			cout<<"\b \b"; //removes asterisk printed
			if(i<l&&i>0)
				i--;  //one pos back
		}
		else if(i<(l-1))  //one ch is saved for null ch
		{
			cout<<"*"; //prints asterisk
			pass[i]=ch; //stores in referenced array
			i++;
		}
	}
}

/* Function that prints customized texts */
void txy(char *txt, int x, int y, int d=0, int a=0, int n=0)
{
	if(n==0) n=strlen(txt); //limiter

	if(a==1) x=x-n/2; //center
	if(a==2) x=x-n; //float right

	gotoxy(x,y);
	for(int i=0; i<n; i++)
	{ cout<<txt[i]; delay(d); }
	if(n<strlen(txt)) cout<<"...";
}

/* Select Option across Y-axis, using arrow keys */
int selopy(int x, int miny, int maxy, char *symbol=">>")
{
	int y = miny;
	int op;
	char ch;
	txy("USE U/D ARROW KEYS TO SELECT OPTION, PRESS ENTER KEY TO CONFIRM", ::maxx/2, ::maxy-2,0,1);
	do{
		txy(symbol,x,y); //pointer object
		ch = getch();
		op = (int)ch;
		txy("  ",x,y);

		if(op==80) //downward key
		{ if(y<maxy) y++;
		  else y=miny;
		}

		if(op==72) //upward key
		{ if(y>miny) y--;
		  else y=maxy;
		}
	}while(op!=13); //enter key
	return (y+1)-miny;
}

/* Select Option across X-axis, using arrow keys */
int selopx(char* options[], int xmin, int xmax, int y, int c)
{
	int x = xmin+4; c--;
	char ch;
	int op, i=0;
	txy("USE L/R ARROW KEYS TO SELECT OPTION, PRESS ENTER KEY TO CONFIRM", maxx/2,maxy-2,0,1);
	do{
		clrln(y,xmin);
		txy(options[i],x,y,0,0);
		if(i>0) { txy("<< ",xmin,y); }
		else txy("   ",xmin,y);
		if(i<c) { txy(" >>",xmax-4,y); }
		else txy("   ",xmax-4,y);
		ch = getch();
		op = (int)ch;

		if(op==77) //left key
		{
		  if(i<c) i++;
		}

		if(op==75) //right key
		{
		  if(i>0) i--;
		}
	}while(op!=13); //enter key
	return i;
}

/* Function to print time in 12hr format */
void prnttime(int time)
{
	//breaks up int carrying time to hr and min
	int pm=0;
	int hr = time/100;
	int min = time-(hr*100);

	if(hr>12) { hr=hr-12; pm=1; }
	else if(hr==12) { pm=1; }
	else if(hr==0)  { hr = 12; }
	if(hr<10) cout<<"0"; //adds 0 before single digits to improve look

	cout<<hr<<":"<<min;

	if(min<10) cout<<"0";
	//prints PM / AM indicator additionally
	if(pm!=1) cout<<" AM";
	else cout<<" PM";
}

/* Returns difference in time */
float timedif(int dept, int arr)
{
   return (float)abs(dept-arr)/100;
}


/* Function to show welcome screen */
void welcome_screen()
{
	clrscr();
	int x=maxx/2-33, y = maxy/2;
	//ASCII-BASED GRAPHICS (credits: chris.com)
	gotoxy(x,y-5); cout<<"                                 |									.";
	gotoxy(x,y-4); cout<<"                                 |									.";
	gotoxy(x,y-3); cout<<"                                 |									.";
	gotoxy(x,y-2); cout<<"                                _|_									.";
	gotoxy(x,y-1); cout<<"                               /___\\								 	.";
	gotoxy(x,y);   cout<<"                              /_____\\								.";
	gotoxy(x,y+1); cout<<"                             /oo   oo\\								.";
	gotoxy(x,y+2); cout<<" \\___________________________\\       /___________________________/  .";
	gotoxy(x,y+3); cout<<"  '-----------|------|--------\\_____/--------|------|-----------'	.";
	gotoxy(x,y+4); cout<<"             ( )    ( )     O|OOo|oOO|O     ( )    ( )				.";
	txy("QUIGO - ADVANCED FLIGHT SEARCH",maxx/2,y+8,45,1);
	txy("AN ASHWIN SHENOY PROJECT",maxx/2,y+10,75,1);
	delay(2500);
}

void quigo_logo(int x, int y)
{
	//ASCII-BASED COOL TEXT (credits: patorjk.com)
	gotoxy(x,y-5); cout<<"    ____    _    _   _____    _____    ____   		";
	gotoxy(x,y-4); cout<<"   / __ \\  | |  | | |_   _|  / ____|  / __ \\  		";
	gotoxy(x,y-3); cout<<"  | |  | | | |  | |   | |   | |  __  | |  | | 		";
	gotoxy(x,y-2); cout<<"  | |  | | | |  | |   | |   | | |_ | | |  | | 		";
	gotoxy(x,y-1); cout<<"  | |__| | | |__| |  _| |_  | |__| | | |__| | 		";
	gotoxy(x,y);   cout<<"   \\___\\_\\  \\____/  |_____|  \\_____|  \\____/  	";
}

void exit_screen()
{
	clrscr();
	quigo_logo(maxx/2-22,8);
	txy("THANKS FOR TRYING QUIGO! HAVE A COOL DAY",maxx/2,(maxy/2)-1,45,1);
	txy("SEND YOUR FEEDBACKS AT ASWINSHENOY@OUTLOOK.COM",maxx/2,(maxy/2)+1,45,1);
	delay(2500);
}
