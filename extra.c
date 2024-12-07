#include <stdio.h>
#include <string.h>


int main() {
    char string[] = "HELLO WORLD";
    strcpy(string, "HELLO");
    printf("%s", string);
    return 0;
}