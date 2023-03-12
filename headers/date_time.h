#include <time.h>
char *getTime();
void setTime(char *str, char t[50]);

char *getTime()
{
    time_t currentTime = time(NULL); // in milliseconds (return type = int)
    struct tm *tm;
    tm = localtime(&currentTime);
    return asctime(tm);
}

void setTime(char *str, char t[50])
{
    const int SPACE = 32;
    for (int i = 0; i < 25; i++)
    {
        if (t[i] == SPACE)
        {
            str[i] = '-';
        }
        else
        {
            str[i] = t[i];
        }
    }
}