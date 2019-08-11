/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0xfbc00daa */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "/home/nikhilsamrat/fpgalink/comm_fpga_fx2.vhdl";
extern char *IEEE_P_2592010699;
extern char *IEEE_P_1242562249;

char *ieee_p_1242562249_sub_1006216973935724872_1035706684(char *, char *, char *, char *, int );
unsigned char ieee_p_1242562249_sub_1434214030532789707_1035706684(char *, char *, char *, char *, char *);
unsigned char ieee_p_1242562249_sub_3307759752501503797_1035706684(char *, char *, char *, int );
unsigned char ieee_p_2592010699_sub_2763492388968962707_503743352(char *, char *, unsigned int , unsigned int );


static void work_a_4263751635_1516540902_p_0(char *t0)
{
    char *t1;
    unsigned char t2;
    char *t3;
    char *t4;
    unsigned char t5;
    unsigned char t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;

LAB0:    xsi_set_current_line(88, ng0);
    t1 = (t0 + 992U);
    t2 = ieee_p_2592010699_sub_2763492388968962707_503743352(IEEE_P_2592010699, t1, 0U, 0U);
    if (t2 != 0)
        goto LAB2;

LAB4:
LAB3:    t1 = (t0 + 9232);
    *((int *)t1) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(89, ng0);
    t3 = (t0 + 1192U);
    t4 = *((char **)t3);
    t5 = *((unsigned char *)t4);
    t6 = (t5 == (unsigned char)3);
    if (t6 != 0)
        goto LAB5;

LAB7:    xsi_set_current_line(96, ng0);
    t1 = (t0 + 3912U);
    t3 = *((char **)t1);
    t2 = *((unsigned char *)t3);
    t1 = (t0 + 9408);
    t4 = (t1 + 56U);
    t7 = *((char **)t4);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    *((unsigned char *)t9) = t2;
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(97, ng0);
    t1 = (t0 + 4392U);
    t3 = *((char **)t1);
    t1 = (t0 + 9472);
    t4 = (t1 + 56U);
    t7 = *((char **)t4);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memcpy(t9, t3, 17U);
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(98, ng0);
    t1 = (t0 + 4712U);
    t3 = *((char **)t1);
    t1 = (t0 + 9536);
    t4 = (t1 + 56U);
    t7 = *((char **)t4);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memcpy(t9, t3, 7U);
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(99, ng0);
    t1 = (t0 + 5032U);
    t3 = *((char **)t1);
    t2 = *((unsigned char *)t3);
    t1 = (t0 + 9600);
    t4 = (t1 + 56U);
    t7 = *((char **)t4);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    *((unsigned char *)t9) = t2;
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(100, ng0);
    t1 = (t0 + 5352U);
    t3 = *((char **)t1);
    t2 = *((unsigned char *)t3);
    t1 = (t0 + 9664);
    t4 = (t1 + 56U);
    t7 = *((char **)t4);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    *((unsigned char *)t9) = t2;
    xsi_driver_first_trans_fast(t1);

LAB6:    goto LAB3;

LAB5:    xsi_set_current_line(90, ng0);
    t3 = (t0 + 9408);
    t7 = (t3 + 56U);
    t8 = *((char **)t7);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    *((unsigned char *)t10) = (unsigned char)0;
    xsi_driver_first_trans_fast(t3);
    xsi_set_current_line(91, ng0);
    t1 = xsi_get_transient_memory(17U);
    memset(t1, 0, 17U);
    t3 = t1;
    memset(t3, (unsigned char)2, 17U);
    t4 = (t0 + 9472);
    t7 = (t4 + 56U);
    t8 = *((char **)t7);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    memcpy(t10, t1, 17U);
    xsi_driver_first_trans_fast(t4);
    xsi_set_current_line(92, ng0);
    t1 = xsi_get_transient_memory(7U);
    memset(t1, 0, 7U);
    t3 = t1;
    memset(t3, (unsigned char)2, 7U);
    t4 = (t0 + 9536);
    t7 = (t4 + 56U);
    t8 = *((char **)t7);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    memcpy(t10, t1, 7U);
    xsi_driver_first_trans_fast(t4);
    xsi_set_current_line(93, ng0);
    t1 = (t0 + 9600);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t7 = (t4 + 56U);
    t8 = *((char **)t7);
    *((unsigned char *)t8) = (unsigned char)2;
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(94, ng0);
    t1 = (t0 + 9664);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t7 = (t4 + 56U);
    t8 = *((char **)t7);
    *((unsigned char *)t8) = (unsigned char)2;
    xsi_driver_first_trans_fast(t1);
    goto LAB6;

}

static void work_a_4263751635_1516540902_p_1(char *t0)
{
    char t14[16];
    char t17[16];
    char *t1;
    char *t2;
    unsigned char t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    unsigned char t9;
    char *t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    int t15;
    unsigned int t16;
    int t18;
    char *t19;
    unsigned char t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    char *t27;
    unsigned char t28;
    unsigned char t29;
    static char *nl0[] = {&&LAB10, &&LAB11, &&LAB3, &&LAB4, &&LAB5, &&LAB6, &&LAB7, &&LAB8, &&LAB9};

LAB0:    xsi_set_current_line(110, ng0);
    t1 = (t0 + 3752U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 9728);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((unsigned char *)t7) = t3;
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(111, ng0);
    t1 = (t0 + 4232U);
    t2 = *((char **)t1);
    t1 = (t0 + 9792);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    memcpy(t7, t2, 17U);
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(112, ng0);
    t1 = (t0 + 4552U);
    t2 = *((char **)t1);
    t1 = (t0 + 9856);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    memcpy(t7, t2, 7U);
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(113, ng0);
    t1 = (t0 + 4872U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 9920);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((unsigned char *)t7) = t3;
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(114, ng0);
    t1 = (t0 + 5192U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 9984);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((unsigned char *)t7) = t3;
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(115, ng0);
    t1 = xsi_get_transient_memory(8U);
    memset(t1, 0, 8U);
    t2 = t1;
    memset(t2, (unsigned char)2, 8U);
    t4 = (t0 + 10048);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    memcpy(t8, t1, 8U);
    xsi_driver_first_trans_fast(t4);
    xsi_set_current_line(116, ng0);
    t1 = (t0 + 10112);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(117, ng0);
    t1 = (t0 + 5968U);
    t2 = *((char **)t1);
    t1 = (t0 + 10176);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    memcpy(t7, t2, 2U);
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(118, ng0);
    t1 = (t0 + 10240);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast_port(t1);
    xsi_set_current_line(119, ng0);
    t1 = (t0 + 10304);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast_port(t1);
    xsi_set_current_line(120, ng0);
    t1 = (t0 + 10368);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast_port(t1);
    xsi_set_current_line(121, ng0);
    t1 = (t0 + 10432);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast_port(t1);
    xsi_set_current_line(123, ng0);
    t1 = (t0 + 3752U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (char *)((nl0) + t3);
    goto **((char **)t1);

LAB2:    t1 = (t0 + 9248);
    *((int *)t1) = 1;

LAB1:    return;
LAB3:    xsi_set_current_line(125, ng0);
    t4 = (t0 + 6328U);
    t5 = *((char **)t4);
    t9 = *((unsigned char *)t5);
    t4 = (t0 + 10496);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t10 = *((char **)t8);
    *((unsigned char *)t10) = t9;
    xsi_driver_first_trans_fast_port(t4);
    xsi_set_current_line(126, ng0);
    t1 = (t0 + 1992U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t9 = (t3 == (unsigned char)3);
    if (t9 != 0)
        goto LAB12;

LAB14:
LAB13:    goto LAB2;

LAB4:    xsi_set_current_line(133, ng0);
    t1 = (t0 + 6328U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 10496);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((unsigned char *)t7) = t3;
    xsi_driver_first_trans_fast_port(t1);
    xsi_set_current_line(134, ng0);
    t1 = (t0 + 1992U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t9 = (t3 == (unsigned char)3);
    if (t9 != 0)
        goto LAB15;

LAB17:
LAB16:    goto LAB2;

LAB5:    xsi_set_current_line(150, ng0);
    t1 = (t0 + 6448U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 10496);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((unsigned char *)t7) = t3;
    xsi_driver_first_trans_fast_port(t1);
    xsi_set_current_line(151, ng0);
    t1 = (t0 + 6208U);
    t2 = *((char **)t1);
    t1 = (t0 + 10176);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    memcpy(t7, t2, 2U);
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(152, ng0);
    t1 = (t0 + 4232U);
    t2 = *((char **)t1);
    t11 = (16 - 8);
    t12 = (t11 * 1U);
    t13 = (0 + t12);
    t1 = (t2 + t13);
    t4 = (t14 + 0U);
    t5 = (t4 + 0U);
    *((int *)t5) = 8;
    t5 = (t4 + 4U);
    *((int *)t5) = 0;
    t5 = (t4 + 8U);
    *((int *)t5) = -1;
    t15 = (0 - 8);
    t16 = (t15 * -1);
    t16 = (t16 + 1);
    t5 = (t4 + 12U);
    *((unsigned int *)t5) = t16;
    t5 = (t0 + 15383);
    t7 = (t17 + 0U);
    t8 = (t7 + 0U);
    *((int *)t8) = 0;
    t8 = (t7 + 4U);
    *((int *)t8) = 8;
    t8 = (t7 + 8U);
    *((int *)t8) = 1;
    t18 = (8 - 0);
    t16 = (t18 * 1);
    t16 = (t16 + 1);
    t8 = (t7 + 12U);
    *((unsigned int *)t8) = t16;
    t3 = ieee_p_1242562249_sub_1434214030532789707_1035706684(IEEE_P_1242562249, t1, t14, t5, t17);
    if (t3 != 0)
        goto LAB33;

LAB35:    xsi_set_current_line(155, ng0);
    t1 = (t0 + 9984);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t1);

LAB34:    xsi_set_current_line(157, ng0);
    t1 = (t0 + 9728);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)5;
    xsi_driver_first_trans_fast(t1);
    goto LAB2;

LAB6:    xsi_set_current_line(160, ng0);
    t1 = (t0 + 6448U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 10496);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((unsigned char *)t7) = t3;
    xsi_driver_first_trans_fast_port(t1);
    xsi_set_current_line(161, ng0);
    t1 = (t0 + 2312U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t9 = (t3 == (unsigned char)3);
    if (t9 != 0)
        goto LAB36;

LAB38:
LAB37:    xsi_set_current_line(164, ng0);
    t1 = (t0 + 2312U);
    t2 = *((char **)t1);
    t9 = *((unsigned char *)t2);
    t20 = (t9 == (unsigned char)3);
    if (t20 == 1)
        goto LAB42;

LAB43:    t3 = (unsigned char)0;

LAB44:    if (t3 != 0)
        goto LAB39;

LAB41:    xsi_set_current_line(177, ng0);
    t1 = (t0 + 6208U);
    t2 = *((char **)t1);
    t1 = (t0 + 10176);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    memcpy(t7, t2, 2U);
    xsi_driver_first_trans_fast(t1);

LAB40:    goto LAB2;

LAB7:    xsi_set_current_line(181, ng0);
    t1 = (t0 + 6448U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 10496);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((unsigned char *)t7) = t3;
    xsi_driver_first_trans_fast_port(t1);
    xsi_set_current_line(182, ng0);
    t1 = (t0 + 6208U);
    t2 = *((char **)t1);
    t1 = (t0 + 10176);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    memcpy(t7, t2, 2U);
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(183, ng0);
    t1 = (t0 + 9728);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)1;
    xsi_driver_first_trans_fast(t1);
    goto LAB2;

LAB8:    xsi_set_current_line(186, ng0);
    t1 = (t0 + 6448U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 10496);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((unsigned char *)t7) = t3;
    xsi_driver_first_trans_fast_port(t1);
    xsi_set_current_line(187, ng0);
    t1 = (t0 + 6208U);
    t2 = *((char **)t1);
    t1 = (t0 + 10176);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    memcpy(t7, t2, 2U);
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(188, ng0);
    t1 = (t0 + 10240);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast_port(t1);
    xsi_set_current_line(189, ng0);
    t1 = (t0 + 9728);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)1;
    xsi_driver_first_trans_fast(t1);
    goto LAB2;

LAB9:    xsi_set_current_line(192, ng0);
    t1 = (t0 + 6328U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 10496);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((unsigned char *)t7) = t3;
    xsi_driver_first_trans_fast_port(t1);
    xsi_set_current_line(193, ng0);
    t1 = (t0 + 1992U);
    t2 = *((char **)t1);
    t9 = *((unsigned char *)t2);
    t20 = (t9 == (unsigned char)3);
    if (t20 == 1)
        goto LAB56;

LAB57:    t3 = (unsigned char)0;

LAB58:    if (t3 != 0)
        goto LAB53;

LAB55:    xsi_set_current_line(201, ng0);
    t1 = (t0 + 6208U);
    t2 = *((char **)t1);
    t1 = (t0 + 10176);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    memcpy(t7, t2, 2U);
    xsi_driver_first_trans_fast(t1);

LAB54:    goto LAB2;

LAB10:    xsi_set_current_line(206, ng0);
    t1 = (t0 + 10432);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast_port(t1);
    xsi_set_current_line(207, ng0);
    t1 = (t0 + 10112);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(208, ng0);
    t1 = (t0 + 15392);
    t4 = (t0 + 10176);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    memcpy(t8, t1, 2U);
    xsi_driver_first_trans_fast(t4);
    xsi_set_current_line(209, ng0);
    t1 = (t0 + 10496);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)4;
    xsi_driver_first_trans_fast_port(t1);
    xsi_set_current_line(210, ng0);
    t1 = (t0 + 10240);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)4;
    xsi_driver_first_trans_fast_port(t1);
    xsi_set_current_line(211, ng0);
    t1 = (t0 + 1992U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t9 = (t3 == (unsigned char)2);
    if (t9 != 0)
        goto LAB64;

LAB66:
LAB65:    goto LAB2;

LAB11:    xsi_set_current_line(217, ng0);
    t1 = (t0 + 6328U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 10496);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((unsigned char *)t7) = t3;
    xsi_driver_first_trans_fast_port(t1);
    xsi_set_current_line(218, ng0);
    t1 = (t0 + 1992U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t9 = (t3 == (unsigned char)3);
    if (t9 != 0)
        goto LAB67;

LAB69:
LAB68:    goto LAB2;

LAB12:    xsi_set_current_line(128, ng0);
    t1 = (t0 + 1672U);
    t4 = *((char **)t1);
    t1 = (t0 + 9792);
    t5 = (t1 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    memcpy(t8, t4, 8U);
    xsi_driver_first_trans_delta(t1, 1U, 8U, 0LL);
    xsi_set_current_line(129, ng0);
    t1 = (t0 + 9728);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast(t1);
    goto LAB13;

LAB15:    xsi_set_current_line(136, ng0);
    t1 = (t0 + 1672U);
    t4 = *((char **)t1);
    t1 = (t0 + 9792);
    t5 = (t1 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    memcpy(t8, t4, 8U);
    xsi_driver_first_trans_delta(t1, 9U, 8U, 0LL);
    xsi_set_current_line(137, ng0);
    t1 = (t0 + 4232U);
    t2 = *((char **)t1);
    t11 = (16 - 15);
    t12 = (t11 * 1U);
    t13 = (0 + t12);
    t1 = (t2 + t13);
    t4 = (t14 + 0U);
    t5 = (t4 + 0U);
    *((int *)t5) = 15;
    t5 = (t4 + 4U);
    *((int *)t5) = 8;
    t5 = (t4 + 8U);
    *((int *)t5) = -1;
    t15 = (8 - 15);
    t16 = (t15 * -1);
    t16 = (t16 + 1);
    t5 = (t4 + 12U);
    *((unsigned int *)t5) = t16;
    t5 = (t0 + 15367);
    t7 = (t17 + 0U);
    t8 = (t7 + 0U);
    *((int *)t8) = 0;
    t8 = (t7 + 4U);
    *((int *)t8) = 7;
    t8 = (t7 + 8U);
    *((int *)t8) = 1;
    t18 = (7 - 0);
    t16 = (t18 * 1);
    t16 = (t16 + 1);
    t8 = (t7 + 12U);
    *((unsigned int *)t8) = t16;
    t9 = ieee_p_1242562249_sub_1434214030532789707_1035706684(IEEE_P_1242562249, t1, t14, t5, t17);
    if (t9 == 1)
        goto LAB21;

LAB22:    t3 = (unsigned char)0;

LAB23:    if (t3 != 0)
        goto LAB18;

LAB20:    xsi_set_current_line(140, ng0);
    t1 = (t0 + 9792);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_delta(t1, 0U, 1, 0LL);

LAB19:    xsi_set_current_line(142, ng0);
    t1 = (t0 + 4872U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t9 = (t3 == (unsigned char)3);
    if (t9 != 0)
        goto LAB30;

LAB32:    xsi_set_current_line(145, ng0);
    t1 = (t0 + 9728);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)8;
    xsi_driver_first_trans_fast(t1);

LAB31:    goto LAB16;

LAB18:    xsi_set_current_line(138, ng0);
    t23 = (t0 + 9792);
    t24 = (t23 + 56U);
    t25 = *((char **)t24);
    t26 = (t25 + 56U);
    t27 = *((char **)t26);
    *((unsigned char *)t27) = (unsigned char)3;
    xsi_driver_first_trans_delta(t23, 0U, 1, 0LL);
    goto LAB19;

LAB21:    t8 = (t0 + 1672U);
    t10 = *((char **)t8);
    t8 = (t0 + 15375);
    t20 = 1;
    if (8U == 8U)
        goto LAB24;

LAB25:    t20 = 0;

LAB26:    t3 = t20;
    goto LAB23;

LAB24:    t16 = 0;

LAB27:    if (t16 < 8U)
        goto LAB28;
    else
        goto LAB26;

LAB28:    t21 = (t10 + t16);
    t22 = (t8 + t16);
    if (*((unsigned char *)t21) != *((unsigned char *)t22))
        goto LAB25;

LAB29:    t16 = (t16 + 1);
    goto LAB27;

LAB30:    xsi_set_current_line(143, ng0);
    t1 = (t0 + 9728);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((unsigned char *)t7) = (unsigned char)4;
    xsi_driver_first_trans_fast(t1);
    goto LAB31;

LAB33:    xsi_set_current_line(153, ng0);
    t8 = (t0 + 9984);
    t10 = (t8 + 56U);
    t19 = *((char **)t10);
    t21 = (t19 + 56U);
    t22 = *((char **)t21);
    *((unsigned char *)t22) = (unsigned char)3;
    xsi_driver_first_trans_fast(t8);
    goto LAB34;

LAB36:    xsi_set_current_line(162, ng0);
    t1 = (t0 + 10304);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((unsigned char *)t7) = (unsigned char)3;
    xsi_driver_first_trans_fast_port(t1);
    goto LAB37;

LAB39:    xsi_set_current_line(165, ng0);
    t1 = (t0 + 6088U);
    t5 = *((char **)t1);
    t1 = (t0 + 10176);
    t6 = (t1 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t10 = *((char **)t8);
    memcpy(t10, t5, 2U);
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(166, ng0);
    t1 = (t0 + 3272U);
    t2 = *((char **)t1);
    t1 = (t0 + 10048);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    memcpy(t7, t2, 8U);
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(167, ng0);
    t1 = (t0 + 10112);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(168, ng0);
    t1 = (t0 + 4232U);
    t2 = *((char **)t1);
    t1 = (t0 + 15224U);
    t4 = ieee_p_1242562249_sub_1006216973935724872_1035706684(IEEE_P_1242562249, t14, t2, t1, 1);
    t5 = (t14 + 12U);
    t11 = *((unsigned int *)t5);
    t12 = (1U * t11);
    t3 = (17U != t12);
    if (t3 == 1)
        goto LAB45;

LAB46:    t6 = (t0 + 9792);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    t10 = (t8 + 56U);
    t19 = *((char **)t10);
    memcpy(t19, t4, 17U);
    xsi_driver_first_trans_fast(t6);
    xsi_set_current_line(169, ng0);
    t1 = (t0 + 4232U);
    t2 = *((char **)t1);
    t1 = (t0 + 15224U);
    t3 = ieee_p_1242562249_sub_3307759752501503797_1035706684(IEEE_P_1242562249, t2, t1, 1);
    if (t3 != 0)
        goto LAB47;

LAB49:
LAB48:    goto LAB40;

LAB42:    t1 = (t0 + 3432U);
    t4 = *((char **)t1);
    t28 = *((unsigned char *)t4);
    t29 = (t28 == (unsigned char)3);
    t3 = t29;
    goto LAB44;

LAB45:    xsi_size_not_matching(17U, t12, 0);
    goto LAB46;

LAB47:    xsi_set_current_line(170, ng0);
    t4 = (t0 + 5192U);
    t5 = *((char **)t4);
    t9 = *((unsigned char *)t5);
    t20 = (t9 == (unsigned char)3);
    if (t20 != 0)
        goto LAB50;

LAB52:    xsi_set_current_line(173, ng0);
    t1 = (t0 + 9728);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)7;
    xsi_driver_first_trans_fast(t1);

LAB51:    goto LAB48;

LAB50:    xsi_set_current_line(171, ng0);
    t4 = (t0 + 9728);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t10 = *((char **)t8);
    *((unsigned char *)t10) = (unsigned char)6;
    xsi_driver_first_trans_fast(t4);
    goto LAB51;

LAB53:    xsi_set_current_line(195, ng0);
    t1 = (t0 + 10368);
    t5 = (t1 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    *((unsigned char *)t8) = (unsigned char)3;
    xsi_driver_first_trans_fast_port(t1);
    xsi_set_current_line(196, ng0);
    t1 = (t0 + 4232U);
    t2 = *((char **)t1);
    t1 = (t0 + 15224U);
    t4 = ieee_p_1242562249_sub_1006216973935724872_1035706684(IEEE_P_1242562249, t14, t2, t1, 1);
    t5 = (t14 + 12U);
    t11 = *((unsigned int *)t5);
    t12 = (1U * t11);
    t3 = (17U != t12);
    if (t3 == 1)
        goto LAB59;

LAB60:    t6 = (t0 + 9792);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    t10 = (t8 + 56U);
    t19 = *((char **)t10);
    memcpy(t19, t4, 17U);
    xsi_driver_first_trans_fast(t6);
    xsi_set_current_line(197, ng0);
    t1 = (t0 + 4232U);
    t2 = *((char **)t1);
    t1 = (t0 + 15224U);
    t3 = ieee_p_1242562249_sub_3307759752501503797_1035706684(IEEE_P_1242562249, t2, t1, 1);
    if (t3 != 0)
        goto LAB61;

LAB63:
LAB62:    goto LAB54;

LAB56:    t1 = (t0 + 3112U);
    t4 = *((char **)t1);
    t28 = *((unsigned char *)t4);
    t29 = (t28 == (unsigned char)3);
    t3 = t29;
    goto LAB58;

LAB59:    xsi_size_not_matching(17U, t12, 0);
    goto LAB60;

LAB61:    xsi_set_current_line(198, ng0);
    t4 = (t0 + 9728);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    *((unsigned char *)t8) = (unsigned char)1;
    xsi_driver_first_trans_fast(t4);
    goto LAB62;

LAB64:    xsi_set_current_line(212, ng0);
    t1 = (t0 + 9728);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((unsigned char *)t7) = (unsigned char)1;
    xsi_driver_first_trans_fast(t1);
    goto LAB65;

LAB67:    xsi_set_current_line(221, ng0);
    t1 = (t0 + 1672U);
    t4 = *((char **)t1);
    t11 = (7 - 6);
    t12 = (t11 * 1U);
    t13 = (0 + t12);
    t1 = (t4 + t13);
    t5 = (t0 + 9856);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t10 = *((char **)t8);
    memcpy(t10, t1, 7U);
    xsi_driver_first_trans_fast(t5);
    xsi_set_current_line(222, ng0);
    t1 = (t0 + 1672U);
    t2 = *((char **)t1);
    t15 = (7 - 7);
    t11 = (t15 * -1);
    t12 = (1U * t11);
    t13 = (0 + t12);
    t1 = (t2 + t13);
    t3 = *((unsigned char *)t1);
    t4 = (t0 + 9920);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    *((unsigned char *)t8) = t3;
    xsi_driver_first_trans_fast(t4);
    xsi_set_current_line(223, ng0);
    t1 = (t0 + 9728);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t1);
    goto LAB68;

}

static void work_a_4263751635_1516540902_p_2(char *t0)
{
    char *t1;
    char *t2;
    int t3;
    unsigned int t4;
    unsigned int t5;
    unsigned int t6;
    unsigned char t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    char *t12;
    char *t13;

LAB0:    xsi_set_current_line(229, ng0);

LAB3:    t1 = (t0 + 4072U);
    t2 = *((char **)t1);
    t3 = (0 - 1);
    t4 = (t3 * -1);
    t5 = (1U * t4);
    t6 = (0 + t5);
    t1 = (t2 + t6);
    t7 = *((unsigned char *)t1);
    t8 = (t0 + 10560);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    t11 = (t10 + 56U);
    t12 = *((char **)t11);
    *((unsigned char *)t12) = t7;
    xsi_driver_first_trans_fast_port(t8);

LAB2:    t13 = (t0 + 9264);
    *((int *)t13) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}

static void work_a_4263751635_1516540902_p_3(char *t0)
{
    char *t1;
    char *t2;
    int t3;
    unsigned int t4;
    unsigned int t5;
    unsigned int t6;
    unsigned char t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    char *t12;
    char *t13;

LAB0:    xsi_set_current_line(230, ng0);

LAB3:    t1 = (t0 + 4072U);
    t2 = *((char **)t1);
    t3 = (1 - 1);
    t4 = (t3 * -1);
    t5 = (1U * t4);
    t6 = (0 + t5);
    t1 = (t2 + t6);
    t7 = *((unsigned char *)t1);
    t8 = (t0 + 10624);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    t11 = (t10 + 56U);
    t12 = *((char **)t11);
    *((unsigned char *)t12) = t7;
    xsi_driver_first_trans_fast_port(t8);

LAB2:    t13 = (t0 + 9280);
    *((int *)t13) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}

static void work_a_4263751635_1516540902_p_4(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;

LAB0:    xsi_set_current_line(231, ng0);

LAB3:    t1 = (t0 + 4552U);
    t2 = *((char **)t1);
    t1 = (t0 + 10688);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    memcpy(t6, t2, 7U);
    xsi_driver_first_trans_fast_port(t1);

LAB2:    t7 = (t0 + 9296);
    *((int *)t7) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}

static void work_a_4263751635_1516540902_p_5(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;

LAB0:    xsi_set_current_line(232, ng0);

LAB3:    t1 = (t0 + 1672U);
    t2 = *((char **)t1);
    t1 = (t0 + 10752);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    memcpy(t6, t2, 8U);
    xsi_driver_first_trans_fast_port(t1);

LAB2:    t7 = (t0 + 9312);
    *((int *)t7) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}

static void work_a_4263751635_1516540902_p_6(char *t0)
{
    char *t1;
    char *t2;
    unsigned char t3;
    unsigned char t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    char *t12;
    char *t13;
    char *t14;
    char *t15;
    char *t16;
    char *t17;

LAB0:    xsi_set_current_line(233, ng0);
    t1 = (t0 + 5672U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t4 = (t3 == (unsigned char)3);
    if (t4 != 0)
        goto LAB3;

LAB4:
LAB5:    t10 = xsi_get_transient_memory(8U);
    memset(t10, 0, 8U);
    t11 = t10;
    memset(t11, (unsigned char)4, 8U);
    t12 = (t0 + 10816);
    t13 = (t12 + 56U);
    t14 = *((char **)t13);
    t15 = (t14 + 56U);
    t16 = *((char **)t15);
    memcpy(t16, t10, 8U);
    xsi_driver_first_trans_fast_port(t12);

LAB2:    t17 = (t0 + 9328);
    *((int *)t17) = 1;

LAB1:    return;
LAB3:    t1 = (t0 + 5512U);
    t5 = *((char **)t1);
    t1 = (t0 + 10816);
    t6 = (t1 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memcpy(t9, t5, 8U);
    xsi_driver_first_trans_fast_port(t1);
    goto LAB2;

LAB6:    goto LAB2;

}


extern void work_a_4263751635_1516540902_init()
{
	static char *pe[] = {(void *)work_a_4263751635_1516540902_p_0,(void *)work_a_4263751635_1516540902_p_1,(void *)work_a_4263751635_1516540902_p_2,(void *)work_a_4263751635_1516540902_p_3,(void *)work_a_4263751635_1516540902_p_4,(void *)work_a_4263751635_1516540902_p_5,(void *)work_a_4263751635_1516540902_p_6};
	xsi_register_didat("work_a_4263751635_1516540902", "isim/test_isim_beh.exe.sim/work/a_4263751635_1516540902.didat");
	xsi_register_executes(pe);
}
