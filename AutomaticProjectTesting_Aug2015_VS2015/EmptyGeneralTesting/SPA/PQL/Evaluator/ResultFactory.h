#pragma once
#include "../QueryTree.h"
#include "../Utilities/ClauseResult.h"
#include "ClauseEvaluator.h"
#include "Pattern/PatternEvaluator.h"
#include "Pattern/AssignPatternEvaluator.h"
#include "Pattern/WhilePatternEvaluator.h"
#include "Pattern/IfPatternEvaluator.h"
#include "SelectionEvaluator.h"
#include "SuchThat/FollowsEvaluator.h"
#include "SuchThat/FollowsStarEvaluator.h"
#include "SuchThat/ParentEvaluator.h"
#include "SuchThat/ParentStarEvaluator.h"
#include "SuchThat/ModifiesEvaluator.h"
#include "SuchThat/UsesEvaluator.h"
#include "SuchThat/NextEvaluator.h"
#include "SuchThat/NextStarEvaluator.h"
#include "SuchThat/CallsEvaluator.h"
#include "SuchThat/CallsStarEvaluator.h"
#include "SuchThat/AffectsEvaluator.h"
#include "SuchThat/AffectsStarEvaluator.h"

class ResultFactory
{
public:
	ResultFactory();
	~ResultFactory();

	ClauseResult makeClauseResult(SelectClause clause);
	ClauseResult makeClauseResult(SuchThatClause clause);
	ClauseResult makeClauseResult(PatternClause clause);
	//ClauseResult makeClauseResult(WithClause clause);

private:

	enum REL 
	{
		MODIFIES = 0,
		USES,
		PARENT,
		PARENTSTAR,
		FOLLOWS,
		FOLLOWSSTAR,
		CALLS,
		CALLSSTAR,
		NEXT,
		NEXTSTAR,
		AFFECTS,
		AFFECTSSTAR,
		PATTERN
	};

	template<typename Base, typename T>
	inline bool instanceof(const T *ptr) {
		return dynamic_cast<const Base*>(ptr) != nullptr;
	}
};

