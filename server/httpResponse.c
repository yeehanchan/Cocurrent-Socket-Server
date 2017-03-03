//
// Created by yeehanchen on 3/1/17.
//

#include <string.h>
#include <stdlib.h>
#include "httpResponse.h"
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#define SERVER_NAME "Liso/1.0"
#define HTTP_VERSION "HTTP/1.1"
#define CONTENT_SIZE 8192
// status 505
int isRightHTTPVersion(Request * request, Response * response){


    if(strcmp(request->http_version, HTTP_VERSION) != 0){

        strcpy(response->status_code, "505");
        strcpy(response->reason_phrase, STATUS_505);
        return 0;
    }

    return 1;
}


// status 411
int isContentLength(Request* request, Response *response){
    return 1;
}

// status 501
int isMethodImplemented(int method, Response *response){
    if(method == 0 || method == 1 || method == 2 ){

        return 1;

    }else{
        strcpy(response->status_code, "501");
        strcpy(response->reason_phrase, STATUS_501);
        return 0;
    }
}

int parseURI(Request *request, char * local_uri){

    int i;
    printf("parse");
    // there is host header
    for(i = 0; i < request->header_count; i++){
        if(strcmp(request->headers[i].header_name, "Host") == 0){
            printf("find header host");
            strcpy(local_uri, request->http_uri);
            printf("with host: %s", local_uri);
            return 1;
        }
    }
    int j;
    // there isn't host header
    for(j = 0; j < sizeof(request->http_uri); j++){
        if(request->http_uri[i] == '/' ){
            printf("no header host");
            memcpy(local_uri, request->http_uri + j,sizeof(request->http_uri) - j + 1);
            printf("no host: %s", local_uri);
        }
    }
    return 0;

}


// status 404
int isValidURI(Request * request, Response * response){


    char *uri = (char *) malloc(4096);
    parseURI(request,uri);
    struct stat sb;

    printf(" what the fuck is the problem \n");

    if (stat(uri, &sb) == 0)
    {
        printf("YES \n");
        return 1;
    } else {
        //
        printf("NO \n");
        strcpy(response->status_code,"404");
        strcpy(response->reason_phrase,STATUS_404);
        return 0;
    }

}


int setContent(char * uri, Response *response){

    printf("open file \n");
    int fd = open(uri, O_RDONLY);
    char cnt[CONTENT_SIZE];


    if(fd < 0) {

        printf("Failed to open the file\n");

        return 0;

    }

    int readRet = read(fd,cnt,CONTENT_SIZE);
    strcpy(response->body, cnt);
    return 1;
}





int setConnection(Response * response, char* value){
    printf("in connection \n");

    strcpy(response->general_headers[response->general_header_count].header_name, CONNECTION);
    printf("set header name \n");
    strcpy(response->general_headers[response->general_header_count].header_value, value);
    printf("set header value! \n");
    response->general_header_count++;

    return 1;
}

int setDate(Response * response){


    time_t rawtime;
    struct tm *info;
    char buffer[80];

    time( &rawtime );

    info = localtime( &rawtime );

    strftime(buffer,80,"%x - %I:%M%p", info);

    strcpy(response->response_headers[response->general_header_count].header_name, CONNECTION);
    strcpy(response->response_headers[response->general_header_count].header_value, buffer);
    response->general_header_count++;
    return 1;
}

int setServer(Response * response){

    strcpy(response->response_headers[0].header_name, SERVER);
    strcpy(response->response_headers[0].header_value, SERVER_NAME);
    response->response_header_count++;

    return 1;
}

int setContentLength(Response * response, char* value){

    strcpy(response->entity_headers[response->entity_header_count].header_name, CONTENT_LENGTH);
    strcpy(response->entity_headers[response->entity_header_count].header_name, value);
    response->entity_header_count++;

    return 1;
}

int setContentType(Response * response, char* value){

    strcpy(response->entity_headers[response->entity_header_count].header_name, CONTENT_TYPE);
    strcpy(response->entity_headers[response->entity_header_count].header_name, value);
    response->entity_header_count++;

    return 1;
}

int setLastModified(Response * response, char* value){

    strcpy(response->entity_headers[response->entity_header_count].header_name, LAST_MODIFIED);
    strcpy(response->entity_headers[response->entity_header_count].header_name, value);
    response->entity_header_count++;

    return 1;
}

int setHTTPVersion(Response * response){

    strcpy(response->http_version, HTTP_VERSION);

    return 1;
}





int respondGET(Request * request, Response *response){

    char* connection_value = "keep-alive";
    if (!setConnection(response,connection_value)){

        printf("Connection header set failed! \n");
        return 0;
    }
    printf("Connection passed! \n");
    if(!setDate(response)){
        printf("date failed! \n");

        setDate(response);
        return 0;
    }
    printf("Date passed! \n");

    char *uri = (char *) malloc(4096);
    parseURI(request,uri);
    printf("Parse passed! \n");


    if(!setContent(uri, response)){
        printf("Content failed! \n");

        return 0;
    }
    printf("Content passed! \n");

    strcpy(response->status_code, "200");
    strcpy(response->reason_phrase, STATUS_200);

    return 1;
}

int respondPOST(Request * request, Response *response) {

//    strcpy(response->status_code,"200") ;
//    strcpy(response->reason_phrase,STATUS_200);

    return 0;
}


int respondHEAD(Request * request, Response *response) {

//    strcpy(response->status_code,"200") ;
//    strcpy(response->reason_phrase,STATUS_200);

    return 0;
}



Response * httpResponse(Request * request){

    Response * response =  (Response *) malloc(sizeof(Response));
    response->general_headers = (Response_header *)malloc(sizeof(response->general_headers)*3);
    response->response_headers = (Response_header *)malloc(sizeof(response->general_headers)*3);
    response->entity_headers = (Response_header *)malloc(sizeof(response->general_headers)*3);

    int method;

    printf("the uri %s \n",request->http_uri);

    if(!isRightHTTPVersion(request, response)) {

        //return status 505
        return response;
    }



    if(!isValidURI(request, response)){

        // status 404
        return response;
    }




    if(strcmp(request->http_method, "GET") == 0){

        printf("GET\n");
        method = 0;

    } else if(strcmp(request->http_method, "HEAD") == 0){

        printf("HEAD\n");
        method = 1;

    }else if(strcmp(request->http_method,"POST") == 0){

        printf("POST\n");
        method = 2;

    }else{

        printf("else\n");
        method = 3;


    }

    if(isMethodImplemented(method,response) == 0){

        //status 501
        return response;
    }else{
            switch (method) {
                case (0):

                    printf("call respondGET \n");
                    if(respondGET(request, response)){
                        return response;
                    }

                case (1):

                    if(respondHEAD(request, response)){
                        return response;
                    }

                case (2):

                    if(respondPOST(request, response)){
                        return response;
                    }

            }


        }

    return NULL;
}


