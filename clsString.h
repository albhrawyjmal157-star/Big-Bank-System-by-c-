#pragma once

#include <iostream> 
#include <vector>
using namespace std;

class clsString
{
private:
	string _Value;

public:
	clsString()
	{
		_Value = "";
	}

	clsString(string Value)
	{
		_Value = Value;
	}

	void SetValue(string Value)
	{
		_Value = Value;
	}

	string GetValue()
	{
		return _Value;
	}

	__declspec(property(get = GetValue, put = SetValue)) string Value;


	static short CountWords(string Statement)
	{
		int pos = 0;
		short Counter = 0;
		string s = " ";

		while ((pos = int(Statement.find(s))) != std::string::npos)
		{
			string Word;
			Word = Statement.substr(0, pos);

			if (Word != "")
			{
				Counter++;
			}

			Statement.erase(0, pos + s.length());
		}

		if (Statement != "")
		{
			Counter++;
		}

		return Counter;
	}

	short CountWords()
	{
		return CountWords(_Value);
	}


	static string UpperLettersCase(string Statement)
	{
		string NewWord = "";

		for (char c : Statement)
		{
			NewWord += toupper(c);
		}

		return NewWord;
	}

	void UpperLettersCase()
	{
		_Value = UpperLettersCase(_Value);
	}


	static string LowerLettersCase(string Statement)
	{
		string NewWord = "";

		for (char c : Statement)
		{
			NewWord += tolower(c);
		}

		return NewWord;
	}

	void LowerLettersCase()
	{
		_Value = LowerLettersCase(_Value);
	}


	 static vector<string> Split(string Statement, string Separator="#//#")
	{
		vector<string> vWords;
		int position = 0;

		string sWord = "";

		while ((position = int(Statement.find(Separator))) != std::string::npos)
		{
			sWord = Statement.substr(0, position);

			if (sWord != "")
			{
				vWords.push_back(sWord);
			}

			Statement.erase(0, position + Separator.length());
		}

		if (Statement != "")
		{
			vWords.push_back(Statement);
		}

		return vWords;
	}

	 vector<string> Split(string Separator="#//#")
	{
		return Split(_Value, Separator);
	}


	static void PrintAllWordsInStatement(string Statement, string Separator)
	{
		vector<string> vWords = Split(Statement, Separator);

		for (string Word : vWords)
		{
			cout << Word << endl;
		}
	}

	void PrintAllWordsInStatement(string Separator)
	{
		PrintAllWordsInStatement(_Value, Separator);
	}


	static string RemovePunctuation(string Statement)
	{
		string s = "";

		for (char i : Statement)
		{
			if (!ispunct(i))
			{
				s += i;
			}
		}

		return s;
	}

	void RemovePunctuation()
	{
		_Value = RemovePunctuation(_Value);
	}


	static string ReplaceWord(string Statement, string OldWord, string NewWord)
	{
		int pos = (int)Statement.find(OldWord);

		while (pos != std::string::npos)
		{
			Statement = Statement.replace(pos, OldWord.length(), NewWord);
			pos =(int) Statement.find(OldWord);
		}

		return Statement;
	}

	void ReplaceWord(string OldWord, string NewWord)
	{
		_Value = ReplaceWord(_Value, OldWord, NewWord);
	}


	static string ReverseWordsInString(string Statement, string Separator)
	{
		string s = "";

		vector<string> vWords = Split(Statement, Separator);
		vector<string>::iterator iter = vWords.end();

		while (iter != vWords.begin())
		{
			--iter;
			s += *iter + Separator;
		}

		s = s.substr(0, s.length() - 1);

		return s;
	}

	void ReverseWordsInString(string Separator)
	{
		_Value = ReverseWordsInString(_Value, Separator);
	}


	static short CountVowels(string Statement)
	{
		short counter = 0;

		for (char Letter : Statement)
		{
			Letter = tolower(Letter);

			if (Letter == 'a' || Letter == 'e' ||
				Letter == 'i' || Letter == 'o' ||
				Letter == 'u')
			{
				counter++;
			}
		}

		return counter;
	}

	short CountVowels()
	{
		return CountVowels(_Value);
	}


	static short Length(string Statement)
	{
		return (short) Statement.length();
	}

	short Length()
	{
		return Length(_Value);
	}


	static string UpperFirstLetterEachWord(string Statement)
	{
		string s = "";
		bool IsFirstLetter = true;

		for (char Letter : Statement)
		{
			if (Letter != ' ' && IsFirstLetter)
			{
				s += toupper(Letter);
			}
			else
			{
				s += Letter;
			}

			Letter == ' ' ? IsFirstLetter = true : IsFirstLetter = false;
		}

		return s;
	}

	void UpperFirstLetterEachWord()
	{
		_Value = UpperFirstLetterEachWord(_Value);
	}


	static string LowerFirstLetterEachWord(string Statement)
	{
		string s = "";
		bool IsFirstLetter = true;

		for (char Letter : Statement)
		{
			if (Letter != ' ' && IsFirstLetter)
			{
				s += tolower(Letter);
			}
			else
			{
				s += Letter;
			}

			Letter == ' ' ? IsFirstLetter = true : IsFirstLetter = false;
		}

		return s;
	}

	void LowerFirstLetterEachWord()
	{
		_Value = LowerFirstLetterEachWord(_Value);
	}


	static char ConvertLetterCase(char Letter)
	{
		if (islower(Letter))
		{
			return toupper(Letter);
		}
		else
		{
			return tolower(Letter);
		}
	}


	static string ConvertAllLettersInStatement(string Statement)
	{
		string s = "";

		for (char Letter : Statement)
		{
			s += ConvertLetterCase(Letter);
		}

		return s;
	}

	void ConvertAllLettersInStatement()
	{
		_Value = ConvertAllLettersInStatement(_Value);
	}


	static short CountCapitalLetters(string Statement)
	{
		short counter = 0;

		for (char Letter : Statement)
		{
			if (isupper(Letter))
			{
				counter++;
			}
		}

		return counter;
	}

	short CountCapitalLetters()
	{
		return CountCapitalLetters(_Value);
	}


	static short CountSmallLetters(string Statement)
	{
		short counter = 0;

		for (char Letter : Statement)
		{
			if (islower(Letter))
			{
				counter++;
			}
		}

		return counter;
	}

	short CountSmallLetters()
	{
		return CountSmallLetters(_Value);
	}


	static short CountSpecificLetter(char Letter, bool MatchCase, string Statement)
	{
		short counter = 0;

		if (MatchCase)
		{
			Letter = tolower(Letter);

			for (char Char : Statement)
			{
				if (tolower(Char) == Letter)
				{
					counter++;
				}
			}

			return counter;
		}

		for (char Char : Statement)
		{
			if (Char == Letter)
			{
				counter++;
			}
		}

		return counter;
	}

	short CountSpecificLetter(char Letter, bool MatchCase)
	{
		return CountSpecificLetter(Letter, MatchCase, _Value);
	}


	static bool IsVowel(char Letter)
	{
		Letter = tolower(Letter);

		if (Letter == 'a' || Letter == 'e' ||
			Letter == 'i' || Letter == 'o' ||
			Letter == 'u')
		{
			return true;
		}

		return false;
	}

};
