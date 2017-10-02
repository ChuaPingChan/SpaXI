#include <string>
#include <list>
#include "../../PKB/PKBMain.h"

using namespace std;

class ClauseEvaluator
{

public:
    ClauseEvaluator();
    ~ClauseEvaluator();

protected:
    PKBMain* pkbInstance;
    list<string> getListStringFromListInt(list<int> listOfInt);

};

