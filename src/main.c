#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 128
#define NAME_SIZE 50
#define PASSWORD_SIZE 50

typedef struct {
    char name[NAME_SIZE];
    char password[PASSWORD_SIZE];
    double balance;
} Account;

static int read_line(const char *prompt, char *buffer, size_t size) {
    fputs(prompt, stdout);
    if (!fgets(buffer, (int)size, stdin)) return 0;
    buffer[strcspn(buffer, "\n")] = '\0';
    return 1;
}

static int read_int(const char *prompt, int *value) {
    char input[INPUT_SIZE];
    char *end;
    long parsed;
    if (!read_line(prompt, input, sizeof input)) return 0;
    errno = 0;
    parsed = strtol(input, &end, 10);
    if (errno || end == input || *end != '\0') return 0;
    *value = (int)parsed;
    return 1;
}

static int read_amount(const char *prompt, double *value) {
    char input[INPUT_SIZE];
    char *end;
    if (!read_line(prompt, input, sizeof input)) return 0;
    errno = 0;
    *value = strtod(input, &end);
    return !errno && end != input && *end == '\0';
}

static void run_atm(Account *account) {
    for (;;) {
        int choice;
        double amount;
        printf("\nWelcome, %s. Current balance: %.2f TRY\n", account->name, account->balance);
        puts("1) Withdraw\n2) Deposit\n3) View balance\n4) Exit");
        if (!read_int("Select an option: ", &choice)) {
            puts("Invalid selection. Enter a number from 1 to 4.");
            continue;
        }

        switch (choice) {
            case 1:
                if (!read_amount("Withdrawal amount: ", &amount) || amount <= 0) {
                    puts("Enter a positive numeric amount.");
                } else if (amount > account->balance) {
                    puts("Insufficient funds.");
                } else {
                    account->balance -= amount;
                    printf("Withdrawal complete. New balance: %.2f TRY\n", account->balance);
                }
                break;
            case 2:
                if (!read_amount("Deposit amount: ", &amount) || amount <= 0) {
                    puts("Enter a positive numeric amount.");
                } else {
                    account->balance += amount;
                    printf("Deposit complete. New balance: %.2f TRY\n", account->balance);
                }
                break;
            case 3:
                printf("Current balance: %.2f TRY\n", account->balance);
                break;
            case 4:
                puts("Session ended safely.");
                return;
            default:
                puts("Invalid selection. Enter a number from 1 to 4.");
        }
    }
}

int main(void) {
    Account account = {.balance = 2000.0};
    char login_name[NAME_SIZE];
    char login_password[PASSWORD_SIZE];

    puts("Terminal ATM Simulator\nCreate a temporary account for this session.");
    if (!read_line("Full name: ", account.name, sizeof account.name) || account.name[0] == '\0' ||
        !read_line("Password: ", account.password, sizeof account.password) || account.password[0] == '\0') {
        fputs("Unable to create the account.\n", stderr);
        return EXIT_FAILURE;
    }

    puts("\nSign in to continue.");
    if (!read_line("Name: ", login_name, sizeof login_name) ||
        !read_line("Password: ", login_password, sizeof login_password)) {
        fputs("Unable to read credentials.\n", stderr);
        return EXIT_FAILURE;
    }

    if (strcmp(login_name, account.name) != 0 || strcmp(login_password, account.password) != 0) {
        fputs("Invalid name or password.\n", stderr);
        return EXIT_FAILURE;
    }

    run_atm(&account);
    return EXIT_SUCCESS;
}
