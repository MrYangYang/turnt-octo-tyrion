#ifndef _MEDICINE_H_
#define _MEDICINE_H_

#include "my_type.h"
#include "history.h"

typedef struct _Medicine Medicine;

struct _Medicine
{
    GString *name;
    GString *unit;
    gulong quantity;
    GString *specification;
    GString *allow_key;
    GString *identify_key;
    GString *producer;

    struct _Medicine *next;
    History *hist_head;
};

Medicine    *medicine_append_with_data  (Medicine *head,
                                                                 gchar *name,
                                                                 gchar *unit,
                                                                 gulong quantity,
                                                                 gchar *specification,
                                                                 gchar *allow_key,
                                                                 gchar *identify_key,
                                                                 gchar *producer);

Medicine    *medicine_new                       (void);
Medicine    *medicine_append_child         (Medicine *head, Medicine *child);
Medicine    *medicine_get_child_at           (Medicine *head, int index);
Medicine    *medicine_remove                  (Medicine *head, int index);
Medicine    *medicine_remove_all             (Medicine *head);
Medicine    *medicine_remove_by_identify_key        (Medicine *head, const gchar *identify_key);
Medicine    *medicine_get_child_by_identify_key      (Medicine *head, const gchar *identify_key);


#endif // _MEDICINE_H_
