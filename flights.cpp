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

void flight::new_flight()
{
	cout<<"Enter Flight Details\n";
	cout<<"Flight Code: "; cin>>code;
	cout<<"Airline Code: "; cin>>airline;
	cout<<"Source: "; cin>>source;
	cout<<"Departure Time: "; cin>>departure;
	cout<<"Destination: "; cin>>dest;
	cout<<"Arrival Time: "; cin>>arrival;
	cout<<"Fare: "; cin>>fare;
}

void flight::update_flight()
{
	cout<<"Airline Code: "; cin>>airline;
	cout<<"Source: "; cin>>source;
	cout<<"Departure Time: "; cin>>departure;
	cout<<"Destination: "; cin>>dest;
	cout<<"Arrival Time: "; cin>>arrival;
	cout<<"Fare: "; cin>>fare;
}

void flight::display_flight(int y)
{
	gotoxy(2,y); cout<<airline<<code;
	gotoxy((maxx/6),y); cout<<source;
	gotoxy((maxx/6)*2,y); prnttime(departure);
	gotoxy((maxx/6)*3,y); cout<<dest;
	gotoxy((maxx/6)*4,y); prnttime(arrival);
	gotoxy((maxx/6)*5,y); cout<<fare;
}

void flight::show_flightdetails(int x, int y)
{
	txy("FLIGHT: ",x,y-7); cout<<airline<<code;
	txy("SOURCE: ",x,y-5); cout<<source;
	txy("DEPARTURE: ",x,y-4); prnttime(departure);
	txy("DESTINATION: ",x,y-2); cout<<dest;
	txy("ARRIVAL: ",x,y-1); prnttime(arrival);
	txy("DURATION: ",x,y+2); cout<<timedif(departure,arrival)<<"hrs";
	txy("FARE: Rs.",x,y+5); cout<<fare;
}

void add_flight()
{
	ofstream fout;
	flight f;
	fout.open("flights.bin",ios::app|ios::binary);
	f.new_flight();
	fout.write((char*)&f,sizeof(f));
	fout.close();
}

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

void remove_flight()
{
	ifstream fin;
	ofstream temp;
	flight f; int fcode;
	fin.open("flights.bin",ios::in|ios::binary);
	temp.open("temp.bin",ios::out|ios::binary);
	cout<<"Enter Flight Code: "; cin>>fcode;
	while(fin.read((char*)&f,sizeof(f)))
	{
		if(f.code==fcode)
		{	cout<<"Deleted "<<f.code<<" successfully"; getch(); }
		else
			temp.write((char*)&f,sizeof(f));
	}
	temp.close();
	fin.close();
	remove("flights.bin");
	rename("temp.bin", "flights.bin");
}

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

void reset_flights()
{
	remove("flights.bin");
	cout<<"Sucessfully reset!"; getch();
}

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

void display_fsresult(flight cf[2],int stops,int x,int y)
{
	flight *df=cf;
	if(stops==1)
	{
		gotoxy(x+5,y);
		cout<<cf[0].airline<<cf[0].code<<", "<<cf[1].airline<<cf[1].code;
		gotoxy(x+25,y); prnttime(cf[0].departure);
		gotoxy(x+35,y); prnttime(cf[1].arrival);
		gotoxy(x+45,y);
		cout<<timedif(cf[0].departure,cf[1].arrival)<<"hrs";
		gotoxy(x+55,y); cout<<"1 ("<<cf[0].dest<<")";
		txy("Rs. ",x+65,y); cout<<0;
		delay(150);
	}
	else if(stops==0)
	{
		txy(df[0].airline,x+5,y); cout<<df[0].code;
		gotoxy(x+25,y); prnttime(df[0].departure);
		gotoxy(x+35,y); prnttime(df[0].arrival);
		gotoxy(x+45,y); cout<<timedif(df[0].departure,df[0].arrival)<<"hrs";
		gotoxy(x+55,y); cout<<"0";
		txy("Rs. ",x+65,y); cout<<df[0].getfare();
		delay(150);
	}
}
