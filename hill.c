#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double determinant(double** m, int n){
  double det = 0;

  if (n == 1){
    det = m[0][0];
  }
  else{
    // recursive case: calculate the determinant using the Laplace expansion
    for (int i = 0; i < n; i++)
    {
      // create a submatrix by removing the i-th row and j-th column
      double** submatrix = malloc((n - 1) * sizeof(double*));
      for (int j = 0; j < n - 1; j++)
      {
        submatrix[j] = malloc((n - 1) * sizeof(double));
      }

      // copy the elements of the original matrix into the submatrix,
      // skipping the i-th row and j-th column
      for (int j = 1; j < n; j++){
        for (int k = 0; k < n; k++){
          if (k < i)
          {
            submatrix[j - 1][k] = m[j][k];
          }
          else if (k > i)
          {
            submatrix[j - 1][k - 1] = m[j][k];
          }
        }
      }

      // use the submatrix to calculate the determinant of the original matrix
      if (i % 2 == 0)
      {
        det += m[0][i] * determinant(submatrix, n - 1);
      }
      else
      {
        det -= m[0][i] * determinant(submatrix, n - 1);
      }

      // free the memory allocated for the submatrix
      for (int j = 0; j < n - 1; j++)
      {
        free(submatrix[j]);
      }
      free(submatrix);
    }
  }

  return det;
}

const char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

const int key[4][4] = {{2, 14, 13, 13},
    {4, 2, 19, 4},
    {3, 6, 17, 0},
    {15, 7, 8, 2}
};

const char *ciphertext = "CCCYTWACWKYWSARTIBMHZAEKFGZPDGBFWKAFKELXCCGSDBTUBNLUGANEDJBRFDEOCCCYTMAKFBRYAOBUPHOFTWNP";

int main(void)
{
    // initialize the plaintext
    char *plaintext = malloc(strlen(ciphertext) + 1);
    memset(plaintext, 0, strlen(ciphertext) + 1);

    // calculate the inverse of the key matrix
    int key_inv[4][4]={{24,5,19,16},{18,3,1,7},{20,21,4,10},{15,11,20,24}};
    // for (int i = 0; i < 4; i++) {
    //     for (int j = 0; j < 4; j++) {
    //         // calculate the (i, j)th element of the inverse key matrix
    //         int element = 0;
    //         for (int k = 0; k < 4; k++) {
    //             element += pow(-1, i + k) * key[(i + 1) % 4][(k + 1) % 4] * key[(k + 1) % 4][(j + 1) % 4];
    //         }
    //         element %= 26;
    //         key_inv[i][j] = element;
    //     }
    // }
    
    // decode the ciphertext using the inverse key matrix
    for (int i = 0; i < strlen(ciphertext); i += 4) {
        // get the current block of ciphertext
        char *ref = malloc(5);
        memset(ref, 0, 5);
        strncpy(ref, ciphertext + i, 4);

        // pad the ref with spaces if it is not long enough
        if (strlen(ref) < 4) {
            strncat(ref, "    ", 4 - strlen(ref));
        }

        // convert the ref to a hill_ct_matrix of positions
        int hill_ct_matrix[4];
        for (int j = 0; j < 4; j++) {
            hill_ct_matrix[j] = strchr(alphabet, ref[j]) - alphabet;
           // printf(" %d  ", hill_ct_matrix[j]);
        }
       // printf("\n");

        // decode the ref using the key matrix

        // multiply the hill_ct_matrix by the inverse key matrix to decode the ref
        int decoded[4] = {0};
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                decoded[i] += key_inv[i][j] * hill_ct_matrix[j];
            }
            decoded[i] %= 26;
        }

    for (int j = 0; j < 4; j++) {
        plaintext[i+j] = alphabet[decoded[j]];
    }
    }

    printf("%s", plaintext);
    // convert the decoded hill_ct_matrix back to a string of letters
    }
