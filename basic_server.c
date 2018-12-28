#include "pipe_networking.h"

static void sighandler(int signo){
  if(signo == SIGINT){
    printf("\nEnding server\n");
    remove("wkp");
    exit(0);
  }
}

int main() {
  signal(SIGINT, sighandler);

  int to_client;
  int from_client;
  char message[BUFFER_SIZE];

  while(1) {
    from_client = server_handshake( &to_client );
    if (from_client){
      // continue reading until an error/end of file
      while(read(from_client, message, BUFFER_SIZE) > 0) {
        printf("[SUBSERVER] Message server received: %s\n", message);
        //process the data
        for(int i = 0; i < strlen(message); i++) {
          message[i] += 13;
        }
        message[strlen(message)-1]='!';
        // write back to client
        write(to_client, message, BUFFER_SIZE);
        printf("[SUBSERVER] Message server sent back: %s\n", message);
      }
      // set up for new client
      printf("[SUBSERVER] Client disconnected. [SERVER] is still open!\n");
    }
  }
  return 0;
}
