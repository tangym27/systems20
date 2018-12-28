#include "pipe_networking.h"

static void sighandler(int signo){
  if(signo == SIGINT){
    printf("\nEnding client\n");

    exit(0);
  }
}

int main() {
  signal(SIGINT, sighandler);

  int to_server;
  int from_server;
  char message[BUFFER_SIZE];

  from_server = client_handshake( &to_server );

  while(1) {

    // gets a message from the client
    printf("[CLIENT] Write a message to the server: ");
    fgets(message, BUFFER_SIZE, stdin);
    message[strlen(message)-1] = '\0';

    // writes it to the server
    write(to_server, message, BUFFER_SIZE);
    printf("[CLIENT] Message sent: %s\n", message);

    // reads the newly processed info from the server
    read(from_server, message, BUFFER_SIZE);
    printf("[CLIENT] Message received: %s\n", message);
  }
}
