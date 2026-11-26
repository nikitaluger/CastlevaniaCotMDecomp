void postDisplaySprite(s32, s32, s32, u16, s32);

/* Run one step of a script command list: dispatch the current command to the
 * command executor, then advance, restart or stop according to its opcode.
 * Returns 0 or 1 when the script finishes, -1 while it keeps looping. */
s32 sub_080038C0(u8 *runner)
{
    s32 result = -1;
    s32 arg = 0x10;
    do {
    loop_1:
        {
            u8 *cmd = (u8 *)(*(u32 *)(runner + 8)) + *(u16 *)(runner + 4) * 0x10;
            if (*(u16 *)cmd & 0x8000) {
                s32 opcode = *(u16 *)cmd & 0xF;
                switch (opcode) {
                case 0:
                    postDisplaySprite(1, *(s32 *)(cmd + 4), *(s32 *)(cmd + 8), *(u16 *)(cmd + 0xC), arg);
                    *(u16 *)(runner + 4) = (u16)opcode;
                    result = 0;
                    break;
                case 1:
                    postDisplaySprite(1, *(s32 *)(cmd + 4), *(s32 *)(cmd + 8), *(u16 *)(cmd + 0xC), arg);
                    *(u16 *)(runner + 4) = *(u16 *)(runner + 4) + 1;
                    goto block_12;
                case 2:
                    *(u16 *)(runner + 4) = 0;
                    goto block_12;
                default:
                    goto block_12;
                }
            } else {
                *(s16 *)(runner + 2) = (s16)(*(u16 *)cmd & 0x1FFF);
                postDisplaySprite(1, *(s32 *)(cmd + 4), *(s32 *)(cmd + 8), *(u16 *)(cmd + 0xC), arg);
                *(u16 *)(runner + 4) = *(u16 *)(runner + 4) + 1;
                result = 1;
            block_12:
                if (result < 0) {
                    goto loop_1;
                }
            }
        }
    } while (0);
    return result;
}
