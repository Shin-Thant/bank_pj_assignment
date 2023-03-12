#include <stdio.h>
#include "./global.h"
// #include "./db.h"
#include "./util.h"
#include "./input_handler.h"

void welcome();
void registeration();
void login();
void userSector();
void moneyTransferProcess(struct data currentUser);

// database
void loadingAllData();
void printingAllData();

void loadingAllData()
{
    FILE *fptr = fopen("./data/db.txt", "r");

    if (!fptr)
    {
        printf("File not found!");
        return;
    }

    for (int userIndex = 0; userIndex < SIZE; userIndex++)
    {
        if (fscanf(fptr, "%u%s%s%s%s%s%s%u%u%f%s%d%s%u%s%d", &db[userIndex].id, &db[userIndex].name, &db[userIndex].nrc, &db[userIndex].email, &db[userIndex].password, &db[userIndex].pOrB, &db[userIndex].loanStatus, &db[userIndex].monthlyIncome, &db[userIndex].loanAmount, &db[userIndex].loanRate, &db[userIndex].accountStatus, &db[userIndex].accountLevel, &db[userIndex].phNumber, &db[userIndex].currentAmount, &db[userIndex].address, &db[userIndex].transAmountLimitPerDay) == EOF)
        {
            // printf("%d - %s\n", db[0].id, db[0].address); // check received data
            break;
        }

        for (int transactionIndex = 0; transactionIndex < spaceRecord[userIndex]-15; transactionIndex++) {
            if(fscanf(fptr, "%s", &db[userIndex].trc[transactionIndex].note) == EOF) {
                printf("\n\nrecord break;\n\n");
                break;
            }
            printf("%s \t", db[userIndex].trc[transactionIndex].note);
        }

        users++;
    }

    printf("User count: %d\n", users);
    fclose(fptr);
}

void printingAllData()
{
    for (int userIndex = 0; userIndex < SIZE; userIndex++)
    {
        if (db[userIndex].id == 0)
        {
            break;
        }
        printf("%u_%s_%s_%s_%s_%s_%s_%u_%u_%f_%s_%d_%s_%u_%s_%d", db[userIndex].id, db[userIndex].name, db[userIndex].nrc, db[userIndex].email, db[userIndex].password, db[userIndex].pOrB, db[userIndex].loanStatus, db[userIndex].monthlyIncome, db[userIndex].loanAmount, db[userIndex].loanRate, db[userIndex].accountStatus, db[userIndex].accountLevel, db[userIndex].phNumber, db[userIndex].currentAmount, db[userIndex].address, db[userIndex].transAmountLimitPerDay);

        for (int transactionIndex = 0; transactionIndex < spaceRecord[userIndex]-15; transactionIndex++) {
            printf("_%s", db[userIndex].trc[transactionIndex].note);
        }

        printf("\n");
    }
}

void welcome()
{
    printf("==== Welcome to our bank! ====\n");
    printf("Press 1: Login\n");
    printf("Press 2: Register\n");
    printf("Press 3: Exit\n");

    int menuIndex = -1;

    printf("Enter number to proceed: ");
    scanf("%d", &menuIndex);

    if (menuIndex == 1)
    {
        login();
    }
    else if (menuIndex == 2)
    {
        registeration();
    }
    else if (menuIndex == 3)
    {
        // exit
    }
    else
    {
        welcome();
    }
}

void registeration()
{
    char emailInput[50];
    int emailErr = 0;

    char nameInput[50];
    int nameErr = 0;

    char nrcInput[50];
    int nrcErr = 0;

    char phNumberInput[50];
    int phNumberErr = 0;

    char pwdInput[50];
    int pwdErr = 0;

    unsigned int monthlyIncomeInput;
    unsigned int currentAmountInput;
    char addressInput[100];
    char pOrB[50];
    int pOrBErr = 0;

    struct data *newUser = &db[users];
    printf("name: %s\n", newUser->name);
    printf("=== User Registration ===\n");

    do {
        printf("Enter your email: ");
        scanf(" %[^\n]", newUser->email);

        emailErr = !isInputEmail(newUser->email) || checkEmailExists(newUser->email);
        if (emailErr)
        {
            printf("Invalid email!\n");
        }
    } while (emailErr);
    
    do {
        printf("Enter your name: ");
        scanf(" %[^\n]", newUser->name);
        nameErr = getStrLength(newUser->name) < 4;
        if (nameErr)
        {
            printf("Invalid name!\n");
        }
    } while (nameErr);
    
    do {
        printf("Enter your nrc: ");
        scanf(" %[^\n]", newUser->nrc);
        nrcErr = !isNrcValid(newUser->nrc);
        if (nrcErr)
        {
            printf("Invalid NRC!\n");
        } else {
            nrcErr = checkNrcExists(newUser->nrc);
            if (nrcErr) {
                printf("NRC already exits!\n");
            }
        }
    } while (nrcErr);

    do {
        printf("Enter your password: ");
        scanf(" %[^\n]", newUser->password);

        pwdErr = getStrLength(newUser->password) < 6;
        if(pwdErr) {
            printf("Password must have at leat 6 characters!\n");
        }
    } while (pwdErr);

    do {
        printf("Enter your Ph no.: ");
        scanf(" %[^\n]", newUser->phNumber);

        phNumberErr = !isPhNumberValid(newUser->phNumber);
        if(phNumberErr) {
            phNumberErr = TRUE;
            printf("Invalid Phone No.!\n");
        } else {
            phNumberErr = checkPhNumberExists(newUser->phNumber);
            if(phNumberErr) {
                printf("Phone no. already exists!\n");
            }
        }
    } while (phNumberErr);

    do {
        printf("Enter your monthly income: ");
        scanf("%u", &newUser->monthlyIncome);
        if(newUser->monthlyIncome <= 0) {
            printf("Invalid montly income!\n");
        }
    } while (newUser->monthlyIncome <= 0);

    do {
        printf("Enter your current amount: ");
        scanf("%u", &newUser->currentAmount);
        if(newUser->currentAmount <= 0) {
            printf("Invalid current amount!\n");
        }
    } while (newUser->currentAmount <= 0);

    printf("Enter your address: ");
    scanf(" %[^\n]", newUser->address);

    do {
        printf("Enter personal or business: ");
        scanf(" %[^\n]", newUser->pOrB);
        pOrBErr = !isValidAccountType(newUser->pOrB);
        if(pOrBErr) {
            printf("Invalid account type!\n");
        }
    } while (pOrBErr);

    // set user's id and transaction limit per day
    newUser->id = users + 1;
    newUser->transAmountLimitPerDay = 1000;

    users++;
    printingAllData();
    return;
}

void login() {
    char emailInput[50];
    int emailErr = 0;
    int matched_email_user = -1;

    char pwdInput[50];
    int pwdErr = 0;
    int matched_pwd_user = -1;

    printf("=== User Login ===\n");

    do {
        printf("Enter your email: ");
        scanf(" %[^\n]", emailInput);

        emailErr = !isInputEmail(emailInput) || !checkEmailExists(emailInput);
        if (emailErr)
        {
            printf("Invalid email!\n");
        }
    } while (emailErr);
    matched_email_user = getUserIndexByEmail(emailInput);

    do {
        printf("Enter your password: ");
        scanf(" %[^\n]", pwdInput);

        pwdErr = getStrLength(pwdInput) < 6;
        if(pwdErr) {
            printf("Password must have at leat 6 characters!\n");
        } else {
            matched_pwd_user = getUserIndexByPwd(pwdInput);
            if(matched_pwd_user < 0 || matched_email_user != matched_pwd_user) {
                pwdErr = TRUE;
                printf("Enter Matched Password!\n");
            }
        }
    } while (pwdErr);

    CURRENT_USER_INDEX = matched_email_user;
    userSector();
}

void userSector()
{
    struct data currentUser = db[CURRENT_USER_INDEX];
    int userOption = 0;
    
    printf("=== User Sector ===\n");
    printf("Welcome %s\n", currentUser.name);
    printf("Press 1 to Transfer Money:\nPress 2 to Withdraw:\nPress 3 to update your information\nPress 4 Cash in :\nPress 5 to Loan:\nPress 6 to view your history:\nPress 7 Exit\n");

    do {
        printf("Enter option: ");
        scanf("%d", &userOption);
    } while (userOption < 1 || userOption > 7);

    switch (userOption) {
        case 1: moneyTransferProcess(currentUser);
        break;
        default: printf("Invalid Option!");
    }

    userSector();
}

void moneyTransferProcess(struct data currentUser)
{
    if(currentUser.currentAmount <= 0) {
        printf("Insufficient balance!\n");
        return;
    }

    int foundUserIndex = -1;
    printf("=== Transfer Option ==\n");

    char phInput[50];
    char phErr = FALSE;
    do {
        printf("Enter receive phone number: ");
        scanf(" %[^\n]", phInput);
        
        phErr = !isPhNumberValid(phInput);
        if(phErr)
        {
            printf("Invalid phone number!\n");
        } else {
            foundUserIndex = getUserIndexByPh(phInput);
            if(foundUserIndex == -1 || foundUserIndex == CURRENT_USER_INDEX) {
                phErr = TRUE;
                printf("Invalid phone number!\n");
            }
        }
    } while (phErr);

    printf("Found User: %s (%s)\n", db[foundUserIndex].name, db[foundUserIndex].email);

    int transferAmount = 0;
    do {
        printf("Enter amount to transfer: ");
        scanf("%d", &transferAmount);
        if(transferAmount <= 0 || transferAmount > currentUser.currentAmount)
        {
            printf("Invalid balance!\n");
            transferAmount = 0;
        }
    } while (transferAmount == 0);

    char inputPwd[30];
    int pwdErr = FALSE;
    do {
        printf("Enter password: ");
        scanf(" %[^\n]", inputPwd);
        pwdErr = getUserIndexByPwd(inputPwd);
        if(pwdErr) {
            printf("Invalid password!\n");
        }
    } while (pwdErr);

    
}
// format = from-john-to-shin-2000