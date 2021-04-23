
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    int i;
    printf("Content-type:text/html\n\n");
    printf("Hello CGI<br>");
#if 0
    printf("Eviroments:<br>");
    
    extern char** environ;
    for(i=0; ;i++)
    {
        if(environ[i] == NULL) break;

        printf("%s<br>", environ[i]);
    }
#endif
    char* queryString = getenv("QUERY_STRING");
    char* username = strtok(queryString, "|");
    char* password = strtok(NULL, "|");
    if(strcmp(username, "aaa")==0
            && strcmp(password, "bbb")==0)
    {
        printf("Login Success<br>");
    }
    else
    {
        printf("Login Error<br>");
    }

    return 0;
}
