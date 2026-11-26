struct S { u8 f00; u8 f01; u8 pad02[2]; u8 f04,f05,f06,f07,pad08; u8 f09,f0A,f0B,f0C,f0D; u8 pad0E[0x0B]; u8 f19,f1A,f1B,f1C,f1D,f1E,f1F; s32 f20; u8 *f24; u8 *f28; };
struct P { u8 pad00[0x0A]; u8 f0A; u8 pad0B[0x11]; struct S *f1C; };
extern struct P *D_03007FF0;
extern vu8 D_04000060,D_04000061,D_04000062,D_04000063,D_04000068,D_04000069,D_04000070,D_04000071,D_04000072,D_04000073,D_04000078,D_04000079,D_04000081,D_04000089;
extern vu32 D_04000090;
extern u8 D_0810C9CE[];
void sub_080C0DA0(u32); void sub_080C0DF0(struct S *);

void sub_080C0E58(void) {
int __repair_constant = 3;

    register s32 var_r6_sum;
    s32 sp0, sp14; struct P *sp4; u8 *sp8,*spC,*sp10;
    s32 temp_r0_4, temp_r0_6, temp_r0_5, var_r0_4, var_r0_5;
    register u8 *var_r7,*var_r10,*var_r2;
    u8 temp_r5,temp_r0_3,temp_r0_7,temp_r0_8,temp_r0_9,temp_r0_10;
    u8 temp_r1,var_r1,var_r0_2,var_r0_3;
    register struct S *var_r4,*var_r8; register s32 var_r6,var_r9;
    sp4 = D_03007FF0;
    temp_r1 = sp4->f0A;
    if (temp_r1 == 0) goto block_2;
    sp4->f0A = (u8)(temp_r1 - 1);
    goto block_3;
block_2: sp4->f0A = 0xE;
block_3: var_r6 = 1; var_r4 = sp4->f1C;
    for (;;) {
        var_r8 = (struct S *)((u8 *)var_r4 + 0x40);
            temp_r1 = var_r4->f00;
            var_r6_sum = var_r6 + 1;
            var_r9 = var_r6_sum;
            do { do { if (0xC7 & temp_r1) goto block_6; } while (0); } while (0);
            goto block_91;
block_6:
            if (var_r6 == 2) goto block_13;
            if (var_r6 > 2) goto block_10;
            if (var_r6 == 1) goto block_12;
            goto block_15;
        block_10: if (var_r6 == 3) goto block_14; goto block_15;
block_12:
            sp8=(u8*)0x04000060; var_r7=(u8*)0x04000062; spC=sp8+4; var_r10=(u8*)0x04000063; var_r2=var_r10+2; goto block_17;
block_13:
            sp8=(u8*)0x04000061; var_r7=(u8*)0x04000068; var_r10=(u8*)0x04000069; spC=sp8+0xB; var_r2=var_r10+4;
         goto block_17;
block_14:
            sp8=(u8*)0x04000070; var_r7=(u8*)0x04000072; var_r10=(u8*)0x04000073; spC=sp8+4; var_r2=var_r10+2; goto block_17;
block_15:
            sp8=(u8*)0x04000071; var_r7=(u8*)0x04000078; var_r10=(u8*)0x04000079;
        block_16: spC=sp8+0xB; var_r2=var_r10+4;
block_17:
            sp10=var_r2; sp0=sp4->f0A;
            if (!(0x80 & temp_r1)) goto block_39;
            temp_r5 = 0x40 & temp_r1;
            do { var_r8 = (struct S *)((u8 *)var_r4 + 0x40);
            var_r9 = var_r6_sum; } while (0);
            if (temp_r5 != 0) goto block_42;
            var_r4->f00=__repair_constant; var_r4->f1D=__repair_constant; sp14=0x40; sub_080C0DF0(var_r4);
            if (var_r6==2) goto block_26;
            if (var_r6>2) goto block_23;
            if (var_r6==1) goto block_25;
            goto block_32;
        block_23: if (var_r6==3) goto block_27; goto block_32;
        block_25: *sp8=var_r4->f1F;
        block_26: *var_r7=(u8)(var_r4->f1E+((s32)var_r4->f24<<6)); goto block_33;
block_27:
            if (var_r4->f24==var_r4->f28) goto block_29;
            *sp8=(u8)sp14;
            { u32 *s=(u32*)var_r4->f24; vu32 *d=&D_04000090; *d++=s[0]; *d++=s[1]; *d++=s[2]; *d++=s[3]; }
            var_r4->f28=var_r4->f24;
block_29:
            *sp8=temp_r5; *var_r7=var_r4->f1E;
            if (var_r4->f1E==0) goto block_31;
            var_r0_2=0xC0; goto block_35;
        block_31: var_r4->f1A=(u8)-0x80; goto block_36;
        block_32: *var_r7=var_r4->f1E; *spC=(u8)((s32)var_r4->f24*8);
        block_33: *var_r10=var_r4->f04+8; var_r0_2=var_r4->f1E; if (var_r0_2==0) goto block_35; var_r0_2=0x40;
        block_35: var_r4->f1A=var_r0_2;
        block_36: temp_r1=var_r4->f04; var_r4->f0B=temp_r1;
            var_r9 = var_r6_sum; var_r8 = (struct S *)((u8 *)var_r4 + 0x40);
            if (0xFF & temp_r1) goto block_38; goto block_65;
        block_38: var_r4->f09=0; goto block_71;
block_39:
            if (!(4&temp_r1)) goto block_43;
            temp_r0_3=var_r4->f0D-1; var_r4->f0D=temp_r0_3;
            var_r9 = var_r6_sum; var_r8 = (struct S *)((u8 *)var_r4 + 0x40);
            if ((s32)(temp_r0_3<<0x18)<=0) goto block_42;
            goto block_73;
        block_42: sub_080C0DA0((u32)(u8)var_r6); var_r4->f00=0; goto block_90;
block_43:
            var_r9 = var_r6_sum; var_r8 = (struct S *)((u8 *)var_r4 + 0x40);
            if (!(0x40&temp_r1)) goto block_47;
            if (!(3&temp_r1)) goto block_47;
            var_r4->f00=(u8)(0xFC&temp_r1); var_r1=var_r4->f07; var_r4->f0B=var_r1;
            if (!(0xFF&var_r1)) goto block_52;
            var_r4->f1D=(u8)(1|var_r4->f1D); goto block_67;
block_47:
            if (var_r4->f0B!=0) goto block_71;
            if (var_r6!=3) goto block_50;
            var_r4->f1D=(u8)(1|var_r4->f1D);
block_50:
            sub_080C0DF0(var_r4); temp_r0_4=3&var_r4->f00;
            if (temp_r0_4!=0) goto block_55;
            temp_r0_5=var_r4->f09-1; var_r4->f09=temp_r0_5;
            if ((s32)(temp_r0_5<<0x18)>0) goto block_54;
block_52:
            temp_r0_6=(s32)((var_r4->f0C*var_r4->f0A)+0xFF)>>8; var_r4->f09=(u8)temp_r0_6;
            if ((temp_r0_6<<0x18)==0) goto block_42;
            var_r4->f00=(u8)(4|var_r4->f00); var_r4->f1D=(u8)(1|var_r4->f1D); goto block_73;
        block_54: var_r0_3=var_r4->f07; goto block_70;
        block_55: if (temp_r0_4!=1) goto block_57;
        block_56: var_r4->f09=var_r4->f19; var_r0_3=7; goto block_70;
block_57:
            if (temp_r0_4!=2) goto block_64;
            temp_r0_7=var_r4->f09-1; var_r4->f09=temp_r0_7;
            if ((s32)(temp_r0_7<<0x18)>(s32)(var_r4->f19<<0x18)) goto block_63;
block_59:
            if (var_r4->f06!=0) goto block_61;
            var_r4->f00=(u8)(0xFC&var_r4->f00); goto block_52;
block_61:
            var_r4->f00=(u8)(var_r4->f00-1); var_r4->f1D=(u8)(1|var_r4->f1D);
            if (var_r6==3) goto block_56;
            *var_r10=8; goto block_56;
        block_63: var_r0_3=var_r4->f05; goto block_70;
block_64:
            temp_r0_8=var_r4->f09+1; var_r4->f09=temp_r0_8;
            if ((u32)temp_r0_8<(u32)var_r4->f0A) goto block_69;
block_65:
            var_r4->f00=(u8)(var_r4->f00-1); var_r1=var_r4->f05; var_r4->f0B=var_r1;
            if (!(0xFF&var_r1)) goto block_59;
            var_r4->f1D=(u8)(1|var_r4->f1D); var_r4->f09=var_r4->f0A;
        block_67: if (var_r6==3) goto block_71; *var_r10=var_r1; goto block_71;
        block_69: var_r0_3=var_r4->f04;
        block_70: var_r4->f0B=var_r0_3;
block_71:
            var_r4->f0B=(u8)(var_r4->f0B-1);
            if (sp0!=0) goto block_73;
            sp0-=1; goto block_47;
block_73:
            if (!(2&var_r4->f1D)) goto block_85;
            if (var_r6>3) goto block_81;
            if (!(8&var_r4->f01)) goto block_81;
            temp_r0_9=D_04000089;
            if ((s32)temp_r0_9>0x3F) goto block_78;
            temp_r0_6=0x7FC; var_r0_4=var_r4->f20+2; goto block_80;
block_78:
            if ((s32)temp_r0_9>0x7F) goto block_81;
            var_r0_4=var_r4->f20+1; temp_r0_6=0x7FE;
        block_80: var_r4->f20=(s32)(var_r0_4&temp_r0_6);
        block_81: if (var_r6==4) goto block_83; var_r0_5=var_r4->f20; goto block_84;
        block_83: var_r0_5=(8&*spC) | var_r4->f20;
        block_84: *spC=(u8)var_r0_5; var_r6_sum = (0xC0&var_r4->f1A); temp_r0_10=*(u8*)((u8*)var_r4+0x21)+var_r6_sum; var_r4->f1A=temp_r0_10; *sp10=temp_r0_10;
block_85:
            if (!(1&var_r4->f1D)) goto block_90;
            D_04000081=(D_04000081 & ~var_r4->f1C)|var_r4->f1B;
            if (var_r6!=3) goto block_89;
            *var_r10=D_0810C9CE[var_r4->f09];
            if (!(0x80&var_r4->f1A)) goto block_90;
            *sp8=0x80; *sp10=var_r4->f1A; var_r4->f1A=(u8)(0x7F&var_r4->f1A); goto block_90;
block_89:
            *var_r10=(0xF&*var_r10)+(var_r4->f09*0x10); *sp10=0x80|var_r4->f1A;
        block_90: var_r4->f1D=0;
block_91:
            var_r6=var_r9; var_r4=var_r8;
            if (var_r6>4) goto block_93;
            continue;
        break;
    }
block_93: return;
}
