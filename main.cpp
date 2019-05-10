#include "define.hpp"
//g++ -std=c++11 -pthread main.cpp -o thread.o && ./thread.o   
void run_thread(int sensor_number){

  int start_area = (sensor_number - 1) * PERIODS;
  // int finish_area = (sensor_number * 20) - 1;

  ifstream myfile(INPUT_FILE);
  string line;

  int counter = 0;
  
  string sensor_number_string;
  stringstream ss;
  ss << sensor_number;
  sensor_number_string = ss.str();

  string path;

  string firstval("result/result");
  string secondval(".txt");
  path = firstval + sensor_number_string + secondval;

  remove(path.c_str());//remove file with same path

  // path = RESULT_FILE;//I tried to write in one file and that file path is RESULT_FILE
  
  

  for(int i = 0; i < PERIODS ; i++){
    while(myfile >> line){
      if (counter == start_area) {
        break;
      }
      counter++;
    }

    if (line[line.size()-1] == ',') {
     line = line.substr(0, line.size()-1);
    }//before last one all number has , at the end of themselves
    
    ofstream result_file;
    result_file.open(path,ios::out|ios::app);
//first cs
    // sem_wait(&Lock);
    // // cout<<line<<'\t'<<"sensor number is :"<<sensor_number<<"   "<< Global_variable <<endl;
    // Global_variable++;
    // sem_post(&Lock);
    // if (Global_variable == NUMBER_OF_SENSOR) {
    //   Max_temperature = 0;
    //   sem_init(&Barrier2,0,0);
    //   sem_init(&Barrier3,0,0);
    //   sem_post(&Barrier);
    // }
    // sem_wait(&Barrier);
    // Global_variable--;

    // sem_post(&Barrier);
      

//first cs
    sem_wait(&Lock2);

    if (stoi(line) > Max_temperature) {
      Max_temperature = stoi(line);
    }
    // cout<< "in this stage sensor number is :" << sensor_number << " and max is :" << Max_temperature << endl;
    Global_variable2++;
    sem_post(&Lock2);
    
    if (Global_variable2 == NUMBER_OF_SENSOR) {
      sem_post(&Barrier2);
      // sem_init(&Barrier,0,0);
      sem_init(&Barrier3,0,0);
    }
    sem_wait(&Barrier2);
      Global_variable2--;
      sem_post(&Barrier2);
        
//second cs
    sem_wait(&Lock3);
    float result = float(stoi(line)) / Max_temperature;
    if (i == 0) {
      
      result_file << sensor_number;
      result_file << ": ";
    }//add sensor number in first of line
    
    result_file << result;
    result_file <<' ';
    
    // cout<<"I wrote my number is :"<<sensor_number<<endl;
    Global_variable3++;
    sem_post(&Lock3);
    
    if (Global_variable3 == NUMBER_OF_SENSOR) {
      Max_temperature = 0;
      sem_post(&Barrier3);
      sem_init(&Barrier2,0,0);
    }
    sem_wait(&Barrier3);
    Global_variable3--;
    sem_post(&Barrier3);

    result_file.close();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    
  }
  
}

int main()
{
  
  sem_init(&Barrier, 0, 0);
  sem_init(&Barrier2, 0, 0);
  sem_init(&Barrier3, 0, 0);
  
  sem_init(&Lock, 0, 1);
  sem_init(&Lock2, 0, 1);
  sem_init(&Lock3, 0, 1);
  


  std::thread t1 (run_thread,1);
  std::thread t2 (run_thread,2);
  std::thread t3 (run_thread,3);
  std::thread t4 (run_thread,4);
  std::thread t5 (run_thread,5);
  std::thread t6 (run_thread,6);
  std::thread t7 (run_thread,7);
  std::thread t8 (run_thread,8);
  std::thread t9 (run_thread,9);
  std::thread t10 (run_thread,10);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  t7.join();
  t8.join();
  t9.join();
  t10.join();
  
  return 0;
}
