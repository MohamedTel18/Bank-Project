#pragma once

#include <iostream>
#include <vector>

using namespace std;

class clsString
{

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

	void SetValue(string Val)
	{
		_Value = Val;
	}

	string GetValue()
	{
		return _Value;
	}
	
	static char InvertLetterCase(char C1)
	{
		return isupper(C1) ? tolower(C1) : toupper(C1);
	}

	__declspec(property(get = GetValue, put = SetValue)) string Value;

	static short Length(string S1)
	{
		return S1.length();
	}

	short Length()
	{
		return _Value.length();
	}

	static short CountWords(string S1)
	{
		string Del = " ", word;

		short Num = 0, Pos;

		while ((Pos = S1.find(Del)) != string::npos)
		{
			word = S1.substr(0, Pos);
			if (word != "")
			{
				Num++;
			}
			
			S1.erase(0, Pos+1);
		}
		
		if (S1 != "")
		{
			Num++;
		}

		return Num;
	}

	short CountWords()
	{
		return CountWords(_Value);
	};

	static string UpperFirstLetterOfEachWord(string S1)
	{
		S1[0] = toupper(S1[0]);

		for (short i = 0; i < S1.length(); i++)
		{

			if (S1[i] == ' ')
			{
				S1[i + 1] = toupper(S1[i + 1]);
			}
		}

		return S1;
	}

	void UpperFirstLetterOfEachWord()
	{
		_Value = UpperFirstLetterOfEachWord(_Value);
	}

	static string LowerFirstLetterOfEachWord(string S1)
	{
		S1[0] = tolower(S1[0]);

		for (short i = 0; i < S1.length(); i++)
		{

			if (S1[i] == ' ')
			{
				S1[i + 1] = tolower(S1[i + 1]);
			}
		}

		return S1;
	}

	void LowerFirstLetterOfEachWord()
	{
		_Value = LowerFirstLetterOfEachWord(_Value);
	}

	static string UpperAllString(string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ')
			{
				S1[i] = toupper(S1[i]);
			}
			
		}

		return S1;
	}
	
	void UpperAllString()
	{
		_Value = UpperAllString(_Value);
	}

	static string LowerAllString(string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ')
			{
				S1[i] = tolower(S1[i]);
			}

		}

		return S1;
	}

	void LowerAllString()
	{
		_Value = LowerAllString(_Value);
	}

	static string InvertAllLettersCase(string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			S1[i] = InvertLetterCase(S1[i]);
		}

		return S1;
	}

	void InvertAllLettersCase()
	{
		_Value = InvertAllLettersCase(_Value);
	}

	enum enTypeLetter { CapitalLetters = 1, Min = 2 };

	static short CountLetters(string S1,enTypeLetter Type)
	{
		short Counter = 0;

		for (short i = 0; i < S1.length(); i++)
		{
			if (isupper(S1[i]) && enTypeLetter::CapitalLetters)
				Counter++;

			if (islower(S1[i]) && enTypeLetter::Min)
				Counter++;
		}

		return Counter;
	}

	static short CountCapitalLetters(string S)
	{
		short Cntr = 0;

		for (short i = 0; i < S.length(); i++)
		{
			if (isupper(S[i]))
				Cntr++;
		}

		return Cntr;
	}

	short CountCapitalLetters()
	{
		return CountCapitalLetters(_Value);
	}

	static short CountSmallLetter(string S)
	{
		short Cntr = 0;

		for (short i = 0; i < S.length(); i++)
		{
			if (islower(S[i]))
				Cntr++;
		}

		return Cntr;
	}

	short CountSmallLetters()
	{
		return CountSmallLetter(_Value);
	}

	static short CountSpecificLetter(char C, string S1, bool MatchCase)
	{
		short Conter = 0;

		for (short i = 0; i < S1.length(); i++)
		{
			if (MatchCase)
			{
				if (S1[i] == C)
					Conter++;
			}
			else
			{
				if (toupper(S1[i]) == toupper(C))
					Conter++;
			}
		}

		return Conter;
	}

	short CountSpecificLetter(char C, bool X)
	{
		return CountSpecificLetter(C, _Value, X);
	}

	static bool IsVowel(char C)
	{
		return (toupper(C) == 'A') || (toupper(C) == 'E') || (toupper(C) == 'I') || (toupper(C) == 'O')
			|| (toupper(C) == 'U');
	}

	static short Countvowel(string S)
	{
		short Cnter = 0;

		for (short i = 0; i < S.length(); i++)
		{
			if (IsVowel(S[i]))
				Cnter++;
		}

		return Cnter;
	}

	short CountVowels()
	{
		return Countvowel(_Value);
	}
	
	static vector <string> Split(string Del,string S)
	{
		vector <string> vString;
		string Word;
		short Pos;

		while ((Pos = S.find(Del)) != string::npos)
		{
			Word = S.substr(0, Pos);

			if (Word != "")
			{
				vString.push_back(Word);
			}

			S.erase(0, Pos + Del.length());
		}

		if (S != "")
		{
			vString.push_back(S);
		}

		return vString;
	}

	vector <string> Split(string Del)
	{
		return Split(Del, _Value);
	}

	static string TrimLeft(string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ')
			{
				return S1.substr(i, S1.length());
			}

		}

		return "";
	}

	void TrimLeft()
	{
		_Value = TrimLeft(_Value);
	}

	static string TrimRight(string S1)
	{
		for (short i = S1.length() - 1 ; i <= 0 ; i--)
		{
			if (S1[i] != ' ')
			{
				return S1.substr(0, i);
			}

		}

		return "";
	}

	void TrimRight()
	{
		_Value = TrimRight(_Value);
	}

	static string Trim(string S1)
	{
		return TrimLeft(TrimRight(S1));
	}

	void Trim()
	{
		_Value = Trim(_Value);
	}

	static string JoinString(vector<string> vString,string Delim )
	{
		string S = "";

		for (string& i : vString)
		{
			S = S + i + Delim;
		}

		return S;
	}

	static string JoinString(string Arr[], short length, string Delim)
	{
		string S = "";

		for (short i = 0; i < length; i++)
		{
			S = S + Arr[i] + Delim;
		}

		return S;
	}

	static string ReverseWordsInString(string S1)
	{
		vector <string> vString = Split(" ", S1);
		vector <string>::iterator iter = vString.end();
		string S = "";

		while (iter != vString.begin())
		{
			--iter;
			S = S + *iter + " ";
		}

		S = S.substr(0, S.length() - 1);

		return S;
	}

	void ReverseWordsInString()
	{
		_Value = ReverseWordsInString(_Value);
	}

	static string ReplaceWord(string S, string WordToReplace, string ReplaceTo)
	{
		vector <string> vString = Split(" ", S);

		for (string& i : vString)
		{
			if (i == WordToReplace)
			{
				i = ReplaceTo;
			}
		}

		return JoinString(vString, " ");
	}

	string ReplaceWord(string WordToReplace, string ReplaceTo)
	{
		return ReplaceWord(_Value, WordToReplace, ReplaceTo);
	}

	static string RemovePunctuations(string S)
	{
		string S1;

		for (short i = 0; i < S.length(); i++)
		{
			if (!ispunct(S[i]))
			{
				S1 += S[i];
			}
		}

		return S1;
	}

	void RemovePunctuations()
	{
		_Value = RemovePunctuations(_Value);
	}
};