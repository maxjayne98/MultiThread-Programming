#include <iostream>
#include <thread>
#include <fstream>
#include <semaphore.h>
#include <typeinfo>
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>

using namespace std;
#define INPUT_FILE "input.txt"
#define RESULT_FILE "result/result_file.txt"
#define PERIODS 20
#define NUMBER_OF_SENSOR 10

int Max_temperature = 0;
int Global_variable = 0;
int Global_variable2 = 0;
int Global_variable3 = 0;
sem_t Barrier;
sem_t Barrier2;
sem_t Barrier3;

sem_t Lock;
sem_t Lock2;
sem_t Lock3;