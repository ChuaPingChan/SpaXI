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

	enum TYPE
	{
		STMT = 0,
		ASSIGN,
		WHILE,
		IF,
		PROG_LINE,
		CALL,
		PROCEDURE,
		VARIABLE,
		INTEGER,
		UNDERSCORE,
		IDENT,
		EXP,
		CONSTANT,
	};

public:
	ClauseEvaluator();
	~ClauseEvaluator();

	virtual ClauseResult evaluate(ClauseObject clause) = 0;

};

