/*
	FILENAME : SEARCH.CPP
	DESCRIPTION: File holding the search feature
*/

/* FUNCTION TO DISPLAY RESULTS */
int show_results(flight rs[50][2], int rf[50], int n)
{
	int x=6, y=5;
	txy("#",x,y);
	txy("FLIGHT NO.",x+5,y);
	txy("DEPART.",x+25,y);
	txy("ARRIVAL",x+35,y);
	txy("DUR.",x+45,y);
	txy("STOPS",x+55,y);
	txy("FARE",x+65,y++);
	prntln(y++);

	for(int i=0; i<n; i++)
	{
		gotoxy(x,y); cout<<i+1;
		//Direct Flights
		if(rf[i]==0)
		{
			txy(rs[i][0].airline,x+5,y); cout<<rs[i][0].code;
			gotoxy(x+25,y); prnttime(rs[i][0].departure);
			gotoxy(x+35,y); prnttime(rs[i][0].arrival);
			gotoxy(x+45,y); cout<<timedif(rs[i][0].departure,rs[i][0].arrival)<<"hrs";
			gotoxy(x+55,y); cout<<"0";
			txy("Rs. ",x+65,y); cout<<rs[i][0].getfare();

		}
		//Connection Flights
		else if(rf[i]==1)
		{
			gotoxy(x+5,y);
			cout<<rs[i][0].airline<<rs[i][0].code<<", "<<rs[i][1].airline<<rs[i][1].code;
			gotoxy(x+25,y); prnttime(rs[i][0].departure);
			gotoxy(x+35,y); prnttime(rs[i][1].arrival);
			gotoxy(x+45,y);
			cout<<timedif(rs[i][0].departure,rs[i][1].arrival)<<"hrs";
			gotoxy(x+55,y); cout<<"1 ("<<rs[i][0].dest<<")";
			txy("Rs. ",x+65,y); cout<<rs[i][0].getfare()+rs[i][1].getfare();
		}
		delay(150); y++;
	}
	txy("USE ARROW KEYS TO SELECT FLIGHT, AND ENTER KEY TO VIEW DETAILS", maxx/2,maxy-2,0,1);
	int op = selopy(2,7,--y); op--;
	return op;
}

/* FUNCTION HOLDING THE SEARCH FEATURE OF QUIGO */
void flight_search()
{
	/* USER QUERY IS ACCEPTED */
	char source[5], dest[5];
	clrscr();
	quigo_logo(maxx/2-22,8);
	txy("ADVANCED FLIGHT SEARCH",maxx/2,10,0,1);
	txy("ENTER JOURNEY DETAILS",maxx/2,14,0,1);
	txy("Source: ",maxx/2,15,0,2);
	txy("Destination: ",maxx/2,16,0,2);
	txy("ENTER IATA CODE OF AIRPORT, LIKE COK FOR KOCHI.",maxx/2,maxy-2,0,1);
	gotoxy(maxx/2,15); cin>>source;
	gotoxy(maxx/2,16); cin>>dest;

	/* PRIMARY SEARCH LOGIC FOR DIRECT FLIGHT MATCHES*/
	flight f, df[30], options[50];
	int d=0, o=0, c=0;
	ifstream fin;
	fin.open("flights.bin",ios::in|ios::binary);
	while(fin.read((char*)&f,sizeof(f)))
	{
		if(strcmpi(f.source,source)==0)
		{
			if(strcmpi(f.dest,dest)==0)
			{ df[d] = f; d++; }
			else if(o<50)  //FLIGHTS FROM SOURCE IS TRACKED
			{ options[o] = f; o++; }
		}
	}
	fin.close();

	/* LEAST FARE OPIONS ARE PREFERRED FIRST FOR CONNECTION FLIGHTS */
	sortflights_byfare(options,o);

	/* SECONDARY SEARCH LOGIC FOR 1-STOP FLIGHT MATCHES*/
	flight cf[25][2];
	fin.open("flights.bin",ios::in|ios::binary);
	while(fin.read((char*)&f,sizeof(f))&&c<25)
	{
		//loops across all options
		for(int k=0; k<o; k++)
		{
			//Is the flight from where option flight reaches 
			if(strcmpi(f.source,options[k].dest)==0)
			{
				//Does the flight goes to search destination
				if(strcmpi(f.dest,dest)==0)
				{
					//Is there sufficient time between connection flights?
					int gap = f.departure-options[k].arrival;
					if((gap>100)&&(gap<800))  //100 = 1 hour
				    {
						cf[c][0] = options[k];
						cf[c][1] = f;
						c++;
				     }
				}
			}
		}
	}
	fin.close();

	/* CHECKS IF QUERY RETURNS ANY RESULT */
	char type;
	if(d!=0||c!=0)
	{
		char sop;
		do{
			int i=0, j=0, n=0;
			flight rs[50][2]; //holds the results
			int rf[50]; //holds whether the result is direct(0)/connection(1) type 
			
			//User is asked for sort-option
			clrscr();
			cout<<"SHOWING FLIGHTS FROM "<<source<<" TO "<<dest<<endl;
			cout<<"SORTED BY ";
			char *types[] = {"CHEAPEST","EARLIEST","FASTEST"};
			type = selopx(types,12,30,2,3);
			
			/* DIRECT FLIGHT AND CONNECTION FLIGHT RESULTS ARE MERGED AND SORTED */

			/* RESULTS ARE INITIALLY SORTED BASED ON FARE */
			sortflights_byfare(df,d);
			sortflights_byfare(cf,c);
			
			/* RESULTS SORTED BY CHEAPEST FARE */
			if(type==0)
			{
				//Arrays of Direct and Connection Flights are already sorted
				//Merging the results
				for(i=0, j=0; i<d||j<c;)
				{
					float cfare= cf[j][0].getfare()+cf[j][1].getfare();
					
					//Connected Flight
					if(i==d||cfare<df[i].getfare()&&j!=c)
					{
						rs[n][0]=cf[j][0];
						rs[n][1]=cf[j][1];
						rf[n]=1; n++; j++;
					}
					
					//Direct Flight
					if((j==c||cfare>df[i].getfare())&&i!=d)
					{

						rs[n][0]=df[i]; 
						rf[n]=0; n++; i++;
					}
				}
			}

			/* RESULTS SORTED BASED ON EARLIEST ARRIVAL*/
			if(type==1)
			{
				//Sorting the results
				sortflights_byarrival(df,d);
				sortflights_byarrival(cf,c);
				
				//Merging the results
				for(i=0, j=0; i<d||j<c;)
				{
					//Connected Flight
					if((i==d||(cf[j][1].arrival<df[i].arrival))&&j!=c)
					{
						rs[n][0]=cf[j][0];
						rs[n][1]=cf[j][1];
						rf[n]=1; n++; j++;
					}

					//Direct Flight
					else if(i!=d)
					{
						rs[n][0]=df[i]; 
						rf[n]=0; n++; i++;
					}
				}
			}

			/* RESULTS SORTED BASED ON SHORTEST DURATION */
			if(type==2)
			{
				//Sorting the results
				sortflights_byduration(df,d);
				sortflights_byduration(cf,c);

				//Direct Flights always take shorter duration
				for(i=0; i<d; i++)
				{
						rs[n][0]=df[i];
						rf[n]=0; n++;
				}
				
				//Connection Flights take more duration
				for(j=0; j<c; j++)
				{
						rs[n][0]=cf[j][0];
						rs[n][1]=cf[j][1];
						rf[n]=1; n++;
				}
			}
			//Selector allowing to view flight details
			int op = show_results(rs,rf,n);
			
			
			/* INDIVIDUAL RESULTS DISPLAYED BASED ON SELECTION*/
			clrscr();
			txy("VIEWING FLIGHT DETAILS",4,2);
			flight rd = rs[op][0];
			rd.show_flightdetails(4,maxy/2);
			if(rf[op]==1)
			{
				rs[op][1].show_flightdetails(maxx/2+4,maxy/2);
				txy("FLIGHT #1",4,4); txy("FLIGHT #2",maxx/2+4,4);
				txy("FARE: Rs.", 4,maxy-8); 
				cout<<rs[op][0].getfare()+rs[op][1].getfare();
				txy("LAYOVER TIME: ",4,maxy-7); 
				cout<<timedif(rs[op][0].arrival,rs[op][1].departure)<<"hrs";
				txy("DURATION: ",4,maxy-6); 
				cout<<timedif(rs[op][0].departure,rs[op][1].arrival)<<"hrs";
			}
			txy("PRESS ESC KEY TO EXIT, OR ANY OTHER KEY TO RETURN TO RESULTS.",maxx/2,maxy-2,0,1);
			sop = getch();

		}while((int)sop!=27);
	}
	else
	{ clrscr(); txy("NO FLIGHTS WERE FOUND!",maxx/2,maxy/2,0,1); getch(); }
}
