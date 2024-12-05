#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRINGMAX 1000
#define FILEPATH "data.txt"
#define MAXNOTES 100

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


// Function to print the options in home
int home_options() {
    int response = 0;
    char buffer[STRINGMAX];
    printf("=== WELCOME TO <INSERT APP NAME> ===\n");
    printf("\nWhat would you like to do?\n");
    printf("[1] Encrypt Text\n");
    printf("[2] Decrypt Text\n");
    printf("[3] Go to Notes\n");
    printf("[4] Learn about the Ciphers\n");
    printf("[5] Exit\n>>> ");
    fgets(buffer, STRINGMAX, stdin);
    sscanf(buffer, "%d", &response);
    return response;
}

// Function to show the cipher options
int encrypt_options() {
    int response = 0;
    char buffer[STRINGMAX];
    
    // Cipher Options
    printf("\nWhich cipher would you like to use?\n");
    printf("[1] Caesar Cipher\n");
    printf("[2] XOR Cipher\n");
    printf("[3] Vigenere Cipher\n");
    printf("[4] Back\n>>> ");
    
    fgets(buffer, STRINGMAX, stdin);
    sscanf(buffer, "%d", &response);
    return response;
}

// Function to display the encryption process and call the appropriate encryption function
int encrypt_page(int chosen_cipher, char * src, char * dest) {
    
    int response = 0;
    char cipher[STRINGMAX]; // stores the cipher name
    int key=0;
    char buffer[STRINGMAX];

    if (chosen_cipher == 1) {
        strcpy(cipher, "Caesar Cipher");
    } else if (chosen_cipher == 2){
        strcpy(cipher, "XOR Cipher");
    } else if (chosen_cipher == 3){
        strcpy(cipher, "Vigenere Cipher");
    }

    printf("=== Encrypt Text Using %s ===\n", cipher);

    printf("\nEnter Message:\n>>> ");
    fgets(src, STRINGMAX, stdin);

    // Input the key
    printf("\nEnter Key:\n>>> ");
    fgets(buffer, STRINGMAX, stdin);
    sscanf(buffer, "%d", &key);

    // Calls the appropriate cipher function
    if (chosen_cipher == 1) {
        encrypt_text(src, key, dest);
    } else if (chosen_cipher == 2){
        xor_encrypt(src, key, dest);
    } else if (chosen_cipher == 3){
        encrypt_text(src, key, dest);
    }

    // Display the output and asks for next action
    printf("\nEncrypted Text:\n%s\n\n", dest);
    printf("[1] Encrypt another\n");
    printf("[2] Back\n>>> ");
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
    printf("\nWhich cipher would you like to use?\n");
    printf("[1] Caesar Cipher\n");
    printf("[2] XOR Cipher\n");
    printf("[3] Vigenere Cipher\n");
    printf("[4] Back\n>>> ");
    
    fgets(buffer, STRINGMAX, stdin); 
    sscanf(buffer, "%d", &response);
    return response;
}

// Function to display the decryption process and call the appropriate decryption function
int decrypt_page(int chosen_cipher, char * src, char * dest) {
    
    int response = 0;
    char cipher[STRINGMAX];
    int key=0;
    char buffer[STRINGMAX];

    if (chosen_cipher == 1) {
        strcpy(cipher, "Caesar Cipher");
    } else if (chosen_cipher == 2){
        strcpy(cipher, "XOR Cipher");
    } else if (chosen_cipher == 3){
        strcpy(cipher, "Vigenere Cipher");
    }

    printf("=== Decrypt Text Using %s ===\n", cipher);

    printf("\nEnter Message:\n>>> ");
    fgets(src, STRINGMAX, stdin);

    // Input the key
    printf("\nEnter Key:\n>>> ");
    fgets(buffer, STRINGMAX, stdin); // Read the entire line into buffer
    sscanf(buffer, "%d", &key);

    // calls the appropriate decryption function
    if (chosen_cipher == 1) {
        encrypt_text(src, key, dest);
    } else if (chosen_cipher == 2){
        xor_decrypt(src, key, dest);
    } else if (chosen_cipher == 3){
        encrypt_text(src, key, dest);
    }

    // Displays the output
    printf("\nPlain Text:\n%s\n\n", dest);
    printf("[1] Decrypt another\n");
    printf("[2] Back\n>>> ");
    fgets(buffer, STRINGMAX, stdin);
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
    printf("=== Learn About Ciphers! ===\n");
    printf("\nThis page will show some information about the ciphers\n");
    printf("used in the program. It can also include our names!! >U< \n");

    printf("\n[1] Back\n>>> ");
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
    printf("=== NOTES ===\n");
    printf("\nNO.\tTITLE\n");
    for (int i = 0; i < note_count; i++) {
        printf("%d\t%s\n", i+1, notes_list[i].title);
    }
}

void display_note(struct note notes_list[], int note_num) {
    printf("=== Notes ===\n\n");
    printf("Title: %s\n", notes_list[note_num].title);
    printf("Message: \n %s\n\n", notes_list[note_num].message);
}

int note_options() {
    int response = 0;
    printf("What would you like to do?\n");
    printf("[1] Encrypt it\n");
    printf("[2] Decrypt it\n");
    printf("[3] Edit\n");
    printf("[4] Delete\n");
    printf("[5] Back to notes\n>>> ");
    scanf("%d", &response);
    getchar();
    return response;
}

int note_encrypt_page(int chosen_cipher, char * src, char * dest) {
    int response = 0;
    char cipher[STRINGMAX]; // stores the cipher name
    int key=0;
    char buffer[STRINGMAX];

    if (chosen_cipher == 1) {
        strcpy(cipher, "Caesar Cipher");
    } else if (chosen_cipher == 2){
        strcpy(cipher, "XOR Cipher");
    } else if (chosen_cipher == 3){
        strcpy(cipher, "Vigenere Cipher");
    } else {
        printf("ERROR");
    }

    printf("-- Encrypting Using %s --\n", cipher);

    // Input the key
    printf("\nEnter Key:\n>>> ");
    fgets(buffer, STRINGMAX, stdin); // Read the entire line into buffer
    sscanf(buffer, "%d", &key);

    if (chosen_cipher == 1) {
        encrypt_text(src, key, dest);
    } else if (chosen_cipher == 2){
        encrypt_text(src, key, dest);
    } else if (chosen_cipher == 3){
        encrypt_text(src, key, dest);
    }

    printf("Encrypted text:\n%s\n", dest);
    printf("[1] Back\n>>> ");
    scanf("%d", &response);
    getchar();
    return response;
}

int note_decrypt_page(int chosen_cipher, char * src, char * dest) {
    int response = 0;
    char cipher[STRINGMAX]; // stores the cipher name
    int key=0;
    char buffer[STRINGMAX];

    if (chosen_cipher == 1) {
        strcpy(cipher, "Caesar Cipher");
    } else if (chosen_cipher == 2){
        strcpy(cipher, "XOR Cipher");
    } else if (chosen_cipher == 3){
        strcpy(cipher, "Vigenere Cipher");
    }

    printf("-- Decrypting Using %s --\n", cipher);

    // Input the key
    printf("\nEnter Key:\n>>> ");
    fgets(buffer, STRINGMAX, stdin); // Read the entire line into buffer
    sscanf(buffer, "%d", &key);

    if (chosen_cipher == 1) {
        encrypt_text(src, key, dest);
    } else if (chosen_cipher == 2){
        encrypt_text(src, key, dest);
    } else if (chosen_cipher == 3){
        encrypt_text(src, key, dest);
    }

    printf("Plaintext:\n%s\n", dest);
    printf("[1] Back\n>>> ");
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
    printf("=== Notes ===\n");
    printf("\n-- Creating New Note --\n");
    printf("Enter title:\n>>> ");
    fgets(notes_list[*note_count].title, STRINGMAX, stdin);
    notes_list[*note_count].title[strcspn(notes_list[*note_count].title, "\n")] = '\0';  // Remove newline

    printf("Enter message:\n>>> ");
    fgets(notes_list[*note_count].message, STRINGMAX, stdin);
    notes_list[*note_count].message[strcspn(notes_list[*note_count].message, "\n")] = '\0';  // Remove newline

    (*note_count)++;
    save_notes(notes_list, *note_count);
}



int delete_note(struct note notes_list[], int * note_count, int note_del) {

    int response=0;

    printf("Are you sure you want to delete this note?\n");
    printf("[1] YES\n[2] BACK\n>>> ");
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

    printf("\n-- Editing --\n");
    printf("Which part to edit?\n");
    printf("[1] Title\n");
    printf("[2] Message\n");
    printf("[3] Back\n>>> ");
    scanf("%d", &response);
    getchar();

    if (response == 1) {
        printf("Enter new title:\n>>> ");
        fgets(new, STRINGMAX, stdin);

        strcpy(notes_list[note_edit].title, new);
    } else if (response == 2) {
        printf("Enter new message:\n>>> ");
        fgets(new, STRINGMAX, stdin);

        strcpy(notes_list[note_edit].message, new);
    } else if (response == 3) {
    } else {
        printf("Invalid Input. Try again.");
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
                printf("=== Encrypt Text ===\n");
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
                page2 = 0;
                page3 = 0;
            }
        }
        
        // 2.0 DECRYPT TEXT
        else if (page1 == 2) {

            // At first enter
            if (page2 == 0) {
                printf("=== Decrypt Text ===\n");
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
                page2 = 0;
                page3 = 0;
            }
        }

        // 3.0 NOTES SYSTEM
        else if (page1 == 3) {
            
            // At first enter
            if (page2 == 0) {
                preview_list(notes_list, note_count);
                printf("\nWhat would you like to do?\n");
                printf("[1] Create a note\n");
                printf("[2] Open/Edit note using note number\n");
                printf("[3] Back\n>>> ");
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
                    printf("\nWhich note to open?\n>>> ");
                    scanf("%d", &note_num);
                    note_num--; // transform it to index
                    getchar();

                    printf("%d\t%d\n", note_num, note_count);
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
                    
                    // At first enter
                    if (page4 == 0) {
                        display_note(notes_list, note_num);
                        page4 = note_options();
                    }

                    // Encrypt note
                    else if (page4 == 1) {
                        display_note(notes_list, note_num);
                        printf("-- Encrypting --\n");
                        page5 = encrypt_options();
                        
                        // Caesar Cipher
                        if (page5 == 1) {
                            page6 = note_encrypt_page(1, plaintext, processedtext);
                            if (page6 == 1) {
                                page5 = 0;
                                page4 = 0;
                            } else {
                                printf("Invalid Input. Try Again.");
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
                            }
                        }

                        else if (page5 == 4) {
                            page6=0;
                            page5=0;
                            page4=0;
                        }

                        else {
                            printf("Invalid Input. Try Again.");
                            page6=0;
                            page5=0;
                            page4=0;
                        }
                    }

                    // Decrypt note
                    else if (page4 == 2) {

                        display_note(notes_list, note_num);
                        printf("-- Decrypting --\n");
                        page5 = decrypt_options();
                        
                        // Caesar Cipher
                        if (page5 == 1) {
                            page6 = note_decrypt_page(1, plaintext, processedtext);
                            if (page6 == 1) {
                                page5 = 0;
                                page4 = 0;
                            } else {
                                printf("Invalid Input. Try Again.");
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
                            }
                        }

                        else if (page5 == 4) {
                            page6=0;
                            page5=0;
                            page4=0;
                        }

                        else {
                            printf("Invalid Input. Try again.");
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
                        page4 = 0;
                    }
                }

                else {
                    printf("Invalid Input. Try again.");
                }
            }
            
            // Back to homepage from notes
            else if (page2 == 3) {
                page1 = 0;
                page2 = 0;
            }

            else {
                printf("Invalid Input. Try again.");
                page2 = 0;
            }

        } 
        
        else if (page1 == 4) {
            page1 = learn_ciphers();
        }
        else {
            printf("Invalid Input. Try again.");
            page1 = 0;
        }
        
    } while(page1 != 5);

    save_notes(notes_list, note_count);
    printf("Terminating program.");
    
    return 0;
}