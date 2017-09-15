#include <unordered_map>
#include <list>

using namespace std;

class ProcIdxTable {
public:
    ProcIdxTable();
    bool addToProcIdxTable(string proc, int index);
    int getIdxFromProc(string proc);
private:
    unordered_map<string, int> procIdxMap;
};