extern void sub_08013C5C(void *, s32);
extern s32 sub_080141AC(s32, void *);
extern s32 sub_08013558(s32, void *, void *);
extern void sub_08013978(void *, void *);
extern void sub_080142C0(void *, void *);
extern void sub_08013AC4(void *);
extern s32 sub_08013B5C(s32, void *);
extern void sub_080113A8(s32, void *);
extern void moveObjectHorizontally(void *, s32, s32);
extern void sub_08013C8C(void *, s32);
extern void sub_08015974(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void *D_08671BDC;
struct FlagBits { u16 lo; u16 hi; };

/* Dracula entity script update: refresh contact/damage flags, run the entity's
 * next script command, then write its camera-relative position back. */
void sub_0802B51C(u8 *self) {
    s32 p38 = *(s32 *)(self + 0x38);
    u8 *pAC = *(u8 **)(self + 0xAC);
    u8 *p3C = *(u8 **)(self + 0x3C);
    u8 *p34 = p3C + 0x34;
    u8 *p48 = p3C + 0x48;

    if (sub_080141AC(p38, p3C) == 1) {
        *(u16 *)p48 = 0;
        return;
    }

    sub_08013C5C(self, p38);
    if (sub_08013558(p38, p3C, *(void **)(p3C + 0x28)) != 0) {
        sub_08013978(self, *(void **)(p3C + 0x28));
    }
    if (*(u16 *)(*(u8 **)(pAC + 4) + 6) == 0) {
        sub_080142C0(self, *(void **)(p3C + 0x28));
    }
    if (*(u16 *)p3C & 1) {
        u8 *script = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        if (*(u8 *)(script + 0x1A) != 2) {
            u8 *scriptPtr;
            s32 *soundTab;
            if (*(u16 *)(*(u8 **)(pAC + 4) + 6) == 0) {
                sub_08013AC4(self);
            } else {
                if (pAC != NULL) {
                    ((struct FlagBits *)pAC)->lo |= 4;
                }
                if (*(void **)(p3C + 0x2C) != NULL) {
                    sub_08015974();
                    *(void **)(p3C + 0x2C) = NULL;
                }
                {
                    u8 *linked = *(u8 **)(p3C + 0x30);
                    if (linked != NULL) {
                        ((struct FlagBits *)linked)->hi |= 2;
                    }
                }
            }
            scriptPtr = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
            *(u8 *)(scriptPtr + 0x1B) = 0;
            soundTab = (s32 *)0x08671BDC;
            sub_080C31E8(self + 0x18, self + 0x22, 2, *soundTab);
        }
    }
    if (sub_08013B5C(p38, p3C) == 0) {
        u8 *scriptPtr;
        s32 idx;
        u8 *base;
        u8 byte;
        void **table;
        void *func;
        *(void **)(self + 0x14) = (void *)0x0866DB00;
        *(u16 *)(self + 0x22) = (u16)(*(u16 *)(self + 0x22) + 1);
        scriptPtr = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        *(u8 *)(scriptPtr + 0x19) = (u8)(*(u8 *)(scriptPtr + 0x19) + 1);
        idx = (*(s16 *)(self + 0x22)) * 2;
        base = self + 0x18;
        byte = *(base + idx);
        table = *(void **)(self + 0x14);
        func = table[byte];
        sub_080C31E0(self, func);
        *(u16 *)(self + 0x22) = (u16)(*(u16 *)(self + 0x22) - 1);
        if ((*(u16 *)(self + 2) & 0x8000) == 0) {
            sub_080113A8(p38, p34);
            moveObjectHorizontally(p3C, 0x80000, 0x80000);
        } else {
            goto done;
        }
    }
    sub_08013C8C(self, p38);
done: ;
}
