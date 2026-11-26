extern u32 postDisplaySprite(u32, void *, void *, u32, u32);
extern u16 *D_08670760[];

void sub_080BE388(void *arg0)
{
    u8 *base = *(u8 **)((u8 *)arg0 + 0x3C);
    u16 f22 = *(u16 *)((u8 *)arg0 + 0x22);
    s32 count;
    u32 i;
    u32 off;
    u8 *srcGBase;
    u8 *srcRBase;
    u8 *srcBBase;
    u8 *dstBase;
    s32 *accRBase;
    s32 *accGBase;
    s32 *accBBase;
    s32 idx;
    s32 block;
    s32 r;
    

    if ((f22 & 3) != 0)
    {
        if (*(u32 *)base != 0)
            return;
    }

    *(u32 *)base = 1;
    count = *(s32 *)(base + 8) - 1;
    *(s32 *)(base + 8) = count;
    if (count != 0)
    {
        accRBase = (s32 *)(base + 0x8C);
        accGBase = (s32 *)(base + 0x90);
        accBBase = (s32 *)(base + 0x94);
        dstBase = base + 0x0C;
        srcRBase = base + 0x38C;
        srcGBase = base + 0x390;
        off = 0;
        srcBBase = base + 0x394;

        i = 0;
        while (i <= 0x3F)
        {
            s16 rv;
            idx = *(s32 *)(base + 4);
            accRBase[off / 4] = accRBase[off / 4] + *(s32 *)(srcRBase + off + (block = (idx + idx * 2) << 8));
            accGBase[off / 4] = accGBase[off / 4] + *(s32 *)(srcGBase + off + block);
            accBBase[off / 4] = accBBase[off / 4] + *(s32 *)(srcBBase + off + block);

            rv = *(s16 *)((u8 *)&accRBase[off / 4] + 2);
            r = rv & 0x1F;
            block = (accGBase[off / 4] >> 11) & 0x3E0;
            *(u16 *)(dstBase + i * 2) = (u16)(r | block | ((accBBase[off / 4] >> 6) & 0x7C00));

            /*__repair_update_run*/__repair_rows: { off += 0x0C;
            i++; }
if (0) goto __repair_rows;
        }

        postDisplaySprite(1, dstBase, (void *)0x05000100, 0x80, 0x10);
    }
    else
    {
        u16 *src;

        *(s32 *)(base + 8) = 0x20;
        idx = *(s32 *)(base + 4) + 1;
        *(s32 *)(base + 4) = idx;
        if (idx == 4)
        {
            *(s32 *)(base + 4) = 0;
        }
        src = D_08670760[*(s32 *)(base + 4)];

        i = 0;
        accRBase = (s32 *)(base + 0x8C);
        accGBase = (s32 *)(base + 0x90);
        off = 0;
        accBBase = (s32 *)(base + 0x94);

        while (i <= 0x3F)
        {
            u16 c = src[i];
            accRBase[off / 4] = (s32)((u32)(c & 0x1F) << 16);
            accGBase[off / 4] = (s32)((u32)(((((u32)c) << 16) >> 21) & 0x1F) << 16);
            accBBase[off / 4] = (s32)((u32)(((((u32)c) << 16) >> 26) & 0x1F) << 16);
            off += 0x0C;
            i++;
        }

        postDisplaySprite(1, src, (void *)0x05000100, 0x80, 0x10);
    }
}
