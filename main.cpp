#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "lib_src/TerminalOptions.hpp"
#include "lib_src/user_class.hpp"
#include "lib_src/sgp4sdp4.hpp"

//подсчет количество строк файла
/*int count_line_in_file(std::string filename)
{
  std::ifstream File;
  File.open(filename );
  int count = 0;
  char buff[1000];
  while(!File.eof())
  {
    count ++;
    File.getline(buff,1000);
  }
  File.close();
  return count -1 ;
}*/

//функция чтения TLE файла и заполнения массива спутников
/*std::vector <sat_t> read_tle(std::string filename,int line)
{
  std::ifstream File;
  File.open(filename);
  char tle_str[3][80];
  int i = 0;
  for (int j=0; j < line/3;j++)
  {
    for (i=0; i < 3;i++)
      File.getline(tle_str[i],80);
    if (Get_Next_Tle_Set(tle_str, &sat.tle) != 1)
    { 
      std::cout << "Формат файла не соответсвует формату TLE" << std::endl;
      break;
    }
    else
    select_ephemeris(&sat);
    sat_vec.push_back(sat);
    ClearFlag(ALL_FLAGS);
  }
return sat_vec;
}
*/

/*
//SGP4 для массива TLE
std::vector <sat_t> sgp4_tle(std::vector <sat_t> sat_vec , double tsin)
{
  sat_t buff_sat;
  for (int i = 0; i<sat_vec.size();i++)
  {
    buff_sat = sat_vec[i];
    SGP4(&buff_sat, tsin);
    sat_vec[i] = buff_sat;
    Convert_Sat_State(&sat_vec[i].pos, &sat_vec[i].vel);
  }
  return sat_vec;
}
*/

/*
 //разбиение строки на время 
tm time_parse(std::string time1)
{
  tm times;
  std::string tmp [6];
  int i = 0;
  int num = 0;
  while(i!= time1.length())
  {
    if (time1[i] == '-' || time1[i] == ':')
    {  
      i++;
      num++;
    }
    tmp[num] += time1[i];
    i++;
  }
  times.tm_year  = std::stoi(tmp[0]);
  times.tm_mon   = std::stoi(tmp[1]);
  times.tm_mday  = std::stoi(tmp[2]);
  times.tm_hour  = std::stod(tmp[3]);
  times.tm_min   = std::stod(tmp[4]);
  times.tm_sec   = std::stoi(tmp[5]);
  return times;
}
*/

/*
//разбиение строки на координаты и высоту
int set_coord(geodetic_t *geodetic, std::string str)
{
  int count = 0;
  std::string tmp [3];
  for (int i = 0; i<str.length();i++)
  {
    if (str[i] == '-')
    count++;
  }
  if (count < 2) return 1;
  else
  {
    int i = 0;
    int num = 0;
    while(i!= str.length())
    {
      if (str[i] == '-')
      {
        i++;
        num++;
      }
      tmp[num] += str[i];
      i++;
    }
    geodetic -> lat  = std::stod(tmp[0]);
    geodetic -> lon  = std::stod(tmp[1]);
    geodetic -> alt  = std::stod(tmp[2]);
    return 0;
  }
}
*/

//подсчет количества видимых спутников
/*
int is_vision(std::vector <int> mass)
{
  int count = 0;

  for (int i = 0; i < mass.size();i++){
    if (mass[i] != 0){
      count++;
    }
  
  }
return count;
}
*/

/*
//индекс выдимого спутника
int vision_pos(int x, std::vector <int> mass){
  int pos = 0;
  for (int i = 0 + x; i < mass.size();i++)
      {
        if (mass[i] == 1)
         {pos = i; 
         return pos;}
         
      }
  return pos;getInputFile()
}
*/

int main(int argc, char* argv[]) 
{
  TerminalOptions       opts;

  TerminalOptions::statusReturn temp = opts.parse(argc, argv);
  if (TerminalOptions::OPTS_SUCESS == temp)
  {
    user_class            usr(opts.getInputFile());
    //time_start = time_parse(opts.getStartTime());
    //time_end = time_parse(opts.getEndTime());
    //tmp_string = opts.getCoord();
    //std::replace(tmp_string.begin(), tmp_string.end(), '-', ' ');
    //coord = Radians(opts.getDegress());
    usr.calculate_sat_duration();

    //sat_vec = read_tle(opts.getInputFile(), count_line_in_file(opts.getInputFile()));

    //double time_itr = Julian_Date(&time_start);
    //bool two_sat = false;
    //bool sec_iter = false;
/*
    if(set_coord(&geo, opts.getCoord()))
    {
      std::cout << "Неправильные координаты - " <<" [" << opts.getCoord()<<"]"<< std::endl;
      return -1;
    }
    std:: vector <int> vision;
    for (int i =0; i< sat_vec.size();i++)
      vision.push_back(0);

    while((time_itr <= Julian_Date(&time_end) ))
    {
      sat_vec = sgp4_tle(sat_vec, ThetaG_JD(time_itr));         
      for (int i = 0; i < sat_vec.size();i++)
      {
        Calculate_Obs(ThetaG_JD(time_itr), &sat_vec[i].pos, &sat_vec[i].vel, &geo, &obs_t);
        if(obs_t.el >= Radians(opts.getDegress()))
        {         
          vision[i] = 1;
          sec_iter = true;
        }
        if(obs_t.el <= Radians(opts.getDegress()) && vision[i] == 1)
        {         
          vision[i] = 0;
        }
      }   
      if (is_vision(vision) > 1 && two_sat == false)
      {
        vis_interval_vec.push_back(interval);
        Date_Time(time_itr, &time_tmp);
        vis_interval_vec[num].start = time_tmp;
        vis_interval_vec[num].end = time_end;
        vis_interval_vec[num].name1 = sat_vec[vision_pos(0,vision)].tle.sat_name;
        vis_interval_vec[num].name2 = sat_vec[vision_pos(vision_pos(0,vision)+1,vision)].tle.sat_name;
        two_sat = true;
      }
      if(is_vision(vision) <= 1 && two_sat == true)
      {
        two_sat = false;
        Date_Time(time_itr, &time_tmp);
        vis_interval_vec[num].end = time_tmp;
        sec_iter = false;
        num++;
      }
      sec_iter == true? time_start = opts.time_iter(time_start, 1) : time_start = opts.time_iter(time_start, 60);
      time_itr = Julian_Date(&time_start);
    }
  std::cout << "\nРЕЗУЛЬТАТ:" <<std::endl;
  for (int i = 0; i < vis_interval_vec.size();i++)
  {
      if (vis_interval_vec[i].name1 == "") continue; 
      std::cout <<"\n[" << vis_interval_vec[i].name1 << "]" <<"   [" << vis_interval_vec[i].name2 << "]" << std::endl;
      std::cout <<"Старт:   " <<  opts.time_string(vis_interval_vec[i].start)<<std::endl;
      std::cout <<"Финиш:   " << opts.time_string(vis_interval_vec[i].end)<<std::endl;          
  }
  */
}

else
  std::cout<<"ОШИБКА - проблема с параметрами" <<std::endl;
  
  return 0;  
}
