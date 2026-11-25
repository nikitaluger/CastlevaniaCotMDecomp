void sub_080C3A48(u16 *arg0, s16 *arg1)
{
    u16 *p;
    u16 *end;

    p = &arg0[*arg1];
    (*p)--;
    end = arg1;
    p++;
    while ((u32)p < (u32)end)
    {
        *p = 0;
        p++;
    }
}

void sub_080C3A6C(u16 *arg0, s16 *arg1)
{
    s16 idx;
    u16 *p;
    u16 *end;

    idx = *arg1;
    if (idx > 0)
    {
        p = &arg0[idx - 1];
        (*p)--;
        end = arg1;
        p++;
        while ((u32)p < (u32)end)
        {
            *p = 0;
            p++;
        }
    }
}

void sub_080C3A20(u16 *arg0, s16 *arg1)
{
    u16 *p;
    u16 *end;

    p = &arg0[*arg1];
    (*p)++;
    *(u8 *)p = 0;
    end = arg1;
    p++;
    while ((u32)p < (u32)end)
    {
        *p = 0;
        p++;
    }
}

void sub_080C3A94(u16 *arg0, s16 *arg1)
{
    u16 *p;
    u16 *end;

    p = &arg0[*arg1 + 1];
    end = arg1;
    if ((u32)p < (u32)end)
    {
        (*p)--;
        p++;
        while ((u32)p < (u32)end)
        {
            *p = 0;
            p++;
        }
    }
}
