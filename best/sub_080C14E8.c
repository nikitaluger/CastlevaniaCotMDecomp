extern void (*D_03004044)(void *, void *);

void sub_080C14E8(void *arg0, void *arg1)
{
    u8 *p;
    u8 b0;
    u8 *p1;
    u8 b1;
    u8 *ptr;
    u8 *p2;
    unsigned int b2;
    u8 *p3;

    p = *(u8 **)((u8 *)arg1 + 0x40);
    b0 = *p;
    p1 = p + 1;
    *(u8 **)((u8 *)arg1 + 0x40) = p1;

    ptr = *(u8 **)((u8 *)arg0 + 0x18);
    b1 = p[1];
    ptr = ptr + b1;

    p2 = p1 + 1;
    *(u8 **)((u8 *)arg1 + 0x40) = p2;
    b2 = p1[1];

    p3 = p2 + 1;
    *(u8 **)((u8 *)arg1 + 0x40) = p3;

    if (b0 > 0x11)
    {
        goto done;
    }

    switch (b0)
    {
    case 0:
        *ptr = b2;
        goto done;

    case 1:
        *ptr = (*ptr) + b2;
        goto done;

    case 2:
        *ptr -= b2;
        goto done;

    case 3:
        *ptr = ((u8 *)(*(void **)((u8 *)arg0 + 0x18)))[b2];
        goto done;

    case 4:
        *ptr += ((u8 *)(*(void **)((u8 *)arg0 + 0x18)))[b2];
        goto done;

    case 5:
        *ptr -= ((u8 *)(*(void **)((u8 *)arg0 + 0x18)))[b2];
        goto done;

    case 6:
        if (*ptr == b2)
            goto call;
        goto advance;

    case 7:
        if (*ptr != b2)
            goto call;
        goto advance;

    case 8:
        if (*ptr > b2)
            goto call;
        goto advance;

    case 9:
        if (*ptr >= b2)
            goto call;
        goto advance;

    case 10:
        if (*ptr <= b2)
            goto call;
        goto advance;

    case 11:
        if (*ptr < b2)
            goto call;
        goto advance;

    case 12:
        if (*ptr == ((u8 *)(*(void **)((u8 *)arg0 + 0x18)))[b2])
            goto call;
        goto advance;

    case 13:
        if (*ptr != ((u8 *)(*(void **)((u8 *)arg0 + 0x18)))[b2])
            goto call;
        goto advance;

    case 14:
        if (*ptr > ((u8 *)(*(void **)((u8 *)arg0 + 0x18)))[b2])
            goto call;
        goto advance;

    case 15:
        if (*ptr >= ((u8 *)(*(void **)((u8 *)arg0 + 0x18)))[b2])
            goto call;
        goto advance;

    case 16:
        if (*ptr <= ((u8 *)(*(void **)((u8 *)arg0 + 0x18)))[b2])
            goto call;
        goto advance;

    case 17:
        if (*ptr < ((u8 *)(*(void **)((u8 *)arg0 + 0x18)))[b2])
            goto call;
        goto advance;
    }

call:
    D_03004044(arg0, arg1);
    goto done;

advance:
    *(u8 **)((u8 *)arg1 + 0x40) = *(u8 **)((u8 *)arg1 + 0x40) + 4;

done:
    return;
}
