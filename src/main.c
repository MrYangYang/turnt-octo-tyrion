#include <stdlib.h>
#include <gtk/gtk.h>
#include "dispensary.h"
#include <string.h>
#include "private.h"
#include "interface.h"
#include "callbacks.h"
#include "data_io.h"
#include "my_type.h"

int main (int argc, char *argv[])
{
    Private *prv = (Private *)g_malloc0(sizeof(Private));
    prv->dsp_head = NULL;
    prv->sort_state = TRUE;

    //init the gtk environment
    gtk_init(&argc, &argv);

    //get objects from ui file.
    create_main_window (prv);


    gtk_window_maximize(GTK_WINDOW(prv->main_window));

    g_signal_connect(prv->main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(prv->dsp_new_btn, "clicked", G_CALLBACK(dsp_new_btn_handle), prv);
    g_signal_connect(prv->dsp_modify_btn, "clicked", G_CALLBACK(dsp_modify_btn_handle), prv);
    g_signal_connect(prv->dsp_remove_btn, "clicked", G_CALLBACK(dsp_remove_btn_handle), prv);
    g_signal_connect(prv->mdc_new_btn, "clicked",  G_CALLBACK(mdc_new_btn_handle), prv);
    g_signal_connect(prv->mdc_modify_btn, "clicked", G_CALLBACK(mdc_modify_btn_handle), prv);
    g_signal_connect(prv->mdc_remove_btn, "clicked", G_CALLBACK(mdc_remove_btn_handle), prv);
    g_signal_connect(prv->mdc_in_btn, "clicked", G_CALLBACK(mdc_in_btn_handle), prv);
    g_signal_connect(prv->mdc_out_btn, "clicked", G_CALLBACK(mdc_out_btn_handle), prv);
    g_signal_connect(prv->mdc_selection, "changed", G_CALLBACK(mdc_selected_changed_handle), prv);
    g_signal_connect(prv->save_item, "activate", G_CALLBACK(menu_save_handle), prv);
    g_signal_connect(prv->mdc_search_btn, "clicked", G_CALLBACK(mdc_search_btn_handle), prv);
    g_signal_connect(prv->mdc_show_all_btn, "clicked", G_CALLBACK(mdc_show_all_handle), prv);
    g_signal_connect(prv->mdc_save_btn, "clicked", G_CALLBACK(mdc_save_handle), prv);
    g_signal_connect(prv->dsp_selection, "changed", G_CALLBACK(dsp_show_my_mdc), prv);

    gtk_widget_show_all(prv->main_window);
    gtk_main();
    return 0;
}
