#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "colors.h"


#define STRINGMAX 1000
#define FILEPATH "data.txt"
#define MAXNOTES 100
#define SLEEP 1

// Structure to represent a Note
struct note{
    char title[STRINGMAX];
    char message[STRINGMAX];
};

// Function prototypes
int home_options();
int encrypt_options();
int encrypt_page(int chosen_cipher, char * src, char * dest);
void encrypt_text(char * src, int key, char * dest); // dummy function
int decrypt_options();
int decrypt_page(int chosen_cipher, char * src, char * dest);
int learn_ciphers();

// Function prototypes for the Notes System
int load_notes(struct note notes_list[]);
void preview_list(struct note notes_list[], int note_count);
void display_note(struct note notes_list[], int note_num);
int note_options();
int note_encrypt_page(int chosen_cipher, char * src, char * dest);
int create_note(struct note notes_list[], int * note_count);
void save_notes(struct note notes_list[], int note_count);
int delete_note(struct note notes_list[], int * note_count, int note_del);
int edit_note(struct note notes_list[], int note_edit);

// Function prototypes for the ciphers
void xor_encrypt(char src[], int key, char dest[]);
void xor_decrypt(char src[], int key, char dest[]);

void vigenere_generatekey(const char *text, const char *keyword, char *newkey);
void vigenere_encrypt(const char *text, const char *key, char *encryptedtext);
void vigenere_decrypt(const char *text, const char *key, char *decryptedtext);


// Function to print the options in home
int home_options() {
    int response = 0;
    char buffer[STRINGMAX];
    printf(BBLU"=== "BYEL"WELCOME TO <INSERT APP NAME>"BBLU" ===\n"reset);
    // printf("=== WELCOME TO <INSERT APP NAME> ===\n");
    printf(BWHT"\nWhat would you like to do?\n");
    printf(CYN"[1] Encrypt Text\n");
    printf(MAG"[2] Decrypt Text\n");
    printf(CYN"[3] Go to Notes\n");
    printf(MAG"[4] Learn about the Ciphers\n");
    printf(BRED"[5] Exit\n"HGRN">>> "reset);
    fgets(buffer, STRINGMAX, stdin);
    sscanf(buffer, "%d", &response);
    return response;
}

// Function to show the cipher options
int encrypt_options() {
    int response = 0;
    char buffer[STRINGMAX];
    
    // Cipher Options
    printf(BWHT"\nWhich cipher would you like to use?\n");
    printf(MAG"[1] Caesar Cipher\n");
    printf(CYN"[2] XOR Cipher\n");
    printf(MAG"[3] Vigenere Cipher\n");
    printf(BRED"[4] Back\n"HGRN">>> "reset);
    
    fgets(buffer, STRINGMAX, stdin);
    sscanf(buffer, "%d", &response);
    return response;
}

// Function to display the encryption process and call the appropriate encryption function
int encrypt_page(int chosen_cipher, char * src, char * dest) {
    
    int response = 0;
    char cipher[STRINGMAX]; // stores the cipher name
    int key=0;
    char keyword[STRINGMAX];
    char buffer[STRINGMAX];

    if (chosen_cipher == 1) {
        strcpy(cipher, "Caesar Cipher");
    } else if (chosen_cipher == 2){
        strcpy(cipher, "XOR Cipher");
    } else if (chosen_cipher == 3){
        strcpy(cipher, "Vigenere Cipher");
    }

    printf("=== "BYEL"Encrypt Text Using "UYEL"%s"reset" ===\n", cipher);

    printf(BLU"\nEnter Message:\n"BGRN">>> "reset);
    fgets(src, STRINGMAX, stdin);

    

    // Calls the appropriate cipher function
    if (chosen_cipher == 1) {
        // Input the key
        printf(BLU"\nEnter Key:\n"BGRN">>> "reset);
        fgets(buffer, STRINGMAX, stdin);
        sscanf(buffer, "%d", &key);
        encrypt_text(src, key, dest);
    } else if (chosen_cipher == 2){
        // Input the key
        printf(BLU"\nEnter Key (Integer):\n"BGRN">>> "reset);
        fgets(buffer, STRINGMAX, stdin);
        sscanf(buffer, "%d", &key);
        xor_encrypt(src, key, dest);
    } else if (chosen_cipher == 3){
        // Input the key
        printf(BLU"\nEnter Key (Word):\n"BGRN">>> "reset);

        fgets(keyword, STRINGMAX, stdin);
        keyword[strcspn(keyword, "\n")] = '\0';
        vigenere_encrypt(src, keyword, dest);

    }

    // Display the output and asks for next action
    printf(YEL"\nEncrypted Text:\n"reset"%s\n\n", dest);
    printf(MAG"[1] Encrypt another\n");
    printf(BRED"[2] Back\n"BGRN">>> "reset);
    fgets(buffer, STRINGMAX, stdin); // Read the entire line into buffer
    sscanf(buffer, "%d", &response);

    if (response == 1) {
        return 1;
    } else if (response == 2) {
        return 2;
    } else {
        return 0;
    }
}

// Temporary "encryption" function
void encrypt_text(char * src, int key, char *dest) {
    printf("src: %s\n", src);
    char temp[2];
    temp[0] = src[1];
    temp[1] = '\0';

    strcpy(dest, temp);
}

// Function to show the cipher options, basically same as the encrypt options
int decrypt_options() {
    int response = 0;
    char buffer[STRINGMAX];
    
    // Cipher options
    printf(BWHT"\nWhich cipher would you like to use?\n");
    printf(MAG"[1] Caesar Cipher\n");
    printf(CYN"[2] XOR Cipher\n");
    printf(MAG"[3] Vigenere Cipher\n");
    printf(BRED"[4] Back\n"HGRN">>> "reset);
    
    fgets(buffer, STRINGMAX, stdin); 
    sscanf(buffer, "%d", &response);
    return response;
}

// Function to display the decryption process and call the appropriate decryption function
int decrypt_page(int chosen_cipher, char * src, char * dest) {
    
    int response = 0;
    char cipher[STRINGMAX];
    int key=0;
    char keyword[STRINGMAX];
    char buffer[STRINGMAX];

    if (chosen_cipher == 1) {
        strcpy(cipher, "Caesar Cipher");
    } else if (chosen_cipher == 2){
        strcpy(cipher, "XOR Cipher");
    } else if (chosen_cipher == 3){
        strcpy(cipher, "Vigenere Cipher");
    }

    printf("=== "BYEL"Decrypt Text Using "UYEL"%s"reset" ===\n", cipher);

    printf(BLU"\nEnter Message:\n"BGRN">>> "reset);
    fgets(src, STRINGMAX, stdin);


    // Calls the appropriate cipher function
    if (chosen_cipher == 1) {
        // Input the key
        printf(BLU"\nEnter Key:\n"BGRN">>> "reset);
        fgets(buffer, STRINGMAX, stdin);
        sscanf(buffer, "%d", &key);
        encrypt_text(src, key, dest);
    } else if (chosen_cipher == 2){
        // Input the key
        printf(BLU"\nEnter Key (Integer):\n"BGRN">>> "reset);
        fgets(buffer, STRINGMAX, stdin);
        sscanf(buffer, "%d", &key);
        xor_decrypt(src, key, dest);
    } else if (chosen_cipher == 3){
        // Input the key
        printf(BLU"\nEnter Key (Word):\n"BGRN">>> "reset);

        fgets(keyword, STRINGMAX, stdin);
        keyword[strcspn(keyword, "\n")] = '\0';
        vigenere_decrypt(src, keyword, dest);

    }

    // Displays the output
    printf(YEL"\nPlain Text:\n"reset"%s\n\n", dest);
    printf(MAG"[1] Decrypt another\n");
    printf(BRED"[2] Back\n"BGRN">>> "reset);
    fgets(buffer, STRINGMAX, stdin); // Read the entire line into buffer
    sscanf(buffer, "%d", &response);

    if (response == 1) {
        return 1;
    } else if (response == 2) {
        return 2;
    } else {
        return 0;
    }
}

// Function to display the information page
int learn_ciphers() {
    int response = 0;
    printf("=== "BYEL"Learn About Ciphers!"reset" ===\n");
    printf(CYN"\nCaesar Cipher\n"reset);
    printf("The Caesar Cipher is one of the simplest and oldest encryption techniques. It works by shifting each letter in the plaintext by a fixed number of positions in the alphabet. For example, with a shift of 3, the letter 'A' becomes 'D', 'B' becomes 'E', and so on. This method is easy to implement and decrypt but is not secure by modern standards, as it can be broken using brute force or frequency analysis.\n");
    printf(CYN"\nXOR Cipher\n"reset);
    printf("The XOR (Exclusive OR) Cipher is a fundamental encryption method that uses the XOR operation between the plaintext and a key. Each bit of the plaintext is XORed with the corresponding bit of the key to produce the ciphertext. This method is fast and effective for short keys but requires the key to be the same length as the message to ensure security. XOR is widely used in modern cryptography as part of more complex algorithms.\n");
    printf(CYN"\nVigenere Cipher\n"reset);
    printf("The Vigenere Cipher is a polyalphabetic cipher that uses a keyword to encrypt the plaintext. Each letter of the plaintext is shifted by a number of positions based on the corresponding letter in the keyword. This method is more secure than the Caesar Cipher because it uses multiple shifting patterns, making it resistant to frequency analysis. However, its security depends on the secrecy and randomness of the keyword.\n");

    printf(BRED"\n[1] Back\n"BGRN">>> "reset);
    scanf("%d", &response);
    getchar();

    if (response == 1) {
        return 0;
    }

    return 12;
}

/* -------- FUNCTIONS FOR THE NOTES SYSTEM -------- */

int load_notes(struct note notes_list[]) {
    FILE *file = fopen(FILEPATH, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
    }

    int note_count = 0;
    while (fgets(notes_list[note_count].title, STRINGMAX, file)) {
        // Remove newline character from the title
        notes_list[note_count].title[strcspn(notes_list[note_count].title, "\n")] = '\0';
        printf("Done!\n");

        // Read the message for this note
        if (fgets(notes_list[note_count].message, STRINGMAX, file)) {
            notes_list[note_count].message[strcspn(notes_list[note_count].message, "\n")] = '\0';
        }
        
        note_count++;

        // Skip empty line (separator between notes)
        fgets(notes_list[note_count].title, STRINGMAX, file);
    }

    fclose(file);
    return note_count;
}

void preview_list(struct note notes_list[], int note_count) {
    printf("=== "BYEL"NOTES"reset" ===\n");
    printf(BWHT"\nNO.\tTITLE\n");
    for (int i = 0; i < note_count; i++) {
        if (i%2 == 0) {
            printf(MAG"%d\t%s\n"reset, i+1, notes_list[i].title);
        } else {
            printf(CYN"%d\t%s\n"reset, i+1, notes_list[i].title);
        }
    }
}

void display_note(struct note notes_list[], int note_num) {
    printf("=== "BYEL"Notes"reset" ===\n\n");
    printf(BBLU"Title: "reset"%s\n\n", notes_list[note_num].title);
    printf(BBLU"Message: \n"reset"%s\n\n", notes_list[note_num].message);
}

int note_options() {
    int response = 0;
    printf(BWHT"What would you like to do?\n");
    printf(CYN"[1] Encrypt it\n");
    printf(MAG"[2] Decrypt it\n");
    printf(GRN"[3] Edit\n");
    printf(RED"[4] Delete\n");
    printf(BRED"[5] Back to notes\n"BGRN">>> "reset);
    scanf("%d", &response);
    getchar();
    return response;
}

int note_encrypt_page(int chosen_cipher, char * src, char * dest) {
    int response = 0;
    char cipher[STRINGMAX]; // stores the cipher name
    int key=0;
    char keyword[STRINGMAX];
    char buffer[STRINGMAX];


    if (chosen_cipher == 1) {
        strcpy(cipher, "Caesar Cipher");
    } else if (chosen_cipher == 2){
        strcpy(cipher, "XOR Cipher");
    } else if (chosen_cipher == 3){
        strcpy(cipher, "Vigenere Cipher");
    } else {
        printf("ERROR");
        return response;
    }

    printf("-- "BYEL"Decrypting Using "UYEL"%s"reset" --\n", cipher);

    if (chosen_cipher == 1) {
        // Input the key
        printf(BLU"\nEnter Key:\n"BGRN">>> "reset);
        fgets(buffer, STRINGMAX, stdin); // Read the entire line into buffer
        sscanf(buffer, "%d", &key);
        encrypt_text(src, key, dest);
    } else if (chosen_cipher == 2){
        // Input the key
        printf(BLU"\nEnter Key (Integer):\n"BGRN">>> "reset);
        fgets(buffer, STRINGMAX, stdin); // Read the entire line into buffer
        sscanf(buffer, "%d", &key);
        xor_encrypt(src, key, dest);
    } else if (chosen_cipher == 3){
        // Input the key
        printf(BLU"\nEnter Key (Word):\n"BGRN">>> "reset);
        fgets(keyword, STRINGMAX, stdin);
        keyword[strcspn(keyword, "\n")] = '\0';
        vigenere_encrypt(src, keyword, dest);
    }

    printf(YEL"Encrypted text:\n"reset"%s\n", dest);
    printf(BRED"[1] Back\n"BGRN">>> "reset);
    scanf("%d", &response);
    getchar();
    return response;
}

int note_decrypt_page(int chosen_cipher, char * src, char * dest) {
    int response = 0;
    char cipher[STRINGMAX]; // stores the cipher name
    int key=0;
    char keyword[STRINGMAX];
    char buffer[STRINGMAX];

    if (chosen_cipher == 1) {
        strcpy(cipher, "Caesar Cipher");
    } else if (chosen_cipher == 2){
        strcpy(cipher, "XOR Cipher");
    } else if (chosen_cipher == 3){
        strcpy(cipher, "Vigenere Cipher");
    }

    printf("-- "BYEL"Decrypting Using "UYEL"%s"reset" --\n", cipher);

    if (chosen_cipher == 1) {
        // Input the key
        printf(BLU"\nEnter Key:\n"BGRN">>> "reset);
        fgets(buffer, STRINGMAX, stdin); // Read the entire line into buffer
        sscanf(buffer, "%d", &key);
        encrypt_text(src, key, dest);
    } else if (chosen_cipher == 2){
        // Input the key
        printf(BLU"\nEnter Key (Integer):\n"BGRN">>> "reset);
        fgets(buffer, STRINGMAX, stdin); // Read the entire line into buffer
        sscanf(buffer, "%d", &key);
        xor_decrypt(src, key, dest);
    } else if (chosen_cipher == 3){
        // Input the key
        printf(BLU"\nEnter Key (Word):\n"BGRN">>> "reset);
        fgets(keyword, STRINGMAX, stdin);
        keyword[strcspn(keyword, "\n")] = '\0';
        vigenere_decrypt(src, keyword, dest);
    }

    printf(YEL"Plaintext:\n"reset"%s\n", dest);
    printf(BRED"[1] Back\n"BGRN">>> "reset);
    scanf("%d", &response);
    getchar();
    return response;
}

void save_notes(struct note notes_list[], int note_count) {
    FILE *file = fopen(FILEPATH, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < note_count; i++) {
        fprintf(file, "%s\n%s\n\n", notes_list[i].title, notes_list[i].message);
    }

    fclose(file);
}

int create_note(struct note notes_list[], int * note_count) {
    printf("=== "BYEL"Notes"reset" ===\n");
    printf(BWHT"\n-- Creating New Note --\n");
    printf(BLU"Enter title:\n"BGRN">>> "reset);
    fgets(notes_list[*note_count].title, STRINGMAX, stdin);
    notes_list[*note_count].title[strcspn(notes_list[*note_count].title, "\n")] = '\0';  // Remove newline

    printf(BLU"Enter message:\n"BGRN">>> "reset);
    fgets(notes_list[*note_count].message, STRINGMAX, stdin);
    notes_list[*note_count].message[strcspn(notes_list[*note_count].message, "\n")] = '\0';  // Remove newline

    (*note_count)++;
    save_notes(notes_list, *note_count);

    return 0;
}


int delete_note(struct note notes_list[], int * note_count, int note_del) {

    int response=0;

    printf(BWHT"Are you sure you want to delete this note?\n");
    printf(BCYN"[1] YES\n"BRED"[2] BACK\n"BGRN">>> "reset);
    scanf("%d", &response);
    getchar();

    if (response == 2) {
        return 0;
    } else if (response == 1) {
        for (int i = note_del; i < *note_count - 1; i++) {
            notes_list[i] = notes_list[i + 1];
        }

        // Decrease the note count
        (*note_count)--;
        return 0;
    } else {
        return 0;
    }
}

int edit_note(struct note notes_list[], int note_edit) {
    
    int response = 0;
    char new[STRINGMAX];

    printf("\n-- "BYEL"Editing"reset" --\n");
    printf(BWHT"Which part to edit?\n");
    printf(MAG"[1] Title\n");
    printf(CYN"[2] Message\n");
    printf(BRED"[3] Back\n"BGRN">>> "reset);
    scanf("%d", &response);
    getchar();

    if (response == 1) {
        printf(BLU"Enter new title:\n"BGRN">>> "reset);
        fgets(new, STRINGMAX, stdin);
        strcpy(notes_list[note_edit].title, new);

    } else if (response == 2) {
        printf(BLU"Enter new message:\n"BGRN">>> "reset);
        fgets(new, STRINGMAX, stdin);
        strcpy(notes_list[note_edit].message, new);
        
    } else if (response == 3) {
        return 5;
    } else {
        printf("Invalid Input. Try again.");
        sleep(SLEEP);

    }

    return 5;
}

/* -------- FUNCTIONS FOR CIPHERS --------*/

void xor_encrypt(char src[], int key, char dest[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i] ^ key; 
        i++;
    }
    dest[i] = '\0';
}

void xor_decrypt(char src[], int key, char dest[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i] ^ key;
        i++;
    }
    dest[i] = '\0';
}

//declare the functions to be used
void vigenere_encrypt(const char *text, const char *keyword, char *encryptedtext);
void vigenere_decrypt(const char *text, const char *keyword, char *decryptedtext);

//void function for vigenere encryption
void vigenere_encrypt(const char *text, const char *keyword, char *encryptedtext) {
    
    //declare an array variable for the new key
    char newkey[STRINGMAX];
    char key_letter;
    //declare the length of the text as a variable
    int textlen = strlen(text), keylen = strlen(keyword);
    
    //for loop for the text and keyword 
    for(int i = 0, j = 0; i < textlen; i++) {
        if(isalpha(text[i])) { //check if certain character in the text is an alphabetic character
            key_letter = keyword[j % keylen]; //to get the matching character of text[i] in the keyword
            if(isupper(text[i])) {
                newkey[i] = toupper(key_letter); //converts a certain character in the key into uppercase
            }
            else {
                newkey[i] = tolower(key_letter); //converts a certain character in the key into lowercase
            }
            
            j++; //keyword will only match with alphabetic characters in the text
        }
        else {
            newkey[i] = text[i]; //non-alphabetic characters will not change
        }
    }

    newkey[textlen] = '\0'; //add null terminator in the end

    for(int i = 0; i < textlen; i++) {
        if (isupper(text[i])) { //check if a certain character in the text is uppercase
            encryptedtext[i] = ((text[i] - 'A' + (newkey[i] - 'A')) % 26) + 'A';
        }
        else if (islower(text[i])) { //check if a certain character in the text is lowercase
            encryptedtext[i] = ((text[i] - 'a' + (newkey[i] - 'a')) % 26) + 'a';
        }
        else {
            encryptedtext[i] = text[i]; //non-alphabetic characters will not change
        }

    }
    encryptedtext[textlen] = '\0'; //add null terminator in the end
}

//void function for vigenere decryption
void vigenere_decrypt(const char *text, const char *keyword, char *decryptedtext) {
    
    //declare an array variable for the new key 
    char newkey[STRINGMAX];
    char key_letter;
    //declare the length of the text as a variable
    int textlen = strlen(text), keylen = strlen(keyword);
    
    //for loop for the text and keyword 
    for(int i = 0, j = 0; i < textlen; i++) {
        if(isalpha(text[i])) { //check if certain character in the text is an alphabetic character
            key_letter = keyword[j % keylen]; //to get the matching character of text[i] in the keyword
            if(isupper(text[i])) {
                newkey[i] = toupper(key_letter); //converts a certain character in the key into uppercase
            }
            else {
                newkey[i] = tolower(key_letter); //converts a certain character in the key into lowercase
            }
            
            j++; //keyword will only match with alphabetic characters in the text
        }
        else {
            newkey[i] = text[i]; //non-alphabetic characters will not change
        }
    }
    newkey[textlen] = '\0'; //add null terminator in the end
    
    for(int i = 0; i < textlen; i++) {
        if (isupper(text[i])) { //check if a certain character in the encrypted text is uppercase
            decryptedtext[i] = (((text[i] - 'A' - (newkey[i] - 'A')) + 26) % 26) + 'A'; 
        }
        else if (islower(text[i])) { //check if a certain character in the encrypted text is lowercase
            decryptedtext[i] = (((text[i] - 'a' - (newkey[i] - 'a')) + 26) % 26) + 'a';
        }
        else {
            decryptedtext[i] = text[i]; //non-alphabetic characters will not change
        }
    }
    decryptedtext[textlen] = '\0'; //add null terminator in the end
}

int main() {
    int page1 = 0, page2 = 0, page3 = 0, page4 = 0, page5 = 0, page6 = 0;
    char plaintext[STRINGMAX], processedtext[STRINGMAX];

    struct note notes_list[MAXNOTES];
    int note_count=0;
    int * note_count_ptr = &note_count;
    note_count = load_notes(notes_list);

    int note_num = 0;

    do {
        system("cls");
        // 0.0 HOMEPAGE
        if (page1 == 0) {
            page1 = home_options();
        }
        
        // 1.0 ENCRYPT TEXT
        else if (page1 == 1) {

            // At first enter
            if (page2 == 0) {
                printf("=== "BYEL"Encrypt Text"reset" ===\n");
                page2 = encrypt_options();
            }
            
            // 1.1
            else if (page2 == 1) {
                // CAESAR CIPHER
                page3 = encrypt_page(1, plaintext, processedtext);
                if (page3 == 1) {
                    page2 = 1;
                } else if (page3 == 2) {
                    page2 = 0;
                } else {
                    printf("Invalid Input. Try Again.");
                    sleep(SLEEP);
                    page2 = 0;
                }
            }
            
            // 1.2
            else if (page2 == 2) {
                page3 = encrypt_page(2, plaintext, processedtext);
                if (page3 == 1) {
                    page2 = 2;
                } else if (page3 == 2) {
                    page2 = 0;
                } else {
                    printf("Invalid Input. Try Again.");
                    sleep(SLEEP);
                    page2 = 0;
                }
            
            }
            
            // 1.3
            else if (page2 == 3) {
                page3 = encrypt_page(3, plaintext, processedtext);
                if (page3 == 1) {
                    page2 = 3;
                } else if (page3 == 2) {
                    page2 = 0;
                } else {
                    printf("Invalid Input. Try Again.");
                    sleep(SLEEP);
                    page2 = 0;
                }
            }
            
            // BACK
            else if (page2 == 4) {
                page1 = 0;
                page2 = 0;
                page3 = 0;
            }

            else {
                printf("Invalid Input. Try Again.");
                sleep(SLEEP);
                page2 = 0;
                page3 = 0;
            }
        }
        
        // 2.0 DECRYPT TEXT
        else if (page1 == 2) {

            // At first enter
            if (page2 == 0) {
                printf("=== "BYEL"Decrypt Text"reset" ===\n");
                page2 = decrypt_options();
            }
            
            // 2.1
            else if (page2 == 1) {
                page3 = decrypt_page(1, plaintext, processedtext);
                if (page3 == 1) {
                    page2 = 1;
                } else if (page3 == 2) {
                    page2 = 0;
                } else {
                    printf("Invalid Input. Try Again.");
                    sleep(SLEEP);
                    page2 = 0;
                }
            }
            
            // 2.2
            else if (page2 == 2) {
                page3 = decrypt_page(2, plaintext, processedtext);
                if (page3 == 1) {
                    page2 = 2;
                } else if (page3 == 2) {
                    page2 = 0;
                } else {
                    printf("Invalid Input. Try Again.");
                    sleep(SLEEP);
                    page2 = 0;
                }
            
            }
            
            // 2.3
            else if (page2 == 3) {
                page3 = decrypt_page(3, plaintext, processedtext);
                if (page3 == 1) {
                    page2 = 3;
                } else if (page3 == 2) {
                    page2 = 0;
                } else {
                    printf("Invalid Input. Try Again.");
                    sleep(SLEEP);
                    page2 = 0;
                }
            }
            
            // BACK
            else if (page2 == 4) {
                page1 = 0;
                page2 = 0;
                page3 = 0;
            }

            else {
                printf("Invalid Input. Try Again.");
                sleep(SLEEP);
                page2 = 0;
                page3 = 0;
            }
        }

        // 3.0 NOTES SYSTEM
        else if (page1 == 3) {
            
            // At first enter
            if (page2 == 0) {
                preview_list(notes_list, note_count);
                printf(BWHT"\nWhat would you like to do?\n");
                printf(BLU"[1] Create a note\n");
                printf(YEL"[2] Open/Edit note using note number\n");
                printf(BRED"[3] Back\n"BGRN">>> "reset);
                scanf("%d", &page2);
                getchar();
            }

            // Create a note
            else if (page2 == 1) {
                create_note(notes_list, note_count_ptr);
                page2 = 0;
            }

            // Open a note
            else if (page2 == 2) {
                
                // At first enter
                if (page3 == 0) {
                    preview_list(notes_list, note_count);
                    printf(BWHT"\nWhich note to open?\n"BGRN">>> "reset);
                    scanf("%d", &note_num);
                    note_num--; // transform it to index
                    getchar();

                    // printf("%d\t%d\n", note_num, note_count);
                    if (note_num >= note_count || note_num < 0) {
                        printf("Note not found.");
                        note_num = 0;
                        page2 = 0;
                    } else {
                        page3 = 1;

                    }
                }
                
                // Opens a note
                else if (page3 == 1) {
                    strcpy(plaintext, notes_list[note_num].message);
                    // At first enter
                    if (page4 == 0) {
                        display_note(notes_list, note_num);
                        page4 = note_options();
                    }

                    // Encrypt note
                    else if (page4 == 1) {
                        display_note(notes_list, note_num);
                        
                        if (page5 == 0) {
                            printf("-- "BYEL"Encrypting"reset" --\n");
                            page5 = encrypt_options();
                        }
                        
                        // Caesar Cipher
                        else if (page5 == 1) {
                            page6 = note_encrypt_page(1, plaintext, processedtext);
                            if (page6 == 1) {
                                page5 = 0;
                                page4 = 0;
                            } else {
                                printf("Invalid Input. Try Again.");
                                sleep(SLEEP);
                            }
                        }

                        // XOR cipher
                        else if (page5 == 2) {
                            page6 = note_encrypt_page(2, plaintext, processedtext);
                            if (page6 == 1) {
                                page5 = 0;
                                page4 = 0;
                            } else {
                                printf("Invalid Input. Try Again.");
                                sleep(SLEEP);
                            }
                        }

                        // Vigenere cipher
                        else if (page5 == 3) {
                            page6 = note_encrypt_page(3, plaintext, processedtext);
                            if (page6 == 1) {
                                page5 = 0;
                                page4 = 0;
                            } else {
                                printf("Invalid Input. Try Again.");
                                sleep(SLEEP);
                            }
                        }

                        else if (page5 == 4) {
                            page6=0;
                            page5=0;
                            page4=0;
                        }

                        else {
                            printf("Invalid Input. Try Again.");
                            sleep(SLEEP);
                            page6=0;
                            page5=0;
                            page4=0;
                        }
                    }

                    // Decrypt note
                    else if (page4 == 2) {

                        display_note(notes_list, note_num);
                        
                        if (page5 == 0) {
                            printf("-- "BYEL"Decrypting"reset" --\n");
                            page5 = decrypt_options();
                        }

                        // Caesar Cipher
                        if (page5 == 1) {
                            page6 = note_decrypt_page(1, plaintext, processedtext);
                            if (page6 == 1) {
                                page5 = 0;
                                page4 = 0;
                            } else {
                                printf("Invalid Input. Try Again.");
                                sleep(SLEEP);
                            }
                        }

                        // XOR Cipher
                        else if (page5 == 2) {
                            page6 = note_decrypt_page(2, plaintext, processedtext);
                            if (page6 == 1) {
                                page5 = 0;
                                page4 = 0;
                            } else {
                                printf("Invalid Input. Try Again.");
                                sleep(SLEEP);
                            }
                        }

                        // Vigenere Cipher
                        else if (page5 == 3) {
                            page6 = note_decrypt_page(3, plaintext, processedtext);
                            if (page6 == 1) {
                                page5 = 0;
                                page4 = 0;
                            } else {
                                printf("Invalid Input. Try Again.");
                                sleep(SLEEP);
                            }
                        }

                        else if (page5 == 4) {
                            page6=0;
                            page5=0;
                            page4=0;
                        }

                        else {
                            printf("Invalid Input. Try again.");
                            sleep(SLEEP);
                            page6=0;
                            page5=0;
                            page4=0;
                        }
                    } 

                    // To edit the note
                    else if (page4 == 3) {
                        display_note(notes_list, note_num);
                        page4 = edit_note(notes_list, note_num);
                    }
                    
                    // To delete the note
                    else if (page4 == 4) {
                        display_note(notes_list, note_num);
                        page2 = delete_note(notes_list, note_count_ptr, note_num);
                        page4 = 0;
                        page3=0;
                        save_notes(notes_list, note_count);
                    }

                    // Back
                    else if (page4 == 5) {
                        page4 = 0;
                        page3 = 0;
                        page2 = 0;
                    }
                    
                    // Invalid input
                    else {
                        printf("Invalid Input. Try again.");
                        sleep(SLEEP);
                        page4 = 0;
                    }
                }

                else {
                    printf("Invalid Input. Try again.");
                    sleep(SLEEP);
                }
            }
            
            // Back to homepage from notes
            else if (page2 == 3) {
                page1 = 0;
                page2 = 0;
            }

            else {
                printf("Invalid Input. Try again.");
                sleep(SLEEP);
                page2 = 0;
            }

        } 
        
        else if (page1 == 4) {
            page1 = learn_ciphers();
        }
        else {
            printf("Invalid Input. Try again.");
            sleep(SLEEP);
            page1 = 0;
        }
        
    } while(page1 != 5);

    save_notes(notes_list, note_count);
    printf("Terminating program.");
    
    return 0;
}