#define _CRT_SECURE_NO_WARNINGS /*<-Preventing some warnings*/
#define MAX_S_LENGHT 10
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctime>
/*Structure for time conversion*/
tm make_tm (int year, int month, int day, int hour, int minute, int second)
{
	tm tm = {0};
	tm.tm_year = year - 1900;
	tm.tm_mon = month - 1;
	tm.tm_mday = day;
	tm.tm_hour = hour;
	tm.tm_min = minute;
	tm.tm_sec = second;
	return tm;
}
		
		

int main ()
{
	/*Variables declaration*/ 
	float lat[10000]={0}, lon[10000] = {0}, result[10000] = {0}, earth_radius, pi, sin_lat, sin_lon, cos_lat_1, cos_lat_2,
	buffer = 0, lat_1_rad = 0, lat_rad = 0, lon_1_rad, lon_rad, distance = 0, time_r = 0;
	earth_radius = 6378.41;
	int year[10000]={0}, month[10000]={0},day[10000]={0}, hour[10000]={0}, minute[10000]={0}, second[10000]={0};
	long int time_t_conversion;
	pi = 3.14159265359;
	int step = 0, step_1 = 0;  
	int d_unit = 0, t_unit;
	char lat_tmp[MAX_S_LENGHT], lon_tmp[MAX_S_LENGHT], year_tmp[4],month_tmp[2], day_tmp[2], hour_tmp[2], minute_tmp[2], second_tmp[2];
	char chr = 0;
	/*File opening and error handling*/
	FILE *fp;
	fp = fopen("test.gpx","rb");
	printf("GPX travel distance and time calculator\nMade by Mateusz Derlecki.\n");
	if (fp == NULL)
	{
		printf("Error: Cannot find GPX file in program directory. \nWrong name of file doesn't exist. \nRename file to 'test.gpx' and try again.");
		getchar();
		exit(EXIT_FAILURE);
	}
	/*Loop parsing coordinates*/
	while(chr != EOF)
	{
		step = 0;
		chr = getc(fp);
		
		if(chr == 'l')
		{
			chr = getc(fp);
			if(chr == 'a')
			{
				chr = getc(fp);
				if(chr == 't')
				{
					chr = getc(fp);
					if(chr == '=')
					{
						chr = getc(fp);
						if(chr == '"')
						{
							chr = getc(fp);
							while(chr != '"')
							{
								lat_tmp[step] = chr;
								step++;
								chr = getc(fp);
							}
							while(chr!= 'l')
							{
								chr = getc(fp);
							}
							if(chr == 'l')
							{
								chr = getc(fp);
								if(chr == 'o')
								{
									chr = getc(fp);
									if(chr == 'n')
									{
										chr = getc(fp);
										if(chr == '=')
										{
											chr = getc(fp);
											if(chr == '"')
											{
												chr = getc(fp);
												step = 0;
												while(chr != '"')
												{
													lon_tmp[step] = chr;
													step++;
													chr = getc(fp);
												}
											}
										}
									}
								}
							}
							/*Converting char table to float*/
							lat[step_1] = atof(lat_tmp);
							lon[step_1] = atof(lon_tmp);
							step_1++;
						}
					}
				}
			}
		}
		else
		{
			step = 0;
			memset(&lat_tmp, 0, sizeof(lat_tmp));
		}
	}
	step = 0;
	/*Implementation of Haversine Formula*/
	while (step <= step_1-2)
	{
		lat_rad = lat[step]*pi/180;
		lat_1_rad = lat[step+1]*pi/180;
		lon_rad = lon[step]*pi/180;
		lon_1_rad = lon[step+1]*pi/180;
		sin_lat = sin((lat_1_rad-lat_rad)/2);
		sin_lon = sin((lon_1_rad-lon_rad)/2);
		cos_lat_1 = cos(lat_rad);
		cos_lat_2 = cos(lat_1_rad);
		result[step] = 2*earth_radius*asin(sqrt(sin_lat*sin_lat+cos_lat_1*cos_lat_2*sin_lon*sin_lon));
		step++;
	}
	for(int a = 0;a <= step;a++)
	{
		distance = distance+result[a];
	}
	/*Reopening the file to go to he begening*/
	fclose(fp);
	fp = fopen("test.gpx","rb");
	chr = 1;
	step_1 = 0;
	/*Loop parsing time data from file*/
	while(chr != EOF)
	{
		chr = getc(fp);
		if(chr == '<')
		{
			chr = getc(fp);
			if (chr == 't')
			{
				chr = getc(fp);
				if (chr == 'i')
				{
					chr = getc(fp);
					if (chr == 'm')
					{
						chr = getc(fp);
						if (chr == 'e')
						{
							chr = getc(fp);
							if (chr == '>')
							{
								chr = getc(fp);
								step = 0;
								while (chr != '-')
								{
									year_tmp[step] = chr;
									step++;
									chr = getc(fp);
								}
								chr = getc(fp);
								step = 0;
								while (chr != '-')
								{
									month_tmp[step] = chr;
									step++;
									chr = getc(fp);
								}
								chr = getc(fp);
								step = 0;
								while (chr != 'T')
								{
									day_tmp[step] = chr;
									step++;
									chr = getc(fp);
								}
								chr = getc(fp);
								step = 0;
								while (chr != ':')
								{
									hour_tmp[step] = chr;
									step++;
									chr = getc(fp);
								}
								chr = getc(fp);
								step = 0;
								while (chr != ':')
								{
									minute_tmp[step] = chr;
									step++;
									chr = getc(fp);
								}
								chr = getc(fp);
								step = 0;
								for (int a = 0; a <= 1;a++)
								{
									second_tmp[step] = chr;
									step++;
									chr = getc(fp);
								}
								/*Char table -> int conversion*/
								year[step_1] = atoi(year_tmp);
								month[step_1] = atoi(month_tmp);
								day[step_1] = atoi(day_tmp);
								hour[step_1] = atoi(hour_tmp);
								minute[step_1] = atoi(minute_tmp);
								second[step_1] = atoi(second_tmp);
								step_1++;
									
							}
						}
					}
				}
			}
		}
		else
		{
			memset(&year_tmp, 0, sizeof(year_tmp));
			memset(&month_tmp, 0, sizeof(month_tmp));
			memset(&day_tmp, 0, sizeof(day_tmp));
			memset(&hour_tmp, 0, sizeof(hour_tmp));
			memset(&minute_tmp, 0, sizeof(minute_tmp));
			memset(&second_tmp, 0, sizeof(second_tmp));
		}
	}
	tm time_1 = make_tm(year[step_1-1],month[step_1-1],day[step_1-1],hour[step_1-1],minute[step_1-1],second[step_1-1]);
	tm time_2 = make_tm(year[0],month[0],day[0],hour[0],minute[0],second[0]);
	/*Converting time values to seconds to easily calculate difference*/
	time_t time_2_c = mktime(&time_2);
	time_t time_1_c = mktime(&time_1);
	time_t difference = (time_1_c - time_2_c);
	/*Menu code*/
	printf("Choose distance units:\n1 - Kilometers (default) 2 - Miles\nChoice: ");
	d_unit = getchar();
	switch(d_unit)
	{
	case 49:
		distance = distance;
		printf("Distance in kilometers: %f\n",distance);
		getchar();
		break;
	case 50:
		distance = distance*0.621371192;
		printf("Distance in miles: %f\n",distance);
		getchar();
		break;
	default:
		printf("Error: wrong value. Using default option.\n");
		distance = distance;
		printf("Distance in kilometers: %f\n",distance);
		getchar();
		break;
	}
	time_t_conversion = static_cast<int> (difference);
	printf("Choose time units:\n1 - seconds 2 - minutes 3 - hours\n");
	t_unit = getchar();
	switch(t_unit)
	{
	case 49:
		printf("Time in seconds: %d",time_t_conversion);
		getchar();
		break;
	case 50:
		time_r = (float)time_t_conversion/60;
		printf("Time in minutes: %f",time_r);
		getchar();
		break;
	case 51:
		time_r = (float)time_t_conversion/3600;
		printf("Time in hours: %f",time_r);
		getchar();
		break;
	default:
		printf("Error: wrong value. using default option.\n");
		printf("Time in seconds: %d",time_t_conversion);
		getchar();
		break;
	}
	getchar();
	return 0;
}