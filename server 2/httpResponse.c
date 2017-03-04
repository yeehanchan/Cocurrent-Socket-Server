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
#include "libgen.h"




#define SERVER_NAME "Liso/1.0"
#define SP ' '
#define CRLF '\r\n'




//returns value of specific header
char* getValueOfHeader(Request * request, char * header){

    int i=0;
    for (i=0;i<request->header_count;i++){
        if(strcmp(request->headers[i].header_name,header) == 0){
            return request->headers[i].header_value;
        }
    }
    return NULL;
}


//parse URI from the request
int parseURI(Request *request, char * local_uri){

    int i;
    // there is host header
    for(i = 0; i < request->header_count; i++){
        if(strcmp(request->headers[i].header_name, "Host") == 0){
            strcpy(local_uri, request->http_uri);
            return 1;
        }
    }
    int j;
    // there isn't host header
    for(j = 0; j < sizeof(request->http_uri); j++){
        if(request->http_uri[i] == '/' ){
            memcpy(local_uri, request->http_uri + j,sizeof(request->http_uri) - j + 1);
        }
    }
    return 0;

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

    if( value != NULL && atoi(value) > 0 && atoi(value)< CONTENT_SIZE){
        return 1;
    }else{
        strcpy(response->status_code, "411");
        strcpy(response->reason_phrase, STATUS_411);
    }

    return 0;

}





// status 500
int isValidRequest(Request* request, Response * response){

    if(request == NULL){
        strcpy(response->status_code, "500");
        strcpy(response->reason_phrase, STATUS_500);
        return 0;
    }

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












// status 404
int isValidURI(Request * request, Response * response){


    char *uri = (char *) malloc(4096);
    parseURI(request,uri);
    struct stat sb;


    if (stat(uri, &sb) == 0)
    {
        printf("YES existing path \n");
        return 1;
    } else {
        //
        printf("Not existing path \n");
        strcpy(response->status_code,"404");
        strcpy(response->reason_phrase,STATUS_404);
        return 0;
    }

}




// function to get content type
int getContentType(Request * request, char* type){

    char *file_ext;
    file_ext = strrchr(request->http_uri, '.');

    if(file_ext!=NULL){

        typedef struct item_t {
            const char *extension;
            const char *content_type;
        } item_t;

        //lookup table for extensions
        item_t table[4] = {
                { ".html", "text/html; charset=iso-8859-1"},
                {".pdf","application/pdf"},
                {".css","text/css"},
                {".png","image/png"}
        };


        for (item_t *p = table; p->extension != NULL; ++p) {
            if (strcmp(p->extension, file_ext) == 0) {
                strcpy(type, p->content_type);
                return 1;
            }
        }
    }

    type[0] = '\0';
    return 1;

}





int setContent(char * uri, Response *response, char* length){

    printf("open file \n");

    FILE *fileptr;
    char *buffer;
    long filelen;

    fileptr = fopen(uri, "rb");            // Open the file
    fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
    filelen = ftell(fileptr);             // Get the current byte offset in the file
    rewind(fileptr);                      // Jump back to the beginning of the file

    buffer = (char *)malloc((filelen+1)*sizeof(char)); // Enough memory for file + \0
    fread(buffer, filelen, 1, fileptr); // Read in the entire file
    fclose(fileptr); // Close the file

    strcpy(response->body, buffer);
    sprintf(length,"%ld",filelen);
    printf("the file length %s \n",length);
    return 1;
}



int getLastModified(Request * request, char* date) {

    struct stat s;
    struct timespec t = { 0, 0 };
    struct tm *info;
    char *uri = (char *) malloc(4096);
    parseURI(request,uri);



    if (!(stat(uri, &s) == 0)){
        date[0] = '\0';
        return 0;
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
    strftime(date,80,"%x - %I:%M%p", info);
    printf("last modified date is %s \n ",date);
    return 1;
}






int setConnection(Response * response, char* value){

    printf("header count  in connection%d \n", response->general_header_count);

    strcpy(response->general_headers[response->general_header_count].header_name, CONNECTION);
    strcpy(response->general_headers[response->general_header_count].header_value, value);
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
    strcpy(response->general_headers[response->general_header_count].header_name, DATE);
    strcpy(response->general_headers[response->general_header_count].header_value, buffer);
    response->general_header_count++;
    return 1;
}





int setServer(Response * response){

    strcpy(response->response_headers[response->response_header_count].header_name, SERVER);
    strcpy(response->response_headers[response->response_header_count].header_value, SERVER_NAME);
    response->response_header_count++;

    return 1;
}




int setContentLength(Response * response, char* value){

    strcpy(response->entity_headers[response->entity_header_count].header_name, CONTENT_LENGTH);
    strcpy(response->entity_headers[response->entity_header_count].header_value, value);
    response->entity_header_count++;

    return 1;
}




int setContentType(Response * response, char* value){

    strcpy(response->entity_headers[response->entity_header_count].header_name, CONTENT_TYPE);
    strcpy(response->entity_headers[response->entity_header_count].header_value, value);
    response->entity_header_count++;

    return 1;
}




int setLastModified(Response * response, char* value){

    strcpy(response->entity_headers[response->entity_header_count].header_name, LAST_MODIFIED);
    strcpy(response->entity_headers[response->entity_header_count].header_value, value);
    response->entity_header_count++;

    return 1;
}





int setHTTPVersion(Response * response){

    strcpy(response->http_version, HTTP_VERSION);

    return 1;
}







// Generate response for request GET
int respondGET(Request * request, Response *response){

    printf("respond to GET \n");
    char connection_value[20] = "keep-alive";
    if (!setConnection(response,connection_value)){

        return 0;
    }
    printf("set Connection passed! \n");


    char uri[4096];
    char length[1024];
    parseURI(request,uri);
    printf("Parse passed! \n");


    if(!setContent(uri, response,length)){

        return 0;
    }
    printf("Content passed! \n");

    if(!setContentLength(response,length)){

        return 0;
    }
    printf("content length passed \n");


    char content_type[80];
    getContentType(request,content_type);
    if(content_type[0] == '\0'){

        return 0;
    }else{
        if(!setContentType(response,content_type)){

            return 0;
        }
    }

    printf("content type passed");

    char last_modified[80];
    getLastModified(request, last_modified);
    if(last_modified[0] == '\0'){
        return 0;
    }
    else{
        if(!setLastModified(response,last_modified)){
            return 0;
        }
    }
    printf("set lastmodified passed! \n");



    if(!setDate(response)){
        printf("date failed! \n");
        return 0;
    }

    printf("Date passed! \n");

    strcpy(response->status_code, "200");
    strcpy(response->reason_phrase, STATUS_200);

    return 1;
}






//Generate respnse for request POST
int respondPOST(Request * request, Response *response) {


    printf("responsd to post \n");

    if(isContentLength(request,response) == 1 ) {

        char content_type[80];
        getContentType(request,content_type);

        if (content_type[0] == '\0') {
            //no content
            strcpy(response->status_code, "204");
            strcpy(response->reason_phrase, STATUS_204);
            printf("Extension not supported \n");
            return 0;
        }

        if(!setContentType(response, content_type)){
            printf("Couldnt retrieve content type \n");
            return  0;
        }

        char lastmodified[80];
        getLastModified(request,lastmodified);

        if(lastmodified[0] == '\0'){
            printf("Couldnt get last modified \n");
            return 0;
        }

        if(!setLastModified(response, lastmodified)){
            printf("Couldnt set last modified \n");
            return 0;
        }
        strcpy(response->status_code, "200");
        strcpy(response->reason_phrase, STATUS_200);
        return 1;
    }
    return  0;
}








//Generate response for request HEAD
int respondHEAD(Request * request, Response *response) {
    printf("respond to HEAD \n");

    char connection_value[20] = "keep-alive";
    if (!setConnection(response,connection_value)){

        return 0;
    }
    printf("set Connection passed! \n");


    char uri[4096];
    char length[1024];
    parseURI(request,uri);
    printf("Parse passed! \n");


    char last_modified[80];
    getLastModified(request, last_modified);
    if(last_modified[0] == '\0'){
        return 0;
    }
    else{
        if(!setLastModified(response,last_modified)){
            return 0;
        }
    }
    printf("set lastmodified passed! \n");



    if(!setDate(response)){
        printf("date failed! \n");
        return 0;
    }

    printf("Date passed! \n");

    strcpy(response->status_code, "200");
    strcpy(response->reason_phrase, STATUS_200);

    return 1;
}








//Convert struct response to buffer
int responseToBuffer(Response * response, char * buffer){



    char status_line[4096];
    char general_headers[4096];
    char response_headers[4096];
    char entity_headers[4096];
    char body[CONTENT_SIZE];

    snprintf(status_line, 4096, "%s %s %s\n", response->http_version, response->status_code, response->reason_phrase);

    if(response->general_header_count > 0){
        int i;
        for(i = 0; i < response->general_header_count;i++){
            char * tmp = (char*)malloc(sizeof(50));
            sprintf(tmp,"%s: %s\n",response->general_headers[i].header_name,response->general_headers[i].header_value);
            strcat(general_headers,tmp);
            free(tmp);
        }
    }else{
        strcpy(general_headers,"");
    }

    if(response->response_header_count > 0){
        int j;
        for(j = 0; j < response->response_header_count;j++){
            char * tmp = (char*)malloc(sizeof(50));
            sprintf(tmp,"%s: %s\n",response->response_headers[j].header_name,response->response_headers[j].header_value);
            strcat(response_headers,tmp);
            free(tmp);

        }
    }else{
        strcpy(response_headers,"");
    }


    if(response->entity_header_count > 0){
        int k;
        for(k = 0; k < response->entity_header_count;k++){
            char *tmp = (char*)malloc(sizeof(50));
            sprintf(tmp,"%s: %s\n",response->entity_headers[k].header_name,response->entity_headers[k].header_value);
            strcat(entity_headers,tmp);
            free(tmp);
        }
        strcat(entity_headers,"\n");
    }else{
        strcpy(entity_headers,"");
    }

    if(strlen(response->body) == -1){
        strcpy(body,"");

    }else{
        strcpy(body,response->body);

    }

    snprintf(buffer, CONTENT_SIZE,"%s%s%s%s%s",status_line,general_headers,response_headers,entity_headers,body);
    printf("the result %s", buffer);
    memset(&status_line[0], 0, sizeof(status_line));
    memset(&general_headers[0], 0, sizeof(general_headers));
    memset(&response_headers[0], 0, sizeof(response_headers));
    memset(&entity_headers[0], 0, sizeof(entity_headers));

    return 1;
}






// Response handler
int httpResponse(Request * request, Response* response){




    if(isValidRequest(request, response) == 0){

        //status 500
        return 0;
    }


    int method;

    printf("the uri %s \n",request->http_uri);

    setServer(response);
    setHTTPVersion(response);


    if(!isRightHTTPVersion(request, response)) {

        //return status 505
        return 0;
    }



    if(!isValidURI(request, response)){

        // status 404
        return 0;
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
        return 0;
    }else{
            switch (method) {
                case (0):
                    respondGET(request,response);
                    break;

                case (1):
                    respondHEAD(request, response);
                    break;

                case (2):
                    respondPOST(request, response);
                    break;

            }

        }


    return 1;
}


