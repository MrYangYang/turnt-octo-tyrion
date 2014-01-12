#ifndef _DATA_IO_H_
#define _DATA_IO_H_

#include "dispensary.h"
#include "history.h"
#include "medicine.h"

#define DISPENSARY_FILE_NAME    "dispensary.dat"
#define MEDICINE_FILE_NAME        "medicine.dat"
#define HISTORY_FILE_NAME          "history.dat"

typedef struct _Dsp_temp Dsp_temp;
typedef struct _Mdc_temp Mdc_temp;
typedef struct _Hist_temp Hist_temp;

/*************************************************************************************
*   一个utf-8占3个字节 name的字符最大长度为20,相当于60个gchar ， 加上结束符
*   ，一共61个；
**************************************************************************************/

struct _Dsp_temp
{
    gint dsp_id;
    gchar name[61];
    gchar place[61];
    gchar tel[31];
};

struct _Mdc_temp
{
    gint dsp_id;
    gchar name[61];
    gchar unit[16];
    gulong quantity;
    gchar specification[61];
    gchar allow_key[40];
    gchar identify_key[43];
    gchar producer[61];
};

struct _Hist_temp
{
    gboolean flag;
    gint dsp_id;
    gchar identify_key[43];
    gulong amount;
    gchar date[25];
};

/** the function to read & write data to file*/
void        save_data   (Dispensary *head);
Dispensary  *read_data  (void);

/** find a string in another string */
gboolean m_strstr(const gchar *target, const gchar *scope);

#endif // _DATA_IO_H_
