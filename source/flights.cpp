/*
	FILENAME : FLIGHTS.CPP
	DESCRIPTION: File holding the class - FLIGHT, and other functions associated
	
*/

/************************************************
*			   CLASS DEFINITION 	 			*
*				NAME : FLIGHT					*
*		 		FILE : FLIGHTS.BIN				*
************************************************/

class flight
{
	float fare;
	public:
	int code;
	float arrival, departure; 
	char airline[5], source[5], dest[5];
	float getfare(){return fare;}
	void new_flight();
	void update_flight();
	void display_flight(int);
	void show_flightdetails(int,int);
};

/* MEMEBER FUNCTION TO ADD NEW FLIGHTS */
void flight::new_flight()
{
	cout<<"Enter Flight Details\n";
	cout<<"Flight Code: "; cin>>code;
	cout<<"Airline Code: "; cin>>airline;
	cout<<"Source: "; cin>>source;
	cout<<"Departure Time(in 24hr) : "; cin>>departure;
	cout<<"Destination: "; cin>>dest;
	cout<<"Arrival Time(in 24hr) : "; cin>>arrival;
	cout<<"Fare: "; cin>>fare;
}

/* MEMEBER FUNCTION TO UPDATE FLIGHTS */
void flight::update_flight()
{
	//Flight Code is non-updatable identifier
	cout<<"Airline Code: "; cin>>airline;
	cout<<"Source: "; cin>>source;
	cout<<"Departure Time(in 24hr) : "; cin>>departure;
	cout<<"Destination: "; cin>>dest;
	cout<<"Arrival Time(in 24hr) : "; cin>>arrival;
	cout<<"Fare: "; cin>>fare;
}

/* MEMEBER FUNCTION TO DISLAY FLIGHTS IN COLUMN WISE */
void flight::display_flight(int y)
{
	gotoxy(2,y); cout<<airline<<code;
	gotoxy((maxx/6),y); cout<<source;
	gotoxy((maxx/6)*2,y); cout<<departure; 
	gotoxy((maxx/6)*3,y); cout<<dest;
	gotoxy((maxx/6)*4,y); cout<<arrival;   
	gotoxy((maxx/6)*5,y); cout<<fare;
	//time is displayed in default int format, for error-detection
}

/* MEMBER FUNCTION TO SHOW FLIGHT DETAILS IN RESULTS PAGE */
void flight::show_flightdetails(int x, int y)
{
	txy("CODE: ",x,y-7); cout<<airline<<code;
	txy("SOURCE: ",x,y-5); cout<<source;
	txy("DEPARTURE: ",x,y-4); prnttime(departure);
	txy("DESTINATION: ",x,y-2); cout<<dest;
	txy("ARRIVAL: ",x,y-1); prnttime(arrival);
	txy("DURATION: ",x,y+2); cout<<timedif(departure,arrival)<<"hrs";
	txy("FARE: Rs.",x,y+3); cout<<fare;
}

/* FUNCTION TO ADD NEW FLIGHT */
void add_flight()
{
	ofstream fout;
	flight f;
	fout.open("flights.bin",ios::app|ios::binary);
	f.new_flight();
	fout.write((char*)&f,sizeof(f));
	fout.close();
}

/* FUNCTION TO EDIT EXISTING FLIGHT INFORMATION */
void edit_flight()
{
	fstream file;
	flight f; int fcode, rec=0;
	file.open("flights.bin",ios::in|ios::out|ios::binary);
	cout<<"Enter Flight Code: "; cin>>fcode;
	while(file.read((char*)&f,sizeof(f)))
	{
		if(f.code==fcode)
		{
			f.update_flight();
			file.seekg(rec*sizeof(f),ios::beg);
			file.write((char*)&f,sizeof(f));
			cout<<"Flight Successfully Updated!"; getch();
		}
		rec++;
	}
	file.close();
}

/* FUNCTION TO DELETE FLIGHT */
void remove_flight()
{
	ifstream fin;
	ofstream temp;
	flight f; int fcode, flag=0;
	fin.open("flights.bin",ios::in|ios::binary);
	temp.open("temp.bin",ios::out|ios::binary);
	cout<<"Enter Flight Code: "; cin>>fcode;
	while(fin.read((char*)&f,sizeof(f)))
	{
		if(f.code==fcode)
		{	
			cout<<"PRESS ENTER TO CONFIRM DELETION, ANY OTHER KEY TO CANCEL";
			char ch = getch();
			clrscr();
			flag=1;
			if((int)ch=='13')
				cout<<"Deleted the flight - "<<f.airline<<f.code<<" successfully";
			else 
			{
				cout<<"The flight was not deleted.";
				temp.write((char*)&f,sizeof(f));
			}	
			getch();
		}
		else
			temp.write((char*)&f,sizeof(f));
	}
	temp.close();
	fin.close();
	remove("flights.bin");
	rename("temp.bin", "flights.bin");
	if(flag==0) { cout<<"The flight was not found, and not deleted."; }
}

/* FUNCTION TO DISPLAY ALL FLIGHTS (in admin area) */
void display_flights()
{
	ifstream fin;
	flight f;
	int y=4, flag=0;
	txy("CODE",2,y);
	txy("SOURCE",(maxx/6),y);
	txy("DEPARTURE",(maxx/6)*2,y);
	txy("DESTINATION",(maxx/6)*3,y);
	txy("ARRIVAL",(maxx/6)*4,y);
	txy("FARE",(maxx/6)*5,y);
	y++;
	fin.open("flights.bin",ios::in|ios::binary);
	while(fin.read((char*)&f,sizeof(f)))
	{
		y++; flag=1;
		f.display_flight(y);
	}
	if(flag==0) txy("No Flights Found!",0,++y,60);
	getch();
	fin.close();
}

/* FUNCTION TO REMOVE ALL FLIGHTS */
void reset_flights()
{
	remove("flights.bin");
	cout<<"Sucessfully reset!"; getch();
}


/************************************************
*			FLIGHT-SORTING FUNCTIONS 			*
*			ALGORITHM : BINARY SORT				*
************************************************/

/* SORT DIRECT FLIGHTS BY FARE */
flight* sortflights_byfare(flight *f, int s)
{
	flight temp;
	for(int i=0; i<s; i++)
	{
		for(int j=0; j<(s-1)-i; j++)
		if(f[j].getfare()>f[j+1].getfare())
		{
			temp=f[j];
			f[j]=f[j+1];
			f[j+1]=temp;
		}
	}
	return f;
} 
 
/* SORT CONNECTION FLIGHTS BY FARE */
flight* sortflights_byfare(flight cf[][2], int c)
{
	flight temp[2];
	for(int i=0; i<c; i++)
	{
		for(int j=0; j<(c-1)-i; j++)
		 {
			int fare1 = cf[j][1].getfare()+cf[j][0].getfare();
			int fare2 = cf[j+1][1].getfare()+cf[j+1][0].getfare();
			if(fare1>fare2)
			{
				temp[0]=cf[j][0]; temp[1]=cf[j][1];
				cf[j][0]=cf[j+1][0]; cf[j][1]=cf[j+1][1];
				cf[j+1][0]=temp[0]; cf[j+1][1]=temp[1];
			}
		 }
	}
	return *cf;
}

/* SORT DIRECT FLIGHTS BY ARRIVAL */
flight* sortflights_byarrival(flight *f, int s)
{
	flight temp;
	for(int i=0; i<s; i++)
	{
		for(int j=0; j<(s-1)-i; j++)
			if(f[j].arrival>f[j+1].arrival)
			{
				temp=f[j];
				f[j]=f[j+1];
				f[j+1]=temp;
			}
	}
	return f;
}

/* SORT CONNECTION FLIGHTS BY ARRIVAL */
flight* sortflights_byarrival(flight cf[][2], int c)
{
	flight temp[2];
	for(int i=0; i<c; i++)
	{
		for(int j=0; j<(c-1)-i; j++)
			if(cf[j][1].arrival>cf[j+1][1].arrival)
			{
				temp[0]=cf[j][0]; temp[1]=cf[j][1];
				cf[j][0]=cf[j+1][0]; cf[j][1]=cf[j+1][1];
				cf[j+1][0]=temp[0]; cf[j+1][1]=temp[1];
			}
	}
	return *cf;
}

/* SORT DIRECT FLIGHTS BY DURATION */
flight* sortflights_byduration(flight *f, int s)
{
	flight temp;
	for(int i=0; i<s; i++)
	{
		for(int j=0; j<(s-1)-i; j++)
		if(abs(f[j].arrival-f[j].departure)>abs(f[j+1].arrival-f[j+1].departure))
		{
			temp=f[j];
			f[j]=f[j+1];
			f[j+1]=temp;
		}
	}
	return f;
}

/* SORT CONNECTION FLIGHTS BY DURATION */
flight* sortflights_byduration(flight cf[][2], int c)
{
	flight temp[2];
	for(int i=0; i<c; i++)
	{
		for(int j=0; j<(c-1)-i; j++)
		{	int dur1 = timedif(cf[j][0].departure,cf[j][1].arrival);
			int dur2 = timedif(cf[j+1][0].departure,cf[j+1][1].arrival);
			if(dur1>dur2)
			{
				temp[0]=cf[j][0]; temp[1]=cf[j][1];
				cf[j][0]=cf[j+1][0]; cf[j][1]=cf[j+1][1];
				cf[j+1][0]=temp[0]; cf[j+1][1]=temp[1];
			}
		}
	}
	return *cf;
}
