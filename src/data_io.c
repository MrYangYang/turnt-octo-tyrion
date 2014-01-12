#include "data_io.h"
#include "my_type.h"
#include <string.h>

/*****************************************************************************
*   the method to save data to file.
*****************************************************************************/

void save_data(Dispensary *head)
{
    FILE *dispensary_datafile;
    FILE *medicine_datafile;
    FILE *history_datafile;

    Dsp_temp *dsp_temp = (Dsp_temp *)g_malloc0(sizeof(Dsp_temp));
    Mdc_temp *mdc_temp = (Mdc_temp *)g_malloc0(sizeof(Mdc_temp));
    Hist_temp *hist_temp = (Hist_temp *)g_malloc0(sizeof(Hist_temp));

    Medicine  *mdc;
    History *hist;

    g_print("saving %o\n", head);

    dispensary_datafile = fopen(DISPENSARY_FILE_NAME, "w");
    medicine_datafile = fopen(MEDICINE_FILE_NAME, "w");
    history_datafile = fopen(HISTORY_FILE_NAME, "w");

    if(!head)
    {
        fclose(dispensary_datafile);
        fclose(medicine_datafile);
        fclose(history_datafile);
        return;
    }

    g_print("saving.....\n");

    while(head)
    {
        g_print("on saving --> id is :%d\n", head->id);
        dsp_temp->dsp_id = head->id;
        strcpy(dsp_temp->name, head->name->str);
        strcpy(dsp_temp->place, head->place->str);
        strcpy(dsp_temp->tel, head->tel->str);

        g_print("%d\n",dsp_temp->dsp_id);
        g_print("%s\n", dsp_temp->name);
        g_print("%s\n", dsp_temp->place);
        g_print("%s\n", dsp_temp->tel);

        mdc = head->mdc_head;
        fwrite(dsp_temp, sizeof(Dsp_temp), 1, dispensary_datafile);

        while(mdc)
        {
            mdc_temp->dsp_id = head->id;
            strcpy(mdc_temp->name, mdc->name->str);
            strcpy(mdc_temp->unit, mdc->unit->str);
            mdc_temp->quantity = mdc->quantity;
            strcpy(mdc_temp->specification, mdc->specification->str);
            strcpy(mdc_temp->allow_key, mdc->allow_key->str);
            strcpy(mdc_temp->identify_key, mdc->identify_key->str);
            strcpy(mdc_temp->producer, mdc->producer->str);

            g_print("%d\n", mdc_temp->dsp_id);
            g_print("%s\n", mdc_temp->name);
            g_print("%s\n",mdc_temp->unit);
            g_print("%ld\n", mdc_temp->quantity);
            g_print("%s\n", mdc_temp->specification);
            g_print("%s\n", mdc_temp->allow_key);
            g_print("%s\n", mdc_temp->identify_key);
            g_print("%s\n", mdc_temp->producer);

            hist = mdc->hist_head;
            fwrite(mdc_temp, sizeof(Mdc_temp), 1, medicine_datafile);

            while(hist)
            {
                hist_temp->dsp_id = head->id;
                strcpy(hist_temp->identify_key, mdc->identify_key->str);
                strcpy(hist_temp->date, hist->date->str);
                hist_temp->amount = hist->amount;
                hist_temp->flag = hist->flag;

                g_print("%d\n",hist_temp->dsp_id);
                g_print("%s\n", hist_temp->identify_key);
                g_print("%s\n", hist_temp->date);
                g_print("%ld\n", hist_temp->amount);
                g_print("%d\n", hist_temp->flag);

                fwrite(hist_temp, sizeof(Hist_temp), 1, history_datafile);

                hist = hist->next;
            }
            mdc = mdc->next;
        }
        head = head->next;
    }

    fclose(dispensary_datafile);
    fclose(medicine_datafile);
    fclose(history_datafile);

}

/***************************************************************************************
*       method to read data from file.
***************************************************************************************/

Dispensary *read_data()
{
    FILE *dispensary_datafile;
    FILE *medicine_datafile;
    FILE *history_datafile;

    Dispensary *dsp_head = NULL;
    Dispensary *dsp_node = NULL;
    Medicine *mdc_head = NULL;
    Medicine *mdc_node = NULL;

    Dsp_temp *dsp = (Dsp_temp *)g_malloc0(sizeof(Dsp_temp));
    Mdc_temp *mdc = (Mdc_temp *)g_malloc0(sizeof(Mdc_temp));
    Hist_temp *hist = (Hist_temp *)g_malloc0(sizeof(Hist_temp));


    dispensary_datafile = fopen(DISPENSARY_FILE_NAME, "r");
    medicine_datafile = fopen(MEDICINE_FILE_NAME, "r");
    history_datafile = fopen(HISTORY_FILE_NAME, "r");

    if( !dispensary_datafile || !medicine_datafile || !history_datafile)
    {
        g_print("the data file is not exist or  broken->  read data failled->\n ");
        return NULL;
    }

    while( fread(dsp, sizeof(Dsp_temp), 1, dispensary_datafile) == 1)
    {
        dsp_head = dispensary_append_with_data(dsp_head, dsp->name, dsp->place, dsp->tel, dsp->dsp_id);
    }

    if(feof(dispensary_datafile))
        g_print("complete reading dsp \n");
    else
    {
        g_print("error occur when read dsp data file\n");
        dispensary_remove_all(dsp_head);
        return NULL;
    }

    while(fread(mdc, sizeof(Mdc_temp), 1 , medicine_datafile) == 1)
    {
        dsp_node = dispensary_get_child_by_id( dsp_head, mdc->dsp_id);
        mdc_head = dsp_node->mdc_head;
        dsp_node->mdc_head = medicine_append_with_data(mdc_head,
                                                       mdc->name,
                                                       mdc->unit,
                                                       mdc->quantity,
                                                       mdc->specification,
                                                       mdc->allow_key,
                                                       mdc->identify_key,
                                                       mdc->producer);
    }

    if(feof(medicine_datafile))
        g_print("reading mdc data->->->->->->-> complete!\n");
    else
    {
        g_print("reading mdc data.........failed!\n free all data!\n ");
        dispensary_remove_all(dsp_head);
        return NULL;
    }

    while( fread(hist, sizeof(Hist_temp), 1, history_datafile) == 1)
    {
        dsp_node = dispensary_get_child_by_id(dsp_head, hist->dsp_id);
        mdc_node = medicine_get_child_by_identify_key(dsp_node->mdc_head, hist->identify_key);
        mdc_node->hist_head = history_append_with_data(mdc_node->hist_head, hist->flag, hist->amount, hist->date);
    }

    if(feof(history_datafile))
        g_print("reading hist data........complete!\n");
    else
    {
        g_print("reading hist data........failed\n free all data!\n");
        dispensary_remove_all(dsp_head);
        return NULL;
    }

    g_print("loading complete!\n");
    fclose(dispensary_datafile);
    fclose(medicine_datafile);
    fclose(history_datafile);
    g_print("head ---> on reading : %o\n",dsp_head);
    return dsp_head;
}

gboolean m_strstr(const gchar *scope, const gchar *target)
{
    if( !target || *target == NULL )
        return TRUE;
    else if( !scope || !(*scope) )
        return FALSE;
    else
    {
        return strstr(scope, target);
    }

}




