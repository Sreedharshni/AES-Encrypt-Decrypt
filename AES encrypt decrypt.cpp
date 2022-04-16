#include <iostream>
#include <iomanip>
#include <stdio.h>
typedef bitset<8> byte;
typedef bitset<32> word;

void charToByte(byte out[16], const char s[16])
{
    for(int i=0; i<16; ++i)
        for(int j=0; j<8; ++j)
            out[i][j]= ((s[i]>>j) & 1);
}


void divideToByte(byte out[16], bitset<128>& data)
{
    bitset<128> temp;
    for(int i=0; i<16; ++i)
    {
        temp = (data << 8*i) >> 120;
        out[i] = temp.to_ulong();
    }
}


bitset<128> mergeByte(byte in[16])
{
    bitset<128> res;
    res.reset();
    bitset<128> temp;
    for(int i=0; i<16; ++i)
    {
        temp = in[i].to_ulong();
        temp <<= 8*(15-i);
        res |= temp;
    }
    return res;
}

int main()
{
    string keyStr = "abcdefghijklmnop";
    byte key[16];
    charToByte(key, keyStr.c_str());

    word w[4*(Nr+1)];
    KeyExpansion(key, w);

    bitset<128> data;
    byte plain[16];

    ifstream in;
    ofstream out;
    in.open("C:\Users\Sree\Downloads\Question 1\Question 1\3D model.obj", ios::binary);
    out.open("C:\Users\Sree\Downloads\pigpen-cipher\PigpenCipher", ios::binary);
    while(in.read((char*)&data, sizeof(data)))
    {
        divideToByte(plain, data);
        encrypt(plain, w);
        data = mergeByte(plain);
        out.write((char*)&data, sizeof(data));
        data.reset();
    }
    in.close();
    out.close();

    in.open("C:\Users\Sree\Downloads\pigpen-cipher\PigpenCipher", ios::binary);
    out.open("C:\Users\Sree\Downloads\Question 1\Question 1\3D model.obj", ios::binary);
    while(in.read((char*)&data, sizeof(data)))
    {
        divideToByte(plain, data);
        decrypt(plain, w);
        data = mergeByte(plain);
        out.write((char*)&data, sizeof(data));
        data.reset();
    }
    in.close();
    out.close();

    return 0;
}
