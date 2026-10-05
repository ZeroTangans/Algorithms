#include "list.h"
#include "stack.h"

struct Stack
{
    List* list;
};

Stack* stack_create()
{
    Stack* stack = new Stack;
    stack->list = list_create();
    return stack;
}

void stack_delete(Stack* stack)
{
    list_delete(stack->list);
    delete stack;
}

void stack_push(Stack* stack, Data data)
{
    list_insert(stack->list, data);
}

Data stack_get(const Stack* stack)
{
    List* list = stack->list;
    ListItem* top = list_first(list);

    if (top == nullptr)
        return Data();

    return list_item_data(top);
}

void stack_pop(Stack* stack)
{
    if (list_first(stack->list) == nullptr)
        return;

    list_erase_first(stack->list);
}

bool stack_empty(const Stack* stack)
{
    List* list = stack->list;
    return list_first(list) == nullptr;
}