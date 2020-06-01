// Lexical & Syntax Analyzer.cpp

/// Template by Zayed ///

/// #include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <cstdlib>

using namespace std;
int caseno = 1;

#define NL '\n'
#define READ() freopen("input.txt", "r", stdin)
#define WRITE() freopen("output.txt", "w", stdout)

#define PB push_back
#define pci pair<char, int>
#define pii pair<int, int>

bool IsLetter(char c) { return c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z'; }//NOTES: IsLetter(
bool IsDigit(char c) { return c >= '0' && c <= '9'; }//NOTES:IsDigit(
bool IsSpecialChar(char c) { return c == '=' || c == '+' || c == '-' || c == '*' || c == '/' || c == '%'; }//NOTES: IsSpecialChar(
string ToString(int n) { string s; stringstream convert; convert << n; s = convert.str(); return s; }//NOTES:ToString(


string statement, S, token;
map<string, int> MAP1; // (token, id)
map<int, string> MAP2; // (id, token)
map<string, string> MAP5;
map<char, string> MAP3;
map<string, char> MAP4;



/***Infix to Postfix***/
bool Operand(char c)
{
	if (c >= '0' && c <= '9')
		return true;
	//if (c >= 'a' && c <= 'z')
	//return true;
	//if (c >= 'A' && c <= 'Z')
	//return true;

	return false;
}

int OperatorGravity(char optr)
{
	int gravity = -1;
	switch (optr)
	{
	case '+':
	case '-':
		return 1;

	case '*':
	case '/':
		return 2;

	case'%':
		return 3;

	case'^':
		return 4;
	}

	return gravity;
}


bool HigherPrecedence(char operator1, char operator2)
{
	int operator1Gravity = OperatorGravity(operator1);
	int operator2Gravity = OperatorGravity(operator2);

	if (operator1Gravity == operator2Gravity)
		return true;

	return operator1Gravity > operator2Gravity ? true : false;
}


string InfixToPostfix(string infix)
{
	stack<char> s;
	string postfix = "";

	int I, len = infix.length();
	for (I = 0; I < len; I++)
	{
		if (infix[I] == ' ' || infix[I] == ',')
			continue;
		else if (infix[I] == '(' || infix[I] == '{' || infix[I] == '[')
			s.push(infix[I]);

		else if (infix[I] == ')' || infix[I] == '}' || infix[I] == ']')
		{
			while (!s.empty() && (s.top() != '(' && s.top() != '{' && s.top() != '['))
			{
				postfix += s.top();
				s.pop();
			}
			s.pop();
		}
		else if (infix[I] == '+' || infix[I] == '-' || infix[I] == '*' || infix[I] == '/' || infix[I] == '^' || infix[I] == '%')
		{
			while (!s.empty() && s.top() != '(' && s.top() != '{' && s.top() != '[' && HigherPrecedence(s.top(), infix[I]))
			{
				postfix += s.top();
				s.pop();
			}
			s.push(infix[I]);
		}

		// Else if character is an operand
		else if (Operand(infix[I]))
			postfix += infix[I];


	}

	while (!s.empty())
	{
		postfix += s.top();
		s.pop();
	}

	return postfix;
}
/***Infix to Postfix***/



/***Lexical Analyzer***/
void LexicalAnalyzer()
{
	int I, cnt = 0, f = 0, len = statement.length();

	///* Generates token(Start) ///
	token = "";
	int id = 0;

	for (I = 0; I < len; I++)
	{
		if (IsSpecialChar(statement[I]) && token.length() == 0)
		{
			token = "";
			token += statement[I];
			MAP1[token] = id;
			MAP2[id] = token;
			token = "";
			id++;
		}
		else if ((statement[I] == ' ' || IsSpecialChar(statement[I])) && token.length() != 0)
		{
			MAP1[token] = id;
			MAP2[id] = token;
			id++;

			if (IsSpecialChar(statement[I]))
			{
				token = "";
				token += statement[I];
				MAP1[token] = id;
				MAP2[id] = token;
				id++;
			}

			cnt++;
			f = 0;
			token = "";

		}
		else if (statement[I] != ' ' && !IsSpecialChar(statement[I]) && f != 1)
			f = 1;

		if (f == 1)
			token += statement[I];

		if (statement[I] == ';')
			break;
	}

	if (token != "")
	{
		if (token.length() > 1 && token[token.length() - 1] == ';')
			token.erase(token.begin() + token.length() - 1);

		MAP1[token] = id;
		MAP2[id] = token;
	}

	cnt = 0;
	cout << "\nTokens:\n";
	S = "";
	map<int, string>::iterator it2 = MAP2.begin();
	while (it2 != MAP2.end())
	{
		if (cnt == 0)
			cout << "id : " << it2->second << NL;
		else
			cout << "id" << it2->first << " : " << it2->second << NL;

		string temp = it2->second;

		if (IsLetter(temp[0]))
		{
			S += "id";

			if (cnt != 0)
				S += ToString(it2->first);
			cnt++;
		}
		else if (IsDigit(temp[0]))
			S += it2->second;
		else
			S += it2->second;

		it2++;
	}
	cout << "\n" << S << NL;

	if (S[S.length() - 1] == ';')
		S.erase(S.begin() + S.length() - 1);
	/// Generates token(End) *///

}
/***Lexical Analyzer ***/


/***Syntax Analyzer***/
vector<pci> op;
queue<char> qc;
string S1;
void SyntaxAnalyzer()
{
	int I, J, len, isBracket = 0, flag = 0, idx;
	S1 = statement;
	len = S1.length();

	for (I = 0; I < len; I++)
	{
		if (S1[I] == ';')
		{
			flag = 1;
			break;
		}
	}

	if (flag == 0)
	{
		cout << "error: expected ';'\n";
		return;
	}

	string temp = "";
	len = statement.length();
	for (I = 0; I < len; I++)
	{
		if (statement[I] != ' ')
			break;
	}

	int f = 0;
	for (int J = I; J < len; J++)
	{
		if (statement[J] == ' ' && f == 0)
		{
			if (statement[J] == ' ')
				temp += ' ';
			f = 1;
		}
		else if (IsLetter(statement[J]) || IsDigit(statement[J]) || statement[J] == '.')
		{
			temp += statement[J];
			f = 0;
		}
		else if (statement[J] == '=' || IsSpecialChar(statement[J]))
		{
			if (statement[J] == '=')
				temp += '=';
			else
				temp += statement[J];

			temp += ' ';
		}

	}


	///cout << "temp = " << temp << NL;

	for (I = 0; I < len; I++)
	{
		if (temp[I] == ' ')
		{
			if (IsLetter(temp[I - 1]) && IsLetter(temp[I + 1]))
			{

				cout << "error: expected ';' before ";
				for (J = I + 1; J < len; J++)
				{
					if (temp[J] == ' ' || J == len - 1)
					{
						cout << '\n';
						return;
					}

					else
						cout << temp[J];
				}

			}
		}
	}


	flag = 0;

	I = 0;
	while (I < len)
	{
		if (S1[I] == ' ')
			S1.erase(S1.begin());
		else
			break;
	}


	///* Operator ///
	S1 = S;
	len = S1.length();

	for (I = 0; I < len; I++)
	{
		if (S1[I] == ')' || S1[I] == '(')
			isBracket = 1;
		else if (S1[I] == '=' || S1[I] == '+' || S1[I] == '-' || S1[I] == '*' || S1[I] == '/' || S1[I] == '%')
			op.PB(pci(S1[I], I));
	}


	for (I = 0; I < op.size(); I++)
	{
		/// 1. For '+' operator
		if (op[I].first == '+')
		{
			idx = op[I].second;

			if (idx + 1 == len)
			{
				flag = 1;
				break;
			}

			if (S1[idx - 1] == ')' && S1[idx + 1] == '(')
				continue;
			else if (S1[idx - 1] == ')' && S1[idx + 1] == 'i')
				continue;
			else if (IsDigit(S1[idx - 1]) && S1[idx + 1] == '(')
				continue;
			else if (IsDigit(S1[idx - 1]) && S1[idx + 1] == 'i')
				continue;
			else if (IsDigit(S1[idx - 1]) && IsDigit(S1[idx + 1]))
				continue;
			else
			{
				cout << "+\n";
				flag = 1;
				break;
			}

		}
		/// For '+' operator


		/// 2. For '-' operator
		if (op[I].first == '-')
		{
			idx = op[I].second;

			if (idx + 1 == len)
			{
				flag = 1;
				break;
			}

			if (S1[idx - 1] == ')' && S1[idx + 1] == '(')
				continue;
			else if (S1[idx - 1] == ')' && S1[idx + 1] == 'i')
				continue;
			else if (IsDigit(S1[idx - 1]) && S1[idx + 1] == '(')
				continue;
			else if (IsDigit(S1[idx - 1]) && S1[idx + 1] == 'i')
				continue;
			else if (IsDigit(S1[idx - 1]) && IsDigit(S1[idx + 1]))
				continue;
			else
			{
				cout << "-\n";
				flag = 1;
				break;
			}

		}
		/// For '-' operator


		/// 3. For '*' operator
		if (op[I].first == '*')
		{
			idx = op[I].second;

			if (idx + 1 == len)
			{
				flag = 1;
				break;
			}

			if (S1[idx - 1] == ')' && S1[idx + 1] == '(')
				continue;
			else if (S1[idx - 1] == ')' && S1[idx + 1] == 'i')
				continue;
			else if (IsDigit(S1[idx - 1]) && S1[idx + 1] == '(')
				continue;
			else if (IsDigit(S1[idx - 1]) && S1[idx + 1] == 'i')
				continue;
			else if (IsDigit(S1[idx - 1]) && IsDigit(S1[idx + 1]))
				continue;
			else
			{
				cout << "*\n";
				flag = 1;
				break;
			}

		}
		/// For '*' operator


		/// 4. For '/' operator
		if (op[I].first == '/')
		{
			idx = op[I].second;

			if (idx + 1 == len)
			{
				flag = 1;
				break;
			}

			if (S1[idx - 1] == ')' && S1[idx + 1] == '(')
				continue;
			else if (S1[idx - 1] == ')' && S1[idx + 1] == 'i')
				continue;
			else if (IsDigit(S1[idx - 1]) && S1[idx + 1] == '(')
				continue;
			else if (IsDigit(S1[idx - 1]) && S1[idx + 1] == 'i')
				continue;
			else if (IsDigit(S1[idx - 1]) && IsDigit(S1[idx + 1]))
				continue;
			else
			{
				cout << "/\n";
				flag = 1;
				break;
			}

		}
		/// For '/' operator


		/// 5. For '%' operator
		if (op[I].first == '%')
		{
			idx = op[I].second;

			if (idx + 1 == len)
			{
				flag = 1;
				break;
			}

			if (S1[idx - 1] == ')' && S1[idx + 1] == '(')
				continue;
			else if (S1[idx - 1] == ')' && S1[idx + 1] == 'i')
				continue;
			else if (IsDigit(S1[idx - 1]) && S1[idx + 1] == '(')
				continue;
			else if (IsDigit(S1[idx - 1]) && S1[idx + 1] == 'i')
				continue;
			else if (IsDigit(S1[idx - 1]) && IsDigit(S1[idx + 1]))
				continue;
			else if (IsDigit(S1[idx - 1]) && IsDigit(S1[idx + 1]))
				continue;
			else
			{
				cout << "%\n";
				flag = 1;
				break;
			}

		}
		/// For '%' operator
	}

	if (flag == 1)
	{
		cout << "\nerror: expected primary-expression before ';' token\n";
		return;
	}

	/// Parenthesis balance checking
	if (isBracket)
	{
		for (I = 0; I < len; I++)
		{
			if (S1[I] == '(')
				qc.push(S1[I]);
			else if (S1[I] == ')')
			{
				if (qc.front() == '(')
					qc.pop();
				else if (qc.empty())
					qc.push(S1[I]);
			}
		}

		if (!qc.empty())
		{
			char ch = qc.front();
			cout << "\nerror: expected ';' before " << ch << " token\n";
			return;
		}

	}

	cout << "\n'" << statement << "' is a valid statement.\n";

	string token = "";
	char ch = 'a';

	S1 = "";
	len = S.length();
	for (I = 0; I < len; I++)
	{
		if (IsSpecialChar(S[I]))
		{
			MAP3[ch] = token;
			MAP4[token] = ch;
			S1 += ch;
			S1 += S[I];
			ch++;
			token = "";
		}
		else
			token += S[I];
	}

	if (token.length() != 0)
	{
		MAP3[ch] = token;
		MAP4[token] = ch;
		S1 += ch;
		ch++;
	}

	string postfix = InfixToPostfix(S1);
	postfix += '=';
	cout << "\nParse tree will be traversed through following precedence of operators: " << postfix << NL;
}
/***Syntax Analyzer***/


int main()
{
	///READ();
	///WRITE();
	int tcases, I, J, K, N, n, m, cnt = 0, len;

	getline(cin, statement);
	LexicalAnalyzer();
	SyntaxAnalyzer();

	return 0;
}

/*
      marvel   =   logan   xmen  +   iron man;
n = ab + c;
initial = position + rate * 60 + value;
child = n
v1 = v2 + ;
c = a + b * 5;
a = b + c / d * e - f;
*/
