/******************************************************************************
* echo_server.c                                                               *
*                                                                             *
* Description: This file contains the C source code for an echo server.  The  *
*              server runs on a hard-coded port and simply write back anything*
*              sent to it by connected clients.  It does not support          *
*              concurrent clients.                                            *
*                                                                             *
* Authors: Athula Balachandran <abalacha@cs.cmu.edu>,                         *
*          Wolf Richter <wolf@cs.cmu.edu>                                     *
*                                                                             *
*******************************************************************************/

#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/fileappender.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>



#define ECHO_PORT 9999
#define BUF_SIZE 4096
#define STDIN 0



// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}




int close_socket(int sock)
{
    if (close(sock))
    {
        fprintf(stderr, "Failed closing socket.\n");
        return 1;
    }
    return 0;
}

int main(int argc, char* argv[])
{
    log4cplus::BasicConfigurator config;
    config.configure();

    log4cplus::SharedAppenderPtr appenderPtr(new log4cplus::FileAppender("logs/server.log",std::ios_base::trunc,true,true));
    log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("server"));
    logger.addAppender(appenderPtr);




    int sock, client_sock;
    ssize_t readret;
    socklen_t cli_size;
    struct sockaddr_in addr, cli_addr;
    char buf[BUF_SIZE];




    fprintf(stdout, "----- Echo Server -----\n");


//    fd_set readfds;
//    struct timeval tv;
//    tv.tv_sec = 2;
//    tv.tv_usec = 500000;
//
//    FD_ZERO(&readfds);
//    FD_SET(STDIN,&readfds);
//    select(STDIN+1, &readfds, NULL, NULL, &tv);
//    if(FD_ISSET(STDIN, &readfds)){
//        fprintf(stderr,"stdin ready!");
//    }
//    else{
//        fprintf(stderr, "not ready");
//    }


    struct timeval tv;

    tv.tv_sec = 5;
    tv.tv_usec = 500000;

    fd_set master;    // master file descriptor list
    fd_set read_fds;  // temp file descriptor list for select()
    int fdmax;        // maximum file descriptor number
    int newfd;        // newly accept()ed socket descriptor
    struct sockaddr_storage remoteaddr; // client address
    socklen_t addrlen;

    int nbytes;

    char remoteIP[INET6_ADDRSTRLEN];

    int i, rv;

    FD_ZERO(&master);    // clear the master and temp sets
    FD_ZERO(&read_fds);
    struct addrinfo  hints,*ai, *p;
    int listener;
    int yes = 1;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((rv = getaddrinfo(NULL, "9999", &hints, &ai)) != 0) {
        fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
        return EXIT_FAILURE;
    }


    for(p = ai; p != NULL; p = p->ai_next){
        listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

        if(listener < 0){
            fprintf(stdout,"create fail %d",p->ai_addrlen);
            continue;
        }

        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
            close(listener);
            continue;
        }

        break;
    }


    if (p == NULL) {
        fprintf(stderr, "selectserver: failed to bind\n");
        return EXIT_FAILURE;
    }


    if (listen(listener, 5) == -1) {
        perror("listen");
        return EXIT_FAILURE;
    }


    FD_SET(listener, &master);
    fdmax = listener;


    for(;;){
        read_fds = master;


        if (select(fdmax+1, &read_fds, NULL, NULL, &tv) == -1) {
            fprintf(stderr,"select");
            exit(4);
        }


        for(i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &read_fds)) { // we got one!!
                if (i == listener) {
                    // handle new connections
                    addrlen = sizeof remoteaddr;
                    newfd = accept(listener,
                                   (struct sockaddr *)&remoteaddr,
                                   &addrlen);

                    if (newfd == -1) {
                        perror("accept");
                    } else {
                        FD_SET(newfd, &master); // add to master set
                        if (newfd > fdmax) {    // keep track of the max
                            fdmax = newfd;
                        }
                        printf("selectserver: new connection from %s on "
                                       "socket %d\n",
                               inet_ntop(remoteaddr.ss_family,
                                         get_in_addr((struct sockaddr*)&remoteaddr),
                                         remoteIP, INET6_ADDRSTRLEN),
                               newfd);
                    }
                } else {
                    // handle data from a client
                    if ((nbytes = recv(i, buf, sizeof buf, 0)) <= 0) {
                        // got error or connection closed by client

                        if (nbytes == 0) {
                            // connection closed
                            printf("selectserver: socket %d hung up\n", i);
                        } else {
                            perror("recv");
                        }
                        close(i); // bye!
                        FD_CLR(i, &master); // remove from master set
                    } else {
                        // we got some data from a client

                        send(i, buf, nbytes, 0);

                    }
                } // END handle data from client
            } // END got new incoming connection
        } // END looping through file descriptors


    }
//
    return EXIT_SUCCESS;
}