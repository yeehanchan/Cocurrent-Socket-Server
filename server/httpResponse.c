//
// Created by yeehanchen on 3/1/17.
//

#include <string.h>
#include <stdlib.h>
#include <fmtmsg.h>
#include "httpResponse.h"
#include <time.h>


#define SERVER_NAME "List/1.0"


// status 505
int isRightHTTPVersion(Request * request, Response * response){

    return 1;
}

// status 404
int isValidURI(Request * request, Response * response){
    return 1;
}

// status 411
int isContentLength(Request* request, Response *response){

}

// status 501
int isMethodImplemented(int method, Response *response){

}

int isHost(Request *request, char * complete_uri){
    return 1;
}

int setConnection(Response * response, char* value){

    strcpy(response->response_headers[response->general_header_count].header_name, CONNECTION);
    strcpy(response->response_headers[response->general_header_count].header_value, value);
    response->general_header_count++;

    return 0;
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
    return 0;
}

int setServer(Response * response){

    strcpy(response->response_headers[response->response_header_count].header_name, SERVER);
    strcpy(response->response_headers[response->response_header_count].header_value, SERVER_NAME);
    response->entity_header_count++;

    return 0;
}

int setContentLength(Response * response, char* value){

    strcpy(response->entity_headers[response->entity_header_count].header_name, CONTENT_LENGTH);
    strcpy(response->entity_headers[response->entity_header_count].header_name, value);
    response->entity_header_count++;

    return 0;
}

int setContentType(Response * response, char* value){

    strcpy(response->entity_headers[response->entity_header_count].header_name, CONTENT_TYPE);
    strcpy(response->entity_headers[response->entity_header_count].header_name, value);
    response->entity_header_count++;

    return 0;
}

int setLastModified(Response * response, char* value){

    strcpy(response->entity_headers[response->entity_header_count].header_name, LAST_MODIFIED);
    strcpy(response->entity_headers[response->entity_header_count].header_name, value);
    response->entity_header_count++;

    return 0;
}





int respondGET(Request * request, Response *response){

//    strcpy(response->status_code,"200") ;
//    strcpy(response->reason_phrase,STATUS_200);

    return 0;
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
    int method;




    if(!isRightHTTPVersion(response, response)) {

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

    if(!isMethodImplemented(method,response)){

        //status 501
        return response;
    }else{
            switch (method) {
                case (0):


                    respondGET(request, response);
                    break;

                case (1):

                    respondHEAD(request, response);
                    break;

                case (2):

                    respondPOST(request, response);
                    break;

            }

            return response;

        }

    return NULL;
}


