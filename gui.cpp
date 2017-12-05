//Active Display Properties
int maxx = 80;
int maxy = 25;

/* Function to clear current line */
void clrln(int y, int x=0)
{
  for(int i=x; i<maxx; i++)
  { gotoxy(i,y); cout<<" "; }
}

/* Function to print line */
void prntln(int y, int x=0, char ch='-')
{
  for(int i=x+1; i<maxx; i++)
  { gotoxy(i,y); cout<<ch; }
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

/* Function to print customized texts */
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

/* Select option across Y-axis, using arrow keys */
int selopy(int x, int miny, int maxy)
{
	int y = miny;
	char ch;
	int op;
	txy("USE U/D ARROW KEYS TO SELECT OPTION, PRESS ENTER KEY TO CONFIRM", ::maxx/2, ::maxy-2,0,1);
	do{
		txy(">>",x,y); //pointer object
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

/* Select options across X-axis, using arrow keys */
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

/* Function to print int-based 24hr time to 12hr based time */
void prnttime(int time)
{
	//breaks up int carrying time to hr and min
	int pm=0;
	int hr = time/100;
	int min = time-(hr*100);
	if(hr>12) { hr=hr-12; pm=1; } //converts to 12hr format
	
    if(hr<10) cout<<"0";
	cout<<hr<<":"<<min;
	if(min==0) cout<<"0";	
    
	//prints PM / AM indicator additionally
	if(pm!=1) cout<<" AM";
	else cout<<" PM";
}

/* Returns difference in time */
float timedif(int dept, int arr)
{
   return abs(dept-arr)/100;
}
