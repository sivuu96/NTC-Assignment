#include <stdio.h>
#include <string.h>

//Function to decrypt the vigenere cipher using the given key
void vigenere_decrypt(char *input, char *key){
    int i, j;
    int input_len = strlen(input);
    int key_len = strlen(key);

    i = 0, j = 0;
    //Loop through each character in the input string
    for (; i < input_len; i++, j++){
        //If the key has been used up, reset it to the beginning
        if (j == key_len)
            j = 0;

        //Subtract the key character from the input character to get the decrypted character
        input[i] = ((input[i] - key[j] + 26) % 26) + 'A';
    }
}

int main(){
    char input[] = "IYEGXPXMMOETTNZKAYAUYYTTBBMVFFYYKKKCIGXELZFXBAVSIJZOXQBBNXUWIOYZVTFRVABXMZXWYROXAZRTXOEOLSKUTJAEKMGWABWHVAMYKPHQVCQLFMQNWOEOBRMETXOFVTQMGHJIIGIRWTKEVYQVFIFAJAEKMGWALYYVAVMUCKIYJQHLNHGGZZWGQBUTXGIMFYLRYVUDAVPIGVL"; //Input string to be decrypted
    char key[] = "INTEGRITY"; //Key used for decryption


    printf("Input String: %s\n", input); //Print the input string

    vigenere_decrypt(input, key); //Decrypt the input string using the given key

    printf("Decrypted String: %s\n", input); //Print the decrypted string

    return 0;
}