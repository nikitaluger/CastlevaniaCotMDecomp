/* Handle a companion command byte ('a'..'j') for a state-3 companion whose
 * per-state flag is still clear: run the command's event, set the flag, play
 * its cue where applicable and run the shared follow-up. */
extern void sub_08005E80();
extern void spawnEntity();
extern void sub_0806DE0C();

struct GameState {
    u8 _p0[0x14EE];
    u8 commandByte;
    u8 _p1[0x14F8 - 0x14EF];
    u32 commandCounter;
};
extern struct GameState gMainWorkspace;

void handleCompanionCommand(void *actor, void *state)
{
    u16 stateKind;
    u8 *flagBytePtr;
    u32 *flagPtr;
    u32 command;
    u32 flag;
    stateKind = *(u16 *)((u8 *)state + 0x2C);
    if (stateKind == 3)
    {
        flagPtr = (u32 *)((u8 *)state + 0xB8);
        flag = *flagPtr;
        flagBytePtr = (u8 *)flagPtr;
        if (flag == 0)
        {
            command = gMainWorkspace.commandByte;
            command -= 0x61;
            if (command <= 9)
            {
                switch (command) {
                case 0:
                    spawnEntity(actor, 0x44, 0x0A, 0x12);
                    *(u32 *)flagBytePtr = 1;
                    sub_08005E80(0x141);
                    sub_0806DE0C();
                    break;
                case 1:
                    spawnEntity(actor, 0x45, 0x0A, 0x12);
                    *(u32 *)flagBytePtr = 1;
                    sub_08005E80(0x143);
                    sub_0806DE0C();
                    break;
                case 2:
                    spawnEntity(actor, 0x47, 0x0A, 0x12);
                    *(u32 *)flagBytePtr = 1;
                    sub_08005E80(0x141);
                    sub_0806DE0C();
                    break;
                case 3:
                case 4:
                case 8:
                    break;
                case 5:
                    spawnEntity(actor, 0x49, 0x0A, 0x12);
                    *(u32 *)flagBytePtr = 1;
                    gMainWorkspace.commandCounter++;
                    sub_08005E80(0x148);
                    sub_0806DE0C();
                    break;
                case 6:
                    spawnEntity(actor, 0x4B, 0x0A, 0x12);
                    *(u32 *)flagBytePtr = 1;
                    sub_08005E80(0x14A);
                    sub_0806DE0C();
                    break;
                case 7:
                    spawnEntity(actor, 0x4D, 0x0A, 0x12);
                    *(u32 *)flagBytePtr = 1;
                    sub_0806DE0C();
                    break;
                case 9:
                    spawnEntity(actor, 0x52, 0x0A, 0x12);
                    *(u32 *)flagBytePtr = 1;
                    sub_0806DE0C();
                    break;
                }
            }
        }
    }
}
