/*
* Filename: server.cpp
* Author: Zelin Liu
* Date: 2019/08/13
* Description: Server implementations
* Instruction:
*/

/*
* @param:hostname the ip address of server
* @param:port The port of the server
* @param:num_thread The number of thread to launch
* @param:socket_per_thread The number of sockets each thread supports
*/
Server::Server(std::string hostname, std::string port, int num_thread, int socket_per_thread){
  this->hostname = hostname;
  this->port = port;
  if(num_thread > SERVER_NUM_THREAD_MAX || num_thread < SERVER_NUM_THREAD_MIN){
    throw std::runtime_error("Server created with wrong num_thread value : " + std::to_string(num_thread));
  }
  if(socket_per_thread > SERVER_SOCKET_PER_THREAD_MAX || socket_per_thread < SERVER_SOCKET_PER_THREAD_MIN){
    throw std::runtime_error("Server created with wrong socket_per_thread value : " + std::to_string(socket_per_thread));
  }
  this->num_thread = num_thread;
  this->socket_per_thread = socket_per_thread;
}

/*
*
*/
int command(int command){
  switch(cmd){

    default:
    break;
  }
}

/*
*
*/
