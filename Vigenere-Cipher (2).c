#include <stdio.h>
#include <string.h>
#include <ctype.h>

//declare the functions to be used
void vigenere_encrypt(const char *text, const char *keyword, char *encryptedtext);
void vigenere_decrypt(const char *text, const char *keyword, char *decryptedtext);

//void function for vigenere encryption
void vigenere_encrypt(const char *text, const char *keyword, char *encryptedtext) {
    char newkey[100];
    char key_letter;
    int textlen = strlen(text), keylen = strlen(keyword);
    
    for(int i = 0, j = 0; i < textlen; i++) {
        if(isalpha(text[i])) {
            key_letter = keyword[j % keylen];
            newkey[i] = isupper(text[i]) ? toupper(key_letter) : tolower(key_letter);
            j++;
        } else {
            newkey[i] = text[i];
        }
    }
    newkey[textlen] = '\0';
    
    for(int i = 0; i < textlen; i++) {
        if (isupper(text[i])) {
            encryptedtext[i] = ((text[i] - 'A' + (newkey[i] - 'A')) % 26) + 'A';
        } else if (islower(text[i])) {
            encryptedtext[i] = ((text[i] - 'a' + (newkey[i] - 'a')) % 26) + 'a';
        } else {
            encryptedtext[i] = text[i];
        }
    }
    encryptedtext[textlen] = '\0';
}

//void function for vigenere decryption
void vigenere_decrypt(const char *text, const char *keyword, char *decryptedtext) {
    char newkey[100];
    char key_letter;
    int textlen = strlen(text), keylen = strlen(keyword);
    
    for(int i = 0, j = 0; i < textlen; i++) {
        if(isalpha(text[i])) {
            key_letter = keyword[j % keylen];
            newkey[i] = isupper(text[i]) ? toupper(key_letter) : tolower(key_letter);
            j++;
        } else {
            newkey[i] = text[i];
        }
    }
    newkey[textlen] = '\0';
    
    for(int i = 0; i < textlen; i++) {
        if (isupper(text[i])) {
            decryptedtext[i] = (((text[i] - 'A' - (newkey[i] - 'A')) + 26) % 26) + 'A'; 
        } else if (islower(text[i])) {
            decryptedtext[i] = (((text[i] - 'a' - (newkey[i] - 'a')) + 26) % 26) + 'a';
        } else {
            decryptedtext[i] = text[i];
        }
    }
    decryptedtext[textlen] = '\0';
}

//main function
int main() {
    char choice;
    char text[100], keyword[100], encryptedtext[100], decryptedtext[100];
    
    printf("The Vigenère cipher is a polyalphabetic substitution cipher, an evolution of the Caesar cipher. It uses a secret key and an encryption table, called a Vigenère square or tabula recta. The table contains the 26 Latin alphabet letters, shifted one position to the right in a cyclic way as the rows progress downwards.\n\n");
    
    while(1) {
        printf("\nInput the text: ");
        fgets(text, sizeof(text), stdin); // Use fgets instead of scanf
        text[strcspn(text, "\n")] = '\0'; // Remove the newline character
        
        printf("Input the keyword: ");
        fgets(keyword, sizeof(keyword), stdin); // Use fgets instead of scanf
        keyword[strcspn(keyword, "\n")] = '\0'; // Remove the newline character

        printf("What would you like to do?\n[A] Encrypt\n[B] Decrypt\n>>> ");
        scanf(" %c", &choice);
        getchar(); // Consume the newline left in the buffer
        
        switch(choice) {
            case 'A': 
            case 'a':
                vigenere_encrypt(text, keyword, encryptedtext);
                printf("\nVigenère Cipher\n");
                printf("Original Text: %s\n", text);
                printf("Key: %s\n", keyword);
                printf("Encrypted Text: %s\n", encryptedtext);
                break;
            case 'B':
            case 'b':
                vigenere_decrypt(text, keyword, decryptedtext);
                printf("\nVigenère Cipher\n");
                printf("Encrypted Text: %s\n", text);
                printf("Key: %s\n", keyword);
                printf("Decrypted Text: %s\n", decryptedtext);
                break;
            default:
                printf("\nInvalid input!\n");
                break;
        }
    }
    return 0;
}
