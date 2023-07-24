#ifndef _USER_CLASS_HPP_
#define _USER_CLASS_HPP_

#include <fstream>
#include "TerminalOptions.hpp"

class user_class : private TerminalOptions {

public:

struct vis_interval{
std::string name1, name2;
std::tm start, end;
};

user_class(std::string filename);
~user_class();


void print_result();

protected:

private:

//чтение tle файла в вектор <sat_t>
std::vector <sat_t> read_tle(std::string filename, int line);

//расчет вектор с помошью алгоритма sgp4 
std::vector <sat_t> sgp4_tle(std::vector <sat_t> sat_vec , double tsin);

//разбиение строки на дату и время
tm time_parse(std::string time);

//разбиение строки на координаты и высоту
int set_coord(geodetic_t *geodetic, std::string str);

//проверка на видимость массив спутников
int is_vision(std::vector <int> mass);

//индекс видимого спутника
int vision_pos(int x, std::vector <int> mass);

//число строк в файле
int count_line_in_file(std::string filename);

//расчет интервалов видимости пар спутников
void calculate_sat_duration();

std::string                     coord;                  // координаты (широта\долгота\высота)
std::string                     file;                   // путь к файлу
vis_interval                    interval;               // интервал видимости (начало-конец; спутник1, спутник2)
std::vector <vis_interval>      vis_interval_vec;       // вектор интервалов
std::vector <int>               vision;                 // массив видимости спутников в текущий момент времени
std::vector <sat_t>             sat_vec;                // вектор данных спутников 
obs_set_t                       obs_t;                  // данные наблюдателя
geodetic_t                      geo;                    // геоцентрическая позиция
tm                              time_start, time_end;   // время начала и конца наблюдения
bool                            two_sat;                // флаг видимости двух спутников в текущий момент времени
bool                            sec_iter;               // флаг иттерации по секунда (по умолчанию иттерация в минутах)
int                             vision_index;           // индекс вектора *vis_intreval_vec*
double                          time_itr;               // иттерации по времени
double                          rad_degress;            // угол в радианах

};


#endif //_USER_CLASS_HPP_