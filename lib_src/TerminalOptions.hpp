#ifndef _TERMINAL_OPTIONS_HPP_
#define _TERMINAL_OPTIONS_HPP_

#include <string>
#include <boost/program_options.hpp>
namespace po = boost::program_options;

/*
[-h| --help ]                        Help menu
[-f| --file ] ARG (std::string)      Input file
[-s| --start] ARG (double)           Start time
[-e| --end  ] ARG (double)           End time
[-c| --crd  ] ARG (str)              latitude longitude height
*/

class TerminalOptions {
    public:
    enum statusReturn{
        OPTS_SUCESS,
        OPTS_VERSION,
        OPTS_HELP,
        OPTS_FAILURE

    };

    TerminalOptions();
    ~TerminalOptions();
    statusReturn parse(int argc, char * argv[]);

    inline const std::string & getInputFile() const;
    inline const double getStartTime() {return startTime;};
    inline const double getEndTime() {return endTime;};
    inline const std::string & getCoord() const;

    protected:
    void setup();
    bool validateFiles();

    private:
    TerminalOptions(const TerminalOptions &rhs);
    TerminalOptions &operator=(const TerminalOptions &rhs);

    po::options_description myOptions;
    std::string myInputFile;
    double startTime;
    double endTime;




};
inline const std::string & TerminalOptions::getInputFile() const{
    static const std::string emptyString;
    return (0 < myInputFile.size())? myInputFile : emptyString;
}

#endif //_TERMINAL_OPTIONS_HPP_