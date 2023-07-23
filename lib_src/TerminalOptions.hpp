#ifndef _TERMINAL_OPTIONS_HPP_
#define _TERMINAL_OPTIONS_HPP_

#include <string>
#include <boost/program_options.hpp>
#include "sgp4sdp4.hpp"

namespace po = boost::program_options;

/*
[-h| --help ]                        Help menu
[-f| --file ] ARG (str)              Input file
[-s| --start] ARG (str)              Start time
[-e| --end  ] ARG (str)              End time
[-c| --crd  ] ARG (str)              latitude longitude height
[-d| --deg  ] AGR (double)
*/

class TerminalOptions {
    public:
    enum statusReturn{
        OPTS_SUCESS,
        OPTS_HELP,
        OPTS_FAILURE

    };

    TerminalOptions();
    ~TerminalOptions();
    statusReturn parse(int argc, char * argv[]);

    inline const std::string & getInputFile()       {return myInputFile;}
    inline const std::string & getStartTime()       {return myStartDateTime;}
    inline const std::string & getEndTime()         {return myEndDateTime;}
    inline const std::string & getCoord()           {return myCoord;}
    inline const double      & getDegress()         {return myDegress;}
    std::string time_string(tm time);
    std::string print(std::string str);
    std::tm time_iter(tm time, int sec);
    
   

    protected:
    void setup();
    bool validateFiles();

    
    

    private:
    TerminalOptions(const TerminalOptions &rhs);
    TerminalOptions &operator=(const TerminalOptions &rhs);

    po::options_description myOptions;
    std::string myInputFile;
    std::string myStartDateTime;
    std::string myEndDateTime;
    std::string myCoord;
    double myDegress;




};


#endif //_TERMINAL_OPTIONS_HPP_