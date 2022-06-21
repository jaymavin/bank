#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "bank.h"

#define MAX_LINES 100
#define MAX_LEN 1000

char g_accounts[MAX_LINES + 1][MAX_LEN + 1] = {'\0'};

void read_accounts() {
    //read accounts(lines) into array g_accounts

    FILE *fp;

    fp = fopen("record.txt", "r");

    if (fp == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    int line = 0;
    int line_count;

    while (!feof(fp) && !ferror(fp)) {
        if (fgets(g_accounts[line], MAX_LEN, fp) != NULL) {
            line++;
            line_count += line;
        }
    }
    fclose(fp);

    for (int i = 0; i < line; i++) {
        printf("%s", g_accounts[i]);
    }
}

void update_accounts() {

}

void delete_accounts() {

}

void add_account() {
    FILE *fp;
    fp=fopen("record.txt","a+");

    if (fp == NULL) {
        printf("Error opening record.");
        exit(1);
    }

    printf("Enter today's date: (dd/mm/yyyy)\n");
    scanf("%d/%d/%d", &add.deposit.day, &add.deposit.month, &add.deposit.year);
    printf("Enter your account number: \n");
    scanf("%d", &add.account_num);
    if (add.account_num == check.account_num) {
        printf("Error. Account already exists.\n");
        exit(1);
    } else {
        check.account_num = add.account_num;
        printf("Enter your first name: \n");
        scanf("%s", add.firstName);
        printf("Enter your last name: \n");
        scanf("%s", add.lastName);
        printf("Enter your date of birth: (dd/mm/yyyy)\n");
        scanf("%d/%d/%d", &add.DOB.day, &add.DOB.month, &add.DOB.year);
        printf("Enter your phone number: \n");
        scanf("%lf", &add.phone);
        printf("Enter your age: \n");
        scanf("%d", &add.age);
        printf("Enter deposit amount: \n");
        scanf("%f", &add.amount);

        fprintf(fp, "%d %s %s %d/%d/%d %lf %d %f %d/%d/%d\n", add.account_num, add.firstName, add.lastName, add.DOB.day, add.DOB.month, 
        add.DOB.year, add.phone, add.age, add.amount, add.deposit.day, add.deposit.month, add.deposit.year);
    }
    fclose(fp);
    printf("\nAccount created successfully!\n");
}

void check_account() {
    FILE *fp;
    fp = fopen("record.txt", "r");

    if (fp == NULL) {
        printf("Error opening record.");
        exit(1);
    }

    printf("Please enter your account number: ");
    scanf("%d", &check.account_num);

    while (!feof(fp)) {
        fscanf(fp,"%d %s %s %d/%d/%d %lf %d %f %d/%d/%d\n", &add.account_num, add.firstName, add.lastName, &add.DOB.day, &add.DOB.month, 
        &add.DOB.year, &add.phone, &add.age, &add.amount, &add.deposit.day, &add.deposit.month, &add.deposit.year);
        if (check.account_num == add.account_num) {
            printf("\nAccount number: %d\nFirst name: %s\nLast name: %s\nDate of birth %d/%d/%d\nPhone number: %lf\nAge: %d\nAmount deposited: %f\nDate of deposit: %d/%d/%d\n", 
            add.account_num, add.firstName, add.lastName, add.DOB.day, add.DOB.month, add.DOB.year, add.phone, add.age, add.amount, add.deposit.day, add.deposit.month, add.deposit.year); 
            break;
        }
    }

    fclose(fp);
}

void make_transaction() {
    int choice = 0;
    FILE *old, *new;
    old = fopen("record.txt", "r");
    new = fopen("new_record.txt", "a+");

    if (old == NULL || new == NULL) {
        printf("Error opening record.");
        exit(1);
    }

    printf("\nEnter your account number: ");
    scanf("%d", &transaction.account_num);
    while(fscanf(old,"%d %s %s %d/%d/%d %lf %d %f %d/%d/%d\n", &add.account_num, add.firstName, add.lastName, &add.DOB.day, &add.DOB.month, 
        &add.DOB.year, &add.phone, &add.age, &add.amount, &add.deposit.day, &add.deposit.month, &add.deposit.year) != EOF) {
        if (add.account_num == transaction.account_num) {
            printf("\nWould you like to deposit or withdraw money?\n(Press 1 to deposit. Press 2 to withdraw)\n");
            scanf("%d", &choice);
            if (choice == 1) {
                //deposit
                printf("Enter the amount you want to deposit: ");
                scanf("%f", &transaction.amount);
                add.amount+=transaction.amount;
                fprintf(new,"%d %s %s %d/%d/%d %lf %d %f %d/%d/%d\n", add.account_num, add.firstName, add.lastName, add.DOB.day, add.DOB.month, 
                add.DOB.year, add.phone, add.age, add.amount, add.deposit.day, add.deposit.month, add.deposit.year);
                printf("Deposit successful. Your balance after deposit is: %f\n", add.amount);
            } else if (choice == 2) {
                //withdraw
                printf("Enter the amount you want to withdraw: ");
                scanf("%f", &transaction.amount);
                add.amount-=transaction.amount;
                fprintf(new,"%d %s %s %d/%d/%d %lf %d %f %d/%d/%d\n", add.account_num, add.firstName, add.lastName, add.DOB.day, add.DOB.month, 
                add.DOB.year, add.phone, add.age, add.amount, add.deposit.day, add.deposit.month, add.deposit.year);
                printf("Withdraw successful. Your balance is: %f\n", add.amount);
            } else {
                fprintf(new,"%d %s %s %d/%d/%d %lf %d %f %d/%d/%d\n", add.account_num, add.firstName, add.lastName, add.DOB.day, add.DOB.month, 
                add.DOB.year, add.phone, add.age, add.amount, add.deposit.day, add.deposit.month, add.deposit.year);
        }
    }
        
    fclose(old);
    fclose(new);
    remove("record.txt");
    rename("new_record.txt", "record.txt");
    }
}

void update_account() {
    int choice;
    FILE *old, *new;
    old = fopen("record.txt", "r");
    new = fopen("new_record.txt", "w");

    if (old == NULL) {
        printf("Error opening record.");
        exit(1);
    }

    printf("\nEnter your account number: ");
    scanf("%d", &update.account_num);
    printf("\nWhat information about the account would you like to update?\n1) First name\n2) Last name\n3) Phone number\n");
    scanf("%d", &choice);
    while(fscanf(old,"%d %s %s %d/%d/%d %lf %d %f %d/%d/%d\n", &add.account_num, add.firstName, add.lastName, &add.DOB.day, &add.DOB.month, 
    &add.DOB.year, &add.phone, &add.age, &add.amount, &add.deposit.day, &add.deposit.month, &add.deposit.year) != EOF) {
        if (add.account_num == update.account_num) {
                if (choice == 1) {
                printf("Your current first name is: %s. What would you like to change it to?", add.firstName);
                scanf("\n%s", update.firstName);
                fprintf(new,"%d %s %s %d %d %d %lf %d %f %d/%d/%d\n", add.account_num, update.firstName, add.lastName, add.DOB.day, add.DOB.month, 
                    add.DOB.year, add.phone, add.age, add.amount, add.deposit.day, add.deposit.month, add.deposit.year);
                printf("Changes saved.");
                } else if (choice == 2) {
                        printf("Your current last name is: %s. What would you like to change it to?", add.lastName);
                        scanf("\n%s", update.lastName);
                        fprintf(new,"%d %s %s %d/%d/%d %lf %d %f %d/%d/%d\n", add.account_num, add.firstName, update.lastName, add.DOB.day, add.DOB.month, 
                        add.DOB.year, add.phone, add.age, add.amount, add.deposit.day, add.deposit.month, add.deposit.year);
                        printf("Changes saved.");
                    } else if (choice == 3) {
                        printf("Your current phone number is: %lf. What would you like to change it to?", add.phone);
                        scanf("\n%lf", &update.phone);
                        fprintf(new,"%d %s %s %d/%d/%d %lf %d %f %d/%d/%d\n", add.account_num, add.firstName, add.lastName, add.DOB.day, add.DOB.month, 
                        add.DOB.year, update.phone, add.age, add.amount, add.deposit.day, add.deposit.month, add.deposit.year);
                        printf("Changes saved.");
                        } else {
                            fprintf(new,"%d %s %s %d/%d/%d %lf %d %f %d/%d/%d\n", add.account_num, add.firstName, add.lastName, add.DOB.day, add.DOB.month, 
                            add.DOB.year, add.phone, add.age, add.amount, add.deposit.day, add.deposit.month, add.deposit.year);
                        }
                    }
                }
            fclose(old);
            fclose(new);
            remove("record.txt");
            rename("new_record.txt", "record.txt");
            }
        

void delete_account() {
    FILE *old, *new;
    old = fopen("record.txt", "r");
    new = fopen("new_record.txt", "w");

    if (old == NULL || new == NULL) {
        printf("Error opening records.");
        exit(1);
    }

    printf("\nEnter your account number you want to delete: ");
    scanf("%d", &delete.account_num);
    while(fscanf(old,"%d %s %s %d/%d/%d %lf %d %f %d/%d/%d\n", &add.account_num, add.firstName, add.lastName, &add.DOB.day, &add.DOB.month, 
        &add.DOB.year, &add.phone, &add.age, &add.amount, &add.deposit.day, &add.deposit.month, &add.deposit.year) != EOF) {
        if (add.account_num != delete.account_num) {
            fprintf(new,"%d %s %s %d/%d/%d %lf %d %f %d/%d/%d\n", add.account_num, add.firstName, add.lastName, add.DOB.day, add.DOB.month, 
                    add.DOB.year, add.phone, add.age, add.amount, add.deposit.day, add.deposit.month, add.deposit.year);
        } else {
            printf("\nRecord deleted successfully.\n");
            }
        }
    fclose(old);
    fclose(new);
    remove("record.txt");
    rename("new_record.txt", "record.txt");
}

void close() {
    printf("Thank you for using our banking services.\n");
}

void menu() {
    int operation;

    printf("Please enter an operation:\n1) Create a new account\n2) Make a transaction\n3) Check an account\n4) Get list of all accounts\n5) Update an account\n6) Delete an existing account\n7) Exit\n");
    scanf("%d", &operation);

    switch(operation) {
        case 1: add_account();
        break;
        case 2: make_transaction();
        break;
        case 3: check_account();
        break;
        case 4: read_accounts();
        break;
        case 5: update_account();
        break;
        case 6: delete_account();
        break;
        case 7: close();
        break;
        default:
            printf("Error. Please select a valid operation.\n");
    }
}

int main() {
    menu();
}