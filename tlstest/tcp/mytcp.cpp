/*
* Filename: mytcp.cpp
* Author: Zelin Liu
* Date: 2019/07/28
* Description:
* Instruction:
*/


Mytcp::Mytcp(){
  this->mysock = -1;
  this->is_listening = false;
}

Mytcp::set_my_sock(char * ip, char* port){

  int sockfd;
  struct addrinfo hints, *myinfo, *p;
  memset(&hints, 0, sizeof (hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE; // use my IP

  int rv;
  if ((rv = getaddrinfo(ip, port, &hints, &myinfo)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    return -1;
  }


  for(p = myinfo; p != NULL; p = p->ai_next) {
    if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
      perror("server: socket");
      continue;
    }

    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
      perror("setsockopt");
      continue;
    }

    if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sockfd);
      perror("server: bind");
      continue;
    }
    break;
  }

  freeaddrinfo(myinfo); // all done with this structure

  if (p == NULL)  {
    fprintf(stderr, "my addr: failed\n");
    return(-1);
  }

  this->mysock = sockfd;
}

int Mytcp::get_sock_by_connect(char * ip, char * port){
  if(is_listening){ //listen() is called, can't connect
    return -1;
  }
  struct addrinfo hints, *theirinfo, *p;
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  int rv;
  if ((rv = getaddrinfo(host, port, &hints, &theirinfo)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    return -1;
  }
  for (p = theirinfo; p != NULL; p=p->ai_next){
    if (connect(socket, p->ai_addr, p->ai_addrlen) == -1) {

      perror("client: connect");
      continue;
    }
    break;
  }
  freeaddrinfo(theirinfo); // all done with this structure

  if (p == NULL)  {
    fprintf(stderr, "my addr: failed\n");
    close(socket);
    return(-1);
  }

  return socket;

}

int Mytcp::listen(){
  if(is_listening){ //already listen() ????
    return 1;
  }
  if (listen(socket, 10) == -1) {
    perror("listen");
    return -1;
  }
  return 0;
}
int Mytcp::get_sock_by_accept(){
  if(!is_listening){ // if haven't started listen() yet
    return -1;
  }
  return accept(socket, their_addr, sin_size);
}
