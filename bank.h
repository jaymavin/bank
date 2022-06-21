struct date
{
    int day;
    int month;
    int year;
};
struct user
{
    int account_num;
    char firstName[50];
    char lastName[50];
    double phone;
    int age;
    float balance;
    float amount;
    struct date DOB;
    struct date deposit;
    struct date withdraw;
}; 
struct user add;
struct user update;
struct user check;
struct user delete;
struct user transaction;