//
// Created by yeehanchen on 3/1/17.
//

#include <string.h>
#include <stdlib.h>
#include <fmtmsg.h>
#include "httpResponse.h"


int checkHTTPVersion(char * version){
    return EXIT_SUCCESS;
}

int checkURI(char * uri){
    return EXIT_SUCCESS;
}

Response* respondGET(Request * request){
    if(checkHTTPVersion(request->http_version)){
        return NULL;
    }
    if(checkURI(request->http_uri)){
        return NULL;
    }

    Response * response =  (Response *) malloc(sizeof(Response));
    strcpy(response->status_code,"200") ;
    strcpy(response->reason_phrase,STATUS_200);

    return response;
}

Response * httpResponse(Request * request){

    int method;
    char http_version[50];
    char http_uri[4096];


    if(strcmp(request->http_method, "GET") == 0){
        printf("GET\n");
        method = 0;
        return respondGET(request);
    } else if(strcmp(request->http_method, "HEAD") == 0){
        printf("HEAD\n");
        method = 1;
    }else if(strcmp(request->http_method,"POST") == 0){
        printf("POST\n");
        method = 2;
    }else{
        printf("else\n");
        method = 4;
    }
    return NULL;

}
