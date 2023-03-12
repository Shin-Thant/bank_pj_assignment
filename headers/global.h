#define SIZE 1000

int FALSE = 0;
int TRUE = 1;
int users = 0;
int gValid = -1;
int emailExist = -1;
int CURRENT_USER_INDEX = -1;
int spaceRecord[30];

struct transitionRecord
{
    char note[100];
};

struct data
{
    unsigned int id;
    char name[30];
    char nrc[50];
    char email[50];
    char password[50];
    char pOrB[20];               // personal or business
    char loanStatus[1];         // loan status
    unsigned int monthlyIncome; // monthy income
    unsigned int loanAmount;    // how much did the person loan?
    float loanRate;
    char accountStatus[1]; // account status
    int accountLevel;
    char phNumber[50];
    unsigned int currentAmount; // current amount
    char address[100];
    int transAmountLimitPerDay; // transition amount limit per day (5 minutes)
    struct transitionRecord trc[100];
};

struct data db[SIZE];