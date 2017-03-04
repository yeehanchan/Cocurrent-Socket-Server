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
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "httpResponse.h"


#define ECHO_PORT "9999"
#define BUF_SIZE 4096
#define ERROR 1
#define DATA 2


void logText(FILE * fptr, int type, char * text, char* parameter){

    char *result[300];

    if (parameter!= NULL){
        sprintf(result,text,parameter);
    }
    if (type == ERROR){
        sprintf(result,"\nERROR:%s",text);
        fprintf(fptr, result);
    }
    else{
        fprintf(fptr, text);
    }

}


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}



int main(int argc, char* argv[])
{

    char buf[BUF_SIZE];

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

    FILE *fptr;
    fptr = fopen("log.txt", "a");

    if (fptr== NULL){
        fptr = stdout;
    }

    logText(fptr, DATA, "----- Echo Server -----\n", NULL);

    if ((rv = getaddrinfo(NULL, ECHO_PORT, &hints, &ai)) != 0) {
        logText(fptr, ERROR,"selectserver: %s\n", gai_strerror(rv));
        return EXIT_FAILURE;
    }


    for(p = ai; p != NULL; p = p->ai_next){
        listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

        if(listener < 0){
            logText(fptr, ERROR,"create fail",p->ai_addrlen);
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
        logText(fptr, ERROR,"selectserver: failed to bind socket\n",NULL);
        return EXIT_FAILURE;
    }


    if (listen(listener, 5) == -1) {
        logText(fptr, ERROR,"listen",NULL);
        return EXIT_FAILURE;
    }

    free(ai);

    FD_SET(listener, &master);
    fdmax = listener;


    for(;;){
        read_fds = master;

        if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
            logText(fptr, ERROR,"Select Error",NULL);
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
                        logText(fptr, ERROR,"Accept Error",NULL);
                    } else {
                        FD_SET(newfd, &master); // add to master set
                        if (newfd > fdmax) {    // keep track of the max
                            fdmax = newfd;
                        }
                        char result[200];
                        sprintf(result,"selectserver: new connection from %s on socket %d\n", inet_ntop(remoteaddr.ss_family,get_in_addr((struct sockaddr*)&remoteaddr), remoteIP,INET6_ADDRSTRLEN),newfd);
                        logText(fptr,DATA,result,NULL);
                    }
                } else {
                    // handle data from a client
                    if ((nbytes = recv(i, buf, BUF_SIZE - 1, 0)) <= 0) {
                        // got error or connection closed by client

                        if (nbytes == 0) {
                            // connection closed
                            logText(fptr, ERROR,"selectserver: socket %s hung up\n",i);
                        } else {
                            logText(fptr, ERROR,"Receive Error",NULL);
                        }
                        close(i); // bye!
                        FD_CLR(i, &master); // remove from master set
                    } else {
                        // we got some data from a client
                        Request *request = parse(buf,BUF_SIZE - 1);
                        Response * response =  (Response *) malloc(sizeof(Response));

                        httpResponse(request,response);
                        char response_buffer[24576];
                        responseToBuffer(response,response_buffer);
                        send(i, response_buffer, sizeof(response_buffer), 0);
                        free(response);
                    }
                } // END handle data from client
            } // END got new incoming connection
        } // END looping through file descriptors


    }
    fclose(fptr);
    return EXIT_SUCCESS;
}
