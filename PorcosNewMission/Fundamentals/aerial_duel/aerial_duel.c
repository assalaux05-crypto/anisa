#include "aerial_duel.h"

#include <stdio.h>

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



}