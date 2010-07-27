#include "Silk.h"

TServerSocket::TServerSocket(int port) {
  isValid = false;
  fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd < 0) {
    perror("socket");
    return;
  }
  printf("Listen Socket fd %d\n", fd);

  {
    int on = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
    //    setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, (char *)&on, sizeof(on));
  }
  struct sockaddr_in my_addr;
  bzero(&my_addr, sizeof(my_addr));
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(port);
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(fd, (struct sockaddr *)&my_addr, sizeof(my_addr))) {
    perror("bind");
    exit(1);
  }
  if (listen(fd, 10)) {
    perror("listen");
    exit(2);
  }
  isValid = true;
}
/*virtual*/ TServerSocket::~TServerSocket() {
  close(fd);
}

TSocket *TServerSocket::Accept() {
  struct sockaddr_in their_addr;
  socklen_t sock_size = sizeof(struct sockaddr_in);

  bzero(&their_addr, sizeof(their_addr));
  // mutex lock around accept (should be faster than all threads doing accept at the same time)
//  accept_lock.Acquire();
  flock(fd, LOCK_EX);
  int newfd = accept(fd, (struct sockaddr *)&their_addr, &sock_size);
  flock(fd, LOCK_UN);
//  accept_lock.Release();
  if (newfd < 0) {
    perror("accept");
    printf("errno = %d\n", errno);
  }
  return new TSocket(newfd, &their_addr);
}
