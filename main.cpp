#include <iostream>
#include <fstream>
#include "lib_src/TerminalOptions.hpp"
#include "lib_src/sgp4sdp4.hpp"
#define TEST_STEPS 5

sat_t sat;
typedef struct {
    double          t;
    double          x;
    double          y;
    double          z;
    double          vx;
    double          vy;
    double          vz;
} dataset_t;


const dataset_t expected[TEST_STEPS] = {
    {0.0,
     2328.97048951, -5995.22076416, 1719.97067261,
     2.91207230, -0.98341546, -7.09081703},
    {360.0,
     2456.10705566, -6071.93853760, 1222.89727783,
     2.67938992, -0.44829041, -7.22879231},
    {720.0,
     2567.56195068, -6112.50384522, 713.96397400,
     2.44024599, 0.09810869, -7.31995916},
    {1080.0,
     2663.09078980, -6115.48229980, 196.39640427,
     2.19611958, 0.65241995, -7.36282432},
    {1440.0,
     2742.55133057, -6079.67144775, -326.38095856,
     1.94850229, 1.21106251, -7.35619372}
};


int CountLineInFile(std::string filename){
  std::ifstream File;
  File.open(filename );
  int count = 0;
  char buff[1000];
  while(!File.eof()){
    count ++;
    File.getline(buff,1000);
    }
  File.close();
  return count -1 ;
}

void open_TLE(std::string filename,int line){
  std::ifstream File;
  File.open(filename);
  int count = -1;
  char tle_str[line][80];
  char buff [1000];

 for (int i = 0; i < line;i++){
  File.getline(tle_str[i],80);
  std::cout << "LINE [" << i << "] :" << tle_str[i] << std::endl;
 }
  Get_Next_Tle_Set(tle_str, &sat.tle);


  select_ephemeris(&sat);


}

int main(int argc, char* argv[]) 
{

  TerminalOptions opts;

  TerminalOptions::statusReturn temp = opts.parse(argc, argv);
  if (TerminalOptions::OPTS_SUCESS == temp){
    std::cout<<"Using:" << opts.getInputFile() << std::endl;

    std::cout<<"User startDateTime: " <<opts.getStartTime()<<std::endl;
    std::cout<<"User endDateTime: " <<opts.getEndTime()<<std::endl;
    std::cout<<"Number of lines: " << CountLineInFile(opts.getInputFile()) << std::endl;
    open_TLE(opts.getInputFile(), CountLineInFile(opts.getInputFile()));
  }
else if ( TerminalOptions::OPTS_HELP == temp)
{
 
}
else{
  std::cout<<"ERROR - problem with options" <<std::endl;
}
  std::cout << opts.print(opts.getStartTime()) << std::endl;
  std::cout << opts.print(opts.getEndTime()) << std::endl;
  
  return 0;  
}
