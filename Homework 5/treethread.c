#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

/* Convert a string to an int */
int stoi(char* value)
{
  /* Determine string length */
  int curPos = 0;
  while (value[curPos] != '\0')
    ++curPos;
  int strlen = curPos;
  curPos = 0;
    
  int multiplier = pow(10, strlen - 1);
    
  /* Increment through string, converting
   * values and multiplying by appropriate
   * multiplier
   */
  int final = 0;
  while (value[curPos] != '\0')
    {
      int temp = value[curPos] - 48;
      temp *= multiplier;
      final += temp;
      multiplier /= 10;
      curPos++;
    }
  return final;
}

int numThreads;
pthread_t* threadID;
int threadCount = 0;
int numParents;

void *printTree(void *curThread)
{
  long curT = (long)curThread;
    
  if (curT < numParents)
    {
      long temp = (2 * curT) + 1;

      /* Create and reap threads */
      pthread_create(&threadID[threadCount], NULL, printTree, (void*)temp);
      pthread_join(threadID[threadCount], NULL);
      ++threadCount;
      ++temp;

      pthread_create(&threadID[threadCount], NULL, printTree, (void*)temp);
      pthread_join(threadID[threadCount], NULL);
      ++threadCount;
    }
    
  printf("%s %ld %s\n", "Thread", curT, "done");
}

int main(int argc, char** argv)
{
  /* Check number of arguments */
  if (argc != 2)
    {
      printf("ERROR: Wrong number of arguments\n");
      exit(1);
    }
    
  /* Check validity of argument */
  numThreads = stoi(argv[1]);
  if (numThreads <= 0)
    {
      printf("ERROR: Number of threads must be positive\n");
      exit(1);
    }
    
  /* Determine number of threads to create */
  int i;
  int nThreads = 2;
  for (i = 1; i < numThreads; ++i)
    nThreads *= 2;
  nThreads -= 2;
    
  /* Create binary tree if more than one thread */
  threadID = (pthread_t*)malloc(sizeof(pthread_t*) * nThreads);
  if (numThreads != 1)
    {
      numParents = pow(2, numThreads) - 1 - pow(2, numThreads - 1);

      long count;
      for (count = 1; count < 3; ++count)
        {
	  pthread_create(&threadID[threadCount], NULL, printTree, (void*)count);
	  pthread_join(threadID[threadCount], NULL);
	  threadCount++;
        }
    }
    
  free(threadID);

  printf("%s %d %s\n", "Thread", 0, "done");
  return 0;
}
