
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
int main()
{
    int i;
    printf("Content-type:text/html\n\n");

    char* contentLength = getenv("CONTENT_LENGTH");
    int len = atoi(contentLength);
    printf("content length = %d<br>\n", len);

    char* buf = malloc(len);
    memset(buf, 0, len);

    fread(buf, len, 1, stdin);
    printf("%s<br>\n", buf);

    free(buf);

#if 0
    char buf[1024] = {0};
    read(0, buf, sizeof(buf));
    printf("read buffer is .... %s<br>\n", buf);
#endif
#if 0
    extern char** environ;
    for(i=0; ;i++)
    {
        if(environ[i] == NULL) break;

        printf("%s<br>\n", environ[i]);
    }



#endif
    return 0;
}
