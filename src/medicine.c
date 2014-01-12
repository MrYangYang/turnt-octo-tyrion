#include "medicine.h"
#include "my_type.h"
#include "string.h"

Medicine *medicine_new(void)
{
    Medicine *node = (Medicine *)g_malloc0(sizeof(Medicine));
    return node;
}

Medicine *medicine_append_child(Medicine *head, Medicine *child)
{
    if(!head && !child)
        return NULL;
    if(!head)
        return child;

    Medicine *var = head;
    for ( ; var->next != NULL; var = var->next);
    var->next = child;
    return head;
}

Medicine *medicine_get_child_at(Medicine *head, int index)
{
    Medicine *var = head;
    for ( ; index > 0; var = var->next, index--);
    return var;
}

Medicine *medicine_remove(Medicine *head, int index)
{
    /*****************************************
    *   free the node,contain its members    *
    *****************************************/
    Medicine *var;
    if(index == 0)
    {
        var = head;
        var = var->next;
        g_free(head->name);
        g_free(head->allow_key);
        g_free(head->identify_key);
        g_free(head->producer);
        g_free(head->specification);
        g_free(head->unit);
        history_remove_all(head->hist_head);
        g_free(head);
        return var;
    }

    var = medicine_get_child_at (head,index-1);
    Medicine *node = var->next;
    var->next = var->next->next;
    g_free(node->name);
    g_free(node->allow_key);
    g_free(node->identify_key);
    g_free(node->producer);
    g_free(node->specification);
    g_free(node->unit);
    history_remove_all(node->hist_head);
    g_free(node);
    return head;
}

Medicine *medicine_append_with_data(Medicine *head,
                                                            gchar *name,
                                                            gchar *unit,
                                                            gulong quantity,
                                                            gchar *specification,
                                                            gchar *allow_key,
                                                            gchar *identify_key,
                                                            gchar *producer)
{
    Medicine *node = medicine_new();

    node->name = g_string_new(name);
    node->unit = g_string_new(unit);
    node->quantity = quantity;
    node->specification = g_string_new(specification);
    node->allow_key = g_string_new(allow_key);
    node->identify_key = g_string_new(identify_key);
    node->producer = g_string_new(producer);

    if( !head )
        return node;

    medicine_append_child(head, node);
    return head;
}

Medicine *medicine_remove_all(Medicine *head)
{
    if(head == NULL)
        return head;
    Medicine *temp;
    for( ; head->next != NULL;  )
    {
        temp = head;
        head = head->next;
        g_free(temp->name);
        g_free(temp->allow_key);
        g_free(temp->identify_key);
        g_free(temp->producer);
        g_free(temp->specification);
        g_free(temp->unit);
        history_remove_all(temp->hist_head);
        g_free(temp);
    }

    g_free(head->name);
    g_free(head->allow_key);
    g_free(head->identify_key);
    g_free(head->producer);
    g_free(head->specification);
    g_free(head->unit);
    history_remove_all(head->hist_head);
    g_free(head);

    return NULL;
}

Medicine *medicine_remove_by_identify_key(Medicine *head, gchar *identify_key)
{
    Medicine *temp = head;
    Medicine *pre;

    if(!head)
        return NULL;

    if(g_strcmp0(temp->identify_key->str, identify_key) == 0)
    {
        g_string_free(temp->name, true);
        g_string_free(temp->unit, true);
        g_string_free(temp->specification, true);
        g_string_free(temp->allow_key, true);
        g_string_free(temp->identify_key, true);
        g_string_free(temp->producer, true);
        head = head->next;
        g_free(temp);
        return head;
    }

    pre = temp;
    temp = temp->next;

    while(temp != NULL)
    {
        if(g_strcmp0(temp->identify_key->str, identify_key) == 0)
        {
            g_string_free(temp->name,true);
            g_string_free(temp->unit,true);
            g_string_free(temp->specification,true);
            g_string_free(temp->allow_key,true);
            g_string_free(temp->identify_key,true);
            g_string_free(temp->producer,true);

            pre->next = temp->next;
            g_free(temp);
            return head;
        }
        pre = pre->next;
        temp = temp->next;
    };

    return head;
}

Medicine *medicine_get_child_by_identify_key(Medicine *head, const gchar *identify_key)
{
    Medicine *temp = head;

    while(temp)
    {
        if(g_strcmp0(temp->identify_key->str, identify_key) == 0)
        {
            return temp;
        }
        temp = temp->next;
    }

    return NULL;
}




