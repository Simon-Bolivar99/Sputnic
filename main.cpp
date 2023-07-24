#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "lib_src/TerminalOptions.hpp"
#include "lib_src/user_class.hpp"
#include "lib_src/sgp4sdp4.hpp"


int main(int argc, char* argv[]) 
{
  TerminalOptions       opts;
  TerminalOptions::statusReturn temp = opts.parse(argc, argv);
  if (TerminalOptions::OPTS_SUCESS == temp)
  {
    user_class  usr(opts.getInputFile());
    usr.print_result();
  }
else
  std::cout<<"ОШИБКА - проблема с параметрами" <<std::endl;

  return 0;  
}
