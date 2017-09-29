#pragma once
#include<string>
#include<regex>
using namespace std;

class RegexValidators
{
public:

    /******************** Declaration Regex ********************/
    bool isValidEntity(string str);

    bool isValidSynonym(string str);

    /******************** Select Overall ********************/
    bool isValidSelectOverallRegex(string str);

    /******************** Pattern Regex ********************/
    bool isValidPatternRegex(string str);

    /******************** Such That Regex ********************/
    bool isValidModifiesRegex(string str);

    bool isValidUsesRegex(string str);

    bool isValidFollowsRegex(string str);

    bool isValidParentRegex(string str);

private:

    /******************** Grammar ********************/
    const string LETTER = "([a-zA-Z])";
    const string DIGIT = "([0-9])";
    const string INTEGER = "(" + DIGIT + "+)";
    const string HASH = "(#)";
    const string UNDERSCORE = "(_)";
    const string IDENT = "(" + LETTER + "(" + LETTER + "|" + DIGIT + "|" + HASH + ")*)";
    const string SYNONYM = IDENT;
    const string STMTREF = "(" + SYNONYM + "|" + UNDERSCORE + "|" + INTEGER + ")";
    const string ENTREF = "(" + SYNONYM + "|" + UNDERSCORE + "|" + "\"" + IDENT + "\"" ")";
    const string NAME = "(" + LETTER + "(" + LETTER + "|" + DIGIT + ")*)";
    const string SPACE_0 = "(\\s*)";
    const string SPACE_1 = "(\\s+)";

    /*--------------- Declaration Regex ---------------*/
    const string DESIGN_ENTITY_REGEX = "(procedure|stmtLst|stmt|assign|call|while|if|variable|constant|prog_line)";

    /*--------------- Pattern Clause Regex ---------------*/
    const string FACTOR = "(" + NAME + "|" + INTEGER + ")";
    const string EXPRESSION_SPEC = "(" + UNDERSCORE + "|" + UNDERSCORE + "\"" + FACTOR + "\"" + UNDERSCORE + ")";
    const string PATTERN_REGEX = "(" + SPACE_0 + "(pattern)" + SPACE_1 + SYNONYM + SPACE_0 + "[(]" + SPACE_0 + ENTREF + SPACE_0 + "[,]" + SPACE_0 + EXPRESSION_SPEC + SPACE_0 + "[)]" + SPACE_0 + ")";

    /*--------------- Relationship Clause Regex ---------------*/
    const string MODIFIES_REGEX = "(" + SPACE_0 + "(Modifies)" + SPACE_0 + "[(]" + SPACE_0 + STMTREF + SPACE_0 + "[,]" + SPACE_0 + ENTREF + SPACE_0 + "[)]" + SPACE_0 + ")";
    const string USES_REGEX = "(" + SPACE_0 + "(Uses)" + SPACE_0 + "[(]" + SPACE_0 + STMTREF + SPACE_0 + "[,]" + SPACE_0 + ENTREF + SPACE_0 + "[)]" + SPACE_0 + ")";
    const string FOLLOWS_REGEX = "(" + SPACE_0 + "(Follows)(\\*)?" + SPACE_0 + "[(]" + SPACE_0 + STMTREF + SPACE_0 + "[,]" + SPACE_0 + STMTREF + SPACE_0 + "[)]" + SPACE_0 + ")";
    const string PARENT_REGEX = "(" + SPACE_0 + "(Parent)(\\*)?" + SPACE_0 + "[(]" + SPACE_0 + STMTREF + SPACE_0 + "[,]" + SPACE_0 + STMTREF + SPACE_0 + "[)]" + SPACE_0 + ")";

    /*--------------- Select Regex ---------------*/
    const string SELECT_REGEX = "(Select)" + SPACE_1 + SYNONYM;
    const string RELREF = "(" + MODIFIES_REGEX + "|" + USES_REGEX + "|" + FOLLOWS_REGEX + "|" + PARENT_REGEX + ")";
    const string SUCH_THAT_REGEX = SPACE_0 + "(such)" + SPACE_1 + "(that)" + SPACE_1 + RELREF;
    const string SELECT_OVERALL_REGEX = "^" + SPACE_0 + SELECT_REGEX + SPACE_0 + "(" + SUCH_THAT_REGEX + "|" + PATTERN_REGEX + ")*" + SPACE_0 + "$";
};

