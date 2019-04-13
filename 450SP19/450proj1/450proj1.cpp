/******************************************************************************\
+																		       +
+	Jeff Olson																   +
+		CS 450		 														   +
+		Project 1						           							   +
+		02/20/19															   +
+																			   +
+																			   +
\******************************************************************************/




#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include <sstream>
#include <fcntl.h>

using namespace std;

void handle_parse(string input);
void handle_command(char *command, char *argv[], char del, char *infile, int num_p, const char *outfile);
bool char_comp(char comp1, char comp2);
void handle_command_pipe(char *cmd1[], char *cmd2[], char *file, int num);
void handle_parse_multi_pipe(char ***cmd3, int n_pipes);
string no_quotes(string string);


int main() {

	string linux_com;
	cout << "Enter a Linux Command: " << endl;
	cout << "--q to quit--" << endl;
	cout << ">";
	getline(cin, linux_com);
	while (linux_com != "q") {
		
		handle_parse(linux_com);
		cout << ">";
		getline(cin, linux_com);

	}
	return 0;
	
}

string no_quotes(string string) {
	int i = 0;
	while (string[i] != NULL) {
		if (string[i] == '\'' || string[i] == '\"') {
			string.erase(string.begin()+i);
			i--;
		}
		else {
			i++;
		}
	}
	return string;
}

bool char_comp(char comp1, char comp2) {
	if (comp1 == comp2) {
		return true;
	}
	else {
		return false;
	}
}

void handle_parse(string input) {
	// This parses and sends ish to handle_command
	const char *OutfileName;
	int num_ele = 0;
    char delimeter = '\0';
	char delimeter2;
	int num_pipes = 0;
	int number_redirects = 0;
	int number_inputs = 0;
	int number_outputs = 0;
	int idx_for_pipe;
    char *filename = nullptr;
	bool redir = false;
	//int number_meta_chars[3];
	


	//parse input string to get info on meta chars and to put elements into arr
	string element_arr[input.size()];

	stringstream ssin(input);
	while(ssin.good()) {
		string temp;
		ssin >> temp;
		if (redir == true) {
			OutfileName = temp.c_str();
		}
		if (temp == "|") {
			//add pipe, split by pipe
			delimeter = '|';
			num_pipes++;
			idx_for_pipe = num_ele;

		}
		else if (temp == "<") {
			delimeter = '<';
			number_redirects++;
			number_inputs++;
		}
		else if (temp == ">") {
			delimeter2 = '>';
			number_redirects++;
			number_outputs++;
			redir = true;
		}
		else {
			element_arr[num_ele] = temp;
			num_ele++;		
		}		
	}
	

	string send = no_quotes(input);
	//second parse for multiple strings
	int tot_num_ele = num_ele + num_pipes + number_redirects;
	//int tot_num_meta = num_pipes + number_redirects;
	char *word[0];
	char *arr_v[20];
	char **mulpip_cmd[20];
	int it = 0;
	int last = 0;
	int l = 0;
	
	stringstream ss2(send);
	while (ss2.good()) {
		string temp3;
		ss2 >> temp3;
		word[0] = strcpy(new char[temp3.length()+1], temp3.c_str());
		if (temp3 == "|") {
			arr_v[it] = NULL;
			mulpip_cmd[l] = &arr_v[last];
			l++;
			it++;
			last = it;
			continue;
		}
		else {
			arr_v[it] = word[0];
			it++;
		}
	}

	mulpip_cmd[l] = &arr_v[last];
	l++;
	arr_v[it] = NULL;
	mulpip_cmd[l] = NULL;

	

	
	
	
	//cout << in_idx_arr[0] << endl;
	

	int number_redirects_save = number_redirects;
	if (redir == true) {
		num_ele--;
	}

	//for no pipes, just basic commands
	char *com_elements[num_ele+1];
	char *cmd;
	bool isfile = false;
	
	//bool ispipe = false;
	//rip chars into elements of com_elements, want to do the same thing
	for (int i = 0; i < num_ele; i++) {
		char *temp = new char(element_arr[i].size()+1);
		for (int l = 0; l < element_arr[i].size(); l++) {
			temp[l] = element_arr[i][l];
			if (char_comp(temp[l], '.')) {
				isfile = true;
			}
			
		}
		if (isfile == true && number_redirects_save > 0) {
			filename = temp;
			num_ele = num_ele - 1;
			number_redirects--;
		}
		else {
			com_elements[i] = temp;
			//cout << com_elements[i] << endl;
		}
	}

	

	cmd = com_elements[0];
	com_elements[num_ele] = NULL;

	if (num_pipes == 0 && number_redirects_save == 0) {
		//cout << "doing something wrong" << endl;
		delimeter = '\0';
		delimeter2 = '\0';
		filename = NULL;
		OutfileName = NULL;
		handle_command(cmd, com_elements, delimeter, filename, num_pipes, OutfileName);
	}

	if (number_inputs > 0 and number_outputs == 0 and num_pipes == 0) {
		handle_command(cmd, com_elements, delimeter, filename, num_pipes, OutfileName);
	}
	else if (number_outputs > 0 and number_inputs == 0 and num_pipes == 0) {
		handle_command(cmd, com_elements, delimeter2, filename, num_pipes, OutfileName);
	}
	else if (number_inputs > 0 and number_outputs > 0 and num_pipes == 0) {
		handle_command(cmd, com_elements, '!', filename, num_pipes, OutfileName);
	}
	// this splits command by pipe idx and I put them into two different arrays
	// this will need to change for the multiple pipes
	else if (num_pipes == 1 and number_redirects_save == 0) {
		int sec_size = num_ele-idx_for_pipe;
		char *cmd_arr2[idx_for_pipe+1];
		char *cmd_ary1[sec_size+1];
		for (int i = 0; i < idx_for_pipe; i++) {
			cmd_ary1[i] = com_elements[i];	
		}
		for (int k = 0; k < num_ele - idx_for_pipe; k++) {
			cmd_arr2[k] = com_elements[idx_for_pipe + k];
			
		}
		cmd_ary1[idx_for_pipe] = nullptr;
		cmd_arr2[sec_size] = nullptr;

		handle_command_pipe(cmd_ary1, cmd_arr2, filename, num_ele);
	}
	else if (num_pipes > 1) {	
		/*
        // ls -l | head -5 | tail -10
		char *ls[] = {"ls", "/usr/bin/", NULL};
		char *grep[] = {"head", "-5", NULL};
  		char *wc[] = {"tail", "-10", NULL};
  		char **cmd_hard[] = {ls, grep, wc, NULL};
  		//num_pipes = 2;
		*/
		handle_parse_multi_pipe(mulpip_cmd, num_pipes);
        //handle_parse_multi_pipe(cmd_hard, num_pipes);
	}
	
}


void handle_command_pipe(char *cmd1[], char *cmd2[], char *file, int num) {


	int pfd[2];
	pid_t pid;
	if (pipe(pfd) == -1)
		printf("%s\n","Could not create a pipe");
	switch(pid = fork()) {
		case -1:
			printf("%s\n","Failed to fork");
			break;
		case 0:
			if(close(0) == -1)
				printf("%s\n", "could not close stdin I");
			dup(pfd[0]);
			if (close(pfd[0]) == -1 || close(pfd[1]) == -1) {
				printf("%s\n","could not close pfds I");
			}
			execvp(cmd2[0], cmd2);
			//execvp(cmd1[0], cmd1);
			printf("%s\n","unsuccessful execvp of first child");
	}

	switch (pid = fork()) {
		case -1:
			printf("%s\n","Fork failed");
			break;
		case 0:
			if (close(1) == -1)
				printf("%s\n","could not close pfds II");
			dup(pfd[1]);
			if (close(pfd[0]) == -1 || close(pfd[1]) == -1) {
				printf("%s\n", "could not close pfds II");
			}
			//execlp(cmd2[0], cmd2[0], NULL);
			execvp(cmd1[0],  cmd1);
			printf("%s\n", "unsuccessful execvp of second child");
	}
	if (close(pfd[0]) == -1 || close(pfd[1]) == -1) {
		printf("%s\n", "parent could not close file descriptors");
		exit(1);
	}
	while ((pid = wait((int *) 0 )) != -1)
	break;

}



void handle_command(char *command, char *argv[], char del, char *infile, int num_p, const char *outfile) {

	//Basic command, fork, call execvp, base case
	if (del == '\0') {
		//cout << "In here" << endl;
		pid_t pid = fork();

		if (pid == -1) {
			printf( "fork failed.\n" );
       		exit( -1 );
		}
		else if (pid == 0) {
			printf( "Child process is about to run execvp\n" );
        	if( execvp( argv[0], argv) == -1 ) {
            	printf( "Failed to run exec\n" );
            	exit( 1 );
       		}
		}

		int childStatus;
		waitpid(pid, &childStatus, WUNTRACED);
		printf( "Parent process waited for the child process to terminate.\n" );
    	printf( "Child's exit status is %d\n", childStatus );
	}

	
	// for redirection of input files
	else if (del == '<') {

		int readFD;
		pid_t child1_pid;
		
		switch (child1_pid = fork()) {
			case -1: 
				printf("Failed to fork");
				exit(-1);
			case  0://child process
				readFD = open( infile, O_RDONLY );
				//cout << readFD << endl;
                
            	dup2(readFD, 0);//dup readFD to stdin
            	close(readFD);
            	//printf("%s\n", "Output of command: ");
                execvp(argv[0], argv);
                printf("%s\n", "execvp failed in the child (read) process.  Terminating." );
                exit(1);
		}


		int childStatus;
		waitpid(child1_pid, &childStatus, WUNTRACED);
		printf( "Parent process waited for the child process to terminate.\n" );
    	printf( "Child's exit status is %d\n", childStatus );
			
	}

	
	// redirect output
	else if (del == '>') {

		//int pfd[2];
		//int sendFD;
		pid_t pid;

		switch (pid = fork()) {
			case -1:
				printf("Failed to fork");
				exit(-1);
			case 0:
				close(1); // close std out
				int openfd = open(outfile, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR); // open txt file
				dup(openfd);
				//printf("%s\n", "Output of command: ");
				execvp(argv[0], argv);
				printf("%s\n", "execvp failed in the child (write) process.  Terminating.");
				exit(1);
		}


		int childStatus;
		waitpid(pid, &childStatus, WUNTRACED);
		printf( "Parent process waited for the child process to terminate.\n" );
    	printf( "Child's exit status is %d\n", childStatus );
	}

	// pipes will have commands saved by how they appear in pipe

	// handles both input and output in same line
	else if (del == '!') {
		//int pfd[2];
		pid_t pid;
		int fdin, fdout;

		switch(pid = fork()) {
			case -1:
				printf("Failed to fork");
				exit(-1);
			case 0:
				if (close(1) == -1)
					printf("couldnt close stdout");
				fdin = open(infile, O_RDONLY); // open read file
				fdout = open(outfile, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR); // open write file
				dup2(fdin, 0); // dup input
				close(fdin); // close input

				dup(fdout); //dup output
				close(fdout);
				execvp(argv[0], argv);
				printf("%s\n", "execvp failed in the child (both) process.  Terminating.");
		}

		int childStatus;
		waitpid(pid, &childStatus, WUNTRACED);
		printf( "Parent process waited for the child process to terminate.\n" );
    	printf( "Child's exit status is %d\n", childStatus );

	}
}

void handle_parse_multi_pipe(char ***cmd3, int n_pipes) {

	
	
	int pfd[2];
	//int mult_pfd[2*n_pipes];
	pid_t pid1;
    /*
	for ( int i = 0; i < n_pipes; i++) {
		if (pipe(mult_pfd + i*2) < 0) {
			printf("%s\n", "Exiting... ");
			exit(1);
		}
	}
     */
    int cout_c = 1;
	int fd_in = 0;
	while (*cmd3 != NULL) {
		pipe(pfd);
		if ((pid1 = fork()) == -1) {
			cout << "fork failed" << endl;
			exit(1);
		}
		else if (pid1 == 0) {
			dup2(fd_in, 0);
			if (*(cmd3 + 1) != NULL) {
				dup2(pfd[1], 1);
			}
			close(pfd[0]);
			execvp((*cmd3)[0], *cmd3);
			cout << "Could not execvp, exiting..." << endl;
			exit(1);
		}
		else {
			while ((pid1 = wait((int *) 0 )) != -1);
			close(pfd[1]);
			fd_in = pfd[0];
			cmd3++;
		}
        cout_c++;
	}


    
	//for (int j = 0; j < 2 * n_pipes; j++) {
	//	close(mult_pfd[j]);
	//}
	
}









