#include "callbacks.h"
#include "private.h"
#include "data_io.h"
#include "dispensary.h"
#include "history.h"
#include "interface.h"
#include "medicine.h"
#include "my_type.h"


void dsp_new_btn_handle(GtkWidget *widget, Private *prv)
{
    prv->dsp_flag = true;
    create_dsp_operation_window(prv);
}

void dsp_cancel_btn_handle(GtkWidget *widget , Private *prv)
{
    gtk_widget_destroy(prv->dsp_operation_window);
}

void dsp_confirm_btn_handle (GtkWidget *widget, Private *prv)
{
    const gchar *name = gtk_entry_get_text(GTK_ENTRY(prv->dsp_name_entry));
    const gchar *place = gtk_entry_get_text(GTK_ENTRY(prv->dsp_place_entry));
    const gchar *tel = gtk_entry_get_text(GTK_ENTRY(prv->dsp_tel_entry));

    if(!(*name) || !(*place) || !(*tel) )
        return;

   if(prv->dsp_flag)
   {
        prv->dsp_head = dispensary_new_with_data(prv->dsp_head, name, place, tel);
        dsp_notify_data_set_changed(prv, prv->dsp_head);
        dsp_cancel_btn_handle(widget, prv);
   }
   else
   {
        int id = 0;
        gtk_tree_model_get(prv->dsp_store, &(prv->dsp_iter), 3, &id, -1);
        Dispensary *node = dispensary_get_child_by_id(prv->dsp_head, id);
        g_string_free(node->name, true);
        g_string_free(node->place, true);
        g_string_free(node->tel, true);
        node->name = g_string_new(name);
        node->place = g_string_new(place);
        node->tel = g_string_new(tel);
        dsp_notify_data_set_changed(prv, prv->dsp_head);
        dsp_cancel_btn_handle(widget, prv);
   }
}

void dsp_modify_btn_handle(GtkWidget *widget, Private *prv)
{
    prv->dsp_flag = false;
    prv->is_selected = gtk_tree_selection_get_selected(prv->dsp_selection, &(prv->dsp_store), &(prv->dsp_iter));
    create_dsp_operation_window(prv);
}

void dsp_remove_btn_handle(GtkWidget *widget, Private *prv)
{
    prv->is_selected = gtk_tree_selection_get_selected(prv->dsp_selection, &(prv->dsp_store), &(prv->dsp_iter));
    if(!prv->is_selected)
        return;

    int id;
    gtk_tree_model_get(prv->dsp_store, &(prv->dsp_iter), 3, &id, -1);
    prv->dsp_head = dispensary_remove_by_id(prv->dsp_head, id);
    gtk_list_store_remove(prv->dsp_store, &(prv->dsp_iter));
    dsp_notify_data_set_changed(prv, prv->dsp_head);
}

void mdc_new_btn_handle(GtkWidget *widget, Private *prv)
{
    prv->mdc_flag = true;
    create_mdc_operation_window(prv);
}

void mdc_cancel_btn_handle(GtkWidget *widget, Private *prv)
{
    gtk_widget_destroy(prv->mdc_opr_window);
}


void mdc_confirm_btn_handle (GtkWidget *widget, Private *prv)
{
    const gchar *name = gtk_entry_get_text(prv->mdc_name_entry);
    const gchar *unit = gtk_entry_get_text(prv->mdc_unit_entry);
    gulong quantity = (gulong) gtk_spin_button_get_value(prv->mdc_quantity_spn_btn);
    const gchar *specification = gtk_entry_get_text(prv->mdc_specification_entry);
    const gchar *allow_key = gtk_entry_get_text(prv->mdc_allow_key_entry);

    //remove the space key of the string.
    gchar *str_temp = gtk_entry_get_text(prv->mdc_identify_key_entry);
    const gchar *identify_key = m_str_rm_space(str_temp);

    const gchar *producer = gtk_entry_get_text(prv->mdc_producer_entry);
    gboolean flag ;
    int id;

    if(! prv->mdc_flag)
    {
        flag = true;
        gtk_tree_model_get(GTK_TREE_MODEL(prv->mdc_store), &(prv->mdc_iter), 8, &id, -1);
        g_print("id ----> on modify %d \n",id);
    }
    else
    {
        flag = gtk_combo_box_get_active_iter(prv->dsp_name_combobox, &(prv->dsp_iter));

    }
    // return when not all the info was given.
    if( !(*name) || !(*unit) || !quantity || !(*specification) || !(*allow_key) || !(*identify_key) || !(*producer) || !(flag) )
        return;
    if(prv->mdc_flag)
    {
        gtk_tree_model_get(GTK_TREE_MODEL(prv->dsp_store), &(prv->dsp_iter), 3, &id, -1);
    }
    prv->dsp_node = dispensary_get_child_by_id(prv->dsp_head, id);

    if(prv->mdc_flag)
    {
        if (medicine_get_child_by_identify_key(prv->dsp_node->mdc_head, identify_key))
            return;

        prv->dsp_node->mdc_head = medicine_append_with_data(prv->dsp_node->mdc_head,
                                                                                                    name,
                                                                                                    unit,
                                                                                                    quantity,
                                                                                                    specification,
                                                                                                    allow_key,
                                                                                                    identify_key,
                                                                                                    producer);
        prv->mdc_node = medicine_get_child_by_identify_key(prv->dsp_node->mdc_head, identify_key);
        prv->mdc_node->hist_head = history_new_with_data(prv->mdc_node->hist_head,
                                                                                                 true,
                                                                                                 quantity);
        gtk_list_store_append(prv->mdc_store, &(prv->mdc_iter));

        gtk_list_store_set(prv->mdc_store, &(prv->mdc_iter),
                                   0, prv->dsp_node->name->str,
                                   1, name,
                                   2, unit,
                                   3, quantity,
                                   4, specification,
                                   5, allow_key,
                                   6, identify_key,
                                   7, producer,
                                   8, id, -1);
        gtk_tree_selection_select_iter(prv->dsp_selection, &(prv->dsp_iter));
        gtk_tree_selection_select_iter(prv->mdc_selection, &(prv->mdc_iter));
    }
    else
    {
        prv->mdc_node = medicine_get_child_by_identify_key(prv->dsp_node->mdc_head, identify_key);
        g_string_free(prv->mdc_node->name, true);
        g_string_free(prv->mdc_node->unit, true);
        g_string_free(prv->mdc_node->specification, true);
        g_string_free(prv->mdc_node->allow_key, true);
        g_string_free(prv->mdc_node->producer, true);

        prv->mdc_node->name = g_string_new(name);
        prv->mdc_node->unit = g_string_new(unit);
        prv->mdc_node->specification = g_string_new(specification);
        prv->mdc_node->allow_key = g_string_new(allow_key);
        prv->mdc_node->producer = g_string_new(producer);

        gtk_list_store_set(prv->mdc_store, &(prv->mdc_iter),
                                   1, name,
                                   2, unit,
                                   4, specification,
                                   5, allow_key,
                                   7,producer, -1);
        hist_notify_data_set_changed(prv, prv->mdc_node);
    }

    mdc_cancel_btn_handle(widget, prv);
}

void mdc_modify_btn_handle (GtkWidget *widget, Private *prv)
{
    prv->mdc_flag = false;
    create_mdc_operation_window(prv);
}

void mdc_remove_btn_handle (GtkWidget *widget, Private *prv)
{
    gboolean flag = gtk_tree_selection_get_selected(prv->mdc_selection, &(prv->mdc_store), &(prv->mdc_iter));
    if( !flag )
        return;

    int id;
    GString identify_key;
    gtk_tree_model_get(GTK_TREE_MODEL(prv->mdc_store), &(prv->mdc_iter),
                                   6, &identify_key,
                                   8, &id, -1);
    g_print("id ---> reload : %d \n", id);
    Dispensary *node = dispensary_get_child_by_id(prv->dsp_head, id);
    prv->mdc_node = medicine_get_child_by_identify_key(node->mdc_head,  identify_key.str);
    prv->mdc_node->hist_head = history_remove_all(prv->mdc_node->hist_head);
    node->mdc_head = medicine_remove_by_identify_key(node->mdc_head,  identify_key.str);
    gtk_list_store_remove(prv->mdc_store, &(prv->mdc_iter));
}

void mdc_in_btn_handle (GtkWidget *widget, Private *prv)
{
    prv->in_n_out_flag = true;
    create_mdc_in_n_out_window(prv);
}

void in_n_out_btn_cancel_handle (GtkWidget *widget, Private *prv)
{
    gtk_widget_destroy(prv->in_n_out_window);
    return;
}

void in_n_out_btn_confirm_handle (GtkWidget *widget, Private *prv)
{
    gulong quantity;
    GString identify_key;
    int id;

    gtk_tree_model_get(GTK_TREE_MODEL(prv->mdc_store), &(prv->mdc_iter),
                                    3, &quantity,
                                    6, &identify_key,
                                    8, &id , -1);

    g_print("id -----------> on in %d \n", id);

    gulong add = (gulong) gtk_spin_button_get_value(prv->mdc_in_n_out_spin_btn);
    prv->dsp_node = dispensary_get_child_by_id(prv->dsp_head, id);
    prv->mdc_node = medicine_get_child_by_identify_key(prv->dsp_node->mdc_head, identify_key.str);
    if(prv->in_n_out_flag)
    {
        quantity += add;
        prv->mdc_node->hist_head = history_new_with_data(prv->mdc_node->hist_head,
                                                         true,
                                                         add);
    }
    else
    {
        quantity -= add;
        prv->mdc_node->hist_head = history_new_with_data(prv->mdc_node->hist_head,
                                                         false,
                                                         add);
    }
    prv->mdc_node->quantity  = quantity;
    gtk_list_store_set(prv->mdc_store, &(prv->mdc_iter),
                               3, quantity, -1);
    gtk_tree_selection_select_iter(prv->mdc_selection, &(prv->mdc_iter));
    hist_notify_data_set_changed(prv, prv->mdc_node);
    in_n_out_btn_cancel_handle(widget, prv);
}

void mdc_out_btn_handle(GtkWidget *widget, Private *prv)
{
    prv->in_n_out_flag = false;
    create_mdc_in_n_out_window(prv);
}

void mdc_selected_changed_handle (GtkWidget *widget, Private *prv)
{
    GtkTreeIter iter;
    GString identify_key;
    int id;
    gboolean valid = gtk_tree_selection_get_selected(prv->mdc_selection, &(prv->mdc_store), &iter);
    if (!valid)
    {
        gtk_list_store_clear(prv->hist_store);
        return;
    }
    gtk_tree_model_get(GTK_TREE_MODEL(prv->mdc_store), &iter,
                                   6, &identify_key,
                                   8, &id, -1);
    prv->dsp_node = dispensary_get_child_by_id(prv->dsp_head, id);
    prv->mdc_node = medicine_get_child_by_identify_key(prv->dsp_node->mdc_head, identify_key.str);
    hist_notify_data_set_changed(prv, prv->mdc_node);
}

void menu_save_handle(GtkWidget *widget, Private *prv)
{
    g_print("save handle %o \n", prv->dsp_head);
    save_data(prv->dsp_head);
}

void sc_cancel_button_handle(GtkWidget *widget, Private *prv)
{
    gtk_widget_destroy(prv->search_window);
    return;
}

void mdc_search_btn_handle(GtkWidget *widget, Private *prv)
{
    create_search_window(prv);
    return;
}

void sc_confirm_button_handle(GtkWidget *widget, Private *prv)
{
    gchar *dsp_name = gtk_entry_get_text(prv->sc_dsp_name_combo_entry);
    gchar *dsp_place = gtk_entry_get_text(prv->sc_dsp_place_entry);
    gchar *dsp_tel = gtk_entry_get_text(prv->sc_dsp_tel_entry);
    gchar *mdc_name = gtk_entry_get_text(prv->sc_mdc_name_entry);
    gchar *mdc_unit = gtk_entry_get_text(prv->sc_mdc_unit_entry);
    gchar *mdc_specification = gtk_entry_get_text(prv->sc_mdc_specification_entry);
    gchar *mdc_allow_key = gtk_entry_get_text(prv->sc_mdc_allow_key_entry);
    gchar *mdc_identify_key = gtk_entry_get_text(prv->sc_mdc_identify_key_entry);
    gchar *mdc_producer = gtk_entry_get_text(prv->sc_mdc_producer_entry);

    Dispensary *dsp = prv->dsp_head;
    Medicine *mdc;
    GtkTreeIter iter;

    gtk_list_store_clear(prv->mdc_store);
    gtk_list_store_clear(prv->hist_store);

    while(dsp)
    {
        if( m_strstr(dsp->name->str, dsp_name) && m_strstr(dsp->place->str, dsp_place) && m_strstr(dsp->tel->str, dsp_tel))
        {
            mdc = dsp->mdc_head;
            while ( mdc )
            {
                if ( m_strstr(mdc->name->str, mdc_name) &&
                     m_strstr(mdc->unit->str, mdc_unit) &&
                     m_strstr(mdc->specification->str, mdc_specification) &&
                     m_strstr(mdc->allow_key->str, mdc_allow_key) &&
                     m_strstr(mdc->identify_key->str, mdc_identify_key) &&
                     m_strstr(mdc->producer->str, mdc_producer)
                   )
                {
                    gtk_list_store_append(prv->mdc_store, &iter);
                    gtk_list_store_set(prv->mdc_store, &iter,
                                        0, dsp->name->str,
                                        1, mdc->name->str,
                                        2, mdc->unit->str,
                                        3, mdc->quantity,
                                        4, mdc->specification->str,
                                        5, mdc->allow_key->str,
                                        6, mdc->identify_key->str,
                                        7, mdc->producer->str,
                                        8, dsp->id, -1);
                }
                mdc = mdc->next;
            }
        }
        dsp = dsp->next;
    }
    sc_cancel_button_handle(widget, prv);
}

void col_mdc_name_handle (GtkWidget *widget, Private *prv)
{
    prv->sort_column = 1;
    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(prv->mdc_store),1, prv->sort_state);
    prv->sort_state = !(prv->sort_state);
}

void col_mdc_dsp_name_handle (GtkWidget *widget, Private *prv)
{
    prv->sort_column = 0;
    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(prv->mdc_store),0, prv->sort_state);
    prv->sort_state = !(prv->sort_state);
}

void col_mdc_unit_handle (GtkWidget *widget, Private *prv)
{
    prv->sort_column = 2;
    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(prv->mdc_store),2, prv->sort_state);
    prv->sort_state = !(prv->sort_state);
}

void col_mdc_quantity_handle (GtkWidget *widget, Private *prv)
{
    prv->sort_column = 3;
    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(prv->mdc_store),3, prv->sort_state);
    prv->sort_state = !(prv->sort_state);
}

void col_mdc_specification_handle (GtkWidget *widget, Private *prv)
{
    prv->sort_column = 4;
    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(prv->mdc_store),4, prv->sort_state);
    prv->sort_state = !(prv->sort_state);
}

void col_mdc_allow_key_handle (GtkWidget *widget, Private *prv)
{
    prv->sort_column = 5;
    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(prv->mdc_store),5, prv->sort_state);
    prv->sort_state = !(prv->sort_state);
}

void col_mdc_identify_key_handle (GtkWidget *widget, Private *prv)
{
    prv->sort_column = 6;
    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(prv->mdc_store),6, prv->sort_state);
    prv->sort_state = !(prv->sort_state);
}

void col_mdc_producer_handle (GtkWidget *widget, Private *prv)
{
    prv->sort_column = 7;
    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(prv->mdc_store),7, prv->sort_state);
    prv->sort_state = !(prv->sort_state);
}

void col_dsp_name_handle (GtkWidget *widget, Private *prv)
{
    prv->sort_column = 0;
    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(prv->dsp_store),0, prv->sort_state);
    prv->sort_state = !(prv->sort_state);
}

void col_dsp_place_handle (GtkWidget *widget, Private *prv)
{
    prv->sort_column = 1;
    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(prv->dsp_store),1, prv->sort_state);
    prv->sort_state = !(prv->sort_state);
}

void col_dsp_tel_handle (GtkWidget *widget, Private *prv)
{
    prv->sort_column = 2;
    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(prv->dsp_store),2, prv->sort_state);
    prv->sort_state = !(prv->sort_state);
}

void col_hist_identify_key_handle (GtkWidget *widget, Private *prv)
{
    prv->sort_column = 0;
    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(prv->hist_store),0, prv->sort_state);
    prv->sort_state = !(prv->sort_state);
}

void col_hist_mdc_name_handle (GtkWidget *widget, Private *prv)
{
    prv->sort_column = 1;
    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(prv->hist_store),1, prv->sort_state);
    prv->sort_state = !(prv->sort_state);
}

void col_hist_opr_handle (GtkWidget *widget, Private *prv)
{
    prv->sort_column = 2;
    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(prv->hist_store),2, prv->sort_state);
    prv->sort_state = !(prv->sort_state);
}

void col_hist_amount_handle (GtkWidget *widget, Private *prv)
{
    prv->sort_column = 3;
    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(prv->hist_store),3, prv->sort_state);
    prv->sort_state = !(prv->sort_state);
}

void col_hist_date_handle (GtkWidget *widget, Private *prv)
{
    prv->sort_column = 4;
    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(prv->hist_store),4, prv->sort_state);
    prv->sort_state = !(prv->sort_state);
}

void mdc_show_all_handle(GtkWidget *widget, Private *prv)
{
    dsp_notify_data_set_changed(prv, prv->dsp_head);
}

void mdc_save_handle(GtkWidget *widget, Private *prv)
{
    save_data(prv->dsp_head);
}

void dsp_show_my_mdc  (GtkWidget *widget, Private *prv)
{
    gint id;
    GString identify_key;
    GtkTreeIter iter;
    gboolean check = gtk_tree_selection_get_selected(prv->dsp_selection, &(prv->dsp_store), &iter);
    if(!check)
        return;

    gtk_tree_model_get(GTK_TREE_MODEL(prv->dsp_store), &iter, 3, &id , -1);
    g_print("get selected id ---> %d\n", id);
    Dispensary *node = dispensary_get_child_by_id(prv->dsp_head, id);
    Medicine *head = node->mdc_head;

    gtk_list_store_clear(prv->mdc_store);


    while(head)
    {
        gtk_list_store_append(prv->mdc_store, &iter);
        gtk_list_store_set(prv->mdc_store,
                           &iter,
                           0,node->name->str,
                           1,head->name->str,
                           2,head->unit->str,
                           3,head->quantity,
                           4,head->specification->str,
                           5,head->allow_key->str,
                           6,head->identify_key->str,
                           7,head->producer->str,
                           8,node->id,
                           -1 );
        head = head -> next;
    }

    gboolean flag = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(prv->mdc_store), &iter);

    if(!flag)
        return;

    gtk_tree_selection_select_iter(prv->mdc_selection, &iter);

    gtk_tree_model_get(GTK_TREE_MODEL(prv->mdc_store), &iter, 6, &identify_key, 8, &id , -1);
    Dispensary *dsp = dispensary_get_child_by_id(prv->dsp_head, id);
    Medicine *mdc = medicine_get_child_by_identify_key(dsp->mdc_head, identify_key.str);
    hist_notify_data_set_changed(prv,mdc);
}




