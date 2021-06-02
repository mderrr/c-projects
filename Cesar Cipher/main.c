#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int mod(int a, int b) {
    int result = a % b;

    return result < 0 ? result + b : result;
}

int int_input(char message_prompt[]) {
    int input_variable;

    printf(message_prompt);
    scanf(" %i", &input_variable);

    return input_variable;
}

char * string_input(char message_prompt[]) {
    char *input_variable_pointer = malloc(sizeof(100));
    
    printf(message_prompt);
    scanf(" %[^\n]", input_variable_pointer);

    return input_variable_pointer;
}

int encrypt_message(char message_string[], short encryption_key) {
    unsigned short message_length = strlen(message_string);
    char encrypted_message[100];

    strncpy(encrypted_message, message_string, message_length + 1);

    for (int i=0; i < message_length; i++) {
        char letter = message_string[i];

        if (letter == ' ') {
            encrypted_message[i] = letter;

        } else if (letter >= 65 && letter <= 90) {
            encrypted_message[i] = mod(letter + encryption_key - 65, 26) + 65;

        } else if (letter >= 97 && letter <= 122) {
            encrypted_message[i] = mod(letter + encryption_key - 97, 26) + 97;

        } else {
            printf("Character not permited\n");
            return 1;
        }
    }

    printf("Your encrypted message is: %s\n", encrypted_message);
    return 0;
}

int decrypt_message(char message_string[], short encryption_key) {
    unsigned short message_length = strlen(message_string);
    char decrypted_message[message_length];

    strcpy(decrypted_message, message_string);

    for (int i=0; i < message_length; i++) {
        char letter = message_string[i];

        if (letter == ' ') {
            decrypted_message[i] = letter;

        } else if (letter >= 65 && letter <= 90) {
            decrypted_message[i] = mod(letter - encryption_key - 65, 26) + 65;

        } else if (letter >= 97 && letter <= 122) {
            decrypted_message[i] = mod(letter - encryption_key - 97, 26) + 97;

        } else {
            printf("Character not permited\n");
            return 1;
        }
    }

    printf("The decrypted message is: %s\n", decrypted_message);
    return 0;
}

void encryption_prompt() {
    int choice;
    int custom_key;
    char * message = malloc(sizeof(100));
    
    message = string_input("Please type your message: ");
    

    printf("Options\n 1. Generate random key\n 2. Specify a custom key\n 3. exit\n");

    while ( true ) {
        choice = int_input("Please select an option: ");

        if (choice == 1) {
            custom_key = random();
            printf("Your decryption key is: %i\n", custom_key);
            break;

        } else if (choice == 2) {
            custom_key = int_input("Please type the key: ");

            break;

        } else if (choice == 3) {
            return;

        } else {
            continue;
        }  
    }

    encrypt_message(message, custom_key);
    free(message);
}

void decryption_prompt() {
    int custom_key;
    char *message = malloc(sizeof(100));

    message = string_input("Please enter the encrypted message: ");
    custom_key = int_input("Please type the decryption key: ");

    decrypt_message(message, custom_key);
    free(message);
}

int main() {
    int choice;

    printf("Options\n 1. Encrypt a message\n 2. Decrypt a message\n 3. exit\n");

    while ( true ) {
        choice = int_input("Please select an option: ");

        if (choice == 1) {
            encryption_prompt();
            break;

        } else if (choice == 2) {
            decryption_prompt();
            break;

        } else if (choice == 3) {
            return 2;

        } else {
            continue;
        }  
    }

    return 0;
}