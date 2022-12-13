#include <bits/stdc++.h>
using namespace std;


string DEC_DES(string plaintext, vector<string> RoundKeyBinary, vector<string> RoundKeyHex);
//int i;

// PARITY DROP TABLE
int paritypos[56] = {57, 49, 41, 33, 25, 17, 9, 1, 58, 
                     50, 42, 34, 26, 18, 10, 2, 59, 51, 
                     43, 35, 27, 19, 11, 3, 60, 52, 44, 
                     36, 63, 55, 47, 39, 31, 23, 15, 7, 
                     62, 54, 46, 38, 30, 22, 14, 6, 61, 
                     53, 45, 37, 29, 21, 13, 5, 28, 20, 
                     12, 4};
// NUMBER OF SHIFTS REQUIRED FOR EACH BIT IN KEY
int shiftval[16] = {1, 1, 2, 2, 
                    2, 2, 2, 2, 
                    1, 2, 2, 2, 
                    2, 2, 2, 1};
// KEY COMPRESSION 
int comptable[48] = {14, 17, 11, 24, 1, 5, 3, 28, 15, 
                     6, 21, 10, 23, 19, 12, 4, 26, 8, 
                     16, 7, 27, 20, 13, 2, 41, 52, 31, 
                     37, 47, 55, 30, 40, 51, 45, 33, 48,
                     44, 49, 39, 56, 34, 53, 46, 42, 50, 
                     36, 29, 32};

// EXPANSION P BOX VALUES
int Pbox_exp[48] = {32, 1, 2, 3, 4, 5, 4, 5, 
                    6, 7, 8, 9, 8, 9, 10, 11, 
                    12, 13, 12, 13, 14, 15, 16, 
                    17, 16, 17, 18, 19, 20, 21, 
                    20, 21, 22, 23, 24, 25, 24, 
                    25, 26, 27, 28, 29, 28, 29, 
                    30, 31, 32, 1};
// INITIAL P BOX VALUES
int InitialPBox[64] = {58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28,
                      20, 12, 4, 62, 54, 46, 38, 30, 22, 14, 6, 64, 56,
                      48, 40, 32, 24, 16, 8, 57, 49, 41, 33, 25, 17, 9,
                      1, 59, 51, 43, 35, 27, 19, 11, 3, 61, 53, 45, 37,
                      29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};
// STANDARD S BOX VALUES
int SBOX[8][4][16] = {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7, 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0, 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10, 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5, 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15, 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8, 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1, 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7, 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15, 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9, 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4, 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9, 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6, 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14, 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11, 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8, 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6, 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1, 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6, 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2, 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7, 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2, 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8, 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
        };

// STRAIGHT P BOX VALUES
int Pbox_str[32] = {16, 7, 20, 21, 29, 12, 28, 
                    17, 1, 15, 23, 26, 5, 18, 
                    31, 10, 2, 8, 24, 14, 32, 
                    27,3, 9, 19, 13, 30, 6, 22, 
                    11, 4, 25};

// FINAL P BOX VALUES
int FinalPBox[64] = {40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55,
                          23, 63, 31, 38, 6, 46, 14, 54, 22, 62, 30, 37, 5,
                          45, 13, 53, 21, 61, 29, 36, 4, 44, 12, 52, 20, 60,
                          28, 35, 3, 43, 11, 51, 19, 59, 27, 34, 2, 42, 10,
                          50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25};

string Bin2Hex(string S_BOX)
{
    // CORRESPONDING BINARY TO HEXADECIMAL CONVERSION IS MAPPED
    unordered_map <string, string> B2H;
    B2H["0000"] = "0"; B2H["0001"] = "1"; B2H["0010"] = "2";
    B2H["0011"] = "3"; B2H["0100"] = "4"; B2H["0101"] = "5";
    B2H["0110"] = "6"; B2H["0111"] = "7"; B2H["1000"] = "8";
    B2H["1001"] = "9"; B2H["1010"] = "A"; B2H["1011"] = "B";
    B2H["1100"] = "C"; B2H["1101"] = "D"; B2H["1110"] = "E";
    B2H["1111"] = "F";
    string retval = "";
    for (int i=0; i<S_BOX.length(); i += 4) {
        string chara = "";
        chara = chara + S_BOX[i]; chara = chara + S_BOX[i+1]; chara = chara + S_BOX[i+2]; chara = chara + S_BOX[i+3]; retval = retval + B2H[chara]; }
    return retval;
}
string ShiftLeft(string key, int shiftno)
{
    string S_BOX = "";
    
    for (int i = 0; i < shiftno; i++)
    {
        for (int j = 1; j <= 27; j++)
        { S_BOX += key[j]; }
        S_BOX += key[0]; key = S_BOX; S_BOX = "";
    }
    
    return key;
}

string X0R(string x, string y)
{
    string retval = "";
    
    for (int i=0; i<x.size(); i++)
    {  if (x[i] == y[i]) {
          retval += "0"; }
       else { 
          retval += "1"; }
    }
    
    return retval;
}

string PermuteIn(string k, int condpos[], int n)
{
    string initialperm = "";
    for (int i = 0; i < n; i++)
    { initialperm = initialperm + k[ condpos[i] - 1 ]; }
    return initialperm;
}

string Hex2Bin(string SBOX)
{
    // hexadecimal to binary conversion
    unordered_map <char, string> H2B;
    H2B['0'] = "0000"; H2B['1'] = "0001"; H2B['2'] = "0010";
    H2B['3'] = "0011"; H2B['4'] = "0100"; H2B['5'] = "0101";
    H2B['6'] = "0110"; H2B['7'] = "0111"; H2B['8'] = "1000";
    H2B['9'] = "1001"; H2B['A'] = "1010"; H2B['B'] = "1011";
    H2B['C'] = "1100"; H2B['D'] = "1101"; H2B['E'] = "1110";
    H2B['F'] = "1111";
    string retval = "";
    for (int i=0; i<SBOX.size(); i++) { retval = retval + H2B[SBOX[i]];
    }
    return retval;
}
int main()
{
    string key;
    fstream CT;
    CT.open("CT_FILE_OP.txt", ios::in);
    string CIPHERTEXT;
    CT>>CIPHERTEXT;
    //cout<<CIPHERTEXT;
    key = "CADA011943ACDABC";
    
    // CONVERT THE KEY TO CORRESPONDING BINARY FORMAT
    // THE KEY IS CONVERTED FROM 64 BITS TO 56 BITS
    // TO ACHIEVE THIS DROP THE CORRESPONDING PARITY BITS
     key = Hex2Bin(key);

     key = PermuteIn(key, paritypos, 56); // key without parity

    // THE GENERATED KEY IS FURTHER DIVIDED INTO A LEFT SUBSTRING AND RIGHT SUBSTRING
    // EACH SUBSTRING IS OF 28 BIT LENGTH
     string LEFT_SUBSTR = key.substr(0, 28);
     string RIGHT_SUBSTR = key.substr(28, 28);
    
    // INIALISE VARIABLE FOR GENERATING ROUNDKEYS
    // ALSO REQUIRED IN HEXADECIMAL AS WELL AS BINARY
    // KEEP VARIABLES READY FOR THE SAME
     vector<string> RoundKeyBinary; 
     vector<string> RoundKeyHex;  
    for (int i=0; i<16; i++) {
    
        // SHIFT THE LEFT SUBSTRING AND RIGHT SUBSTRING ACCORDINGLY
        // THE SHIFT VALUE OR NO OF BITS TO BE SHIFTED BY 
        // CAN BE TAKEN FROM SHIFTVAL TABLE INITIALISED GLOBALLY
        // AFTER THAT COMBINE THE GENERATED KEYS TOGETHER
          // cout<<CIPHERTEXT;
           LEFT_SUBSTR = ShiftLeft(LEFT_SUBSTR, shiftval[i]);
          // cout<<LEFT_SUBSTR<<endl;
           RIGHT_SUBSTR = ShiftLeft(RIGHT_SUBSTR, shiftval[i]);
           string DEC_TEXT = LEFT_SUBSTR + RIGHT_SUBSTR;
          // cout<<DEC_TEXT<<endl;

        // COMPRESS THE 56 BITS KEY TO FORM 48 BIT KEY
        // THIS IS DONE USING COMPRESSION PERMUTATION TABLE
           string RoundKey = PermuteIn(DEC_TEXT, comptable, 48);

           RoundKeyBinary.push_back(RoundKey);  RoundKeyHex.push_back(Bin2Hex(RoundKey)); 
    }

      reverse(RoundKeyBinary.begin(), RoundKeyBinary.end()); reverse(RoundKeyHex.begin(), RoundKeyHex.end());  
   // cout<<CIPHERTEXT;
    string text = DEC_DES(CIPHERTEXT, RoundKeyBinary, RoundKeyHex);
    cout << "PLAINTEXT GENERATED: " << text << endl; 

    return 0;
}



string DEC_DES(string plaintext, vector<string> RoundKeyBinary, vector<string> RoundKeyHex)
{
    // CONVERT HEXADECIMAL CODE TO BINARY
    plaintext = Hex2Bin(plaintext);
    // DO THE INITIAL PERMUTATION
    plaintext = PermuteIn(plaintext, InitialPBox, 64);
    cout << "INITIAL PERMUTATION: "<< Bin2Hex(plaintext)<<"\n";

    // SPLIT THE ABOVE GENERATED PLAINTEXT INTO 2 SUBSTRINGS
    // EACH SUBSTRING IS OF LENGTH 32 BITS
    string LEFTSUBSTR = plaintext.substr(0, 32);  string RIGHTSUBSTR = plaintext.substr(32, 32);
    
    cout<< "L0=" << Bin2Hex(LEFTSUBSTR)<<endl;
    cout<< "R0=" << Bin2Hex(RIGHTSUBSTR)<<endl;
    cout<<endl;
    
    // 16 ROUNDS OF DECRYPTION BEGINS AT THIS POINT
    for (int i=0; i<16; i++) {
        // cout<<"i   :"<<i<<endl;
        // THE GENERATED RIGHT SUBSTRING OF 32 BITS IS EXPANDED 
        // TO WORK WITH FEISTEL CIPHER
        string exp_rightsubstr = PermuteIn(RIGHTSUBSTR, Pbox_exp, 48);

        // XOR VALUES OF RoundKeyBinary[i] and exp_rightsubstr
        string xor_ = X0R(RoundKeyBinary[i], exp_rightsubstr);

        // THE VALUES ARE PUT INTO S BOX
        string OUTPUT = "";
        for (int j=0; j<8; j++) {
            int M = (2*int(xor_[j*6] - '0')) + (int(xor_[j*6+5] - '0'));
            int N = (8*int(xor_[j*6+1] - '0')) + (4*int(xor_[j*6+2] - '0')) + (2*int(xor_[j*6+3] - '0')) + (int(xor_[j*6+4] - '0'));
            int comp;
            comp = SBOX[j][M][N];
            
            OUTPUT = OUTPUT + char(comp/8 + '0'); comp = comp % 8;
            
            OUTPUT = OUTPUT + char(comp/4 + '0'); comp = comp % 4;
            
            OUTPUT = OUTPUT + char(comp/2 + '0'); comp = comp % 2;
            
            OUTPUT = OUTPUT + char(comp + '0');
        }
        //  OUTPUT GOES THROUGH STRAIGHT P BOX
        //  FURTHER XOR THE LEFT SUBSTRING AND THE ABOVE GENERATED OUTPUT
            OUTPUT = PermuteIn(OUTPUT, Pbox_str, 32);
            xor_ = X0R(OUTPUT, LEFTSUBSTR);
            LEFTSUBSTR = xor_;

        //  SWAP FINAL L0 AND R0
            swap(LEFTSUBSTR, RIGHTSUBSTR);
            cout<<"R"<<i+1<<" "<<Bin2Hex(LEFTSUBSTR)<<" "<<Bin2Hex(RIGHTSUBSTR)<<" "<<RoundKeyHex[i]<<endl<< endl;
    }
    swap(LEFTSUBSTR, RIGHTSUBSTR);
    
    // TO GENERATE THE FINAL CIPHER TEST 
    // COMBINE THE ABOVE LEFT SUBSTRING AND RIGHT SUBSTRING
    string FINAL_COMB = LEFTSUBSTR + RIGHTSUBSTR;

    // Final Permutation Table
    

    // Final Permutation
    string Dec_text = Bin2Hex(PermuteIn(FINAL_COMB, FinalPBox, 64));
    return Dec_text;
}