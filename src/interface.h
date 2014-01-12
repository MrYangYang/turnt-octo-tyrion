#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

#include "private.h"
#define MAIN_UI_FILE "window_main.ui"
#define DSP_UI_FILE "dsp_operation.ui"
#define MDC_UI_FILE "mdc_operation.ui"
#define MDC_IN_N_OUT_UI_FILE "mdc_in_n_out.ui"
#define SEARCH_WINDOW_UI "search_window.ui"

void        create_main_window              (Private *prv);
void        create_dsp_operation_window     (Private *prv);
void        create_mdc_operation_window     (Private *prv);
void        dsp_notify_data_set_changed     (Private *prv, Dispensary *dsp_head);
void        hist_notify_data_set_changed    (Private *prv, Medicine *node);
void        create_mdc_in_n_out_window      (Private *prv);
void        create_search_window            (Private *prv);
gint        mdc_sort                        (GtkTreeModel *model, GtkTreeIter *current, GtkTreeIter *next, Private *prv);
gint        string_sort                     (GtkTreeModel *model, GtkTreeIter *current, GtkTreeIter *next, Private *prv);


#endif // _USER_INTERFACE_H_
