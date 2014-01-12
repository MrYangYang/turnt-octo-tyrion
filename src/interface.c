#include "interface.h"
#include <gtk/gtk.h>
#include "private.h"
#include "my_type.h"
#include "callbacks.h"
void  create_main_window (Private *prv)
{
    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;

    gboolean is_complete = gtk_builder_add_from_file(builder, MAIN_UI_FILE, &error);
    if(!is_complete)
    {
        g_print("the ui file is not complete. program force quit!\n");
        return;
    }

    //main window
    prv->main_window = (GtkWidget *)gtk_builder_get_object(builder, "window1");

    //medicine operation
    prv->mdc_in_btn = (GtkWidget *)gtk_builder_get_object(builder, "button1");
    prv->mdc_out_btn = (GtkWidget *)gtk_builder_get_object(builder, "button2");
    prv->mdc_search_btn = (GtkWidget *)gtk_builder_get_object (builder, "search_button");
    prv->mdc_new_btn = (GtkWidget *)gtk_builder_get_object(builder, "button3");
    prv->mdc_modify_btn = (GtkWidget *)gtk_builder_get_object(builder, "button4");
    prv->mdc_remove_btn = (GtkWidget *)gtk_builder_get_object(builder, "button5");
    prv->mdc_show_all_btn = (GtkWidget *)gtk_builder_get_object(builder, "button9");
    prv->mdc_save_btn = (GtkWidget *)gtk_builder_get_object(builder, "button10");

    //medicine_treeview
    prv->mdc_store = GTK_LIST_STORE(gtk_builder_get_object (builder, "mdc_store"));
    prv->mdc_treeview = (GtkWidget *)gtk_builder_get_object(builder, "mdc_treeview");
    prv->mdc_selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(prv->mdc_treeview));
    gtk_tree_sortable_set_default_sort_func( GTK_TREE_SORTABLE(prv->mdc_store),
                                             mdc_sort,
                                             prv,
                                             prv);

    //dispensary widgets
    prv->dsp_store = GTK_LIST_STORE(gtk_builder_get_object(builder, "dsp_store"));
    prv->dsp_treeview = (GtkWidget *)gtk_builder_get_object(builder, "treeview2");
    prv->dsp_new_btn = (GtkWidget *)gtk_builder_get_object(builder, "button6");
    prv->dsp_modify_btn = (GtkWidget *)gtk_builder_get_object(builder, "button7");
    prv->dsp_remove_btn = (GtkWidget *)gtk_builder_get_object(builder, "button8");
    prv->dsp_selection= gtk_tree_view_get_selection(GTK_TREE_VIEW(prv->dsp_treeview));
    gtk_tree_sortable_set_default_sort_func(GTK_TREE_SORTABLE(prv->dsp_store),
                                            string_sort,
                                            prv,
                                            prv);

    //history widgets
    prv->hist_store = GTK_LIST_STORE(gtk_builder_get_object(builder, "hsty_store"));
    prv->hist_treeview = (GtkWidget *)gtk_builder_get_object(builder, "treeview1");
    gtk_tree_sortable_set_default_sort_func(GTK_TREE_SORTABLE(prv->hist_store),
                                            string_sort,
                                            prv,
                                            prv);

    // menu items
    prv->need_to_save = false;
    prv->save_item = (GtkImageMenuItem *)gtk_builder_get_object(builder, "imagemenuitem3");

    // colums
    prv->col_dsp_name = (GtkWidget *)gtk_builder_get_object(builder, "treeviewcolumn10");
    prv->col_dsp_place = (GtkWidget *)gtk_builder_get_object(builder, "treeviewcolumn11");
    prv->col_dsp_tel = (GtkWidget *)gtk_builder_get_object(builder, "treeviewcolumn12");

    prv->col_mdc_dsp = (GtkWidget *)gtk_builder_get_object(builder, "treeviewcolumn1");
    prv->col_mdc_name = (GtkWidget *)gtk_builder_get_object(builder, "treeviewcolumn2");
    prv->col_mdc_unit = (GtkWidget *)gtk_builder_get_object(builder, "treeviewcolumn3");
    prv->col_mdc_quantity = (GtkWidget *) gtk_builder_get_object(builder, "treeviewcolumn4");
    prv->col_mdc_specification = (GtkWidget *)gtk_builder_get_object(builder, "treeviewcolumn5");
    prv->col_mdc_allow_key = (GtkWidget *)gtk_builder_get_object(builder, "treeviewcolumn6");
    prv->col_mdc_identify_key = (GtkWidget *)gtk_builder_get_object(builder, "treeviewcolumn7");
    prv->col_mdc_producer = (GtkWidget *)gtk_builder_get_object(builder, "treeviewcolumn8");

    prv->col_hist_identify_key = (GtkWidget *)gtk_builder_get_object(builder, "treeviewcolumn13");
    prv->col_hist_mdc_name = (GtkWidget *)gtk_builder_get_object(builder, "treeviewcolumn14");
    prv->col_hist_opr = (GtkWidget *)gtk_builder_get_object(builder, "treeviewcolumn15");
    prv->col_hist_amount = (GtkWidget *)gtk_builder_get_object(builder, "treeviewcolumn16");
    prv->col_hist_date = (GtkWidget *)gtk_builder_get_object(builder, "treeviewcolumn17");


    // connect the sort function;
    g_signal_connect(prv->col_mdc_name,"clicked", G_CALLBACK(col_mdc_name_handle), prv);
    g_signal_connect(prv->col_mdc_dsp, "clicked", G_CALLBACK(col_mdc_dsp_name_handle), prv);
    g_signal_connect(prv->col_mdc_unit, "clicked", G_CALLBACK(col_mdc_unit_handle), prv);
    g_signal_connect(prv->col_mdc_quantity, "clicked", G_CALLBACK(col_mdc_quantity_handle),prv);
    g_signal_connect(prv->col_mdc_specification, "clicked", G_CALLBACK(col_mdc_specification_handle), prv);
    g_signal_connect(prv->col_mdc_allow_key, "clicked", G_CALLBACK(col_mdc_allow_key_handle),prv);
    g_signal_connect(prv->col_mdc_identify_key, "clicked", G_CALLBACK(col_mdc_identify_key_handle), prv);
    g_signal_connect(prv->col_mdc_producer,"clicked", G_CALLBACK(col_mdc_producer_handle), prv);

    g_signal_connect(prv->col_dsp_name,"clicked", G_CALLBACK(col_dsp_name_handle), prv);
    g_signal_connect(prv->col_dsp_place,"clicked", G_CALLBACK(col_dsp_place_handle), prv);
    g_signal_connect(prv->col_dsp_tel,"clicked", G_CALLBACK(col_dsp_tel_handle), prv);

    g_signal_connect(prv->col_hist_identify_key, "clicked", G_CALLBACK(col_hist_identify_key_handle), prv);
    g_signal_connect(prv->col_hist_mdc_name, "clicked", G_CALLBACK(col_hist_mdc_name_handle), prv);
    g_signal_connect(prv->col_hist_opr, "clicked", G_CALLBACK(col_hist_opr_handle), prv);
    g_signal_connect(prv->col_hist_amount, "clicked", G_CALLBACK(col_hist_amount_handle), prv);
    g_signal_connect(prv->col_hist_date, "clicked", G_CALLBACK(col_hist_date_handle), prv);

    g_print("before --------------> %o\n", prv->dsp_head);
    prv->dsp_head = read_data();
    g_print("after ----------------->%o\n", prv->dsp_head);
    if(prv->dsp_head)
        dsp_notify_data_set_changed(prv, prv->dsp_head);

}

void create_dsp_operation_window    (Private *prv)
{
    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;
    gboolean check = gtk_builder_add_from_file(builder, DSP_UI_FILE , &error);

    if(!check)
    {
        g_print("the file dsp_operation.ui is not exist or broken! program force quit!\n");
        return ;
    }

    prv->dsp_operation_window = (GtkWidget *)gtk_builder_get_object(builder, "window1");
    prv->dsp_name_entry = (GtkWidget *)gtk_builder_get_object(builder, "entry1");
    prv->dsp_place_entry = (GtkWidget *)gtk_builder_get_object(builder, "entry2");
    prv->dsp_tel_entry = (GtkWidget *)gtk_builder_get_object (builder, "entry3");
    prv->dsp_confirm = (GtkWidget *)gtk_builder_get_object (builder, "button1");
    prv->dsp_cancel = (GtkWidget *)gtk_builder_get_object (builder , "button2");

    g_signal_connect(prv->dsp_cancel, "clicked", G_CALLBACK(dsp_cancel_btn_handle), prv);
    g_signal_connect(prv->dsp_confirm, "clicked", G_CALLBACK(dsp_confirm_btn_handle),prv);

    if (prv->dsp_flag)
        gtk_window_set_title(GTK_WINDOW(prv->dsp_operation_window), "新建药房");
    else
    {
        if(!prv->is_selected)
            return;

        gtk_window_set_title(GTK_WINDOW(prv->dsp_operation_window), "修改药房");
        GString name;
        GString place;
        GString tel;
        gtk_tree_model_get(prv->dsp_store,&(prv->dsp_iter), 0 , &name, 1, &place, 2, &tel, -1);

        gtk_entry_set_text(GTK_ENTRY(prv->dsp_name_entry), name.str);
        gtk_entry_set_text(GTK_ENTRY(prv->dsp_place_entry), place.str);
        gtk_entry_set_text(GTK_ENTRY(prv->dsp_tel_entry), tel.str);

    }

    gtk_window_set_position(GTK_WINDOW(prv->dsp_operation_window), GTK_WIN_POS_CENTER);
    gtk_widget_show_all(prv->dsp_operation_window);
}

void dsp_notify_data_set_changed(Private *prv, Dispensary *dsp_head)
{
    gtk_list_store_clear(prv->dsp_store);
    gtk_list_store_clear(prv->mdc_store);
    GtkTreeIter iter;
    GtkTreeIter mdc_iter;
    Medicine *mdc_head;
    gboolean valid;

    if(!dsp_head)
        return;

    do
    {
        gtk_list_store_append(prv->dsp_store,&iter);
        gtk_list_store_set(prv->dsp_store, &iter,
                           0, dsp_head->name->str,
                           1, dsp_head->place->str,
                           2, dsp_head->tel->str,
                           3, dsp_head->id, -1);

        mdc_head = dsp_head->mdc_head;
        while(mdc_head)
        {
                gtk_list_store_append(prv->mdc_store, &mdc_iter);
                gtk_list_store_set( prv->mdc_store, &mdc_iter,
                                    0, dsp_head->name->str,
                                    1, mdc_head->name->str,
                                    2, mdc_head->unit->str,
                                    3, mdc_head->quantity,
                                    4, mdc_head->specification->str,
                                    5, mdc_head->allow_key->str,
                                    6, mdc_head->identify_key->str,
                                    7, mdc_head->producer->str,
                                    8, dsp_head->id, -1);
                mdc_head = mdc_head->next;
        }
        dsp_head = dsp_head->next;
    }while(dsp_head != NULL);

    valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(prv->mdc_store), &mdc_iter);
    if( !valid )
    {
        gtk_list_store_clear(prv->hist_store);
        return;
    }

    gtk_tree_selection_select_iter(prv->mdc_selection, &mdc_iter);
    int id;
    GString identify_key;
    gtk_tree_model_get(GTK_TREE_MODEL(prv->mdc_store), &(mdc_iter),
                                   6, &identify_key,
                                   8, &id, -1);
    Dispensary *dsp_node = dispensary_get_child_by_id(prv->dsp_head, id);
    Medicine *mdc_node = medicine_get_child_by_identify_key(dsp_node->mdc_head, identify_key.str);
    hist_notify_data_set_changed(prv, mdc_node);
}

void create_mdc_operation_window(Private *prv)
{
    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;
    gboolean flag = gtk_builder_add_from_file(builder, MDC_UI_FILE, &error);

    if ( !flag )
    {
        g_print("the file 'mdc_operation.ui' is not exist or broken! \n");
        return;
    }

    prv->mdc_opr_window = (GtkWidget *)gtk_builder_get_object(builder, "window1");
    prv->mdc_name_entry = (GtkEntry *)gtk_builder_get_object(builder, "entry1");
    prv->mdc_unit_entry = (GtkEntry *)gtk_builder_get_object(builder, "entry2");
    prv->mdc_quantity_spn_btn = (GtkSpinButton *)gtk_builder_get_object(builder, "spinbutton1");
    prv->mdc_specification_entry = (GtkEntry *)gtk_builder_get_object(builder, "entry4");
    prv->mdc_allow_key_entry = (GtkEntry *)gtk_builder_get_object(builder, "entry5");
    prv->mdc_identify_key_entry = (GtkEntry *)gtk_builder_get_object(builder, "entry6");
    prv->mdc_producer_entry = (GtkEntry *)gtk_builder_get_object(builder, "entry7");
    prv->dsp_name_combobox = (GtkComboBox *)gtk_builder_get_object(builder, "combobox1");
    prv->mdc_confirm_btn = (GtkWidget *)gtk_builder_get_object(builder, "button1");
    prv->mdc_cancel_btn = (GtkWidget *)gtk_builder_get_object(builder, "button2");

    GtkWidget *mdc_identify_key_label = (GtkWidget *)gtk_builder_get_object(builder, "label6");
    GtkWidget *dsp_name_label =(GtkWidget *)gtk_builder_get_object(builder, "label8");
    GtkWidget *mdc_quantity_label = (GtkWidget *)gtk_builder_get_object(builder, "label3");


    // set the model of the dsp_name_combo_box
    GtkTreeModel *model = gtk_tree_view_get_model(prv->dsp_treeview);
    gtk_combo_box_set_model(prv->dsp_name_combobox, model);
    gtk_combo_box_set_column_span_column(prv->dsp_name_combobox, 0);

    g_signal_connect(prv->mdc_confirm_btn, "clicked", G_CALLBACK(mdc_confirm_btn_handle), prv);
    g_signal_connect(prv->mdc_cancel_btn, "clicked", G_CALLBACK(mdc_cancel_btn_handle),prv);

    if(prv->mdc_flag)
    {
        gtk_window_set_title(GTK_WINDOW(prv->mdc_opr_window), "新增药品");
    }
    else
    {
        gtk_window_set_title(GTK_WINDOW(prv->mdc_opr_window), "修改药品");
        prv->is_selected = gtk_tree_selection_get_selected(prv->mdc_selection, &(prv->mdc_store), &(prv->mdc_iter));

        if(!prv->is_selected)
        {
            gtk_widget_destroy(prv->mdc_opr_window);
            return;
        }

        GString mdc_name;
        GString mdc_unit;
        gulong mdc_quantity;
        GString mdc_specification;
        GString mdc_allow_key;
        GString mdc_identify_key;
        GString mdc_producer;

        gtk_tree_model_get(GTK_TREE_MODEL(prv->mdc_store), &(prv->mdc_iter),
                           1, &mdc_name,
                           2, &mdc_unit,
                           3, &mdc_quantity,
                           4, &mdc_specification,
                           5, &mdc_allow_key,
                           6, &mdc_identify_key,
                           7, &mdc_producer,
                           -1);

        gtk_combo_box_set_active_iter(prv->dsp_name_combobox, &(prv->dsp_iter));
        gtk_entry_set_text(prv->mdc_name_entry, mdc_name.str);
        gtk_entry_set_text(prv->mdc_unit_entry, mdc_unit.str);
        gtk_spin_button_set_value(prv->mdc_quantity_spn_btn, (gdouble)mdc_quantity);
        gtk_entry_set_text(prv->mdc_specification_entry, mdc_specification.str);
        gtk_entry_set_text(prv->mdc_allow_key_entry, mdc_allow_key.str);
        gtk_entry_set_text(prv->mdc_identify_key_entry, mdc_identify_key.str);
        gtk_entry_set_text(prv->mdc_producer_entry, mdc_producer.str);

        // hide some info that users should not modify.
        gtk_widget_hide(prv->mdc_identify_key_entry);
        gtk_widget_hide(prv->dsp_name_combobox);
        gtk_widget_hide(prv->mdc_quantity_spn_btn);
        gtk_widget_hide(mdc_quantity_label);
        gtk_widget_hide(mdc_identify_key_label);
        gtk_widget_hide(dsp_name_label);
    }

    gtk_window_set_position(GTK_WINDOW(prv->mdc_opr_window), GTK_WIN_POS_CENTER);
    gtk_widget_show(prv->mdc_opr_window);

}

void create_mdc_in_n_out_window(Private *prv)
{
    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;

    gboolean check = gtk_builder_add_from_file(builder, MDC_IN_N_OUT_UI_FILE, &error);
    if(!check)
    {
        g_print("the ui file is broken or not exist!\n");
        return;
    }

    prv->in_n_out_window = (GtkWidget *) gtk_builder_get_object(builder, "window1");
    prv->mdc_name_label = (GtkWidget *) gtk_builder_get_object(builder, "label7");
    prv->mdc_identify_key_label = (GtkWidget *) gtk_builder_get_object(builder, "label6");
    prv->mdc_unit_label = (GtkWidget *) gtk_builder_get_object(builder, "label5");
    prv->mdc_in_n_out_spin_btn = (GtkSpinButton *)gtk_builder_get_object(builder, "spinbutton1");
    prv->in_n_out_confirm = (GtkWidget *) gtk_builder_get_object( builder,  "button1");
    prv->in_n_out_cancel = (GtkWidget *) gtk_builder_get_object( builder, "button2");

    gboolean is_selected = gtk_tree_selection_get_selected(prv->mdc_selection, &(prv->mdc_store), &(prv->mdc_iter));
    if( !is_selected )
    {
        gtk_widget_destroy(prv->in_n_out_window);
        return;
    }

    g_signal_connect(prv->in_n_out_cancel, "clicked", G_CALLBACK(in_n_out_btn_cancel_handle), prv);
    g_signal_connect(prv->in_n_out_confirm, "clicked", G_CALLBACK(in_n_out_btn_confirm_handle), prv);

    GString name;
    GString identify_key;
    GString unit;
    gulong quantity;
    gtk_tree_model_get(GTK_TREE_MODEL(prv->mdc_store), &(prv->mdc_iter),
                       1, &name,
                       6, &identify_key,
                       2, &unit,
                       3, &quantity, -1);

    gtk_label_set_text(GTK_LABEL(prv->mdc_name_label), name.str);
    gtk_label_set_text(GTK_LABEL(prv->mdc_identify_key_label), identify_key.str);
    gtk_label_set_text(GTK_LABEL(prv->mdc_unit_label), unit.str);

    if(! prv->in_n_out_flag)
    {
        GtkAdjustment *adjustment = gtk_adjustment_new(1, 1, (gdouble)quantity, 1, 10, 10);
        gtk_spin_button_set_adjustment(prv->mdc_in_n_out_spin_btn, adjustment);
        gtk_window_set_title(GTK_WINDOW(prv->in_n_out_window), "药品出库");
    }
    else
        gtk_window_set_title(GTK_WINDOW(prv->in_n_out_window), "药品入库");

    gtk_widget_show_all(prv->in_n_out_window);
}

void hist_notify_data_set_changed (Private *prv, Medicine *node)
{
    if(!node)
        return;
    gtk_list_store_clear(prv->hist_store);
    GtkTreeIter iter;
    History *head = node->hist_head;
    gchar *opr_str;
    while(head)
    {
        opr_str = head->flag? "入库" : "出库" ;
        gtk_list_store_append(prv->hist_store, &iter);
        gtk_list_store_set(prv->hist_store, &iter,
                           0, opr_str,
                           1, node->identify_key->str,
                           2, node->name->str,
                           3, head->amount,
                           4,head->date->str, -1);
        head = head -> next;
    }
}

void create_search_window(Private *prv)
{
    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;

    gboolean check = gtk_builder_add_from_file(builder,SEARCH_WINDOW_UI, &error);

    if(!check)
    {
        g_print("search_window.ui is not exist. create window fail!\n");
        return;
    }

    prv->search_window = (GtkWidget *)gtk_builder_get_object(builder, "dialog1");
    prv->sc_dsp_name_combo_entry = (GtkWidget *)(gtk_builder_get_object(builder, "entry9"));
    prv->sc_dsp_place_entry = (GtkWidget *)gtk_builder_get_object(builder, "entry1");
    prv->sc_dsp_tel_entry = (GtkWidget *)gtk_builder_get_object(builder, "entry2");
    prv->sc_mdc_name_entry = (GtkWidget *)gtk_builder_get_object(builder, "entry3");
    prv->sc_mdc_unit_entry = (GtkWidget *)gtk_builder_get_object(builder, "entry4");
    prv->sc_mdc_specification_entry = (GtkWidget *)gtk_builder_get_object(builder, "entry5");
    prv->sc_mdc_allow_key_entry = (GtkWidget *)gtk_builder_get_object(builder, "entry6");
    prv->sc_mdc_identify_key_entry = (GtkWidget *)gtk_builder_get_object(builder, "entry7");
    prv->sc_mdc_producer_entry = (GtkWidget *)gtk_builder_get_object(builder, "entry8");
    prv->sc_confirm = (GtkWidget *)gtk_builder_get_object(builder, "button1");
    prv->sc_cancel = (GtkWidget *)gtk_builder_get_object(builder, "button2");



    g_signal_connect(prv->sc_cancel, "clicked", G_CALLBACK(sc_cancel_button_handle), prv);
    g_signal_connect(prv->sc_confirm, "clicked", G_CALLBACK(sc_confirm_button_handle), prv);

    gtk_widget_show(prv->search_window);
    gtk_widget_show_all(prv->search_window);
    return;
}



gint mdc_sort(GtkTreeModel *model, GtkTreeIter *current, GtkTreeIter *next, Private *prv)
{
    if(prv->sort_column == 3)
    {
        gulong cur;
        gulong nxt;
        gtk_tree_model_get(model, current, prv->sort_column, &cur, -1);
        gtk_tree_model_get(model, current, prv->sort_column, &nxt, -1);
        return cur - nxt;
    }

    GString current_str;
    GString next_str;
    gtk_tree_model_get(model, current, prv->sort_column, &current_str, -1);
    gtk_tree_model_get(model, current, prv->sort_column, &next_str, -1);

    return g_strcmp0(current_str.str, next_str.str);
}

gint string_sort(GtkTreeModel *model, GtkTreeIter *current, GtkTreeIter *next, Private *prv)
{
    GString current_str;
    GString next_str;
    gtk_tree_model_get(model, current, prv->sort_column, &current_str, -1);
    gtk_tree_model_get(model, current, prv->sort_column, &next_str, -1);
    return g_strcmp0(current_str.str, next_str.str);
}
