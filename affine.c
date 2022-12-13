#include <stdio.h>
#include <string.h>

int inverse_mod(int a, int m){
    a = a % m;
    for (int x = 1; x < m; x++){
        if ((a * x) % m == 1){
            return x;
        }
    }
}

char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char *plaintext;

// Affine cipher with brute force
// function to decrypt the affine cipher using brute force

long gcd(long x, long y){
    if (y == 0){
        return x;
    }
    else{
        return gcd(y, x % y);
    }
}

void decrypt_affine_cipher(char *message, int m){
    // loop through all possible values of a and b
    for (int a = 1; a < m; a++){
        if (gcd(a, m) != 1) // if a and m are not coprime, skip
            continue;
        for (int b = 0; b < m; b++){
            // decrypted message
            char decryptedMessage[strlen(message)];

            // loop through each character in the cipher text
            for (int i = 0; i < strlen(message); i++){
                // decrypt the current character
                char decryptedChar = ((inverse_mod(a, m) * (message[i] - 'A' - b + m)) % m) + 'A';

                // add the decrypted character to the decrypted message
                decryptedMessage[i] = decryptedChar;
            }

            // print the decrypted message
            printf("For a = %d, b = %d Message: %s\n", a, b, decryptedMessage);
        }
    }
}
int main()
{
    // Sample ciphertext to decrypt
    char ciphertext[] = "NUTALDQIQTAYRQNJDHHNLDMTLDHYVNAEDPHDMYRDAHPQDYCDTAYDLQTYFRUNMRVPJDAYRQNJDHHNLDYRDAHPQDYCDTAYDLQTYFRUNJDHHNLDERYCYCDJDHHNLDNAMYCDJDHHNLDMTLDHYNQDADDMDM";

    // Decrypt the ciphertext using brute force
    decrypt_affine_cipher(ciphertext, 26);

    return 0;
}
