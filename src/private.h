#ifndef _PRIVATE_H_
#define _PRIVATE_H_

#include <gtk/gtk.h>
#include "dispensary.h"
#include "medicine.h"
#include "history.h"
#include "my_type.h"

typedef struct _Private Private;

struct _Private
{
    //main window
    GtkWidget *main_window;

    //medicine operation
    GtkWidget *mdc_in_btn;
    GtkWidget *mdc_out_btn;
    GtkWidget *mdc_search_btn;
    GtkWidget *mdc_new_btn;
    GtkWidget *mdc_remove_btn;
    GtkWidget *mdc_modify_btn;
    GtkWidget *mdc_show_all_btn;
    GtkWidget *mdc_save_btn;

    //medicine_treeview
    GtkListStore *mdc_store;
    GtkWidget *mdc_treeview;
    GtkTreeSelection *mdc_selection;
    GtkTreeIter mdc_iter;

    //dispensary widgets
    GtkListStore *dsp_store;
    GtkWidget *dsp_treeview;
    GtkTreeSelection *dsp_selection;
    GtkTreeIter dsp_iter;
    gboolean is_selected;
    GtkWidget *dsp_new_btn;
    GtkWidget *dsp_modify_btn;
    GtkWidget *dsp_remove_btn;

    //history widgets
    GtkListStore *hist_store;
    GtkWidget *hist_treeview;

    //list variables
    Dispensary *dsp_head;
    Dispensary *dsp_node;
    Medicine *mdc_head;
    Medicine *mdc_node;
    History *hist_head;

    //dispensary operation winow
    GtkWidget *dsp_operation_window;
    gboolean dsp_flag;  //true if the operation is to create a dsp. false if the operation is to modify a dsp
    GtkWidget *dsp_name_entry;
    GtkWidget *dsp_place_entry;
    GtkWidget *dsp_tel_entry;
    GtkWidget *dsp_confirm;
    GtkWidget *dsp_cancel;

    //mdc operation window
    gboolean mdc_flag; // true if the mdc_new_btn clicked, false if the mdc_modify_btn clicked.
    GtkWidget *mdc_opr_window;
    GtkEntry *mdc_name_entry;
    GtkEntry *mdc_unit_entry;
    GtkSpinButton *mdc_quantity_spn_btn;
    GtkEntry *mdc_specification_entry;
    GtkEntry *mdc_allow_key_entry;
    GtkEntry *mdc_identify_key_entry;
    GtkEntry *mdc_producer_entry;
    GtkComboBox *dsp_name_combobox;
    GtkWidget *mdc_confirm_btn;
    GtkWidget *mdc_cancel_btn;

    // in n out window
    GtkWidget *in_n_out_window;
    gboolean *in_n_out_flag; // true if import, false if export
    GtkWidget *mdc_name_label;
    GtkWidget *mdc_identify_key_label;
    GtkWidget *mdc_unit_label;
    GtkSpinButton *mdc_in_n_out_spin_btn;
    GtkWidget *in_n_out_confirm;
    GtkWidget *in_n_out_cancel;

    // search window widgets
    GtkWidget *search_window;
    GtkWidget *sc_dsp_name_combo_entry;
    GtkWidget *sc_dsp_place_entry;
    GtkWidget *sc_dsp_tel_entry;
    GtkWidget *sc_mdc_name_entry;
    GtkWidget *sc_mdc_unit_entry;
    GtkWidget *sc_mdc_specification_entry;
    GtkWidget *sc_mdc_allow_key_entry;
    GtkWidget *sc_mdc_identify_key_entry;
    GtkWidget *sc_mdc_producer_entry;
    GtkWidget *sc_confirm;
    GtkWidget *sc_cancel;

    // menu items
    gboolean need_to_save;
    GtkImageMenuItem *save_item;

    // sort variable
    gboolean sort_state; // TRUE up; FALSE down
    gint sort_column;
    gint sort_store; // 0 for dispensary, 1 for medicine, 2 for history;

    // column head;
    GtkWidget *col_dsp_name;
    GtkWidget *col_dsp_place;
    GtkWidget *col_dsp_tel;

    GtkWidget *col_mdc_dsp;
    GtkWidget *col_mdc_name;
    GtkWidget *col_mdc_unit;
    GtkWidget *col_mdc_quantity;
    GtkWidget *col_mdc_specification;
    GtkWidget *col_mdc_allow_key;
    GtkWidget *col_mdc_identify_key;
    GtkWidget *col_mdc_producer;

    GtkWidget *col_hist_identify_key;
    GtkWidget *col_hist_mdc_name;
    GtkWidget *col_hist_opr;
    GtkWidget *col_hist_amount;
    GtkWidget *col_hist_date;

};

#endif // _PRIVATE_H_
