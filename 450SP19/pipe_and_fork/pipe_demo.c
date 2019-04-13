#include<stdio.h> 
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<errno.h>
#include<string.h>

// Save it in pipe_demo.c and compile it using "gcc pipe_demo.c". 

// This program create two process, one runs "w" and the other, "wc".
// The output of "w" gets piped to "wc."

void syserror( const char * );

int main(void)
{
  int pfd[2], pid;  

  if ( pipe (pfd) == -1 )  // create a pipe and store its descriptors in pdf.
      syserror( "Could not create a pipe" );
  switch ( pid = fork() ) {
      case -1: 
          syserror( "Fork failed." );
          break;
      case  0:    // The child process.
	        if ( close( 0 ) == -1 )    // close the child process's read file-descriptor
              syserror( "Could not close stdin I" );
  	      dup(pfd[0]); // copy the read end of the pipe in place of the process's read file-descriptor.
	        if ( close (pfd[0]) == -1 || close (pfd[1]) == -1 )  // close the read and the write ends of the pipe.
              syserror( "Could not close pfds I" );
	        execlp("sort", "sort", NULL);                  // let the child process run "wc"
	        syserror( "unsuccessfull execlp I!!");   // this statement gets executed only if exec fails.
  }
  fprintf(stderr, "The first child's pid is: %d\n", pid);
  // ^^ this is first pipe created and runs wc, outputs pid
  // can sub wc for parsed input


  switch ( pid = fork() ) {
      case -1: 
          syserror( "Could not fork successfully II" );
          break;
      case  0: 
          if ( close( 1 ) == -1 )
              syserror( "Could not close stdout" );
          dup(pfd[1]);
          if ( close (pfd[0]) == -1 || close (pfd[1]) == -1 )
              syserror( "Could not close pfds II" );
          execlp("ls", "ls", NULL);
          syserror( "Execlp error" );
  }
  fprintf(stderr, "The second child's pid is: %d\n", pid);
  if ( close (pfd[0]) == -1 || close (pfd[1]) == -1 )
    syserror( "parent could not close file descriptors!!");
  while ( (pid = wait( (int *) 0 ) ) != -1) 
    ;    /* fprintf(stderr,"%d\n", pid) */ 
}

void syserror(const char *s)
{
  extern int errno;

  fprintf( stderr, "%s\n", s );
  fprintf( stderr, " (%s)\n", strerror(errno) );
  exit( 1 );
}
