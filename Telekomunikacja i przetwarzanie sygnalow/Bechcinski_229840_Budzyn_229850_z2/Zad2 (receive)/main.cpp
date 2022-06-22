#include <iostream>
#include <fstream>
#include <string.h>
#include <windows.h>
#include <winbase.h>
#include <conio.h>
#include <iomanip>

using namespace std;

// CONST
const char SOH = (char)1;
const char NACK = (char)15;
const char CAN = (char)18;
const char ACK = (char)6;
const char EOT = (char)4;

HANDLE const_handle;
LPCTSTR const_lpctstr;
DCB const_dcb;
COMSTAT const_comstat;
DWORD const_dword;
COMMTIMEOUTS const_commtimeouts;
USHORT const_ushort;

// FUNCTIONS
int portSettings(LPCTSTR const_lpctstr) //NADANIE PORTOWI PARAMETROW + OTWORZENIE GO
{
    if (const_handle == INVALID_HANDLE_VALUE)
    {
        return 0;
    }
    else
    {
        const_handle = CreateFile(const_lpctstr, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
        const_dcb.DCBlength = sizeof(const_dcb);
        const_dcb.BaudRate = CBR_9600; // predkosc transmisji
        const_dcb.fParity = TRUE;
        const_dcb.Parity = NOPARITY; // bez bitu parzystosci
        const_dcb.StopBits = ONESTOPBIT; // ustawienie bitu stopu (jeden bit)
        const_dcb.ByteSize = 8; // liczba wysylanych bitów
        const_dcb.fDtrControl = DTR_CONTROL_DISABLE; // Kontrola linii DTR: sygnal nieaktywny
        const_dcb.fRtsControl = RTS_CONTROL_DISABLE; // Kontrola linii RTS: sygnal nieaktywny
        const_dcb.fOutxCtsFlow = FALSE;
        const_dcb.fOutxDsrFlow = FALSE;
        const_dcb.fDsrSensitivity = FALSE;
        const_dcb.fAbortOnError = FALSE;
        const_dcb.fOutX = FALSE;
        const_dcb.fInX = FALSE;
        const_dcb.fErrorChar = FALSE;
        const_dcb.fNull = FALSE;
        return 1;
    }
}

int checkCRC(char* point, int count)
{
    int CRCchecksum = 0;

    while (--count >= 0)
    {
        CRCchecksum = CRCchecksum ^ (int)*point++ << 8; // weŸ znak i dopisz osiem zer
        for (int i = 0; i < 8; ++i)
        {
            if (CRCchecksum & 0x8000)
                CRCchecksum = CRCchecksum << 1 ^ 0x1021; // jeœli lewy bit == 1 wykonuj XOR generatorm 1021
            else
                CRCchecksum = CRCchecksum << 1; // jeœli nie to XOR przez 0000, czyli przez to samo
        }

    }
    return (CRCchecksum & 0xFFFF);
}

int binToDec(int y)
{
    if (y == 0) return 1;
    if (y == 1) return 2;

    int result = 2;

    for (int i = 2; i <= y; i++)
        result = result * 2;

    return result;
}


char checkCRCsign(int CRC, int signNumber) //przeliczanie CRC na postaæ binarn¹
{
    int tmp, binary[16];

    for (int i = 0; i < 16; i++)
        binary[i] = 0;

    for (int i = 0; i < 16; i++)
    {
        tmp = CRC % 2;
        if (tmp == 1) CRC = (CRC - 1) / 2;
        if (tmp == 0) CRC = CRC / 2;
        binary[15 - i] = tmp;
    }

    //obliczamy poszczegolne znaki receivedCRC (1-szy lub 2-gi)
    tmp = 0;
    int h;

    if (signNumber == 1) h = 7;
    if (signNumber == 2) h = 15;

    for (int i = 0; i < 8; i++)
        tmp = tmp + binToDec(i) * binary[h - i];

    return (char)tmp;//zwraca 1 lub 2 znak (bo 2 znaki to 2 bajty, czyli 16 bitów)
}


// MAIN
int main()
{
    // VARIABLES
    char sign;
    long unsigned int sizeOfSign = sizeof(sign);
    fstream receive;
    char data[128];
    int blockNumber = 0;
    char fillTo255;
    bool rightPackage;
    char receivedCRC[2];

    // MENU
    char choice;
    cout << "Wybierz opcje:\n"
        << "[1] - COM1\n"
        << "[2] - COM2\n"
        << "[3] - COM3\n"
        << "[4] - COM4\n"
        << "[q] - Zakoncz program\n";
    choice = getch();
    cin.sync();

    switch (choice)
    {
    case '1':
        const_lpctstr = "COM1";
        cout << "Wybrano COM1\n";
        break;
    case '2':
        const_lpctstr = "COM2";
        cout << "Wybrano COM2\n";
        break;
    case '3':
        const_lpctstr = "COM3";
        cout << "Wybrano COM3\n";
        break;
    case '4':
        const_lpctstr = "COM4";
        cout << "Wybrano COM4\n";
        break;
    case 'q':
    default:
        cout << "\nExiting...\n";
        return 0;
    }

    portSettings(const_lpctstr);

    cout << "Wybierz opcje:\n"
        << "[1] - ACK\n"
        << "[2] - NACK\n";
    choice = getch();
    cin.sync();

    switch (choice)
    {
    case '1':
        sign = 'C';
        cout << "Wybrano ACK\n";
        break;
    case '2':
        sign = NACK;
        cout << "Wybrano NACK\n";
        break;
    default:
        cout << "\nExiting...\n";
        return 0;
    }

    // HANDSHAKE
    for (int i = 0; i < 6; i++)
    {
        WriteFile(const_handle, &sign, 1, &sizeOfSign, NULL);
        cout << "Ustanawianie polaczenia...\n";
        ReadFile(const_handle, &sign, 1, &sizeOfSign, NULL); //sign == SOH || EOT || CAN
        if (sign == SOH)
        {
            cout << "Polaczenie zostalo ustanowione.\n";
            break;
        }
    }

    if (sign != SOH)
    {
        cout << "Nie udalo sie ustanowic polaczenia.\n";
        return 0;
    }

    receive.open("receive.txt", ios::out | ios::binary);
    cout << "Trwa odbieranie pliku...\n";

    //RECEIVE DATA
    while (true)
    {
        if (blockNumber != 0) //zostalo to wczesniej wykonane dla pierwszego bloku jako HANDSHAKE
        {
            ReadFile(const_handle, &sign, 1, &sizeOfSign, NULL); //sign == SOH || EOT || CAN
            if (sign == EOT || sign == CAN) break;
        }

        ReadFile(const_handle, &sign, 1, &sizeOfSign, NULL); //sign == numer bloku
        blockNumber = (int)sign;

        ReadFile(const_handle, &sign, 1, &sizeOfSign, NULL); //sign == dopelnienie do 255
        fillTo255 = sign;

        for (int i = 0; i < 128; i++)
        {
            ReadFile(const_handle, &sign, 1, &sizeOfSign, NULL); //sign == litera, gdzie jest to powielone 128 razy czyli jest to blok danych
            data[i] = sign;
        }


        ReadFile(const_handle, &sign, 1, &sizeOfSign, NULL);
        receivedCRC[0] = sign;
        ReadFile(const_handle, &sign, 1, &sizeOfSign, NULL);
        receivedCRC[1] = sign;
        rightPackage = true;

        if ((char)(255 - blockNumber) != fillTo255)
        {
            cout << "Niepoprawny numer pakietu.\n";
            WriteFile(const_handle, &NACK, 1, &sizeOfSign, NULL);
            rightPackage = false;
        }
        else
        {
            const_ushort = checkCRC(data, 128);

            if (checkCRCsign(const_ushort, 1) != receivedCRC[0] || checkCRCsign(const_ushort, 2) != receivedCRC[1])
            {
                cout << "Niepoprawna suma kontrolna.\n";
                WriteFile(const_handle, &NACK, 1, &sizeOfSign, NULL);
                rightPackage = false;
            }
        }
        if (rightPackage)
        {
            for (int i = 0; i < 128; i++)
            {
                if (data[i] != 26)
                    receive << data[i];
            }
            cout << "Odbieranie " << blockNumber << ". pakietu powiodlo sie.\n";
            WriteFile(const_handle, &ACK, 1, &sizeOfSign, NULL);
        }
    }
    // END
    WriteFile(const_handle, &ACK, 1, &sizeOfSign, NULL);

    receive.close();
    CloseHandle(const_handle);

    if (sign == CAN) cout << "Polaczenie zostalo utracone.\n";
    else cout << "Plik zostal odebrany w calosci.\n";
    system("Pause");


    return 0;
}
