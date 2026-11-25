/* Step the script interpreter at `script` once: its 8-byte entry table lives
 * at script+8, indexed by the u16 at script+4. A data entry (bit 0x8000
 * clear) stores its 13-bit value at script+2, writes its payload (entry+4) to
 * *out, advances the index and returns 1. A command entry switches on its low
 * nibble: 0 writes the payload, resets the index and returns 0; 1 advances the
 * index and 2 resets it, both continuing the loop. */

inline u16 *halfword_at(u8 *ptr)
{
    return (u16 *)ptr;
}

s32 sub_0800395C(void *arg0, s32 *arg1)
{
    u8 *script = arg0;
    s32 *out = arg1;
    u8 *script_copy;
    s32 status = -1;
    do
    {
        u16 index = *((u16 *)(script + 4));
        u8 *entry = (*((u8 **)(script + 8))) + (index * 8);
        u16 word;
        if ((*((u16 *)entry)) & 0x8000)
        {
            s32 command = (*((u16 *)entry)) & 0xF;
            switch (command)
            {
            case 0:
                *out = *((s32 *)(((*((u8 **)(script + 8))) + (index * 8)) + 4));
                *halfword_at(script + 4) = 0;
                status = 0;
                break;

            case 1:
                *((u16 *)(script + 4)) = index + 1;
                break;

            case 2:
                *((u16 *)(script + 4)) = 0;
                break;
            }
        }
        else
        {
            status = (*((u16 *)(script + 2)) = (*((u16 *)entry)) & 0x1FFF);
            script_copy = script;
            *out = *((s32 *)(((*((u8 **)(script + 8))) + (index * 8)) + 4));
            *((u16 *)(script + 4)) = (*((u16 *)(script_copy + 4))) + 1;
            status = 1;
        }
    }
    while (status < 0);
    return status;
}
