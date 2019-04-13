#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>


int main( int argc, char *argvp[] )
{
    pid_t pid = fork();
    if( pid == -1 ) {
        printf( "fork failed.\n" );
        exit( -1 );
    }
    if( pid == 0 ) {
        printf( "Child process is about to run execlp...\n" );
        if( execlp( "/bin/ls", "ls", "/usr", NULL ) == -1 ) {
            printf( "Failed to run exec\n" );
            exit( 1 );
        }
    }

    int childStatus;
    waitpid( pid, &childStatus, WUNTRACED );
    printf( "Parent process waited for the child process to terminate.\n" );
    printf( "Child's exit status is %d\n", childStatus );
    return 0;
}
