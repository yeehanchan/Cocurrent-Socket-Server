//
// Created by yeehanchen on 3/1/17.
//


#include "parse.h"

#ifndef SERVER_HTTPRESPONSE_H
#define SERVER_HTTPRESPONSE_H

#endif //SERVER_HTTPRESPONSE_H




typedef struct
{
    char header_name[4096];
    char header_value[4096];
} Response_header;


#define CONTENT_SIZE 20480
#define RESPONSE_SIZE 30600

typedef struct
{
    // status line
    char http_version[50];
    char status_code[50];
    char reason_phrase[4096];


    //header field
    Response_header *general_headers; // 0:connection, 1:date
    Response_header *response_headers;// 0:server
    Response_header *entity_headers;  //

    // length of headers
    int general_header_count;
    int response_header_count;
    int entity_header_count;

    // /entity-body
    char* body;
} Response;

#define HTTP_VERSION "HTTP/1.1"

#define STATUS_200  "OK"
#define STATUS_204  "NO CONTENT"
#define STATUS_404  "NOT FOUND"
#define STATUS_411  "LENGTH REQUIRED"
#define STATUS_500  "INTERNAL SERVER ERROR"
#define STATUS_503  "SERVICE UNAVAILABLE"
#define STATUS_501  "NOT IMPLEMENTED"
#define STATUS_505  "HTTP VERSION NOT SUPPORTED"
#define STATUS_405  "METHOD NOT ALLOWED"



// General headers
#define CONNECTION "Connection"
#define DATE "Date"

// Response headers
#define SERVER "Server"


// Entity headers
#define CONTENT_LENGTH "Content-Length"
#define CONTENT_TYPE "Content-Type"
#define LAST_MODIFIED "Last-Modified"

int httpResponse(Request *request, Response* response);
int responseToBuffer(Response * response, char *);
