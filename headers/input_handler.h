int isInputEmail(char emailInput[50]);
int checkSpaceInEmail(char email[50], int emailLength);
int checkEmailExtension(char email[50], int emailLength);
int checkEmailExists(char inputEmail[50]);
int checkEmailsEqual(char inputEmail[50], char userEmail[50]);
int isNrcValid(char inputNrc[50]);
int checkNrcExists(char inputNrc[50]);
int isPhNumberValid(char inputPhNumber[50]);
int checkPhNumberExists(char inputPhNumber[50]);
int isPwdValid(char inputPwd[50]);
int isValidAccountType(char input[20]);
int getUserIndexByEmail(char inputEmail[50]);
int getUserIndexByPwd(char inputPwd[50]);
int getUserIndexByPh(char inputPh[50]);

int isInputEmail(char emailInput[50])
{
    int emailLength = getStrLength(emailInput);

    if (emailLength <= 10)
    {
        return FALSE;
    }

    return !checkSpaceInEmail(emailInput, emailLength) && checkEmailExtension(emailInput, emailLength);
}

int checkSpaceInEmail(char email[50], int emailLength)
{
    // check email have space
    for (int i = 0; i < emailLength - 10; i++)
    {
        if (email[i] == ' ')
        {
            return TRUE;
        }
    }

    return FALSE;
}

int checkEmailExtension(char email[50], int emailLength)
{
    // @gmail.com = 10
    char MAIL_EXTENSION[11] = "@gmail.com";

    // check email have @gmail.com
    for (int i = (emailLength - 10); i < emailLength; i++)
    {
        int mailIndex = (i + 10) - emailLength;

        if (email[i] != MAIL_EXTENSION[mailIndex])
        {
            return FALSE;
        }
    }

    return TRUE;
}

int checkEmailExists(char inputEmail[50])
{
    for (int i = 0; i < users; i++)
    {
        if (checkEmailsEqual(inputEmail, db[i].email))
        {
            return TRUE;
        }
    }

    return FALSE;
}

int checkEmailsEqual(char inputEmail[50], char userEmail[50])
{
    int inputEmailLength = getStrLength(inputEmail);
    int userEmailLength = getStrLength(userEmail);

    if (inputEmailLength != userEmailLength)
    {
        return FALSE;
    }

    for (int i = 0; i < inputEmailLength; i++)
    {
        if (inputEmail[i] != userEmail[i])
        {
            return FALSE;
        }
    }
    return TRUE;
}

int isNrcValid(char inputNrc[50]) {
    int SLASH = 47;
    int OPEN_BRACKET = 40;
    int CLOSE_BRACKET = 41;
    int SMALL_A = 97;
    int SMALL_Z = 122;
    int CAPITAL_N = 78;

    int nrcLength = getStrLength(inputNrc);
    if(nrcLength < 10) {
        return FALSE;
    }

    // 48 -> 57 (0 -> 9)
    int startIndex = 2;
    int moreThanNine = 0;
    if(inputNrc[1] != SLASH) {
        if(inputNrc[0] != 49) {
            return FALSE;
        }
        moreThanNine = 1;
        startIndex = 3;
    }
    if(!moreThanNine) {
        if(!(49 <= inputNrc[0]) && !(inputNrc[0] <= 57)) {
            return FALSE;
        }
    } else {
        if(!(48 <= inputNrc[1]) || !(inputNrc[1] <= 52)) {
            return FALSE;
        }
    }

    // check chars and (N)
    int j = 0;
    for(j = startIndex; inputNrc[j] != OPEN_BRACKET; j++) {
        if(j > nrcLength) {
            return FALSE;
        }
        if(inputNrc[j] < SMALL_A || inputNrc[j] > SMALL_Z) {
            return FALSE;
        }
    }

    if(j == nrcLength) {
        return FALSE;
    }
    j += 1;
    if(inputNrc[j] != CAPITAL_N || inputNrc[j + 1] != CLOSE_BRACKET) {
        return FALSE;
    }
    j += 1;

    // check the rest of the number
    if((nrcLength - j) != 7) {
        return FALSE;
    }
    int k = 0;
    for (k = j + 1; k < nrcLength; k++)
    {
        if(inputNrc[k] < 48 || inputNrc[k] > 57) {
            return FALSE;
        }
    }
    

    return TRUE;
}

int checkNrcExists(char inputNrc[50]) {
    int count = 0;
    while(count < users) {
        if(checkStringsEqual(inputNrc, db[count].nrc)) {
            return TRUE;
        }
        count++;
    }
    return FALSE;
}

int isPhNumberValid(char inputPhNumber[50]) {
    int phNumLength = getStrLength(inputPhNumber);
    if(phNumLength < 7 || phNumLength > 14) {
        return FALSE;
    }

    int maxLength = 0;
    if(startsWith(inputPhNumber, "959") == TRUE) {
        maxLength = 9;
    } else if (startsWith(inputPhNumber, "20") == TRUE) {
        maxLength = 7;
    }

    if((maxLength == 9 && (phNumLength-5) != maxLength) || (maxLength == 7 && (phNumLength-4) != maxLength)) {
        printf("length false!\n");
        return FALSE;
    }
    for (int i = 0; i <= maxLength; i++)
    {
        if(inputPhNumber[i] < 48 || inputPhNumber[i] > 57) {
            printf("char false!\n");
            return FALSE;
        }
    }
    return TRUE;
}

int checkPhNumberExists(char inputPhNumber[50]) {
    int count = 0;
    while(count < users) {
        if(checkStringsEqual(inputPhNumber, db[count].nrc)) {
            return TRUE;
        }
        count++;
    }
    return FALSE;
}

int isPwdValid(char inputPwd[50]) {
    int pwdLength = getStrLength(inputPwd);
    if(pwdLength < 6) {
        return FALSE;
    }
    return TRUE;
}

int getUserIndexByPh(char inputPh[50])
{
    int userIndex = -1;
    int count = 0;
    while(count < users) {
        if(checkStringsEqual(inputPh, db[count].phNumber)) {
            userIndex = count;
            return userIndex;
        }
        count++;
    }
    return userIndex;
}

int isValidAccountType(char input[20])
{
    char personal[9] = "personal";
    char business[9] = "business";
    int isPersonal = TRUE;
    int isBusiness = TRUE;
    int inputLength = getStrLength(input);

    // check for personal
    for (int i = 0; i < inputLength; i++)
    {
        if(input[i] != personal[i]) {
            isPersonal = FALSE;
            break;
        }
    }

    for (int i = 0; i < inputLength; i++)
    {
        if(input[i] != business[i]) {
            isBusiness = FALSE;
            break;
        }
    }

    if(isPersonal)
    {
        return isPersonal;
    }
    if(isBusiness)
    {
        return isBusiness;
    }
    return FALSE;
}

int getUserIndexByEmail(char inputEmail[50]) {
    int userIndex = -1;
    int count = 0;
    while(count < users) {
        if(checkStringsEqual(inputEmail, db[count].email)) {
            userIndex = count;
            return userIndex;
        }
        count++;
    }
    return userIndex;
}

int getUserIndexByPwd(char inputPwd[50]) {
    int userIndex = -1;
    int count = 0;
    while(count < users) {
        if(checkStringsEqual(inputPwd, db[count].password)) {
            userIndex = count;
            return userIndex;
        }
        count++;
    }
    return userIndex;
}