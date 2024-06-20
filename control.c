void sendRes(char *resCode, char *resName, char *conType, char *con){
    char response[MAX_SIZE];
    snprintf(response, sizeof(response),
        "HTTP/1.1 %s %s\r\n"
        "Content-Type: %s\r\n"
        "Content-strlength: %zu\r\n"
       // "Access-Control-Allow-Origin: *\r\n\r\n"
    "%s", resCode, resName, conType, strlen(con), con);

    n = write(newsockfd, response, strlen(response));
    if(n < 0){
        error("Unable to write response");
    }
}

char *extractXML(char *parent, char *buffer) {

    // Declare required variables

    char xml[MAX_SIZE];
    char start[MAX_SIZE];
    char end[MAX_SIZE];

    // Create start and end tags

    sprintf(start, "<%s>", parent);
    sprintf(end, "</%s>", parent);

    // Find start tag

    char *startPtr = strstr(buffer, start);
    if (startPtr != NULL) {

        // Find end tag

        char *endPtr = strstr(startPtr, end);
        if (endPtr != NULL) {

            // Calculate length and copy XML content

            size_t rng = endPtr - startPtr + strlen(end);
            strncpy(xml, startPtr, rng);
            xml[rng] = '\0';
            return strdup(xml);

        }

    }

    // Return NULL if tags are not found

    return NULL;

}

void handleRequests(char *buffer) {

    // Home page

    if(strncmp(buffer, "GET / ", 6) == 0){
        sendRes("200", "OK", "text/html", "<h1>Hi</h1>");
    }

}
