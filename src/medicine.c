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
    if (!head)
        return head;

    Medicine *var;
    if(index == 0)
    {
        var = head;
        var = var->next;
        if (head->name)
            g_string_free(head->name, TRUE);
        if (head->allow_key)
            g_string_free(head->allow_key, TRUE);
        if (head->identify_key)
            g_string_free(head->identify_key, TRUE);
        if (head->producer)
            g_string_free(head->producer, TRUE);
        if (head->specification)
            g_string_free(head->specification, TRUE);
        if (head->unit)
            g_string_free(head->unit, TRUE);
        history_remove_all(head->hist_head);
        g_free(head);
        return var;
    }

    index--;

    Medicine *prev = head;
    Medicine *temp = head->next;

    for( ; index > 0 && temp; temp = temp->next, prev = prev->next);

    if (index != 0 || !temp)
        return head; // index out of bound
    
    prev->next = temp->next;
    Medicine *node = temp;
    history_remove_all(node->hist_head);
    if (node->name) {
        g_string_free(node->name, TRUE);
        node->name = NULL;
    }
    if (node->allow_key) {
        g_string_free(node->allow_key, TRUE);
        node->allow_key = NULL;
    }
    if (node->identify_key){
        g_string_free(node->identify_key, TRUE);
        node->identify_key = NULL;
    }
    if (node->producer) {
        g_string_free(node->producer, TRUE);
        node->producer = NULL;
    }
    if (node->specification) {
        g_string_free(node->specification, TRUE);
        node->specification = NULL;
    }
    if (node->unit) {
        g_string_free(node->unit, TRUE);
        node->unit = NULL;
    }

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
    Medicine *temp = head;
    while(head)
    {


        temp = head;
        head = head->next;
        
        if (temp->name) {
            g_string_free(temp->name, TRUE);
            temp->name = NULL;
        }
        if (temp->allow_key) {
            g_string_free(temp->allow_key, TRUE);
            temp->allow_key = NULL;
        }
        if (temp->identify_key){
            g_string_free(temp->identify_key, TRUE);
            temp->identify_key = NULL;
        }
        if (temp->producer) {
            g_string_free(temp->producer, TRUE);
            temp->producer = NULL;
        }
        if (temp->specification) {
            g_string_free(temp->specification, TRUE);
            temp->specification = NULL;
        }
        if (temp->unit) {
            g_string_free(temp->unit, TRUE);
            temp->unit = NULL;
        }
        temp->hist_head = history_remove_all(temp->hist_head);
        g_free(temp);
    }
    return NULL;
}

Medicine *medicine_remove_by_identify_key(Medicine *head, const gchar *identify_key)
{
    Medicine *temp = head;
    Medicine *pre;

    if(!head)
        return NULL;

    if(temp->identify_key &&
            g_strcmp0(temp->identify_key->str, identify_key) == 0)
    {
        if (temp->name) {
            g_string_free(temp->name, TRUE);
            temp->name = NULL;
        }
        if (temp->allow_key) {
            g_string_free(temp->allow_key, TRUE);
            temp->allow_key = NULL;
        }
        if (temp->identify_key){
            g_string_free(temp->identify_key, TRUE);
            temp->identify_key = NULL;
        }
        if (temp->producer) {
            g_string_free(temp->producer, TRUE);
            temp->producer = NULL;
        }
        if (temp->specification) {
            g_string_free(temp->specification, TRUE);
            temp->specification = NULL;
        }
        if (temp->unit) {
            g_string_free(temp->unit, TRUE);
            temp->unit = NULL;
        }

        head = head->next;
        history_remove_all(temp->hist_head);
        g_free(temp);
        return head;
    }

    pre = temp;
    temp = temp->next;

    while(temp)
    {
        if(temp->identify_key && 
                g_strcmp0(temp->identify_key->str, identify_key) == 0)
        {
            if (temp->name) {
                g_string_free(temp->name, TRUE);
                temp->name = NULL;
            }
            if (temp->allow_key) {
                g_string_free(temp->allow_key, TRUE);
                temp->allow_key = NULL;
            }
            if (temp->identify_key){
                g_string_free(temp->identify_key, TRUE);
                temp->identify_key = NULL;
            }
            if (temp->producer) {
                g_string_free(temp->producer, TRUE);
                temp->producer = NULL;
            }
            if (temp->specification) {
                g_string_free(temp->specification, TRUE);
                temp->specification = NULL;
            }
            if (temp->unit) {
                g_string_free(temp->unit, TRUE);
                temp->unit = NULL;
            }
            pre->next = temp->next;
            temp->hist_head = history_remove_all(temp->hist_head);
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




