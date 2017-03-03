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



char* getValueOfHeader(Request * request, char * header){

    int i=0;
    for (i=0;i<request->header_count;i++){
        if(strcmp(request->headers[i].header_name,header) == 0){
            return request->headers[i].header_value;
        }
    }
    return '\0';
}

char * getContentType(Request * request){

    char *file_ext;
    file_ext = strrchr(request->http_uri, '.');

    if(file_ext!=NULL){

        typedef struct item_t {
            const char *extension;
            const char *content_type;
        } item_t;

        //initial table will more extensions if needed later
        item_t table[] = {
                { ".html", "text/html; charset=ISO-8859-1" },
                { ".png", "image/png" },
                {".pdf","application/pdf"},
        };

        for (item_t *p = table; p->extension != NULL; ++p) {
            if (strcmp(p->extension, file_ext) == 0) {
                return p->content_type;
            }
        }
    }

    return '\0';

}

char* getLastModified(Request * request) {

    struct stat s;
    struct timespec t = { 0, 0 };
    char buffer[80];
    struct tm *info;

    if (!(stat(request->http_uri, &s) == 0)){
        return "\0";
    }

#if defined(MTIME) && MTIME == 1    // Linux

    t.tv_sec = s.st_mtime;

#elif defined (MTIME) && MTIME == 2    // Mac OS X

    t.tv_sec = s.st_mtimespec;
#elif defined(MTIME) && MTIME == 3    // Mac OS X, with some additional settings

    t.tv_sec = s.st_mtime;
    t.tv_nsec = s.st_mtimensec;

#else                                   // Solaris

    t.tv_sec = s.st_mtime;

#endif

    info = localtime( &t.tv_sec );

    strftime(buffer,80,"%x - %I:%M%p", info);

    return buffer;
}

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

    char *value;
    value = getValueOfHeader(request,"Content-Length" );

    if( value != '\0' && atoi(value) > 0 && atoi(value)< CONTENT_SIZE){
        return 1;
    }

    return 0;

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

    if(isContentLength(request,response) == 1 ) {

        char *content_type;
        content_type = getContentType(request);

        if (content_type == '\0') {
            printf("Extension not supported");
            return 0;
        }

        if(!setContentType(response, content_type)){
            printf("Couldnt retrieve content type");
            return  0;
        }

        char *lastmodified;
        lastmodified = getLastModified(request);

        if(lastmodified == '\0'){
            printf("Couldnt get last modified");
            return 0;
        }

        if(!setLastModified(response, lastmodified)){
            printf("Couldnt set last modified");
            return 0;
        }
        strcpy(response->status_code, "200");
        strcpy(response->reason_phrase, STATUS_200);
        return 1;
    }
    return  0;


//        if (access(request->http_uri, F_OK)==0) {
//
//            char *cmd = "file --mime-type";
//            char *full_cmd= (char *)malloc(strlen(cmd)+strlen(request->http_uri)+2);
//
//            //sprintf(str, "Value of Pi = %f", M_PI);
//            sprintf(full_cmd,"%s %s", cmd,request->http_uri);
//
//            printf("Full command", full_cmd);
//
//            FILE * f= popen(full_cmd, 'r');
//
//            if(f != NULL){
//                char *cont;
//                while (fgets(cont,100, f) != NULL)
//                    printf("%s", cont);
//            }
//
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


