#include "dispensary.h"
#include "my_type.h"
#include "string.h"

Dispensary *dispensary_new(void)
{
    Dispensary *node;
    node = (Dispensary *) g_malloc0(sizeof (Dispensary));
    return node;
}

Dispensary *dispensary_append_child (Dispensary *head, Dispensary *child)
{
    if(!head && !child)
        return NULL;
    if(!head)
    {
        child->id = 0;
        return child;
    }

    Dispensary *var = head;
    int max_id = 0;
    for( ; head->next != NULL; head = head->next)
    {
        if(head->id>max_id)
            max_id = head->id;
    }
    head->next = child;
    child->id = max_id + 1;
    return var;
}
Dispensary *dispensary_new_with_data (Dispensary *head, gchar *name, gchar *place, gchar *tel)
{
    Dispensary *node = dispensary_new();
    node->name = g_string_new(name);
    node->place = g_string_new(place);
    node->tel = g_string_new(tel);

    node -> next = NULL;

    if(!head)
    {
        node->id = 0;
        return node;
    }

    Dispensary *var = head;
    Dispensary *pre;
    int max_id = var->id;

    do
    {
        if((var->id) >= max_id)
        {
            max_id = var->id;
        }
        pre = var;
        var = var -> next;
    }while(  var != NULL );

    node->id = (max_id+1);

    pre->next = node;

    return head;
}

Dispensary *dispensary_get_child_at(Dispensary *head, int index)
{
    for( ; index > 0; head = head->next, index--);
    return head;
}

Dispensary *dispensary_replace_with(Dispensary *head, int index, Dispensary *node)
{
    if(index == 0)
    {
        node->next = head->next;
        g_free(head);
        return node;
    }

    Dispensary *var = dispensary_get_child_at(head,index-1);
    Dispensary *temp = var->next;
    var->next = node;
    node->next = temp->next;
    g_free(temp);

    return head;
}

Dispensary *dispensary_remove(Dispensary *head, int index)
{
    Dispensary *var;
    if(index == 0)
    {
        var = head;
        head = head->next;
        g_free(var->name);
        g_free(var->place);
        g_free(var->tel);
        medicine_remove_all(var->mdc_head);
        g_free(var);
        return head;
    }
    var = dispensary_get_child_at(head,index-1);
    Dispensary *temp = var->next;
    var->next = var->next->next;
    g_free(temp->name);
    g_free(temp->place);
    g_free(temp->tel);
    medicine_remove_all(temp->mdc_head);
    g_free(temp);
    return head;
}

Dispensary *dispensary_remove_all(Dispensary *head)
{
    if(head == NULL)
        return head;
    Dispensary *temp;
    for ( ; head->next != NULL ; )
    {
        temp = head;
        head = head -> next;
        g_free(temp->name);
        g_free(temp->place);
        g_free(temp->tel);
        medicine_remove_all(temp->mdc_head);
        g_free(temp);
    }

    g_free(head->name);
    g_free(head->place);
    g_free(head->tel);
    medicine_remove_all(head->mdc_head);
    g_free(head);

    return NULL;
}

Dispensary *dispensary_get_child_by_id (Dispensary *head, int id)
{
    if(!head)
        return NULL;

    while(head)
    {
        if(head->id == id)
            return head;
        head = head->next;
    }

    return NULL;
}

Dispensary *dispensary_remove_by_id (Dispensary *head, int id)
{
    if(!head)
        return NULL;

    Dispensary *pre;
    Dispensary *temp = head;
    if(head->id == id)
    {
        g_string_free(head->name, true);
        g_string_free(head->place, true);
        g_string_free(head->tel, true);
        pre = head;
        head = head->next;
        g_free(pre);
        return head;
    }

    pre = head;
    head = head->next;

    do
    {
        if(head->id == id)
        {
            pre->next = head->next;
            g_string_free(head->name, true);
            g_string_free(head->place, true);
            g_string_free(head->tel, true);
            g_free(head);
            return temp;
        }
        pre = pre->next;
        head = head->next;
    }while(head != NULL);

    return temp;
}

Dispensary *dispensary_append_with_data(Dispensary *head, gchar *name, gchar *place, gchar *tel, gint id)
{
    Dispensary *node = dispensary_new();
    node->name = g_string_new(name);
    node->place = g_string_new(place);
    node->tel = g_string_new(tel);
    node->id = id;
    node->next = NULL;
    node->mdc_head = NULL;

    if(!head)
        return  node;

    Dispensary *var = head;

    while(var->next != NULL)
        var = var->next;

    var->next = node;
    return head;
}



