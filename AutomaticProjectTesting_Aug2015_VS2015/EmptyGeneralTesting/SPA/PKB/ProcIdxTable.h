#include <unordered_map>
#include <list>

using namespace std;

class ProcIdxTable {
public:
    ProcIdxTable();
    bool addToProcIdxTable(string proc);
    int getIdxFromProc(string proc);
	string getProcFromIdx(int procIdx);
	list<int> getAllProceduresIndex();
	list<string> getAllProceduresName();
private:
    unordered_map<string, int> procIdxMap;
    int procIdx = 0;
	list<int> allProcIdx;
	list<string> allProcString;
	unordered_map<int, string> procIdxToStringMap;
};