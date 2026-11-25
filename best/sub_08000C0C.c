extern u32 D_02004060[];

void *sub_08000C0C(void *arg0)
{
    u32 *p = D_02004060;
    u32 *last = D_02004060 + 0x100;
    if (p >= last) goto fail;
loop:
    if (p[1] != 0)
    {
        p += 2;
        if (p < last) goto loop;
        goto fail;
    }
    p[1] = (u32)arg0;
    p[0] = 0;
    return p;
fail:
    return 0;
}
