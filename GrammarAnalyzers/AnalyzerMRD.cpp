// AnalyzerMRD - Analyzer by Method of Recursive Descent
//	Analyzing by follow grammar rules:
//		S->E<end>
//		E->E+T | E-T | T
//		T->T*F | T/F | F
//		F->I | I^N | (E)
//		I->a | b | c | d
//		N->2 | 3 | 4
// Create by Gribinchuk Vladislav

#include <iostream>
const size_t _MAXLENGTH = 256;

class AnalyzerMRD
{
private:
	// internal actual buffer
	std::string buf;
	size_t bufsize;
	FILE* pf;

public:
	// _fromfile - the indicator of file presence
	// _buf - name of file when _fromfile is true otherwise
	// _buf - input buffer 
	AnalyzerMRD(char* _buf, bool _fromfile = 0)
	{
		if (_fromfile){
			//
			// True value of _fromfile means, that 
			// input data will be taken from file path _buf.
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
		bufsize = buf.size();
	}
	//////////// End Constructor ////////////

	~AnalyzerMRD()
	{
		if (pf) fclose(pf);
	}

	int scan()
	{
		// Scanning input data according to grammatic rules 
		// and return result: 0 - if input string matches rules
		//	otherwise return -1.
		if (!buf.empty()){
			
			// Initial condition: 
			//	start from first symbol in buffer(index=0)
			//	end in next-to-last symbol.
			if (state_E(0,bufsize-1) == -1)
				return -1;
			
			// Analyze last character
			// in case of it is not equal end-symbol "!"
			// return error value.
			if (buf[bufsize-1] != '!')
				return -1;
		}
		else 
			return -1;
		
		// If there is no error occurrence
		// return 0.
		return 0;
	}

private:
	// Following functions produce  
	// analyzing substrings from internal actual buffer, 
	// starting with the character at the position _from
	// and ending symbol at the position _to.
	// Return value 0 - if substring has been matched rules 
	// otherwise return -1
	
	int state_E(size_t _from, size_t _to)
	{
		std::string buffer = buf.substr(_from,_to-_from);
		size_t pos = buffer.find_first_of("+-", 0);
		//E -> E + T | E - T
		while ((pos != std::string::npos)){
			if (state_E(_from, _from + pos) != -1 &&
				state_T(_from + pos + 1, _to) != -1)
				return 0;
			// find next
			pos = buffer.find_first_of("+-", pos + 1);
		}
		//E -> T
		if(state_T(_from, _to) == -1)
			return -1;
		else
			return 0;
	}

	int state_T(size_t _from, size_t _to)
	{
		std::string buffer = buf.substr(_from, _to - _from);
		size_t pos = buffer.find_first_of("*/", 0);
		while ((pos != std::string::npos)){
			if (state_T(_from, _from + pos) != -1 &&
				state_F(_from + pos + 1, _to) != -1)
				return 0;
			pos = buffer.find_first_of("*/", pos + 1);
		}
		if (state_F(_from, _to) == -1)
			return -1;
		else
			return 0;
	}

	int state_F(size_t _from, size_t _to)
	{
		std::string buffer = buf.substr(_from,_to-_from);
		size_t pos;
		if ((pos = buffer.find('^')) != -1){
			if (state_I(_from, _from + pos) == -1 || state_N(_from+pos + 1, _to) == -1)
				return -1;
			else
				return 0;
		}
		else
			if ((buffer[0] == '(') && (buffer[buffer.length()-1] == ')')){
				if (state_E(_from+1, _to-1) == -1)
					return -1;
				else
					return 0;
			}
			else
				if (state_I(_from, _to) == -1)
					return -1;
				else
					return 0;
	}

	int state_I(size_t _from, size_t _to)
	{
		std::string buffer = buf.substr(_from, _to - _from); 
		if (buffer == "a" ||
			buffer == "b" ||
			buffer == "c" ||
			buffer == "d")
				return 0;
			else
				return -1;
	}
	
	int state_N(size_t _from, size_t _to)
	{
		std::string buffer = buf.substr(_from, _to - _from);
		if (buffer == "2" ||
			buffer == "3" ||
			buffer == "4")
			return 0;
		else
			return -1;
	}

}; // end class AnalyzerSD

int main(int argc, char** argv)
{
	AnalyzerMRD* pAnalyzerObj;

	if (--argc)
		pAnalyzerObj = new AnalyzerMRD(argv[1], true);
	else{
		char input[_MAXLENGTH] = "";
		std::cin >> input;
		pAnalyzerObj = new AnalyzerMRD(input);
	}

	// Analyze input data and get result
	if (pAnalyzerObj->scan() == -1)
		std::cout << "error!\n";
	else
		std::cout << "success!\n";

	// Clean up
	delete pAnalyzerObj;
	return 0;
}