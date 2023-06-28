#include <iostream>
#include "lib_src/TerminalOptions.hpp"
#include "lib_src/sgp4sdp4.hpp"

int main(int argc, char* argv[]) 
{

  TerminalOptions opts;

  TerminalOptions::statusReturn temp = opts.parse(argc, argv);
  if (TerminalOptions::OPTS_SUCESS == temp){
    std::cout<<"Using:" << opts.getInputFile() << std::endl;

    std::cout<<"User startDateTime:" <<opts.getStartTime()<<std::endl;
    std::cout<<"User endDateTime:" <<opts.getEndTime()<<std::endl;
  }
else if ( TerminalOptions::OPTS_HELP == temp)
{
 
}
else{
  std::cout<<"ERROR - problem with options" <<std::endl;
}
  return 0;  
}
