#pragma once
class ClauseObject
{
protected:
	enum TYPE {
		SELECT = 0,
		REL,
		PATTERN,
		WITH
	};

	TYPE clauseType;

public:
	ClauseObject();
	~ClauseObject();
};

