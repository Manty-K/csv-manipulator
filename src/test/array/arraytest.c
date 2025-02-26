#include "../../common-headers.h"
#include "../../data-structures/data-structures.h"
int main(int argc, char const *argv[])
{
    ARRAY *arr = createArray(1);

    char *a = "Manty";
    char *b = "k";

    char *c = "Hello";

    appendArray(arr, a);
    appendArray(arr, b);

    insertArray(arr, 1, c);

    for (int i = 0; i < getArraySize(arr); i++)
    {
        printf("YO : %s\n", (char *)getElementArray(arr, i));
    }

    /* code */
    return 0;
}
