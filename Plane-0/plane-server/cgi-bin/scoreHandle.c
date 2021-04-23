
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

void saveScore(const char* queryString)
{
    sqlite3* db;
    int ret = sqlite3_open("/home/xuegl/plane/plane.db", &db);
    if(ret != SQLITE_OK)
    {
        printf("ERR:open database error");
        return;
    }

    char sql[2048];
    sprintf(sql, "insert into PlaneHighScore (score) values(%s)", queryString);
    ret = sqlite3_exec(db, sql, NULL, NULL, NULL);
    if(ret != SQLITE_OK)
    {
        printf("ERR:insert error:%s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_close(db);
}

char* _score[10] = {NULL};
int _idx = 0;

int callback(void* p, int argc, char** argv, char** argvv)
{
    _score[_idx++] = strdup(argv[1]);
    if(_idx == 10)
        return -1;
    return 0;
}

int getHighScore()
{
    sqlite3* db;
    int ret = sqlite3_open("/home/xuegl/plane/plane.db", &db);
    if(ret != SQLITE_OK)
    {
        printf("ERR:open database error");
        return -1;
    }

    _idx = 0;
    ret = sqlite3_exec(db, "select * from PlaneHighScore order by score desc limit 10", callback, NULL, NULL);
    if(ret != SQLITE_OK)
    {
        printf("ERR:select error:%s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_close(db); 
    return 0;
}

int main()
{
    printf("Content-type:text/html\n\n");
    char* queryString = getenv("QUERY_STRING"); 

    saveScore(queryString);
    if(getHighScore() ==0)
    {
        printf("OK:");
        int i;
        for(i=0 ;i<10; i++)
        {
            if(_score[i])
                printf("%s|", _score[i]);
        }
    }

    return 0;
}
