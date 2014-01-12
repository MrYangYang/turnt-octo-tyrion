#ifndef _DISPENSARY_H_
#define _DISPENSARY_H_
#include "my_type.h"
#include "medicine.h"
#include <gtk/gtk.h>

struct _Dispensary
{
    int id;
    GString *name;
    GString *place;
    GString *tel;
    struct _Dispensary *next;
    Medicine *mdc_head;
};

typedef struct _Dispensary Dispensary;


/*********************************************************
*    与链表有关的函数，返回值大多数都是表头地址，每次
*    使用后，都要使链表表头指向函数返回值
*********************************************************/

Dispensary        *dispensary_new                          (void);
Dispensary        *dispensary_new_with_data                (Dispensary *head, gchar *name, gchar *place, gchar *tel);
Dispensary        *dispensary_append_child                 (Dispensary *head, Dispensary *child);
Dispensary        *dispensary_get_child_at                 (Dispensary *head, int index);
Dispensary        *dispensary_replace_with                 (Dispensary *head, int index, Dispensary *new_node);
Dispensary        *dispensary_remove                       (Dispensary *head, int index);
Dispensary        *dispensary_remove_all                   (Dispensary *head);
Dispensary        *dispensary_get_child_by_id              (Dispensary *head, int id);
Dispensary        *dispensary_remove_by_id                 (Dispensary *head, int id);
Dispensary        *dispensary_append_with_data             (Dispensary *head,  gchar *name, gchar *place, gchar *tel, gint id);

#endif
