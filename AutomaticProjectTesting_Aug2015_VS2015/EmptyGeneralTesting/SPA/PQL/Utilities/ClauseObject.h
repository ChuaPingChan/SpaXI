#pragma once
class ClauseObject
{
protected:
	TYPE clauseType;

public:
	ClauseObject();
	~ClauseObject();

	enum TYPE {
		SELECT = 0,
		REL,
		PATTERN,
		WITH
	};

	/* Getter */
	TYPE getClauseType()
	{
		return clauseType;
	}
	
};

