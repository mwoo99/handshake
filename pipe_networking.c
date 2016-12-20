#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "pipe_networking.h"


int server_handshake(int *from){
  MESSAGE_BUFFER_SIZE = 128;
  char buffer[MESSAGE_BUFFER_SIZE];

  //1. Server creates a FIFO (Well Known Pipe)
  mkfifo("wkp",0644);
  printf("[SERVER] WKP Created\n");
  int pipe = open("wkp",O_RDONLY);
  *from = pipe;


  //2. Server waits for a connection
  printf("[SERVER] waiting for client\n");
  read(pipe,buffer,sizeof(buffer));

  //6. Server receives client’s message and removes the WKP
  printf("[SERVER] Received: %s\n", buffer);
  close(pipe);
  remove("wkp");

//7. Server connects to client FIFO, sending an initial acknowledgement message.
  int message = open (buffer, O_WRONLY);
  write(message, "boi", 10); 
  printf("[SERVER] message of acknowledgement sent\n");
  return message;
}

int client_handshake(int* to){
  MESSAGE_BUFFER_SIZE = 128;
  char buffer[MESSAGE_BUFFER_SIZE];

  //3. Client create a “private” FIFO
  mkfifo("pp",0644);
  *to = open("pp",O_WRONLY);
  printf("[CLIENT] PP Created");

  //4. Client connects to server and send the private FIFO name
  //*to = open("WKP", O_WRONLY);
  int pipe = open("wkp", O_WRONLY);
  write(pipe,"pp",10);
  printf("[CLIENT] private FIFO name sent\n");

  //5. Client waits for a message from the server
  //read(pp, buffer, sizeof(buffer));
  int message = open("pp",O_RDONLY);
  read(message, buffer, 10);
  
  //8. Client receives server’s message, removes its private
  //printf("[CLIENT] Message from Server: %s\n",message);
  printf("[CLIENT] Server has connected. \n");


  //9. Client sends acknowledgement message.
  //write(*to, "fin", 10);
  remove("pp");
}
