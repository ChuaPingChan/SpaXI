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
    bool isProcedure(string procName);
    bool addStmtToProc(int stmt, int procIdx);
    int getProcIdxFromStmt(int stmt);
    int getFirstStmtFromProc(int procIdx);
    list<int> getAllStmtsFromProc(int procIdx);
private:
    unordered_map<string, int> procIdxMap;
    int procIdx = 0;
    list<int> allProcIdx;
    list<string> allProcString;
    unordered_map<int, string> procIdxToStringMap;
    unordered_map<int, list<int>> procToStmtMap;
    unordered_map<int, int> stmtToProcMap;
};