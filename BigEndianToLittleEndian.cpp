#include <iostream>
using namespace std;

enum endianMode {LittleEndian, BigEndian, Unknown};

// unsigned short Endian conversion
unsigned short convertShortEndian(unsigned short s) {
    return (s >> 8) | (s << 8);
}

// long long convert
unsigned long long convertLongLongEndian(unsigned long long ull) {
    // byte1 to byte8 | byte8 to byte1 | byte2 to byte7 | byte3 to byte6 | byte4 to byte5 | byte5 to byte4 | byte6 to byte3 | byte7 to byte2
    return (ull >> 8*7) | (ull << 8*7) | ((ull >> 8*5)&(0xFF00)) | ((ull >> 8*3)&(0xFF0000)) | ((ull >> 8)&(0xFF000000)) | ((ull<<8)&(0xFF00000000)) | ((ull<<8*3)&(0xFF0000000000)) | ((ull<<8*5)&(0xFF000000000000));
}

// check LittleEndian(HostByteOrder) and BigEndian(NetworkByteOrder)
// LittleEndian(HostByteOrder): data's low byte at the beginning of address
// BigEndian(NetworkByteOrder): data's high byte at the beginning of address
endianMode getEndianMode() {
    union {
        unsigned short s;
        unsigned char c[2];
    }u;
    u.s = 0x1234;
    if (u.c[0] == 0x34) {
        return endianMode::LittleEndian;
    } else if (u.c[0] == 0x12) {
        return endianMode::BigEndian;
    }
    return endianMode::Unknown;
}

int main() {
    unsigned short original = 0x1234;
    unsigned short bigEndianShort = 0;
    unsigned long long ull = 0x1122334455667788;
    unsigned long long bigEndianUll = 0;
    if (getEndianMode() == endianMode::LittleEndian) {
        bigEndianShort = convertShortEndian(original);
        bigEndianUll = convertLongLongEndian(ull);
    }

    cout << "0x" << hex << bigEndianShort << endl;
    cout << "0x" << hex << bigEndianUll << endl;
    return 0;
}