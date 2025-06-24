#include <iostream>
using namespace std;

enum endianMode {LittleEndian, BigEndian, Unknown};

// unsigned short Endian conversion
unsigned short convertShortEndian(unsigned short s) {
    return (s >> 8) | (s << 8);
}

// long long convert
unsigned long long convertLongLongEndian(unsigned long long ull) {
    // byte1 to byte4 | byte4 to byte1 | byte2 to byte3 | byte3 to byte2
    return (ull >> 24) | (ull << 24) | ((ull >> 8)|(0x0000FF00)) | ((ull<<8)|(0x00));
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
    if (getEndianMode() == endianMode::LittleEndian) {
        bigEndianShort = convertShortEndian(original);
    }

    cout << hex << bigEndianShort << endl;
    return 0;
}