#include <iostream>
#include <fstream>
#include <vector>
#include "lib_src/TerminalOptions.hpp"
#include "lib_src/sgp4sdp4.hpp"


#define TEST_STEPS 5
#define _MINUTE_STEP_ 
#define _SECOND_STEP_ 

sat_t                 sat;
std::vector<sat_t>    sat_vec;
obs_set_t             obs_t;
geodetic_t            geo;
tm                    time_start, time_end, time_tmp;

typedef struct{
std::string name;
tm start, end;
int visible = 0;
std::vector <std::string> time_interval;
} vis_interval;

std::vector <vis_interval> vis_vec;

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
/*
void vec_tle_print(std::vector <sat_t> sat_vec){
  if (sat_vec.empty()){
    std::cout<< "vector is empty" << std::endl;
    
  }
  else{
  for(int i = 0; i < sat_vec.size();i++)
  std::cout <<"\n["<<    i+1          << "]"
            <<"\n" << "epoch : "      << sat_vec[i].tle.epoch
            <<"\n" << "epoch day : "  << sat_vec[i].tle.epoch_day
            <<"\n" << "sat name: "    << sat_vec[i].tle.sat_name
            <<"\n" << "sat.x "        << sat_vec[i].pos.x
            <<std::endl;
  
  }
} */   

std::vector <sat_t> read_TLE(std::string filename,int line, std::vector <sat_t> sat_vec){
  std::ifstream File;
  File.open(filename);
  char tle_str[3][80];
int i = 0;
for (int j=0; j < line/3;j++){
 for (i=0; i < 3;i++){
  File.getline(tle_str[i],80);
 }
 if (Get_Next_Tle_Set(tle_str, &sat.tle) != 1){ 
    std::cout << "Format doesn`t match TLE" << std::endl;
    break;
  }
  else
  select_ephemeris(&sat);
  sat_vec.push_back(sat);
  ClearFlag(ALL_FLAGS);


}
return sat_vec;
 
}

std::vector <sat_t> SGP4_TLE(std::vector <sat_t> sat_vec , double tsin){
  sat_t buff_sat;
  for (int i = 0; i<sat_vec.size();i++){
  buff_sat = sat_vec[i];
  SGP4(&buff_sat, tsin);
  sat_vec[i] = buff_sat;
  Convert_Sat_State(&sat_vec[i].pos, &sat_vec[i].vel);
  }

  return sat_vec;
}

tm time_parse(std::string time1){
    tm times , timeEnd;
    std::string tmp = "0";
    
    int i = 0;
    while(time1[i] != '-'){
      tmp += time1[i];
      i++;
    }
    
    times.tm_year = std::stoi(tmp);
   

    i++;
    tmp = "0";
   
    while(time1[i] != '-'){
      tmp += time1[i];
      
      i++;
    }

    times.tm_mon = std::stoi(tmp);
    

    i++;
    tmp = "0";
    
 while(time1[i] != '-'){
      tmp += time1[i];
  
      i++;
    }

    times.tm_mday = std::stoi(tmp);
    

    i++;
    tmp = "0";
    
 while(time1[i] != ':'){
      tmp += time1[i];
      
      i++;
    }

    times.tm_hour = std::stoi(tmp);
    
    
    i++;
    tmp = "0";
    
 while(time1[i] != ':'){
      tmp += time1[i];
      
      i++;
    }

    times.tm_min = std::stoi(tmp);
    

    i++;
    tmp = "0";
    

 while(i != time1.length()){
      tmp += time1[i];
      
      i++;
    }

    times.tm_sec = std::stoi(tmp);
    

        return times;
}


int set_coord(geodetic_t *geodetic, std::string str){
    
    int count = 0;
    double lat,lon,alt;
    std::string tmp = " ";

    for (int i = 0; i<str.length();i++){
      if (str[i] == '.')
        count++;
    }
    if (count <3)
    return 1;
    else{
        
        
        int i = 0;
        while (str[i] != '-'){
            tmp += str[i];
            i++;
        }
        lat = std::stod(tmp);
        tmp = " ";
        i++;
        while (str[i] != '-'){
            tmp += str[i];
            i++;
        }
        lon = std::stod(tmp);
        tmp = " ";
        i++;
        while (i != str.length()){
            tmp += str[i];
            i++;
        }
        alt = std::stod(tmp);

        geodetic ->lat = lat;
        geodetic -> lon = lon;
        geodetic -> alt = alt;
        
        return 0;
      }
      
}


int main(int argc, char* argv[]) 
{
  TerminalOptions       opts;
  TerminalOptions::statusReturn temp = opts.parse(argc, argv);
  if (TerminalOptions::OPTS_SUCESS == temp){

    
    //time_start = time_parse(opts.getStartTime());
    //time_end = time_parse(opts.getEndTime());
    time_start = time_parse("2023-01-01-00:00:00");
    time_end = time_parse("2023-01-01-01:00:01");
    vis_interval interval;

    for (int i = 0; i<CountLineInFile(opts.getInputFile());i++)
      vis_vec.push_back(interval);

    
  
    std::cout<<"Using:" << opts.getInputFile() << std::endl;

    std::cout<<"User startDateTime: " <<opts.getStartTime()<<std::endl;
    std::cout<<"User endDateTime: " <<opts.getEndTime()<<std::endl;

    sat_vec = read_TLE(opts.getInputFile(), CountLineInFile(opts.getInputFile()), sat_vec);

    double time_itr = Julian_Date(&time_start);

    if(set_coord(&geo, opts.getCoord())) std::cout << "Wrong coordinates - " <<" [" << opts.getCoord()<<"]"<< std::endl;
    for(int j = 0; j < 86400; j++){
      sat_vec = SGP4_TLE(sat_vec, ThetaG_JD(time_itr));
      
      for (int i = 0; i < sat_vec.size();i++){
        Calculate_Obs(ThetaG_JD(time_itr), &sat_vec[i].pos, &sat_vec[i].vel, &geo, &obs_t);
        if(obs_t.el >= Radians(30)){
          if (vis_vec[i].visible == 0){
          vis_vec[i].visible = 1;
          Time_of_Day(time_itr, &time_tmp);
          Calendar_Date(time_itr, &time_tmp);
          vis_vec[i].start = time_tmp;
          
        }
 
              }
          if(vis_vec[i].visible == 1 && obs_t.el <= Radians(30)){
            vis_vec[i].visible = 3;
            Time_of_Day(time_itr, &time_tmp);
            Calendar_Date(time_itr, &time_tmp);
            vis_vec[i].end = time_tmp;
        }
             
              

    }
              time_start = opts.time_iter(time_start, 1);
              time_itr = Julian_Date(&time_start);
    }
  for (int i = 0; i < sat_vec.size();i++){
      std::cout <<"[" << i << "]" << std::endl;
      std::cout <<"Start: " << vis_vec[i].start.tm_hour << ":"<< vis_vec[i].start.tm_min << ":" << vis_vec[i].start.tm_sec 
      << " " << vis_vec[i].start.tm_mday << "."<< vis_vec[i].start.tm_mon <<" " << vis_vec[i].start.tm_year<<std::endl;
      std::cout <<"End: " << vis_vec[i].end.tm_hour << ":"<< vis_vec[i].end.tm_min << ":" << vis_vec[i].end.tm_sec 
      << " " << vis_vec[i].end.tm_mday << "."<< vis_vec[i].end.tm_mon <<" " << vis_vec[i].end.tm_year<<std::endl;
  }
  
}
else if ( TerminalOptions::OPTS_HELP == temp)
{
 
}
else{
  std::cout<<"ERROR - problem with options" <<std::endl;
}
  /*std::cout.setf(std::ios::fixed);
  std::cout.precision(40); //0 - число символов после точки
   std::cout.precision(4); //0 - число символов после точки
  */


  
  return 0;  
}
