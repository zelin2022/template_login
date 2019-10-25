/*
* Filename: template_login.cpp
* Author: Zelin Liu
* Date: 2019/07/21
* Description: main file for template login project
* Instruction: compile with

g++ template_login.cpp -std=c++17 -I /usr/local/include/mysql++/ -I /usr/include/mysql/ -lmysqlpp -lmysqlclient

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

  Server *server = new Server(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]));

    server->start();
    while(!server->check_want_exit()){}
  // std::string command;
  // while(true)
  // {
  //   #ifdef _DEBUG
  //   std::cout<<"begining loop in main()\n";
  //   #endif
  //
  //   // std::cin.sync();
  //   // std::getline(std::cin, command, '\n');
  //   while(!(std::cin>>command)){
  //     std::cin.clear();
  //     std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
  //     std::cout<<"failed\n";
  //   }
  //   // std::cout<<"hi\n";
  //   // std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
  //
  //
  //   server->give_command(command);
  //   command.clear();
  //
  //   if(server->check_want_exit())
  //   {
  //     server->exit();
  //     break;
  //   }
  //
  // }
  delete(server);
  return 0;
}
