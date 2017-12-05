void flight_search()
{
	clrscr();
	
	/* USER QUERY IS ACCEPTED */
	
	char source[5], dest[5];
	txy("QUIGO SEARCH",maxx/2,2,0,1);
	txy("BOOK TICKET FASTER & EASIER", maxx/2,3,20,1);
	txy("Source: ",maxx/2,8,0,2);
	txy("Destination: ",maxx/2,9,0,2);
	txy("Sort By: ", maxx/2,10,0,2);
	char *types[] = {"CHEAPEST","EARLIEST","FASTEST"};
	gotoxy(maxx/2,8); cin>>source;
	gotoxy(maxx/2,9); cin>>dest;
	int type = selopx(types,maxx/2,maxx/2+21,10,3);

	
	/* PRIMARY SEARCH  FOR DIRECT FLIGHT MATCHES*/
	flight f, df[25], options[50];
	int d=0, o=0, c=0;
	ifstream fin;
	fin.open("flights.bin",ios::in|ios::binary);
	while(fin.read((char*)&f,sizeof(f)))
	{
		if(strcmpi(f.source,source)==0)
		{
			if(strcmpi(f.dest,dest)==0)
			{ df[d] = f; d++; }
			else if(o<50)  //ALL FLIGHTS FROM SOURCE IS TRACKED
			{ options[o] = f; o++; }
		}
	}
	fin.close();
	
	/* RESULT IS ALWAYS SORTED FOR LEAST FARE, REGARDGLESS OF USER-SORT REQUEST */
	sortflights_byfare(df,d);
	sortflights_byfare(options,o);
	
	/* SECONDARY SEARCH  FOR 1-STOP FLIGHT MATCHES*/
	flight cf[2][50];
	fin.open("flights.bin",ios::in|ios::binary);
	while(fin.read((char*)&f,sizeof(f)))
	{
		for(int k=0; k<o; k++)
		{
			if(strcmpi(f.source,options[k].dest)==0)
			{
				if(strcmpi(f.dest,dest)==0)
				{
				    //Checks if time-gap b/w connection flights
					if(f.departure>options[k].arrival+100) //1 hrs is set as default
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
	
	if(d!=0||c!=0)
	{
		int i=0, j=0, n=0, x=6, y=5;
		clrscr();
		flight rs[2][25]; int rf[25];
		
		cout<<"SHOWING FLIGHTS FROM "<<source<<" TO "<<dest<<endl;
		cout<<"SORTED BY "<<types[type];
		
		txy("#",x,y);
		txy("FLIGHT NO.",x+5,y);
		txy("DEPART.",x+25,y);
		txy("ARRIVAL",x+35,y);
		txy("DUR.",x+45,y);
		txy("STOPS",x+55,y);
		txy("FARE",x+65,y++);
		prntln(y++);

		/* RESULTS FROM PRIMARY & SECONDARY SEARCHES ARE MERGED AND SORTED */
		
		/* RESULTS SORTED BASED ON FARE */

		if(type==0)
		{   
			for(i=0, j=0; (i<d||j<c)&&n<15;)
			{
				float cfare= cf[j][0].getfare()+cf[j][1].getfare();
				if(i==d||cfare<df[i].getfare()&&j!=c)
				{
					n++; 
					gotoxy(x+5,y);
					cout<<cf[j][0].airline<<cf[j][0].code<<", "<<cf[j][1].airline<<cf[j][1].code;
					gotoxy(x+25,y); prnttime(cf[j][0].departure);
					gotoxy(x+35,y); prnttime(cf[j][1].arrival);
					gotoxy(x+45,y);
					cout<<timedif(cf[j][0].departure,cf[j][1].arrival)<<"hrs";
					gotoxy(x+55,y); cout<<"1 ("<<cf[j][0].dest<<")";
					txy("Rs. ",x+65,y); cout<<cfare;
					delay(150); y++;
					rs[n][0]=cf[j][0];
					rs[n][1]=cf[j][1];
					rf[n]=1; j++;
				}
				if((j==c||cfare>df[i].getfare())&&i!=d)
				{
					n++;
					txy(df[0].airline,x+5,y); cout<<df[0].code;
					gotoxy(x+25,y); prnttime(df[0].departure);
					gotoxy(x+35,y); prnttime(df[0].arrival);
					gotoxy(x+45,y); cout<<timedif(df[0].departure,df[0].arrival)<<"hrs";
					gotoxy(x+55,y); cout<<"0";
					txy("Rs. ",x+65,y); cout<<df[0].getfare();
					delay(150); y++;
					rs[n][0]=df[i]; rf[n]=0;
					 i++;
				}
			}
		}
		
		/* RESULTS SORTED BASED ON EARLIEST ARRIVAL*/
		
		if(type==1)
		{
			sortflights_byarrival(df,d);
			
			flight temp[2];
			for(i=0; i<c; i++)
			{
				for(j=0; j<(c-1)-i; j++)
					if(cf[j][1].arrival>cf[j+1][1].arrival)
					{
						temp[0]=cf[j][0]; temp[1]=cf[j][1];
						cf[j][0]=cf[0][j+1]; cf[1][j]=cf[1][j+1];
						cf[j+1][0]=temp[0]; cf[j+1][1]=temp[1];
					}
			}
			
			
			for(i=0,j=0; (i<d||j<c)&&n<15;)
			{
				if((i==d||(cf[j][1].arrival<df[i].arrival))&&j!=c)
				{
					n++;
					gotoxy(x+5,y);
					cout<<cf[j][0].airline<<cf[j][0].code<<", "<<cf[j][1].airline<<cf[j][1].code;
					gotoxy(x+25,y); prnttime(cf[j][0].departure);
					gotoxy(x+35,y); prnttime(cf[j][1].arrival);
					gotoxy(x+45,y);
					cout<<timedif(cf[j][0].departure,cf[j][1].arrival)<<"hrs";
					gotoxy(x+55,y); cout<<"1 ("<<cf[j][0].dest<<")";
					txy("Rs. ",x+65,y); cout<<cf[j][0].getfare()+cf[j][1].getfare();
					delay(150); y++;
					rs[n][0]=cf[j][0];
					rs[n][1]=cf[j][1];
					rf[n]=1; j++;
				}
				if((j==c||(cf[j][1].arrival>df[i].arrival))&&i!=d)
				{
					n++;
					txy(df[0].airline,x+5,y); cout<<df[0].code;
					gotoxy(x+25,y); prnttime(df[0].departure);
					gotoxy(x+35,y); prnttime(df[0].arrival);
					gotoxy(x+45,y); cout<<timedif(df[0].departure,df[0].arrival)<<"hrs";
					gotoxy(x+55,y); cout<<"0";
					txy("Rs. ",x+65,y); cout<<df[0].getfare();
					delay(150); y++;
					rs[n][0]=df[i]; rf[n]=0;
					i++;
				}
			}
		}

		/* RESULTS SORTED BASED ON SHORTEST DURATION */

		if(type==2)
		{
			sortflights_byduration(df,d);

			for(i=0; i<d; i++)
			{
					n++;
					txy(df[0].airline,x+5,y); cout<<df[0].code;
					gotoxy(x+25,y); prnttime(df[0].departure);
					gotoxy(x+35,y); prnttime(df[0].arrival);
					gotoxy(x+45,y); cout<<timedif(df[0].departure,df[0].arrival)<<"hrs";
					gotoxy(x+55,y); cout<<"0";
					txy("Rs. ",x+65,y); cout<<df[0].getfare();
					delay(150); y++;
					rs[n][0]=df[i]; rf[n]=0;
			}

			flight temp[2];
			for(i=0; i<c; i++)
			{
				for(j=0; j<(c-1)-i; j++)
					if(abs(cf[j][1].arrival-cf[j][0].departure)>abs(cf[j+1][1].arrival-cf[j+1][0].departure))
					{
						temp[0]=cf[0][j]; temp[1]=cf[j][1];
						cf[j][0]=cf[0][j+1]; cf[j][1]=cf[j+1][1];
						cf[j+1][0]=temp[0]; cf[j+1][1]=temp[1];
					}
			}

			for(j=0; j<c; j++)
			{
					n++;
					gotoxy(x+5,y);
					cout<<cf[j][0].airline<<cf[j][0].code<<", "<<cf[j][1].airline<<cf[j][1].code;
					gotoxy(x+25,y); prnttime(cf[j][0].departure);
					gotoxy(x+35,y); prnttime(cf[j][1].arrival);
					gotoxy(x+45,y);
					cout<<timedif(cf[j][0].departure,cf[j][1].arrival)<<"hrs";
					gotoxy(x+55,y); cout<<"1 ("<<cf[j][0].dest<<")";
					txy("Rs. ",x+65,y); cout<<cf[j][0].getfare()+cf[j][1].getfare();
					delay(150); y++;
					rs[n][0]=cf[j][0];
					rs[n][1]=cf[j][1];
					rf[n]=1;
			}
		}

		txy("USE ARROW KEYS TO SELECT FLIGHT, AND ENTER KEY TO VIEW DETAILS", maxx/2,maxy-2,0,1);
		int op = selopy(2,7,--y);
		
		/* INDIVIDUAL RESULTS DISPLAYED BASED ON SELECTION*/
		clrscr();
		float totalfare;
		flight rd = rs[op][0];
		rd.show_flightdetails(4,maxy/2);
		totalfare += f.getfare();
		if(rf[op]==1)
		{
			rs[op][1].show_flightdetails(maxx/2,maxy/2);
			totalfare += f.getfare();
			txy("TOTAL FARE: Rs.", maxx/2,maxy/2+8,0,1); cout<<totalfare;
		}
		getch();
	}
	else
	{ clrscr(); txy("NO FLIGHTS FOUND!",maxx/2,maxy/2,0,1); getch(); }
}
