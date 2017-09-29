#pragma once
class ClauseObject
{
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

protected:
	TYPE clauseType;
	
};

