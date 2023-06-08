// IPC: program handling with PIPE
#include<stdio.h>
#include<unistd.h>

int main(){
	FILE *ftpr;
	ftpr = fopen("demo.txt", "w");
	fprintf(ftpr, "Hello World");
	fclose(ftpr);

	int pipefds[2];
	int returnStatus = pipe(pipefds);
	int pid = fork();
	char writemsg[20], readmsg[20];

	ftpr = fopen("demo.txt", "r");
	fgets(writemsg, 20, ftpr);

	if(returnStatus == -1){
		printf("Unable to create pipe");
		return 1;
	}
	
	if(pid == 0){
		read(pipefds[0], readmsg, sizeof(readmsg));
		printf("Child process - reading from pipe - message is %s\n", readmsg);
	}
	else{
		printf("Parent process - writing from pipe - message is %s\n", writemsg);
		write(pipefds[1], writemsg, sizeof(writemsg));
	}

	fclose(ftpr);
	return 0;
}
