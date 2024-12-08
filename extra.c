#include <stdio.h>
#include <string.h>
#include <ctype.h>



int main() {

    int key = 2;
    char src [] = "HelloWorld";
    char dest [100];

    for (int i = 0; i < strlen(src); i++)
    {
        // printf("%c\n",src[i] + key);
        if (src[i] > 64){
            printf("Uppercase:%c\n", src[i]);
        } 
        else{
            printf("lowercase: %c\n", src[i]);
        }                
        
        
    }
    printf("chuchu\n");


    return 0;
}