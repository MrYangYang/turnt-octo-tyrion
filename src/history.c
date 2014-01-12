#include "history.h"
#include "string.h"
#include <time.h>

History *history_new(void)
{
    History *node = (History *)g_malloc0(sizeof(History));
    return node;
}

History *history_get_child_at(History *head, int index)
{
    History *var = head;
    for( ; index > 0; var = var->next, index--);
    return var;
}

History *history_append_child(History *head, History *child)
{
    History *var = head;
    for ( ; var->next != NULL; var = var->next);
    var->next = child;
    return head;
}

History *history_new_with_data (History *head, gboolean flag, gulong amount)
{
    History *node = history_new();
    node->flag = flag;
    time_t timer = time(NULL);
    gchar *date = ctime(&timer);
    *(date + 24) = '\0';
    node->date = g_string_new(date);
    node->amount = amount;
    node->next = NULL;

    if(!head)
        return node;
    history_append_child (head, node);
    return head;
}

History *history_remove (History *head, int index)
{
    History *var;
    if(index == 0)
    {
        var = head;
        head = head->next;
        g_free(var->date);
        g_free(var);
        return head;
    }

    var = history_get_child_at(head, index-1);
    History *temp = var->next;
    var->next = var->next->next;
    g_free(temp->date);
    g_free(temp);
    return head;
}

History *history_remove_all(History *head)
{
    History *temp;
    while(head)
    {
        g_string_free(head->date, true);
        temp = head;
        head = head->next;
        g_free(temp);
    }
    return NULL;
}

History *history_append_with_data (History *head, gboolean flag, gulong amount, const gchar *date)
{
    History *node = history_new();
    node->flag = flag;
    node->amount = amount;
    node->date = g_string_new(date);
    node->next = NULL;

    if(!head)
        return node;
    history_append_child (head, node);
    return head;
}


