#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "pipe_networking.h"

int client_handshake(int* to){
  MESSAGE_BUFFER_SIZE = 128;
  
  mkfifo("hello",0644);
  *to = open("hello",O_WRONLY);
  
  mkfifo(getpid(),0644);
  int ret = open(getpid(),O_RDONLY);
  
  write(*to,getpid(),sizeof(int));
  
  char message[128];
  read(ret,&message,sizeof(message));
  //remove private pipe here.
  
  return ret;
}

int server_handshake(int* from){
  MESSAGE_BUFFER_SIZE = 128;
  
  mkfifo("hello",0644);
  *from = open("hello",O_RDONLY);
  
  int cpid;
  read(*from,&cpid,sizeof(int));

  mkfifo(cpid,0644);
  int ret = open(cpid,O_WRONLY); 
  
  char c[3] = "hey";
  write(ret, c, sizeof(c)); 
  //remove wkp here
  
  char message[128];
  read(*from, &message, sizeof(message));
  
}
