#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem *prev;
    ListItem *next;
};

struct List
{
    ListItem* head;
    ListItem* tail;
    size_t size;
};

List *list_create(size_t size)
{
    List* list = new List;
    list->head = nullptr;
    list->tail = nullptr;
    list->size = size;
    return list;
}

void list_delete(List* list)
{
    ListItem* current = list->head;
    while (current != nullptr)
    {
        ListItem* next = current->next;
        delete current;
        current = next;
    }
    delete list;
}

ListItem *list_first(List *list)
{
    if (list == nullptr) {
        return nullptr;
    }
    return list->head;
}

ListItem *list_last(List *list)
{
    if (list == nullptr) {
        return nullptr;
    }
    return list->tail;
}

Data list_item_data(const ListItem *item)
{

    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem* item = new ListItem;
    item->data = data;
    item->prev = nullptr;
    item->next = list->head;

    if (list->head == nullptr)
    {
        list->head = item;
        list->tail = item;
    }
    else
    {
        list->head->prev = item;
        list->head = item;
    }

    list->size++;
    return item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item == nullptr)
    {
        return list_insert(list, data);
    }

    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->prev = item;
    newItem->next = item->next;

    if (item->next == nullptr)
    {
        list->tail = newItem;
    }
    else
    {
        item->next->prev = newItem;
    }

    item->next = newItem;
    list->size++;

    return newItem;
}

ListItem *list_erase_first(List *list)
{
    if (list->head == nullptr)
    {
        return nullptr;
    }

    ListItem* victim = list->head;
    ListItem* next = victim->next;

    if (next == nullptr)
    {
        list->head = nullptr;
        list->tail = nullptr;
    }
    else
    {
        next->prev = nullptr;
        list->head = next;
    }

    delete victim;
    list->size--;

    return next;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item == nullptr)
    {
        return list_erase_first(list);
    }

    if (item->next == nullptr)
    {
        return nullptr;
    }

    ListItem* victim = item->next;
    ListItem* next = victim->next;

    item->next = next;

    if (next == nullptr)
    {
        list->tail = item;
    }
    else
    {
        next->prev = item;
    }

    delete victim;
    list->size--;

    return next;
}
