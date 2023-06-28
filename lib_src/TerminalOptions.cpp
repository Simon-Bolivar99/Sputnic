
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/algorithm/string/trim.hpp>
namespace fs = boost::filesystem;

#include "TerminalOptions.hpp"

TerminalOptions::TerminalOptions():
    myOptions       (""),
    myInputFile     (""),
    myStartDateTime (""),
    myEndDateTime   (""),
    myCoord         (""),
    myDegress       (0.0)
   {
    setup();
   }

TerminalOptions::~TerminalOptions(){}

void TerminalOptions::setup()
{
    po::options_description options( "Program Options" );
    options.add_options()
    ("help,h","Display help menu.")
    ("file,f", po::value<std::string>(&myInputFile),"User-specified value")
    ("start,s",po::value<std::string>(&myStartDateTime),"Start time")
    ("end,s", po::value<std::string>(&myEndDateTime),"End time")
    ("crd,c",po::value<std::string>(&myCoord),"Coordinate latitude longitude height")
    ("deg,d",po::value<double> (&myDegress),"Degress");
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
        if (!(0 < varMap.count("file"))){
            std::cout<< "ERROR - Input file must be specified!!!" << std::endl; 
            std::cout<< myOptions<<std::endl;
            return OPTS_FAILURE;
        }
        else{
            boost::algorithm::trim(myInputFile);

            realpath(myInputFile.c_str(),filename);
            myInputFile = filename;
            ret = validateFiles()? OPTS_SUCESS : OPTS_FAILURE;

        }
        if (!varMap["start"].defaulted()) {
            std::cout<< "Warning - Default value for User-time1 overwtiren to " << myStartDateTime << std::endl;
        }
    }
    catch(std::exception &e){
        std::cout<<"ERROR - paseing error: " <<e.what() << std::endl;
        ret = OPTS_FAILURE;
    }
    catch(...){
        std::cout<<"ERROR - parsing error (unknow type)." << std::endl;
        ret = OPTS_FAILURE;
    }
    return ret;
}

bool TerminalOptions::validateFiles(){
    if(!boost::filesystem::is_regular_file(myInputFile))
    {
        std::cout<<"ERROR - Input file provided does not exist! [" << myInputFile <<"]"<<std::endl;
        return false;
    }
    return true;
}