#include <string>
#include <list>
#include "../Utilities/ClauseResult.h"
#include "../Utilities/ClauseObject.h"
#include "../../PKB/PKBMain.h"

using namespace std;

class ClauseEvaluator
{
protected:
	PKBMain* pkbInstance;
	list<string> getListStringFromListInt(list<int> listOfInt);

public:
	ClauseEvaluator();
	~ClauseEvaluator();

	virtual ClauseResult evaluate(ClauseObject clause) = 0;

};

