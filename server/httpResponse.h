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



typedef struct
{
    // status line
    char http_version[50];
    char status_code[50];
    char reason_phrase[4096];
    //header field
    Response_header *headers;
    int header_count;
    //entity-body
    char body[8192];
} Response;

#define GET "GET"
#define HEAD "HEAD"
#define POST "POST"

#define STATUS_501  "NOT IMPLEMENTED"
#define STATUS_404  "NOT FOUND"
#define STATUS_202  "ACCEPT"
#define STATUS_200  "OK"
#define STATUS_505  "HTTP VERSION NOT SUPPORTED"
#define STATUS_405  "METHOD NOT ALLOWED"
#define STATUS_500  "INTERNAL SERVER ERROR"

Response * httpResponse(Request *request);

