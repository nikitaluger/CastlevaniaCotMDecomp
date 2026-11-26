struct S_02021E90 { u8 b[0x20]; };
extern struct S_02021E90 gCameraState[];

extern void sub_08000F50(void);
extern void sub_080C31E0(void *, s32);

/* Finish a screen/palette transition: clear the first byte of the 0x9B-th
 * 0x20-byte entry in the display buffer, clear the display-mode flag bit via
 * sub_08000F50, then run the object's saved callback at +0x5C. */
void sub_080BE214(void *obj)
{
    gCameraState[0x9B].b[0] = 0;
    sub_08000F50();
    sub_080C31E0(obj, *(s32 *)((u8 *)obj + 0x5C));
}
