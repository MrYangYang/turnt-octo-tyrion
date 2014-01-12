#include "my_type.h"

// use to remove space from a string
gchar *m_str_rm_space(gchar *str)
{
    gchar *result = str;
    while(*str != '\0' )
    {
        if(*str == '\x20')
        {
            gchar *temp = str;
            while(*temp != '\0')
            {
                *temp = *(temp + 1);
                temp++;
            }
        }
        else
            ++str;
    }

    return result;
}
