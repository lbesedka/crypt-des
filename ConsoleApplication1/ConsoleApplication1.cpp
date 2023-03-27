// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <bitset>
#include <Windows.h>
#include <vector>
using namespace std; 

//таблица начальной перестановки
const int IP_table[64] = { 58, 50, 42, 34, 26, 18, 10, 2, 
 60, 52, 44, 36, 28, 20, 12, 4, 
 62, 54, 46, 38, 30, 22, 14, 6, 
 64, 56, 48, 40, 32, 24, 16, 8, 
 57, 49, 41, 33, 25, 17, 9,  1, 
 59, 51, 43, 35, 27, 19, 11, 3, 
 61, 53, 45, 37, 29, 21, 13, 5,
 63, 55, 47, 39, 31, 23, 15, 7 };

//таблицы перестановки ключа
const int KeyPermutationTable[56] = { 57, 49, 41, 33, 25, 17, 9, 
 1, 58, 50, 42, 34, 26, 18, 
 10, 2,	59,	51, 43, 35, 27, 
 19, 11, 3, 60, 52, 44, 36,
 63, 55, 47, 39, 31, 23, 15, 
 7, 62, 54, 46, 38, 30, 2,
 14, 6,	61,	53,	45,	37,	29,	
 21, 13, 5,	28,	20,	12,	4
};
const int KeyPermutation2[48] = { 14, 17, 11, 24,  1,  5,
 3, 28, 15,  6, 21, 10,
 23, 19, 12,  4, 26,  8,
 16,  7, 27, 20, 13,  2,
 41, 52, 31, 37, 47, 55,
 30, 40, 51, 45, 33, 48,
 44, 49, 39, 56, 34, 53,
 46, 42, 50, 36, 29, 32
};
const int E_BlockTable[48] = { 32,  1,  2,  3,  4,  5,
 4,  5,  6,  7,  8,  9,
 8,  9, 10, 11, 12, 13,
 12, 13, 14, 15, 16, 17,
 16, 17, 18, 19, 20, 21,
 20, 21, 22, 23, 24, 25,
 24, 25, 26, 27, 28, 29,
 28, 29, 30, 31, 32,  1
};
//8 s-box
const int S_Boxes[8][4][16] = {
       {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    }, {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    }, {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    }, {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    }, {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    }, {
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    }, {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    }, {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};


const int IP_1Table[64] = { 40, 8, 48, 16, 56, 24, 64, 32,
 39, 7, 47, 15, 55, 23, 63, 31,
 38, 6, 46, 14, 54, 22, 62, 30,
 37, 5, 45, 13, 53, 21, 61, 29,
 36, 4, 44, 12, 52, 20, 60, 28,
 35, 3, 43, 11, 51, 19, 59, 27,
 34, 2, 42, 10, 50, 18, 58, 26,
 33, 1, 41,  9, 49, 17, 57, 25 };
//перестановка P для правой стороны

const int P[32] = {16,  7, 20, 21,
 29, 12, 28, 17,
 1, 15, 23, 26,
 5, 18, 31, 10,
 2,  8, 24, 14,
 32, 27,  3,  9,
 19, 13, 30,  6,
 22, 11,  4, 25
}; 

//начальная перестановка
std::bitset<64> IP(const std::bitset<64> block) {
    std::bitset<64> new_block;
    for (int i = 0; i < 64; i++) {
        new_block[i] = block[IP_table[i] - 1];
    }
    return new_block;
};
//конечная перестановка
bitset<64> IP_1(const std::bitset<64> block) {
    bitset<64> text;
    for (int i = 0; i < 64; i++) {
        text[i] = block[IP_1Table[i] - 1];
    }
    return text;
}

std::bitset<64> convertTexttoBit(string str) {
    bitset<64> bits;
    for (int i = 0; i < 8; ++i) {
        char c = str[i];
        for (int j = 7; j >= 0 && c; --j) {
            if (c & 0x1) {
                bits.set(8 * i + j);
            }
            c >>= 1;
        }
    }
    return bits;
};

std::bitset<56> convertKeytoBit(string str) {
    bitset<56> bits;
    for (int i = 0; i < 7; ++i) {
        char c = str[i];
        for (int j = 6; j >= 0 && c; --j) {
            if (c & 0x1) {
                bits.set(8 * i + j);
            }
            c >>= 1;
        }
    }
    return bits;
};

bitset<8> XorReverse(bitset<8> to_reverse)
{
    bitset<8> result;
    for (int i = 0; i < 4; i++)
    {
        bitset<1> function = to_reverse[i] ^ to_reverse[7 - i];
        result[i] = to_reverse[i] ^ function[0];
        result[7 - i] = to_reverse[7 - i] ^ function[0];
    }
    return result;
}


string BitsetToChar(bitset<64> bits) {
    char s[9];
    bitset<8> c;
    for (int i = 0; i < 8; i++) {
        for (int j = 7; j >= 0; j--) {
            c[j] = bits[j+8*i];
        }
        c = XorReverse(c);
        long character = c.to_ulong();
        s[i] = char(c.to_ulong());
        //s[7 - i] = c.to_ulong();
    }
    s[8] = '\0';
    return (string)s;
}; 

bitset<56> KeyPermutation(bitset<64> key)
{
    bitset<56> new_block;
    int counter = 0;
    for (int order : KeyPermutationTable)
    {
        new_block[counter] = key[order-1];
        counter++;
    }
    return new_block;
}

bitset<56> RemoveBits(bitset<64> bits) {
    bitset<56> redacted_set;
    int counter = 0;
    for (int i = 0; i < 64; i++) {
        if (i !=0 && (i + 1) % 8 == 0)
        {
            counter++;
            continue;
        }
        redacted_set[i - counter] = bits[i]; 
    }
    return redacted_set;
}

bitset<64> EnlargeKey(bitset<56> bits) {
    string s1 = bits.to_string();
    string s2 = "00000000";
    bitset<64> new_key (s2 + s1);
    bitset<64> enlarged_key;
    int counter = 0; 
    for (int i = 0; i < 64; i++) {
        if ((i + 1) % 8 == 0 && i != 0)
        {
            if (counter % 2 == 0)
                enlarged_key[i] = 1;
            else
                enlarged_key[i] = 0;
            new_key = (new_key <<= 1);
            counter = 0;
            continue;
        }
        enlarged_key[i] = new_key[i];
        if (new_key[i] == 1)
            counter++;
    }
    return enlarged_key;
}


bitset <56> concat(bitset <28> b1, bitset <28> b2) {
    string s1 = b1.to_string();
    string s2 = b2.to_string();
    return bitset <56>(s1 + s2);
}

bitset<48>* RoundKeyGeneration(bitset<64> key) {
    //предополжим уже был сжатый ключ
    bitset<56> new_key; 
    new_key = KeyPermutation(key);
    bitset<28> C, D; 
    bitset<48> round_key[16];
    for (int i = 0; i < 28; i++) {
        C[i] = key[i];
        D[i] = key[i + 28];
    }
    int len_shift[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
    bitset<56> CD; 
    for (int i = 0; i < 16; i++) {
        C = (C >>= len_shift[i]);
        D = (D >>= len_shift[i]);
        CD = concat(C, D);
        for (int j = 0; j < 48; j++) {
            round_key[i][j] = CD[KeyPermutation2[j] - 1];
        }
    }
    return round_key;
}


bitset<48> ExpandBlock(bitset<32> right) {
    bitset<48> E;
    for (int i = 0; i < 48; i++) {
        E[i] = right[E_BlockTable[i] - 1];
    }
    return E;
}


bitset<32> FunctionFeistel(bitset<48>* round_key, bitset<32> right, int round_number) {
    bitset<48> expand_right;
    bitset<32> result; 
    expand_right = ExpandBlock(right);
    expand_right ^= round_key[round_number]; 
    // 8 шестибитовых подблоков
    for (int i = 0; i < 8; i++) {
        int head = 47 - i * 6; // индекс начала каждого подблока
        int row = expand_right[head] * 2 + expand_right[head - 5];
        int col = expand_right[head - 1] * 8 + expand_right[head - 2] * 4 + expand_right[head - 3] * 2 + expand_right[head - 4];
        bitset<4> res(S_Boxes[i][row][col]);
        for (int j = 0; j < 4; j++)
            result[31 - i * 4 - j] = res[3 - j];
    }
    bitset<32> res = result;
    for (int j = 0; j < 32; j++) {
        result[j] = res[P[j] - 1];
    }
    return result; 
}


bitset<64> Encrypt(bitset<64> text_block, bitset<64> key) {
    bitset<32> left;
    bitset<32> rigth;
    bitset<32> left_new;
    bitset<48>* new_key; 
    bitset<64> new_block;
    text_block = IP(text_block); 
    for (int i = 0; i < 32; i++) {
        left[i] = text_block[i+32];
        rigth[i] = text_block[i];
    }
    new_key = RoundKeyGeneration(key);
    for (int i = 0; i < 16; i++) {
        left_new = rigth;
        rigth = left ^ FunctionFeistel(new_key, rigth, i);
        left = left_new;
    }
    for (int i = 0; i < 32; i++) {
        new_block[i] = left[i];
        new_block[i+32] = rigth[i];
    }
    return IP_1(new_block);

}


vector<string> PreparateText(string text) {
    vector<string> preparedStrings;
    string tmp = "";
    while (text.length() % 8 != 0)
    {
        text += "a";
    }
    for (int i = 0; i < text.length(); i++) {
        tmp += text[i];
        if ((i + 1) % 8 == 0 && i != 0)
        {
            preparedStrings.push_back(tmp);
            tmp = "";
        }
    }
    return preparedStrings;
}

bitset<64> Decrypt(bitset<64> text_block, bitset<64> key) {
    bitset<32> left;
    bitset<32> rigth;
    bitset<32> rigth_new;
    bitset<48>* new_key;
    bitset<64> new_block;
    text_block = IP(text_block);
    for (int i = 0; i < 32; i++) {
        left[i] = text_block[i];
        rigth[i] = text_block[i+32];
    }
    new_key = RoundKeyGeneration(key);
    for (int i = 0; i<16; i++) {
        rigth_new = left;
        left = rigth ^ FunctionFeistel(new_key, left, 15-i);
        rigth = rigth_new;
    }
    for (int i = 0; i < 32; i++) {
        new_block[i+32] = left[i];
        new_block[i] = rigth[i];
    }
    return IP_1(new_block);
}

int main()
{
    
    string a = "1234567";
   /* string text = "asdfghjklzxcvbnmqwertyuiopaqswdefrgthyjukilocvbnmxzqswfrgtjuf";
    vector<string> preparatedText = PreparateText(text);
    for (int i = 0; i < preparatedText.size(); i++)
        cout << preparatedText[i] << endl;*/
  /*  bitset<56> s = convertKeytoBit(a);
    
    bitset<64> key = EnlargeKey(s);
    bitset<64> textw;
    textw = convertTexttoBit(text);
    cout << textw << endl; 
    cout << Encrypt(textw, key) << endl;
    //cout << BitsetToChar(Encrypt(textw, key)) << endl; */

    bitset<56> s = convertKeytoBit(a);
    bitset<64> key = EnlargeKey(s);
    string text = "abcdefde";
    bitset<64> textw;
    textw = Encrypt(convertTexttoBit(text), key);
    string chipher_text = BitsetToChar(textw); 
    cout << chipher_text << endl; 
    bitset<64> plain_text = Decrypt(textw, key);
    string plaintext = BitsetToChar(plain_text);
    cout << plaintext << endl;

    /*for (int i = 0; i < preparatedText.size(); i++)
        cout << BitsetToChar(Encrypt(convertTexttoBit(preparatedText[i]), key))<< endl;*/
    /*for (int i = 0; i < preparatedText.size(); i++)
        cout << BitsetToChar(Decrypt(Encrypt(convertTexttoBit(preparatedText[i]), key), key)) << endl;*/

}
