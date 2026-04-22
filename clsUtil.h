#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include"clsString.h"
#include "clsDate.h"

using namespace std;


class clsUtil
{

public :

	enum enOperation{SmallLetter=1,CapitalLetter=2,Digit=3,MaxChars=4,Punct=5};

	static void Srand()
	{
		srand((unsigned)time(NULL));
	}

	static int RandNumber(int From, int To)
	{
		return rand() % (To - From + 1) + From;
	}

    static char GetRandomCharacter(enOperation Operation)
    {
        switch (Operation)
        {
        case enOperation::CapitalLetter:
            return (char)RandNumber(65, 90);

        case enOperation::SmallLetter:
            return (char)RandNumber(97, 122);

        case enOperation::Digit:
            return (char)RandNumber(48, 57);
        case enOperation::Punct:
            return (char)RandNumber(32, 47);
        default:
            return (char)RandNumber(33, 126); // أي حرف
        }
    }

    static string GenerateWord(enOperation Operation,int Length)
    {
        string word = "";
        for (int i = 1; i <= Length; i++)
        {
            word += GetRandomCharacter(Operation);
        }

        return word;
    }

    static string GenerateKey(enOperation Operation)
    {
        string Key = "";
        Key += GenerateWord(Operation, 4) + "-";
        Key += GenerateWord(Operation, 4) + "-";
        Key += GenerateWord(Operation, 4) + "-";
        Key += GenerateWord(Operation, 4) ;
        return Key;
    }

    static void GenerateKeys(int Length, enOperation Operation)
    {
        for (int i = 1; i <= Length; i++)
        {
            cout << "Key [" << i << "] : " << GenerateKey(Operation) << endl;
        }
    }

    static void Swap(int& num1, int& num2)
    {
        int Temp = 0;
        Temp = num1;
        num1 = num2;
        num2 = Temp;
    }
    static void Swap(double& num1, double& num2)
    {
        double Temp = 0;
        Temp = num1;
        num1 = num2;
        num2 = Temp;
    }
    static void Swap(string& word1, string& word2)
    {
        string Temp ="";
        Temp = word1;
        word1 = word2;
        word2 = Temp;
    }
    static void Swap(clsDate & Date1, clsDate &Date2)
    {
        clsDate Temp ;
        Temp = Date1;
        Date1 = Date2;
        Date2 = Temp;
    }

    static void PrintArray(int Array[], int Length)
    {
        for (int i = 0; i < Length; i++)
        {
            cout<<Array[i]<<endl;

        }
    }
    static void PrintArray(string Array[], int Length)
    {
        for (int i = 0; i < Length; i++)
        {
            cout << Array[i] << endl;

        }
    }

    static void ShuffleArray(int arr[100], int Length)
    {
        for (int i = 0; i < Length; i++)
        {
            int index1 = RandNumber(0, Length - 1);
            int index2 = RandNumber(0, Length - 1);

            Swap(arr[index1], arr[index2]);
        }
    }
    static void ShuffleArray(string arr[100], int Length)
    {
        for (int i = 0; i < Length; i++)
        {
            int index1 = RandNumber(0, Length - 1);
            int index2 = RandNumber(0, Length - 1);

            Swap(arr[index1], arr[index2]);
        }
    }

    static void FillArrayWithRandomNumbers(int arr[100], int Length, int From, int To)
    {
        for (int i = 0; i < Length; i++)
        {
            arr[i] = RandNumber(From, To);
        }
    }
    static void FillArrayWithRandomWords(string arr[100], int LengthOfArray
        , enOperation Operation, int LengthOfWord)
    {
        for (int i = 0; i < LengthOfArray; i++)
        {
            arr[i] = GenerateWord(Operation, LengthOfWord);
        }
    }
    static void FillArrayWithRandomKeys(string  arr[100], int LengthOfArray
        , enOperation Operation)
    {
        for (int i = 0; i < LengthOfArray; i++)
        {
            arr[i] = GenerateKey(Operation);
        }
    }
    static void Tabs(string Text1, string Text2,int Length)
    {
        cout << Text1;
        for (int i = 1; i <= Length; i++)
        {
            cout << "\t";
        }
        cout << Text2 << endl;;
    }

    static string EncrptionWord(string word)
    {
        const int KeyWord = 2;
        string EncrptionWord = "";
        for (char Letter : word)
        {
            int index = (int)Letter;
            int NewIndex = index + KeyWord;
            EncrptionWord += char(NewIndex);
        }

        return EncrptionWord;


    }
    static string DecrptionWord(string word)
    {
        const int KeyWord = 2;
        string EncrptionWord = "";
        for (char Letter : word)
        {
            int index = (int)Letter;
            int NewIndex = index - KeyWord;
            EncrptionWord += char(NewIndex);
        }

        return EncrptionWord;


    }
    static string NumberToText(int Number)
    {

        if (Number == 0)
        {
            return "";
        }

        if (Number >= 1 && Number <= 19)
        {
            string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven",
        "Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
          "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

            return  arr[Number] + " ";

        }

        if (Number >= 20 && Number <= 99)
        {
            string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
            return  arr[Number / 10] + " " + NumberToText(Number % 10);
        }

        if (Number >= 100 && Number <= 199)
        {
            return  "One Hundred " + NumberToText(Number % 100);
        }

        if (Number >= 200 && Number <= 999)
        {
            return   NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
        }

        if (Number >= 1000 && Number <= 1999)
        {
            return  "One Thousand " + NumberToText(Number % 1000);
        }

        if (Number >= 2000 && Number <= 999999)
        {
            return   NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
        }

        if (Number >= 1000000 && Number <= 1999999)
        {
            return  "One Million " + NumberToText(Number % 1000000);
        }

        if (Number >= 2000000 && Number <= 999999999)
        {
            return   NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
        }

        if (Number >= 1000000000 && Number <= 1999999999)
        {
            return  "One Billion " + NumberToText(Number % 1000000000);
        }
        else
        {
            return   NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
        }
    }
};

