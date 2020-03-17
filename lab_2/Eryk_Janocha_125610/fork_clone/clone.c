#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include"pomiar_czasu/pomiar_czasu.c"
#include <linux/sched.h>

int zmienna_globalna=0;

#define ROZMIAR_STOSU 1024*64

int funkcja_watku( void* argument )
{

  zmienna_globalna++;

   int wynik; 
   wynik=execv("./program",NULL); 
   if(wynik==-1) 
     printf("Proces potomny nie wykonal programu\n"); 

  return 0;
}

main()
{

  void *stos;
  pid_t pid;
  int i; 
  
  stos = malloc( ROZMIAR_STOSU );
  if (stos == 0) {
    printf("Proces nadrzędny - blad alokacji stosu\n");
    exit( 1 );
  }
  inicjuj_czas();
  for(i=0;i<1000;i++){

    pid = clone( &funkcja_watku, (void *) stos+ROZMIAR_STOSU,CLONE_UNTRACED, 0 );
//CLONE_FS | CLONE_FILES | CLONE_SIGHAND nie działa :(  | CLONE_VM,
   if ( pid < 0 ) {
        printf("ERROR: Unable to create the child process.\n");
        exit(EXIT_FAILURE);
   }

    waitpid(pid, NULL, __WCLONE);

  }
  drukuj_czas();
  free( stos );
}
