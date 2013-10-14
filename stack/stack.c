/*
** program name: stack.c
** author:       luo feng
** date:         2013/9/12
*/

#include "stack.h"

/*
**initialize a stack
*/
status stack_init()
{
    stack_index = 0;
}

/*
**push an element into a stack
*/
status stack_push(stack_elem st_elem)
{
    if(stack_index == STACK_SIZE-1)
        return FAIL_FULL;

    Stack[++stack_index] = st_elem;
    return SUCCESS;
}

/*
**pop an element from a stack
*/
status stack_pop(stack_elem *st_elem)
{
    if(stack_index == 0)
        return FAIL_EMPTY;

    *st_elem = Stack[stack_index--];
    return SUCCESS;
}

/*
**get the top element from a stack
*/
status stack_top(stack_elem *st_elem)
{
    if(stack_index == 0)
        return FAIL_EMPTY;

    *st_elem = Stack[stack_index];
    return SUCCESS;
}
