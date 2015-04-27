#include <iostream>
const size_t _MAXLENGTH = 256;

class Analyzer
{
public:

	////////////// Constructors //////////////
	// 1. Open file for read data from it
	Analyzer(char* _fname)
	{
		fopen_s(&pf, _fname, "r");
	}

	// 2. Create buffer from input string
	Analyzer(std::string _buf)
	{
		buf = _buf;	
	}
	//////////// End Constructors ////////////

	~Analyzer()
	{
		if (pf) fclose(pf);
	}

	int scan()
	{
		// if buffer not empty
		// analyze buffer
		if (!buf.empty())
			for (int i = 0; i < buf.size(); ++i)
				if (analyzer(buf[i]) == state::_ER)
					return -1;	
				else;
		else
			// or analyze opened file
			while (!feof(pf)){
				char sym = fgetc(pf);
				if (sym != -1)
					if (analyzer(sym) == state::_ER)
					return -1;
			}

		return 0;
	}

private:
	int analyzer(char sym)
	{
		// Analyze according to grammatics rule 
		switch (CurState){
		case state::_H:
			if (sym == '0' || sym == '1')
				CurState = state::_N;
			else
				CurState = state::_ER;
			break;
		case state::_N:
			if (sym == '0' || sym == '1')
				CurState = state::_N;
			else
				if (sym == '.')
					CurState = state::_P;
				else
					CurState = state::_ER;
			break;
		case state::_P:
			if (sym == '0' || sym == '1')
				CurState = state::_S;
			else
				CurState = state::_ER;
			break;
		case state::_S:
			if (sym == '0' || sym == '1')
				CurState = state::_S;
			else
				CurState = state::_ER;
			break;
		}

		return CurState;
	}
	
	// internal var and data
	enum state { _H, _N, _P, _S, _ER };
	int CurState = state::_H;
	std::string buf;
	FILE* pf;
};

int main(int argc, char** argv)
{
	Analyzer* pAnalyzerObj;

	// Open file or read input data from stdin
	if (--argc)
		pAnalyzerObj = new Analyzer(argv[1]);
	else{
		char input[_MAXLENGTH] = "";
		std::cin >> input;
		std::string str(input);
		pAnalyzerObj = new Analyzer(str);
	}

	// Analyze input data and get result
	if(pAnalyzerObj->scan() == -1)
		std::cout << "error!\n";
	else
		std::cout << "success!\n";
	
	// Clean up and pause
	delete pAnalyzerObj;
	system("pause");
	return 0;
}