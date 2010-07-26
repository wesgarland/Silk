#include "Silk.h"

TSocket::TSocket(int fd, sockaddr_in *their_addr) {
    this->fd = fd;
    strcpy(remote_addr, inet_ntoa(their_addr->sin_addr));
    putback_char = -1;
    indx = inlen = 0;

    struct timeval t;
    t.tv_sec = 10;
    t.tv_usec = 0;
    setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &t, sizeof (t));
    //  setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &t, sizeof(t));
}

TSocket::TSocket(const char *hostname, int port) {
    fd = -1;
    struct hostent *h = gethostbyname(hostname);
    if (h == NULL) {
        /* gethostbyname returns NULL on error */
        herror("gethostbyname failed");
        return;
    }

    struct sockaddr_in sock_addr;

    /* memcpy(dest, src, length) */
    memcpy(&sock_addr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
    /* copy the address to the sockaddr_in struct. */

    /* set the family type (PF_INET) */
    sock_addr.sin_family = h->h_addrtype;

    /* addr->sin_port = port won't work because they are different byte
     * orders
     */
    sock_addr.sin_port = htons(port);

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket");
        return;
    }
    if (connect(fd, (struct sockaddr *) &sock_addr, sizeof (struct sockaddr_in)) < 0) {
        /* connect returns -1 on error */
        perror("connect(...) error");
        close(fd);
        fd = -1;
        return;
    }
    putback_char = -1;
    indx = inlen = 0;

    struct timeval t;
    t.tv_sec = 10;
    t.tv_usec = 0;
    setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &t, sizeof (t));
}

/*virtual*/ TSocket::~TSocket() {
    close(fd);
}

void TSocket::SetTimeout(int msec) {
    struct timeval t;
    t.tv_sec = msec / 1000;
    t.tv_usec = (msec % 1000)*1000;
    socklen_t tsize = sizeof (t);
    setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &t, tsize);
}

bool TSocket::Write(const unsigned char *data, int len) {
    if (write(fd, data, len) != len) {
        perror("write");
        return false;
    }
    return true;
}

int TSocket::Read() {
    if (putback_char != -1) {
        int ret = putback_char;
        putback_char = -1;
        return ret;
    }
    if (indx >= inlen) {
        inlen = read(this->fd, (void *) &input[0], SOCKET_BUFFER_SIZE);
        indx = 0;
    }
    if (indx >= inlen)
        return -1;
    return input[indx++];
}

int TSocket::Read(unsigned char *buf, int len) {
    for (int i = 0; i < len; i++) {
        int n = Read();
        if (n < 0)
            return n;
        buf[i] = n;
    }
    return len;
}

bool TSocket::ReadLine(char *line) {
    int ndx = 0;
    int b;
    bool done = false;
    bool eof = false;
    while (!done) {
        b = Read();
        if (b == -1) {
            eof = true;
            break;
        }
        switch (b) {
            case '\r':
                b = Read();
                if (b != '\n')
                    putback_char = b;
                done = true;
                break;
            case '\n':
                done = true;
                break;
            default:
                line[ndx++] = b;
                break;
        }
    }
    line[ndx] = '\0';
    if (eof && ndx == 0)
        return false;
    return true;
}
