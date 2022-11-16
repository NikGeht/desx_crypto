#include <iostream>
#include <fstream>
#include <string>
#include <bitset>


using namespace std;


bitset<48> subKey[16];

int IP[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

int IP_1[] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

int P_BOX_EXPAND[] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

int S_BOX[8][4][16] = {
{
{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
},
{
{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
},
{
{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
},
{
{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
},
{
{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
},
{
{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
},
{
{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
},
{
{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
}
};

int P_BOX_DIR[] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
};

int leftshift[] = {
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

int keyCompress_56[] = {
    57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4
};

int keyCompress_48[] = {
    14, 17, 11, 24, 1, 5, 3, 28,
    15, 6, 21, 10, 23, 19, 12, 4,
    26, 8, 16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32
};
bitset<28> ShiftLeft(bitset<28> k, int shift)
{
	bitset<28> tmp = k;
	for (int i = 27; i >= 0; --i)
	{
		if (i - shift < 0)
			k[i] = tmp[i - shift + 28];
		else
			k[i] = tmp[i - shift];
	}
	return k;
}

bitset<64> charToBitset(const char s[8])
{
	bitset<64> bits;
	for (int i = 0; i < 8; i++)
	{
		int num = int(s[i]);
		bitset<8> temp(num);
		for (int j = 7; j >= 0; j--)
		{
			bits[8 * i + j] = temp[7 - j];
		}
	}
	return bits;
}

bitset<32> f(bitset<32> R, bitset<48> k){
    bitset<48> R_EXPAND;
    for(int i = 0; i < 48; i++){
        R_EXPAND[47 - i] = R[32 - P_BOX_EXPAND[i]]; // EXPAND to 48 bit
    }

    R_EXPAND = R_EXPAND ^ k; // XOR
    bitset<32> output;
    int x = 0;
    for(int i = 0; i < 48; i = i + 6){
        
        int row = R_EXPAND[47 - i - 5] * 2 + R_EXPAND[47 - i];
        int col = R_EXPAND[47 - i - 1] * 8 + R_EXPAND[47 - i - 2] * 4 + R_EXPAND[47 - i - 3] * 2 + R_EXPAND[48 - i - 4];
        int num = S_BOX[i / 6][row][col];
        bitset<4> bin(num);
        output[31 - x] = bin[3];
		output[31 - x - 1] = bin[2];
		output[31 - x - 2] = bin[1];
		output[31 - x - 3] = bin[0];
		x += 4;
    }

    bitset<32> tmp = output;
    for(int i = 0; i < 32; i++){
        output[31 - i] = tmp[31 - P_BOX_DIR[i]];
    }

    return output;
}

void generateKeys(bitset<64> check_key){
    bitset<56> key;
    bitset<28> C_key;
    bitset<28> D_key;
    bitset<48> compress_key;
    for(int i = 0; i < 56; i++){
        key[55 - i] = check_key[63 - keyCompress_56[i]];
    }

    for(int round = 0; round < 16; round++)
    {
        for(int i = 28; i < 56; i++){
            C_key[i - 28] = key[i];
        }
        for(int i = 0; i < 28; i++){
            D_key[i] = key[i];
        }

        C_key = ShiftLeft(C_key, leftshift[round]);
        D_key = ShiftLeft(D_key, leftshift[round]);

        for (int i = 28; i < 56; i++){
            key[i] = C_key[i - 28];
        }
        for(int i = 0; i < 28; i++){
            key[i] = D_key[i];
        }

        for(int i = 0; i < 48; i++){
            compress_key[47 - i] = key[55 - keyCompress_48[i]];
        }
        
        subKey[round] = compress_key;
    }

}
    

    bitset<64> swap(bitset<64> temp){
        bitset<64> temp_bit;
        bitset<8> n;
        for (int i = 0; i < 64; i = i + 8)
	{
		for (int j = 0; j < 8; j++)
		{
			temp_bit[i + j] = temp[i + 7 - j];
		}
	}
	return temp_bit;
    }


    bitset<64> encrypt(bitset<64>& text){
        bitset<64> cipher;
        bitset<64> currentBits;
        bitset<32> left;
        bitset<32> right;
        bitset<32> newLeft;
        // Шаг 1: Первоначальная замена IP
        for (int i = 0; i < 64; ++i)
            currentBits[63 - i] = text[64 - IP[i]];
        // Шаг 2: Получи L и R
        for (int i = 32; i < 64; ++i)
            left[i - 32] = currentBits[i];
        for (int i = 0; i < 32; ++i)
            right[i] = currentBits[i];
        // Шаг 3: 16 итераций
        for (int round = 0; round < 16; ++round)
        {
            newLeft = right;
            right = left ^ f(right, subKey[round]);
            left = newLeft;
        }
        // Четвертый шаг: объединить L16 и R16
        for (int i = 0; i < 32; ++i)
            cipher[i] = left[i];
        for (int i = 32; i < 64; ++i)
            cipher[i] = right[i - 32];
        // Шаг 5: заменить IP-1 в конце
        currentBits = cipher;
        for (int i = 0; i < 64; ++i)
            cipher[63 - i] = currentBits[64 - IP_1[i]];
        // вернуть зашифрованный текст
        return cipher;
    }

    bitset<64> decrypt(bitset<64>& cipher)
{

	bitset<64> plain;
	bitset<64> currentBits;
	bitset<32> left;
	bitset<32> right;
	bitset<32> newLeft;
	// Шаг 1: Первоначальная замена IP
	for (int i = 0; i < 64; ++i)
		currentBits[63 - i] = cipher[64 - IP[i]];
	// Шаг 2: Получи Ли и Ри
	for (int i = 32; i < 64; ++i)
		left[i - 32] = currentBits[i];
	for (int i = 0; i < 32; ++i)
		right[i] = currentBits[i];
	// Третий шаг: всего 16 циклов итерации (подпункт приложения в обратном порядке)
	for (int round = 0; round < 16; ++round)
	{
		newLeft = right;
		right = left ^ f(right, subKey[15 - round]);
		left = newLeft;
	}
	// Четвертый шаг: объединить L16 и R16, обратите внимание на объединение в R16L16
	for (int i = 0; i < 32; ++i)
		plain[i] = left[i];
	for (int i = 32; i < 64; ++i)
		plain[i] = right[i - 32];
	// Шаг 5: заменить IP-1 в конце
	currentBits = plain;
	for (int i = 0; i < 64; ++i)
		plain[63 - i] = currentBits[64 - IP_1[i]];
	// возврат в открытый текст
	return plain;
}

int main(){
    string s = "program1";
	string k = "12345678";
	bitset<64> plain = charToBitset(s.c_str());
	cout << plain << endl;
	bitset<64> key = charToBitset(k.c_str());


	// Генерируем 16 подключей
	generateKeys(key);


	// зашифровать текст написать a.txt
	bitset<64> cipher = encrypt(plain);
	cout << cipher << endl;
	fstream file1;
	file1.open("a.txt", ios::binary | ios::out);
	file1.write((char*)&cipher, sizeof(cipher));
	file1.close();


	// читаем файл a.txt
	bitset<64> temp;
	file1.open("a.txt", ios::binary | ios::in);
	file1.read((char*)&temp, sizeof(temp));
	file1.close();


	// расшифровываем и записываем в файл b.txt
	bitset<64> temp_plain = decrypt(temp);
	temp_plain = swap(temp_plain);
	file1.open("b.txt", ios::binary | ios::out);
	file1.write((char*)&temp_plain, sizeof(temp_plain));
	file1.close();
	
    return 0;
}