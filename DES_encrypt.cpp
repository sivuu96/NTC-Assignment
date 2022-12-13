#include <bits/stdc++.h>
using namespace std;

string encryption(vector<string> round_key_binary, vector<string> round_key_arr,string plain_text);
string Permutation(string str, int *par_arr, int n);

// S-box Table
int Sbox[8][4][16] = {
    {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
     0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
     4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
     15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
    {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
     3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
     0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
     13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
    {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
     13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
     13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
     1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
    {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
     13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
     10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
     3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
    {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
     14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
     4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
     11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
    {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
     10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
     9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
     4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
    {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
     13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
     1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
     6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
    {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
     1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
     7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
     2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};

int Straight_per_table[32] = {16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23,
    26, 5, 18, 31, 10, 2, 8, 24, 14, 32, 27,
    3, 9, 19, 13, 30, 6, 22, 11, 4, 25
};

int shiftTable[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

string shiftLeft(string str, int moves){
    string Sbox = "";
    for (int i = 0; i < moves; i++){
        for (int j = 1; j < 28; j++){
            Sbox += str[j];
        }
        Sbox += str[0];
        str = Sbox;
        Sbox = "";
    }
    return str;
}

string Xor(string x1, string x2){
    string mid = "";
    for (int i = 0; i < x1.size(); ++i){
        if (x1[i] != x2[i]){
            mid += "1";
        }
        else{
            mid += "0";
        }
    } 
    return mid;
}

string Bin_to_Hex(string Sbox){
    // binary to hexadecimal conversion
    unordered_map<string, string> HexMap;
    HexMap["0000"] = "0";
    HexMap["0001"] = "1";
    HexMap["0010"] = "2";
    HexMap["0011"] = "3";
    HexMap["0100"] = "4";
    HexMap["0101"] = "5";
    HexMap["0110"] = "6";
    HexMap["0111"] = "7";
    HexMap["1000"] = "8";
    HexMap["1001"] = "9";
    HexMap["1010"] = "A";
    HexMap["1011"] = "B";
    HexMap["1100"] = "C";
    HexMap["1101"] = "D";
    HexMap["1110"] = "E";
    HexMap["1111"] = "F";
    string hex = "";
    for (int i = 0; i < Sbox.length(); i += 4){
        string temp = "";
        temp += Sbox[i];
        temp += Sbox[i + 1];
        temp += Sbox[i + 2];
        temp += Sbox[i + 3];
        hex += HexMap[temp];
    }
    return hex;
}

string Hex_to_Bin(string Sbox){
    // hexadecimal to binary conversion
    unordered_map<char, string> HexMap;
    HexMap['0'] = "0000";
    HexMap['1'] = "0001";
    HexMap['2'] = "0010";
    HexMap['3'] = "0011";
    HexMap['4'] = "0100";
    HexMap['5'] = "0101";
    HexMap['6'] = "0110";
    HexMap['7'] = "0111";
    HexMap['8'] = "1000";
    HexMap['9'] = "1001";
    HexMap['A'] = "1010";
    HexMap['B'] = "1011";
    HexMap['C'] = "1100";
    HexMap['D'] = "1101";
    HexMap['E'] = "1110";
    HexMap['F'] = "1111";
    string binary = "";
    for (int i = 0; i < Sbox.size(); ++i){
        binary += HexMap[Sbox[i]];
    }
    return binary;
}

int main(){
    string plain_text, key;

    //a random value assigned to key and plaintext
    key = "BABB09182736CCDD";
    plain_text = "CA123D56DBC51342";
    
    // Key-Compression Table
    int key_comp[48] = {14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
    };

    // Hex to binary as a part of key generation
    key = Hex_to_Bin(key);

    // Parity bit table
    int parity_key[56] = {57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4
    };

    // getting 56 bit key from 64 bit using the parity bits
    key = Permutation(key, parity_key, 56); // key without parity

    // Splitting the permuted key
    string left_per = key.substr(0, 28);
    string right_per = key.substr(28, 28);

    vector<string> round_key_arr;  // rk for RoundKeys in hexadecimal
    vector<string> round_key_binary; // rkb for RoundKeys in binary

    for (int i = 0; i < 16; ++i){
        // Shifting
        left_per = shiftLeft(left_per, shiftTable[i]);
        right_per = shiftLeft(right_per, shiftTable[i]);

        // Combining
        string Combined = left_per + right_per;

        // Key Compression
        string Round_Key = Permutation(Combined, key_comp, 48);

        round_key_binary.push_back(Round_Key);
        round_key_arr.push_back(Bin_to_Hex(Round_Key));
    }

    cout << "\nEncryption Starts:\n"<<endl;
    string Cipher_Text = encryption(round_key_binary, round_key_arr,plain_text);
    cout << "\nCipher Text: " << Cipher_Text << endl;
    cout << "\nEncryption ends" << endl;

    fstream cipherText;
    cipherText.open("cipherText.txt", ios::out);
    cipherText << Cipher_Text << endl;
    cipherText.close();
    return 0;
}

string Permutation(string str, int *par_arr, int n){
    string ret = "";
    for (int i = 0; i < n; ++i){
        ret += str[par_arr[i] - 1];
    }
    return ret;
}

string encryption(vector<string> round_key_binary, vector<string> round_key_arr,string plain_text){
    
    plain_text = Hex_to_Bin(plain_text);

    // Initial Permutation Table
    int perm_table_initial[64] = {58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28,
        20, 12, 4, 62, 54, 46, 38, 30, 22, 14, 6, 64, 56,
        48, 40, 32, 24, 16, 8, 57, 49, 41, 33, 25, 17, 9,
        1, 59, 51, 43, 35, 27, 19, 11, 3, 61, 53, 45, 37,
        29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
    };
    
    // Expansion D-box Table
    int EXPANSION_D[48] = {32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9,
        8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1
    };

    plain_text = Permutation(plain_text, perm_table_initial, 64);
    cout << "Initial permutation: " << Bin_to_Hex(plain_text) << endl;

    // Splitting
    string left_per = plain_text.substr(0, 32);
    string right_per = plain_text.substr(32, 32);
    cout << "Splitting of initial permutation: L0=" << Bin_to_Hex(left_per) << " R0=" << Bin_to_Hex(right_per)
    << endl;

    cout << "\n";
    cout << "16 rounds of encryption"<<endl;
    cout << "\n";

    for (int i = 0; i < 16; i++){
        // Expansion D-box
        string right_expanded = Permutation(right_per, EXPANSION_D, 48);

        // XOR RoundKey[i] and right_expanded
        string _xor = Xor(round_key_binary[i], right_expanded);

        // S-boxes
        string output = "";
        for (int i = 0; i < 8; i++){
            int row = int(_xor[i * 6 + 5] - '0') + 2 * int(_xor[i * 6] - '0');
            int col = 8 * int(_xor[i * 6 + 1] - '0') +
                      4 * int(_xor[i * 6 + 2] - '0') +
                      2 * int(_xor[i * 6 + 3] - '0') + int(_xor[i * 6 + 4] - '0');
            int val = Sbox[i][row][col];
            output += char(val / 8 + '0');
            val = val % 8;
            output += char(val / 4 + '0');
            val = val % 4;
            output += char(val / 2 + '0');
            val = val % 2;
            output += char(val + '0');
        }
        // Straight D-box
        output = Permutation(output, Straight_per_table, 32);

        // XOR left_per and output
        _xor = Xor(output, left_per);

        left_per = _xor;

        swap(left_per, right_per);
        cout << "Round-" << i + 1 << " " << Bin_to_Hex(left_per) << " "
        << Bin_to_Hex(right_per) << " " << round_key_arr[i] << endl;
    }

    swap(left_per, right_per);
    cout << "\nAfter Final-Swapping : "
         << " " << Bin_to_Hex(left_per) << " " << Bin_to_Hex(right_per) << " " << endl;
    // Combination
    string Combined = left_per + right_per;

    // Final Permutation Table
    int final_permutation_table[64] = {40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55,
        23, 63, 31, 38, 6, 46, 14, 54, 22, 62, 30, 37, 5,
        45, 13, 53, 21, 61, 29, 36, 4, 44, 12, 52, 20, 60,
        28, 35, 3, 43, 11, 51, 19, 59, 27, 34, 2, 42, 10,
        50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25
    };

    // Final Permutation
    string Cipher_Text = Bin_to_Hex(Permutation(Combined, final_permutation_table, 64));
    return Cipher_Text;
}


