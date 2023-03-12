#include <stdio.h>
void spaceCounting();
int getStrLength(char inputStr[50]);
int checkStringsEqual(char inputStr[100], char checkStr[100]);
int startsWith(char fullStr[50], char prefixStr[3]);

int getStrLength(char inputStr[50]) {
    int count = 0;
    for(int i = 0; i < 50; i++) {
        if(inputStr[i] == '\0') {
            return count;
        }
        count++;
    }
    return count;
}

int checkStringsEqual(char inputStr[100], char checkStr[100]) {
    int inputStrLength = getStrLength(inputStr);
    int checkStrLength = getStrLength(checkStr);
    if(inputStrLength != checkStrLength) {
        return 0;
    }
    for (int i = 0; i < inputStrLength; i++)
    {
        if (inputStr[i] != checkStr[i]) {
            return 0;
        }
    }
    return 1;
}

int startsWith(char fullStr[50], char prefixStr[3]) {
    int prefixStrLength = getStrLength(prefixStr);

    for (int i = 0; i < prefixStrLength; i++) 
    {
        if(fullStr[i] != prefixStr[i]) 
        {
            return FALSE;
        }
    }
    return TRUE;
}

void spaceCounting() {
    FILE *fptr = fopen("./data/db.txt", "r");

    if(fptr == NULL) {
        printf("File Not Found!\n");
        return;
    }

    const char SPACE = ' ';
    char data = fgetc(fptr);
    int recordIndex = 0;

    while (!feof(fptr))
    {
        if(data == '\n') {
            recordIndex++;
            data = fgetc(fptr);
            continue;
        }

        if(data == SPACE) {
            spaceRecord[recordIndex]++;
        }
        data = fgetc(fptr);
    }

    printf("%d\n", spaceRecord[0]);
}