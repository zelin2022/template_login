/*
* Filename: template_login.cpp
* Author: Zelin Liu
* Date: 2019/07/21
* Description: main file for template login project
* Instruction: compile with ____
*/
#include <cstdlib>
#include <iostream>
#include <string>
#include "lib/server.hpp"

int main(int argc, char** argv)
{

  if (argc != 5)
  {
    printf("wrong argc\n");
    return -1;
  }

  Server server = new Server(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]));

  std::string command;

  while(true)
  {

    std::cin >> command;
    server.give_command(command);

    if(server.check_want_exit())
    {
      server.exit();
      break;
    }

  }
  delete(server);
  return 0;
}
