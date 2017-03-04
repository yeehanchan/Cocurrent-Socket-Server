#include "parse.h"
/**
* Given a char buffer returns the parsed request headers
*/
Request * parse(char *buffer, int size) {
  //Differant states in the state machine
	enum {
		STATE_START = 0, STATE_CR, STATE_CRLF, STATE_CRLFCR, STATE_CRLFCRLF
	};

	int i = 0, state;
	size_t offset = 0;
	char ch;


	state = STATE_START;
	while (state != STATE_CRLFCRLF) {
        char expected = 0;

        if (i == size)
            break;

        ch = buffer[i++];
        buffer[offset++] = ch;
        switch (state) {
            case STATE_START:
            case STATE_CRLF:
                expected = '\r';
                break;
            case STATE_CR:
                expected = '\r';
            case STATE_CRLFCR:
                expected = '\n';
                break;
            default:
                state = STATE_START;
                continue;
        }

        if (ch == expected) {
            state++;
        }
		else{
            state = STATE_START;
        }

	}

  //Valid End State
	if (state == STATE_CRLFCRLF) {
		Request *request = (Request *) malloc(sizeof(Request));
    request->header_count=0;
    //TODO You will need to handle resizing this in parser.y
    request->headers = (Request_header *) malloc(sizeof(Request_header)*1);
		set_parsing_options(buffer, i, request);
		if (yyparse() == SUCCESS) {

            //add body to header
            char * body;
            body = strchr(buffer, '\r\n\r\n');
            body+=4; //removing \r\n\r\n

            if (strlen(body)>0){
                strcpy(request->headers[request->header_count].header_name,"Body");
                strcpy(request->headers[request->header_count].header_name,body);
                request->header_count++;
            }
        return request;
		}
	}
  //TODO Handle Malformed Requests
    printf("Parsing Failed\n");
	return NULL;

}
