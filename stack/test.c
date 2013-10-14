#include <stdio.h>
#include "status.h"
#include "stack.h"

int main(int argc, char *argv[])
{
    stack_init();
    
    stack_push(1);
    stack_push(2);
    stack_push(3);
    stack_push(4);

    stack_elem ret = 0;
    stack_pop(&ret);
    printf("%d\n", ret);
    stack_pop(&ret);
    printf("%d\n", ret);
    stack_pop(&ret);
    printf("%d\n", ret);
    stack_pop(&ret);
    printf("%d\n", ret);

    return 0;
}
