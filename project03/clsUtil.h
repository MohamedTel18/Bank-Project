#pragma once

#include <iostream>
#include <string>
#include "clsDate.h";

using namespace std;

class clsUtil
{

public:

    static void Srand()
    {
        srand((unsigned)time(NULL));
    }

    enum enChar { CapitalLetter = 1, enSmall = 2, enDigit = 3, MixChars = 4, enSpecial = 5 };

    static int RandomNumber(int From, int To)
    {
        return rand() % (To - From + 1) + From;
    }

    static char GetRandomCharacter(enChar CharType)
    {
        if (CharType == MixChars)
            CharType = (enChar)RandomNumber(1, 3);

        switch (CharType)
        {
        case CapitalLetter:
            return (char)RandomNumber(65, 90);
            break;

        case enSmall:
            return (char)RandomNumber(97, 122);
            break;

        case enDigit:
            return (char)RandomNumber(48, 57);
            break;

        case enSpecial:
            return (char)RandomNumber(48, 57);
            break;


        }


    }

    static string GenerateWord(enChar CharType, short WordLength)
    {
        string S = "";

        for (short i = 0; i < WordLength; i++)
        {
            S += GetRandomCharacter(CharType);
        }

        return S;
    }

    static string GenerateKey(enChar CharType)
    {
        string Key = "";

        for (short i = 0; i < 4; i++)
        {
            for (short j = 0; j < 4; j++)
            {
                Key += GetRandomCharacter(CharType);
            }

            if (i != 3)
            {
                Key += '-';
            }
        }

        return Key;
    }

    static void GenerateKeys(short KeyNumber, enChar CharType)
    {
        for (short i = 0; i < KeyNumber; i++)
        {
            cout << "Key [" << i << "]: "
                << GenerateKey(CharType) << endl;
        }
    }

    static void Swap(int& x, int& y)
    {
        int K;

        K = x;
        x = y;
        y = K;
    }

    static void Swap(double& x, double& y)
    {
        double K;

        K = x;
        x = y;
        y = K;
    }

    static void Swap(string& x, string& y)
    {
        string K;

        K = x;
        x = y;
        y = K;
    }

    static void Swap(clsDate& x, clsDate& y)
    {
        clsDate K;

        K = x;
        x = y;
        y = K;
    }

    static void ShuffleArray(int Arr[], int ArrLength)
    {

        for (int i = 0; i < ArrLength; i++)
        {
            Swap(Arr[RandomNumber(1, ArrLength) - 1], Arr[RandomNumber(1, ArrLength) - 1]);
        }
    }

    static void ShuffleArray(string Arr[], int ArrLength)
    {

        for (int i = 0; i < ArrLength; i++)
        {
            Swap(Arr[RandomNumber(1, ArrLength) - 1], Arr[RandomNumber(1, ArrLength) - 1]);
        }
    }

    static void FillArrayWithRandomNumbers(int Arr[], int ArrLength, int From, int To)
    {
        for (int i = 0; i < ArrLength; i++)
        {
            Arr[i] = RandomNumber(From, To);
        }
    }

    static void FillArrayWithRandomWords(string Arr[], int ArrLength, enChar CharType, int WordLength)
    {
        for (int i = 0; i < ArrLength; i++)
        {
            Arr[i] = GenerateWord(CharType, WordLength);
        }
    }

    static void FillArrayWithRandomKeys(string Arr[], int ArrLength, enChar CharType)
    {
        for (int i = 0; i < ArrLength; i++)
        {
            Arr[i] = GenerateKey(CharType);
        }
    }

    static string Tabs(int Num)
    {
        string t = "";

        for (int i = 0; i < Num; i++)
        {
            t += "\t";
        }

        return t;
    }

    static string EncryptText(string S, int encryptionKey)
    {
        for (int i = 0; i < S.length(); i++)
        {
            S[i] = char((int)S[i] + encryptionKey);
        }

        return S;
    }

    static string DecryptText(string S, int DecryptionKey)
    {
        for (int i = 0; i < S.length(); i++)
        {
            S[i] = char((int)S[i] - DecryptionKey);
        }

        return S;
    }

    static string NumberToText(int Num)
    {
        if (Num == 0)
        {
            return "";
        }

        if (Num >= 1 && Num <= 19)
        {
            string Arr[] = { "","one","two","three","four","five","six","seven","eight","nine",
            "ten","eleven","twelve","thrteen","fourteen","fifteen","sixteen","seventeen",
            "eighteen","nineteen" };

            return Arr[Num] + " ";
        }

        if (Num >= 20 && Num <= 99)
        {
            string Arr[] = { "","","twenty","therty","fourty","fifty","sixty","seventy",
            "eighty","ninety" };

            return Arr[Num / 10] + " " + NumberToText(Num % 10);
        }

        if (Num >= 100 && Num <= 999)
        {
            return NumberToText(Num / 100) + "Handred " + NumberToText(Num % 100);
        }

        if (Num >= 1000 && Num <= 999999)
        {
            return NumberToText(Num / 1000) + "thausend "+NumberToText(Num % 1000);
        }

        if (Num >= 1000000 && Num <= 999999999)
        {
            return NumberToText(Num / 1000000) + "Million " + NumberToText(Num % 1000000);
        }

        if (Num >= 1000000000 && Num <= 999999999999)
        {
            return NumberToText(Num / 1000000000) + "Billion " + NumberToText(Num % 1000000000);
        }
    }

};