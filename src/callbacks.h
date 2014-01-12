#ifndef _CALLBACKS_H_
#define _CALLBACKS_H_
#include <gtk/gtk.h>
#include "private.h"
#include "interface.h"

// dsp opr callbacks
void dsp_new_btn_handle          (GtkWidget *widget, Private *prv);
void dsp_cancel_btn_handle       (GtkWidget *widget, Private *prv);
void dsp_confirm_btn_handle      (GtkWidget *widget, Private *prv);
void dsp_modify_btn_handle       (GtkWidget *widget, Private *prv);
void dsp_remove_btn_handle       (GtkWidget *widget, Private *prv);
void dsp_show_my_mdc             (GtkWidget *widget, Private *prv);

// mdc opr callbacks
void mdc_new_btn_handle          (GtkWidget *widget, Private *prv);
void mdc_confirm_btn_handle      (GtkWidget *widget, Private *prv);
void mdc_cancel_btn_handle       (GtkWidget *widget, Private *prv);
void mdc_modify_btn_handle       (GtkWidget *widget, Private *prv);
void mdc_remove_btn_handle       (GtkWidget *widget, Private *prv);
void mdc_in_btn_handle           (GtkWidget *widget, Private *prv);
void mdc_out_btn_handle          (GtkWidget *widget, Private *prv);
void in_n_out_btn_confirm_handle (GtkWidget *widget, Private *prv);
void in_n_out_btn_cancel_handle  (GtkWidget *widget, Private *prv);
void mdc_selected_changed_handle (GtkWidget *widget, Private *prv);
void mdc_search_btn_handle       (GtkWidget *widget, Private *prv);

//search window callbacks
void sc_cancel_button_handle     (GtkWidget *widget, Private *prv);
void sc_confirm_button_handle    (GtkWidget *widget, Private *prv);

//menu item callbacks
void menu_save_handle            (GtkWidget *widget, Private *prv);

//column headers
void col_mdc_dsp_name_handle     (GtkWidget *widget, Private *prv);
void col_mdc_name_handle         (GtkWidget *widget, Private *prv);
void col_mdc_unit_handle         (GtkWidget *widget, Private *prv);
void col_mdc_quantity_handle     (GtkWidget *widget, Private *prv);
void col_mdc_specification_handle (GtkWidget *widget, Private *prv);
void col_mdc_allow_key_handle    (GtkWidget *widget, Private *prv);
void col_mdc_identify_key_handle (GtkWidget *widget, Private *prv);
void col_mdc_producer_handle     (GtkWidget *widget, Private *prv);

void col_dsp_name_handle         (GtkWidget *widget, Private *prv);
void col_dsp_place_handle        (GtkWidget *widget, Private *prv);
void col_dsp_tel_handle          (GtkWidget *widget, Private *prv);

void col_hist_identify_key_handle       (GtkWidget *widget, Private *prv);
void col_hist_mdc_name_handle           (GtkWidget *widget, Private *prv);
void col_hist_opr_handle                (GtkWidget *widget, Private *prv);
void col_hist_amount_handle             (GtkWidget *widget, Private *prv);
void col_hist_date_handle               (GtkWidget *widget, Private *prv);

void mdc_show_all_handle                (GtkWidget *widget, Private *prv);
void mdc_save_handle                    (GtkWidget *widget, Private *prv);

#endif // _CALLBACKS_H_
