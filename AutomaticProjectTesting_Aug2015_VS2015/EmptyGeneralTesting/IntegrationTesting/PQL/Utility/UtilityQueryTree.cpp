#include "UtilityQueryTree.h"


UtilityQueryTree::UtilityQueryTree()
{
}


UtilityQueryTree::~UtilityQueryTree()
{
}

bool UtilityQueryTree::isGetAllAssignsSame(QueryTreeStub qt1, QueryTreeStub qt2)
{
    vector<string> assignListFromQt1 = qt1.getAssigns();
    vector<string> assignListFromQt2 = qt2.getAssigns();
    for (std::vector<string>::iterator itTwo = assignListFromQt1.begin(); itTwo != assignListFromQt1.end(); ++itTwo) {
        string assignFromQt1 = *itTwo;

        for (std::vector<string>::iterator itTwo = assignListFromQt2.begin(); itTwo != assignListFromQt2.end(); ++itTwo) {
            string assignFromQt2 = *itTwo;

            if (assignFromQt1 != assignFromQt2) {
                return false;
            }
        }
    }
    return true;
}
