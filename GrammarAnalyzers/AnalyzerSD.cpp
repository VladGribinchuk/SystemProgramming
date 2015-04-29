// AnalyzerSD - Analyzer by State Diagrams
//	Analyzing by follow grammar rules:
//		S->S0 | S1 | P0 | P1
//		P->N.
//		N -> 0 | 1 | N0 | N1
// Create by Gribinchuk Vladislav

#include <iostream>
const size_t _MAXLENGTH = 256;

class AnalyzerSD
{
private:
	// internal var and data
	enum state { _H, _N, _P, _S, _ER };
	int CurState = state::_H;
	std::string buf;
	FILE* pf;

public:

	// _fromfile - the indicator of file presence
	// _buf - name of file when _fromfile is true otherwise
	// _buf - input buffer 
	AnalyzerSD(char* _buf, bool _fromfile = 0)
	{
		if (_fromfile){
			//
			// True value of _fromfile means, that 
			// input data will be taken from file path _buf
			fopen_s(&pf, _buf, "r");
			
			int offset = 0;
			while (!feof(pf))
				buf.push_back(fgetc(pf));
			// last element is symbol EOF
			// thus it will be removed
			buf.pop_back();
		}
		else {
			//
			// otherwise input data is _buf
			buf = _buf;
		}
		
	}
	//////////// End Constructor ////////////

	~AnalyzerSD()
	{
		if (pf) fclose(pf);
	}

	int scan()
	{
		if (!buf.empty())
			for (int i = 0; i < buf.size(); ++i)
				if (analyzer(buf[i]) == state::_ER)
					return -1;	

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

}; // end class AnalyzerSD

int main(int argc, char** argv)
{
	AnalyzerSD* pAnalyzerObj;

	if (--argc)
		pAnalyzerObj = new AnalyzerSD(argv[1],true);
	else{
		char input[_MAXLENGTH] = "";
		std::cin >> input;
		pAnalyzerObj = new AnalyzerSD(input);
	}

	// Analyze input data and get result
	if(pAnalyzerObj->scan() == -1)
		std::cout << "error!\n";
	else
		std::cout << "success!\n";
	
	// Clean up
	delete pAnalyzerObj;
	return 0;
}