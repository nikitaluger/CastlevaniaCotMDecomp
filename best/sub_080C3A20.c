void sub_080C3A48(u16 *arg0, s16 *arg1)
{
    u16 *end;
    u16 *p;

    end = (u16 *)arg1;
    p = arg0 + *arg1;
    (*p)--;
    p++;
    if (p < end)
    {
        do
        {
            *p = 0;
            p++;
        } while (p < end);
    }
}

void sub_080C3A6C(u16 *arg0, s16 *arg1)
{
    s16 idx;

    idx = *arg1;
    if (idx > 0)
    {
        u16 *end;
        u16 *p;

        end = (u16 *)arg1;
        p = arg0 + idx - 1;
        (*p)--;
        p++;
        if (p < end)
        {
            do
            {
                *p = 0;
                p++;
            } while (p < end);
        }
    }
}

void sub_080C3A20(u16 *arg0, s16 *arg1)
{
    u16 *end;
    u16 *p;

    end = (u16 *)arg1;
    p = arg0 + *arg1;
    (*p)++;
    *(u8 *)p = 0;
    p++;
    if (p < end)
    {
        do
        {
            *p = 0;
            p++;
        } while (p < end);
    }
}

void sub_080C3A94(u16 *arg0, s16 *arg1)
{
    u16 *end;
    u16 *p;

    end = (u16 *)arg1;
    p = arg0 + *arg1 + 1;
    if (p < end)
    {
        u16 *q;

        q = p;
        (*q)--;
        q++;
        if (q < end)
        {
            do
            {
                *q = 0;
                q++;
            } while (q < end);
        }
    }
}
