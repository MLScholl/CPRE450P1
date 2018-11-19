/*
*		Cpre 450
*
*   Code Provided By: Dr. Guan
*
*   Author: Michael Scholl
*/
#include <rpc/rpc.h>
#include <time.h>
#include <sys/types.h>
#include <linux/kernel.h>
#include <sys/sysinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include "date.h"

#define MAX_LEN 100


char **date_1(long *option)
{
  struct tm *timeptr;
  time_t clock;
  static char *ptr;
  static char err[] = "Invalid Response \0";
  static char s[MAX_LEN];

  clock = time(0);
  timeptr = localtime(&clock);
  
  switch(*option)
  {
	case 1:
	
		strftime(s,MAX_LEN,"%A, %B %d, %Y",timeptr);
		ptr=s;
		break;

	case 2:strftime(s,MAX_LEN,"%T",timeptr);
	  ptr=s;
	  break;
	
	case 3:strftime(s,MAX_LEN,"%A, %B %d, %Y - %T",timeptr);
	  ptr=s;
	  break;

	default: ptr=err;
	  break;
  }

  return(&ptr);
}

double *memory_1(long *option)
{
	static double *resultp;
	static double result;
	
	struct sysinfo info;
	sysinfo(&info);

	double temp;
	
	long int avpage = get_avphys_pages();
	long int page = get_phys_pages();
	
	switch(*option)
  {
  	// Memory free
		case 1:
		result = (double)((double)avpage/page)* 100.0;
		break;
		
		// Current Processes
		case 2:
		result = (double)(info.procs);
		break;
		
		// Total Physical Pages
		case 3:
		result = (double)(get_phys_pages());
		break;
		
		// Total Physical Pages Available
		case 4:
		result = (double)(get_avphys_pages());
		break;
		
		// Pagesize
		case 5:
		result = (double) getpagesize();
		break;
		
		// Uptime
		case 6:
		result = (double)(info.uptime);
		break;
		
		// Memory used
		case 7:
		result = 100 - (double)((((double)get_avphys_pages()/get_phys_pages())*100.0));
		break;
  }
  
  resultp = &result;
  return(resultp);
}

double *process_1(long *option)
{
	static double load[MAX_LEN];
	static double *loadval;
	
	static double error = 1.0;
	
	if (getloadavg(load, 3) == 1) {
		return &error;
	}
	else {
	}
	//printf("%lf %lf %lf\n", load[0], load[1], load[2]);
	
	switch(*option)
  {
  	// 1 Minute Average
		case 1:
		loadval = &load[0];
		return(loadval);
		break;
		
		// 5 Minute Average
		case 2:
		loadval = &load[1];
		return(loadval);
		break;
		
		// 15 Minute Average
		case 3:
		loadval = &load[2];
		return(loadval);
		break;
  }
  loadval = &error;
  return loadval;
}

// CPU Usage code was taken from
// https://stackoverflow.com/questions/3769405/determining-cpu-utilization
// I was unsure as to how long you should look at CPU Usage so the 1 second time was left

double *cpu_1(long *option)
{
	static double *resultp;
	static double result;

	
	long double a[4], b[4];
  FILE *fp;
  char dump[50];

  fp = fopen("/proc/stat","r");
  fscanf(fp,"%*s %Lf %Lf %Lf %Lf",&a[0],&a[1],&a[2],&a[3]);
  fclose(fp);
  sleep(1);

  fp = fopen("/proc/stat","r");
  fscanf(fp,"%*s %Lf %Lf %Lf %Lf",&b[0],&b[1],&b[2],&b[3]);
  fclose(fp);
  
  result = (double)((b[0]+b[1]+b[2]) - (a[0]+a[1]+a[2])) / ((b[0]+b[1]+b[2]+b[3]) - (a[0]+a[1]+a[2]+a[3]));
  result = result * 100.0;
  resultp = &result;
  return(resultp);
}

