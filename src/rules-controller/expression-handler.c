#include "../common-headers.h"
#include "../data-structures/data-structures.h"
#include "expression-handler.h"
#include "ctype.h"
STACK *expstack;
TREENODE *currentTree;

extern RC currentRC;

RC identifier;

void setIndentifier()
{

    identifier = currentRC;
}

int getChildCountFromData(EXP_DATA *data)
{
    if (data->type == NUM || data->type == CSV_ELE)
    {
        return 0;
    }

    if (data->type == OP)
    {
        char *twoops[] = {"+", "-", "*", "/"};
        int lengthTwoOps = sizeof(twoops) / sizeof(char *);

        for (int i = 0; i < lengthTwoOps; i++)
        {
            if (!strcmp(data->val.s, twoops[i]))
            {
                return 2;
            }
        }
        fprintf(stderr, "Operand %s not defined\n", data->val.s);
        exit(1);
    }

    fprintf(stderr, "Type %d not defined\n", data->type);
    exit(1);
}

void expressionStart()

{
    expstack = createStack();
}

void pushExpTree(EXP_DATA *data)
{
    unsigned int childCount = getChildCountFromData(data);
    currentTree = createTreeNode(data, childCount);
    for (unsigned int i = 0; i < childCount; i++)
    {
        currentTree->children[childCount - i - 1] = (TREENODE *)popStack(expstack);
    }
    pushStack(expstack, currentTree);
}

void pushOperator(char *op)
{
    EXP_DATA *data = malloc(sizeof(EXP_DATA));
    data->type = OP;
    data->val.s = op;
    pushExpTree(data);
}

void pushRC()
{
    EXP_DATA *data = malloc(sizeof(EXP_DATA));
    data->type = CSV_ELE;
    data->val.rc = currentRC;
    pushExpTree(data);
}

void pushNum(float num)
{
    EXP_DATA *data = malloc(sizeof(EXP_DATA));
    data->type = NUM;
    data->val.f = num;

    pushExpTree(data);
}

float solve(float n1, float n2, char *op)
{

    if (!strcmp(op, "+"))
    {
        return n1 + n2;
    }
    if (!strcmp(op, "-"))
    {
        return n1 - n2;
    }
    if (!strcmp(op, "*"))
    {
        return n1 * n2;
    }
    if (!strcmp(op, "/"))
    {
        return n1 / n2;
    }

    fprintf(stderr, "%s not found\n", op);
    exit(0);
}

float traverseSolve(TREENODE *node)
{

    EXP_DATA *exp_data = node->data;
    if (exp_data->type == NUM)
    {
        return exp_data->val.f;
    }

    if (exp_data->type == CSV_ELE)
    {

        CSV_DATA *data = getEntryFromDatabase(exp_data->val.rc);

        if (data == NULL)
        {
            // fprintf(stderr, "No entry in r%u%u", data->rowNo, data->colNo);
            // exit(1);
            return 0; // returning 0 instead of throwing error
        }

        if (data->valueType == STR_TYPE)
        {
            fprintf(stderr, "String not allowed in numeric expression r%u%u", data->rowNo, data->colNo);
            exit(1);
        }

        if (data->valueType == NUM_TYPE)
        {
            return data->value.f;
        }

        fprintf(stderr, "Ivalid Value type %d", data->valueType);
        exit(1);
    }

    if (exp_data->type == OP)
    {
        return solve(traverseSolve(node->children[0]), traverseSolve(node->children[1]), exp_data->val.s);
    }

    fprintf(stderr, "Ivalid EXPDATA type %d", exp_data->type);
    exit(1);
}

float getResultOfCurrentTree()
{
    return traverseSolve(popStack(expstack));
}

void storeNumResultInDatabase(float result)
{
    CSV_DATA *data = malloc(sizeof(CSV_DATA));
    data->rowNo = identifier.rowNo;
    data->colNo = identifier.colNo;
    data->value.f = result;
    data->valueType = NUM_TYPE;
    addDataToCSV(data);
}

void expressionEnd()
{
    storeNumResultInDatabase(getResultOfCurrentTree());
    freeStack(expstack);
}