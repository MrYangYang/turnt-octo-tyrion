#ifndef HISTORY_H_INCLUDED
#define HISTORY_H_INCLUDED

#include "my_type.h"
#include <time.h>

typedef struct _History History;

struct _History
{
    gboolean flag; //true if the operation is import, and false otherwise.
    gulong amount; //how much import (or export).
    GString *date; //the time when operated.
    struct _History *next;
};

History     *history_new_with_data       (History *head, gboolean flag, gulong amount); //when opr the mdc,
History     *history_append_with_data    (History *head, gboolean flag, gulong amount, const gchar *date); //when read data from file.
History     *history_new                 (void);
History     *history_append_child        (History *head, History *child);
History     *history_get_child_at        (History *head, int index);
History     *history_remove              (History *head, int index);
History     *history_remove_all          (History *head);

#endif // HISTORY_H_INCLUDED
