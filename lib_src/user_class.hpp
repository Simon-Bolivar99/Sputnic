#ifndef _USER_CLASS_HPP_
#define _USER_CLASS_HPP_

#include <fstream>
#include "TerminalOptions.hpp"

class user_class : public TerminalOptions {

public:

struct vis_interval{
std::string name1, name2;
std::tm start, end;
};

user_class(std::string filename);
~user_class();
std::vector <sat_t> read_tle(std::string filename, int line);
std::vector <sat_t> sgp4_tle(std::vector <sat_t> sat_vec , double tsin);
void calculate_sat_duration();
void print_result(vis_interval *vector);
tm time_parse(std::string time);
int set_coord(geodetic_t *geodetic, std::string str);
int is_vision(std::vector <int> mass);
int vision_pos(int x, std::vector <int> mass);
int count_line_in_file(std::string filename);

protected:

private:

std::string                     coord;
std::string                     file;
vis_interval                    interval;
std::vector <vis_interval>      vis_interval_vec;
std::vector <int>               vision;
std::vector <sat_t>             sat_vec;
obs_set_t                       obs_t;
geodetic_t                      geo;
tm                              time_start, time_end;
bool                            two_sat, sec_iter;
int                             vision_index;
double                          time_iter , rad_degress;

};


#endif //_USER_CLASS_HPP_