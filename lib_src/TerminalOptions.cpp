
#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

namespace fs = boost::filesystem;
using namespace boost::gregorian;
using namespace boost::posix_time;

#include "TerminalOptions.hpp"

TerminalOptions::TerminalOptions():
    myOptions       (""),
    myInputFile     (""),
    myStartDateTime ("2023-01-01-00:00:00"),
    myEndDateTime   ("2023-01-02-00:00:00"),
    myCoord         ("60.0-30.0-0.0"),
    myDegress       (30.0)
   {
    setup();
   }

TerminalOptions::~TerminalOptions(){}

void TerminalOptions::setup()
{
    po::options_description options( "Параметры" );
    options.add_options()
    ("help,h","Меню параметров.")
    ("file,f", po::value<std::string>(&myInputFile),"Путь к файлу TLE")
    ("start,s",po::value<std::string>(&myStartDateTime),"Время старта       [YYYY-MM-DD-HH:MM:SS]")
    ("end,e", po::value<std::string>(&myEndDateTime),"Время финиша       [YYYY-MM-DD-HH:MM:SS]")
    ("crd,c",po::value<std::string>(&myCoord),"Координаты наблюдателя: широта долгота высота [x.x-x.x-x.x]")
    ("deg,d",po::value<double> (&myDegress),"Угол наблюдения");
    myOptions.add(options);

}
TerminalOptions::statusReturn TerminalOptions::parse(int argc, char* argv[]){
    statusReturn ret = OPTS_SUCESS;
    po::variables_map varMap;
    char filename[5000];

    try{
        po::store (po::parse_command_line(argc,argv,myOptions),varMap);
        po::notify(varMap);
    
        if (varMap.count("help")){
            std::cout<<myOptions<<std::endl;
            return OPTS_HELP;
        }
        if (!(0 < varMap.count("file")) ){
            std::cout<< "ОШИБКА - Отсутвует входной файл!!!" << std::endl; 
            std::cout<< myOptions<<std::endl;
            return OPTS_FAILURE;
        }
        else{
            boost::algorithm::trim(myInputFile);

            realpath(myInputFile.c_str(),filename);
            myInputFile = filename;
            ret = validateFiles()? OPTS_SUCESS : OPTS_FAILURE;

        }
    }
    catch(std::exception &e){
        std::cout<<"ОШИБКА - ошибка парсинга: " <<e.what() << std::endl;
        ret = OPTS_FAILURE;
    }
    catch(...){
        std::cout<<"ОШИБКА- ошибка парсинга (неизвестная ошибка)." << std::endl;
        ret = OPTS_FAILURE;
    }
    return ret;
}

bool TerminalOptions::validateFiles(){
    if(!boost::filesystem::is_regular_file(myInputFile))
    {
        std::cout<<"ОШИБКА - файл по данному пути не найден! [" << myInputFile <<"]"<<std::endl;
        return false;
    }
    return true;
}



//итерация времени в секундах
std::tm TerminalOptions::time_iter(tm time, int sec){
    tm mt = time;
    mt.tm_mon --;
    ptime xTime = ptime_from_tm(mt); 
    time_iterator xIt(xTime, seconds(sec));
    ++xIt;
    std::string str = to_simple_string(*xIt);
    xTime = *xIt;
    mt = to_tm(xTime);
    mt.tm_mon++;
    return mt;
    
    }

//перевод тм времени в формат boost::posix_time
std::string TerminalOptions::time_string(tm time){
    tm mt = time;
    ptime xTime = ptime_from_tm(mt);
    std::string str = to_simple_string(xTime);

    return str;
}