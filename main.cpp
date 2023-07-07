#include <iostream>
#include <fstream>
#include <vector>
#include "lib_src/TerminalOptions.hpp"
#include "lib_src/sgp4sdp4.hpp"


#define TEST_STEPS 5

sat_t                 sat;
std::vector<sat_t>    sat_vec;
obs_set_t             obs_t;
geodetic_t            geo;


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
}    

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

double time_parse(std::string time1){
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
    

    //std::cout << timeStart.tm_year << " " << timeStart.tm_mon << " " << timeStart.tm_mday << " " << timeStart.tm_hour << " " << 
    //timeStart.tm_min << " " << timeStart.tm_sec << std::endl;
    //std::cout << timeEnd.tm_year << " " << timeEnd.tm_mon << " " << timeEnd.tm_mday << " "<< timeEnd.tm_hour << " " << 
    //timeEnd.tm_min << " " << timeEnd.tm_sec << std::endl;;
    
    //std::cout << Epoch_Time(Julian_Date(&times)) << std::endl;

       //std::cout << Epoch_Time(Julian_Date(&times)) << std::endl;
        return Julian_Date(&times);
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
    std::cout<<"Using:" << opts.getInputFile() << std::endl;

    std::cout<<"User startDateTime: " <<opts.getStartTime()<<std::endl;
    std::cout<<"User endDateTime: " <<opts.getEndTime()<<std::endl;
    double time_mass[CountLineInFile(opts.getInputFile())][3];
    sat_vec = read_TLE(opts.getInputFile(), CountLineInFile(opts.getInputFile()), sat_vec);
    sat_vec = SGP4_TLE(sat_vec, Epoch_Time(time_parse(opts.getStartTime())));
    //vec_tle_print(sat_vec);
    if(set_coord(&geo, opts.getCoord())) std::cout << "Wrong coordinates - " <<" [" << opts.getCoord()<<"]"<< std::endl;
    for (int i = 0; i < sat_vec.size();i++){
    Calculate_Obs(Epoch_Time(time_parse(opts.getStartTime())), &sat_vec[i].pos, &sat_vec[i].vel, &geo, &obs_t);
    std::cout << sat_vec[i].flags<<std::endl;}
    
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
