extern void sub_08003A6C(void *, s32, const void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern void sub_0808449C(void);
extern void *D_08671BB0;
extern const void D_084A3DA4;
extern const void D_084A3E44;
extern const void D_084A3E5C;

/* Initialise an actor's sub-object state, select an animation table by the
 * flag at +0x7C, fire the effect callback, then dispatch the next script
 * handler. */
void sub_0807654C(void *arg0)
{
    u8 *subObj;
    u8 *obj;
    u8 *ctx;
    s16 index;
    u8 *paramPtr;

    subObj = *(u8 **)((u8 *)arg0 + 0x6C);
    obj = subObj + 4;
    ctx = *(u8 **)((u8 *)arg0 + 0x38);

    *(u32 *)(obj + 0x2C) = 0;
    *(u32 *)(obj + 0x30) = 0;
    *(u32 *)(obj + 0x34) = 0;
    *(u32 *)(obj + 0x38) = 0;
    *(u32 *)(obj + 0x3C) = 0;

    *(u32 *)(obj + 0x18) = *(u32 *)((u8 *)arg0 + 0x24);
    *(void **)((u8 *)arg0 + 0x24) = sub_0808449C;
    *(const void **)(ctx + 0x24) = &D_084A3DA4;

    if (*(u16 *)((u8 *)arg0 + 0x7C) != 0) {
        sub_08003A6C(subObj + 0x20, 0, &D_084A3E5C);
    } else {
        sub_08003A6C(subObj + 0x20, 0, &D_084A3E44);
    }

    *(u32 *)(ctx + 0x1C) = 0x80000006;

    index = *(s16 *)((u8 *)arg0 + 0x22);
    ((u8 *)arg0)[index * 2 + 0x19] = 0;

    {
        void **effectIds = &D_08671BB0;
        paramPtr = (u8 *)arg0 + 0x18;
        sub_080C31E4(paramPtr, (u8 *)arg0 + 0x22, *effectIds);
    }

    index = *(s16 *)((u8 *)arg0 + 0x22);
    ((u8 *)arg0)[index * 2 + 0x19]++;

    index = *(s16 *)((u8 *)arg0 + 0x22);
    paramPtr = paramPtr + index * 2;
    sub_080C31E0(arg0, *(void **)(*(u32 *)((u8 *)arg0 + 0x14) + paramPtr[0] * 4));
}
