/*
*		Cpre 450
*
*   Code Provided By: Dr. Guan
*
*   Author: Michael Scholl
*/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <rpc/rpc.h>
#include "date.h"

#define MAX_LEN 100

CLIENT *rpc_setup(char *host);
long get_response(void);
void date(CLIENT *clnt, long *option);
void memory(CLIENT *clnt);
void process(CLIENT *clnt);
void cpu(CLIENT *clnt);

main(int argc, char **argv)
{
  CLIENT *clnt;  /* client handle to server */
  char *server;  /* server */
  long response;
  

  if(argc != 2)
  {
    fprintf(stderr, "usage:%s hostname\n", argv[0]);
    exit(1);
  }

  server = argv[1];

  if((clnt = rpc_setup(server)) == 0)
    exit(1);	/* cannot connect */

  response = get_response();
  
  while(response!=7)
  {
    switch(response)
    {
      case 1: case 2: case 3:
      	//printf("\nTest Case 1, 2, 3\n");
        date(clnt, &response);
      break;
      case 4:
      	//printf("\nTest Case 4\n");
        memory(clnt);
      break;
      case 5:
        //printf("\nTest Case 5\n");
        process(clnt);
      break;
      case 6:
        //printf("\nTest Case 6\n");
        cpu(clnt);
      break;
    }
    response = get_response();
  }

  clnt_destroy(clnt);
  exit(0);
}

CLIENT *rpc_setup(char *server)
{
  CLIENT *clnt = clnt_create(server,DATE_PROG,DATE_VERS,"udp");
  if(clnt == NULL)
  {
    clnt_pcreateerror(server);
    return(0);
  }
  return(clnt);
}

long get_response()
{
  long choice;
  printf("Menu: \n");
  printf("1. Date\n");
  printf("2. Time\n");
  printf("3. Both\n");
  printf("4. Memory\n");
  printf("5. Process\n");
  printf("6. CPU\n");
  printf("7. Exit\n");
  printf("Make a choice (1-7):");
  scanf("%ld", &choice);
  return(choice);
}

long mem_response()
{
	long choice;
	printf("\n");
	printf("	Memory Menu: \n");
  printf("1. Ram usage\n");
  printf("2. Current # of Processes\n");
  printf("3. Total Physical Pages\n");
  printf("4. Available Physical Pages\n");
  printf("5. Page Size\n");
  printf("6. Uptime\n");
  printf("7. Print all options\n");
  printf("8. Exit\n");
  printf("Make a choice (1-8):");
  scanf("%ld", &choice);
  return(choice);
}

void date(CLIENT *clnt, long *option)
{
	printf("\n");
	
	char **sresult = date_1(option, clnt);
	printf("%s\n", *sresult);
	
	printf("\n");
}


void memory(CLIENT *clnt)
{
	long response;
	double *sresult;
	double uptime;
	int day, hour, minute, second;
	
	response = mem_response();
	printf("\n");
	
	switch(response)
    {
    	// Memory free
      case 1:
      sresult = memory_1(&response, clnt);
      printf("Free Memory: %.2lf%\n", *sresult);
      response = 7.0;
      sresult = memory_1(&response, clnt);
      printf("Used Memory: %.2lf%\n", *sresult);
      break;
      
      // Current Processes
      case 2:
      sresult = memory_1(&response, clnt);
      printf("Current Processes: %.0lf\n", *sresult);
      break;
      
      // Total Physical Pages
      case 3:
      sresult = memory_1(&response, clnt);
      printf("Total Physical Pages: %.0lf\n", *sresult);
      break;
      
      // Total Physical Pages Available
      case 4:
      sresult = memory_1(&response, clnt);
      printf("Total Physical Pages Available: %.0lf\n", *sresult);
      break;
      
      // Pagesize
      case 5:
      sresult = memory_1(&response, clnt);
      printf("Total Pagesize: %.0lf\n", *sresult);
      break;
      
      // Uptime
      case 6:
      sresult = memory_1(&response, clnt);
      uptime = *sresult;
      if (uptime > 86399){
        day = uptime/86400;
        hour = (uptime - day*86400)/3600;
        minute = (uptime - day*86400 - hour*3600)/60;
        second = (uptime - day*86400 - hour*3600 - minute*60);
        printf("Uptime: %d Days %d Hours %d Minutes %d Seconds\n", day, hour, minute ,second);
    	}else if(uptime > 3599){
        hour = uptime/3600;
        minute = (uptime - hour*3600)/60;
        second = (uptime - hour*3600 - minute*60);
        printf("Uptime: %d Hours %d Minutes %d Seconds\n", hour, minute, second);
    	}else if(uptime > 59){
        minute = uptime/60;
        second = (uptime - minute*60);
        printf("Uptime: %d Minutes %d Seconds\n", minute, second);
    	}else{
        second = uptime;
        printf("Uptime: %d Seconds\n", second);
    	}
      break;
      // Print all functions
      case 7:
      response = 1.0;
      sresult = memory_1(&response, clnt);
      printf("Free Memory: %.2lf%\n", *sresult);
      response = 7.0;
      sresult = memory_1(&response, clnt);
      printf("Used Memory: %.2lf%\n", *sresult);
      response = 2.0;
      sresult = memory_1(&response, clnt);
      printf("Current Processes: %.0lf\n", *sresult);
      response = 3.0;
      sresult = memory_1(&response, clnt);
      printf("Total Physical Pages: %.0lf\n", *sresult);
      response = 4.0;
      sresult = memory_1(&response, clnt);
      printf("Total Physical Pages Available: %.0lf\n", *sresult);
      response = 5.0;
      sresult = memory_1(&response, clnt);
      printf("Total Pagesize: %.0lf\n", *sresult);
      break;
    }
    printf("\n");
}

void process(CLIENT *clnt)
{
	const struct argp *argp;
	double *result;
	long response = 1.0;
	
	printf("\n");
	
	result = process_1(&response, clnt);
	printf("1 Minute Load Average: %.4lf\n", *result);
	
	response = 2.0;
	result = process_1(&response, clnt);
	printf("5 Minute Load Average: %.4lf\n", *result);
	
	response = 3.0;
	result = process_1(&response, clnt);
	printf("15 Minute Load Average: %.4lf\n", *result);
	
	printf("\n");
}

void cpu(CLIENT *clnt)
{
	const struct argp *argp;
	double *sresult;
	
	printf("\n");
	
	sresult = cpu_1(argp, clnt);
	printf("Current CPU utilization: %.2lf%\n", *sresult);
	
	printf("\n");
}
