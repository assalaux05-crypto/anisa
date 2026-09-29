#include "aerial_duel.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int simulate_porco_duel(int seed) {
  unsigned int x = seed;

  /* linear congruential generator (glibc constants), two rounds to mix the seed */
  x = x * 1103515245u + 12345u;
  x = x * 1103515245u + 12345u;

  return (x >> 16) & 1;
}
/*
int main(void)
{
    int result = simulate_porco_duel(42); // 1
printf("%i",result);
}
*/
int simulate_curtis_duel(int seed) {
  unsigned int x = seed;

  /* linear congruential generator (different constants), two rounds to mix the seed */
  x = x * 214013u + 2531011u;
  x = x * 214013u + 2531011u;

  return (x >> 16) & 1;
}
/*
int main(void)
{
    int result = simulate_curtis_duel(42); // 0
    printf("%i",result);

}
*/
void run_aerial_duel(int seed) {

  pid_t pid1=fork();

  if(pid1<0 )
  {
    printf("Error : Could not fork.\n");
    return;
  }
  if(pid1==0)
  {

    int res1=simulate_porco_duel(seed);
    exit(res1);
    
  }
  pid_t pid2=fork();

  if(pid2==0)
  {
    int res2=simulate_curtis_duel(seed);
    exit(res2);
  }
  if(pid2<0 )
  {
    printf("Error : Could not fork.\n");
    return;
  }

  int status;
  int s1=0;
  int s2=0;
  for(int i=0;i<2;i++)
  {
    pid_t res=wait(&status); /*pid denfant qui vien de terminer */
    if (!WIFEXITED(status))/*verif si process enfant sans probleme fini*/
        {
            printf("Error : Child failed.\n");
            return;
        }
    if(res==pid1)
    {
      s1=WEXITSTATUS(status);/*valeur du fils*/
    }
    else if (res==pid2)
    {
      s2=WEXITSTATUS(status);
    }

  }
  

  if (s1<s2)
  {
    printf("Porco wins!\n");
  }
  else if(s2<s1)
  {
    printf("Curtis wins!\n");
  }
  else 
  {
    printf("It's a tie!\n");
  }
}

int main(void)
{
  run_aerial_duel(42);
// prints "Curtis wins!\n"

}
