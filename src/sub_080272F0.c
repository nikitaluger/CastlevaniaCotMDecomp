/* Trail emitter: records recent positions, spawns two linked trail segments,
 * initializes a small descriptor and dispatches a message. */
void *sub_0805FAEC(void *, s32);
void sub_080C31E4(void *, void *, void *);
extern void *D_08671BB0;
struct ZeroPair { u32 word; u8 byte; };
void sub_080272F0(void *entity) {
    u8 *state = *(u8 **)((u8 *)entity + 0x3C);
    u8 *ctrl = state + 0x48;
    u8 *trail = state + 0x5C;
    s32 i;
    u8 zeroByte;
    for (i = 4; i >= 0; i--) {
        s32 coord;
        coord = *(s32 *)(state + 8);
        *(u16 *)trail = coord;
        coord = *(s32 *)(state + 0xC);
        *(u16 *)(trail + 0xA) = coord;
        trail += 2;
    }
    {
        u8 *segment = sub_0805FAEC(entity, 0xB2);
        if (segment != 0) {
            s32 coord;
            coord = *(s32 *)(state + 8);
            if (coord < 0) coord += 0xFFFF;
            coord >>= 16;
            *(s16 *)(segment + 0x4C) = coord;
            coord = *(s32 *)(state + 0xC);
            if (coord < 0) coord += 0xFFFF;
            coord >>= 16;
            *(s16 *)(segment + 0x54) = coord;
            *(s16 *)(segment + 0x5C) = 0;
            { u16 angle = *(u16 *)(state + 0x1C); *(u16 *)(segment + 0x6C) = angle; }
            segment = sub_0805FAEC(segment, 0xB2);
            if (segment != 0) {
                coord = *(s32 *)(state + 8);
                if (coord < 0) coord += 0xFFFF;
                coord >>= 16;
                *(s16 *)(segment + 0x4C) = coord;
                coord = *(s32 *)(state + 0xC);
                if (coord < 0) coord += 0xFFFF;
                coord >>= 16;
                *(s16 *)(segment + 0x54) = coord;
                *(s16 *)(segment + 0x5C) = 1;
                { u16 angle = *(u16 *)(state + 0x1C); *(u16 *)(segment + 0x6C) = angle; }
            }
        }
    }
    {
        struct ZeroPair zeroPair = {0, 0};
        u8 *info = ctrl + 0x2C;
        *(s32 *)(ctrl + 0x2C) = 0x30000;
        *(s32 *)(info + 4) = *(u16 *)(*(u8 **)(ctrl + 0x58) + 2);
        *(s32 *)(info + 8) = zeroPair.word;
        *(s32 *)(info + 0xC) = 0x30000;
        *(s32 *)(info + 0x10) = 0x1800;
        *(s32 *)(info + 0x14) = 0x200;
        zeroByte = zeroPair.byte;
    }
    *(s16 *)(ctrl + 0x28) = 0x78;
    {
        s16 index = *(s16 *)((u8 *)entity + 0x22);
        *((u8 *)entity + index * 2 + 0x19) = zeroByte;
    }
    {
        void **msgTable = &D_08671BB0;
        sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *msgTable);
    }
}
