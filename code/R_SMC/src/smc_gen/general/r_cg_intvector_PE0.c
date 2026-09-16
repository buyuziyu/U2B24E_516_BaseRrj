/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2018, 2025 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : r_cg_intvector_PE0.c
* Version          : 1.0.100
* Device(s)        : R7F7025BxFABC -C
* Description      : None
***********************************************************************************************************************/
/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
/* IPIR CH0 interrupt; */
extern void eiint0(void);
/* IPIR CH1 interrupt; */
extern void eiint1(void);
/* IPIR CH2 interrupt; */
extern void eiint2(void);
/* IPIR CH3 interrupt; */
extern void eiint3(void);
/* Broadcast notification 0; */
extern void eiint4(void);
/* Broadcast notification 1; */
extern void eiint5(void);
/* Broadcast notification 2; */
extern void eiint6(void);
/* Broadcast notification 3; */
extern void eiint7(void);
/* ECM maskable interrupt (EI level); */
extern void eiint8(void);
/* DCLS error interrupt (EI level); */
extern void eiint9(void);
/* TAUD0 Channel 0 interrupt; */
extern void eiint10(void);
/* TAUD0 Channel 2 interrupt; */
extern void eiint11(void);
/* TAUD0 Channel 4 interrupt; */
extern void eiint12(void);
/* TAUD0 Channel 6 interrupt; */
extern void eiint13(void);
/* Software interrupt 0; */
extern void eiint14(void);
/* Software interrupt 1; */
extern void eiint15(void);
/* Software interrupt 2; */
extern void eiint16(void);
/* Software interrupt 3; */
extern void eiint17(void);
/* Reserved; */
extern void eiint18(void);
/* Reserved; */
extern void eiint19(void);
/* Reserved; */
extern void eiint20(void);
/* Inter-PE interrupt from ICUMHB to PE0(Single interrupt request from ICUP to CPU (PE)); */
extern void eiint21(void);
/* WDTB0 interrupt; */
extern void eiint22(void);
/* TAUD0 Channel 8 interrupt; */
extern void eiint23(void);
/* TAUD0 Channel 10 interrupt; */
extern void eiint24(void);
/* TAUD0 Channel 12 interrupt; */
extern void eiint25(void);
/* TAUD0 Channel 14 interrupt; */
extern void eiint26(void);
/* Reserved; */
extern void eiint27(void);
/* Reserved; */
extern void eiint28(void);
/* sDMAC0 address error or sDMAC1 address error interrupt; */
extern void eiint29(void);
/* DTS transfer error; */
extern void eiint30(void);
/* TPTM Interval timer Interrupt for PE0; */
extern void eiint31(void);
/* interrupt for degradation; */
extern void eiint32(void);
/* Unimplemented area access detected in a request to instrumentation RAM; */
extern void eiint33(void);
/* Mask generation notification interrupt signal for execution / access hold request; */
extern void eiint34(void);
/* FPSYS0 Flash sequencer processing end interrupt; */
extern void eiint35(void);
/* External interrupt 44; */
extern void eiint36(void);
/* FPSYS2 Flash sequencer processing end interrupt; */
extern void eiint37(void);
/* iso_dfa_int_swc[0]; */
extern void eiint38(void);
/* iso_dfa_int_swc[1]; */
extern void eiint39(void);
/* iso_dfa_int_swc[2]; */
extern void eiint40(void);
/* iso_dfa_int_swc[3]; */
extern void eiint41(void);
/* iso_dfa_int_dfa[0]; */
extern void eiint42(void);
/* iso_dfa_int_dfa[1]; */
extern void eiint43(void);
/* iso_dfa_int_dfa[2]; */
extern void eiint44(void);
/* iso_dfa_int_dfa[3]; */
extern void eiint45(void);
/* iso_dfa_int_dfa[4]; */
extern void eiint46(void);
/* TPBA0 Period match detection interrupt; */
extern void eiint47(void);
/* TPBA0 Duty match detection interrupt; */
extern void eiint48(void);
/* TPBA0 Pattern number matching detection interrupt; */
extern void eiint49(void);
/* TPBA1 Period match detection interrupt; */
extern void eiint50(void);
/* TPBA1 Duty match detection interrupt; */
extern void eiint51(void);
/* TPBA1 Pattern number matching detection interrupt; */
extern void eiint52(void);
/* OSPI0 Interrupt pulse signal by factors excluding errors; */
extern void eiint53(void);
/* Completion of ACEU0 encryption or decryption with CPU transfer; */
extern void eiint54(void);
/* Completion of ACEU0 encryption or decryption with DTF transfer; */
extern void eiint55(void);
/* ACEU BUS slave error of ACEU0 during DTF transfer; */
extern void eiint56(void);
/* Compare error from duplex circuit of ACEU0; */
extern void eiint57(void);
/* Completion of ACEU1 encryption or decryption with CPU transfer; */
extern void eiint58(void);
/* Completion of ACEU1 encryption or decryption with DTF transfer; */
extern void eiint59(void);
/* ACEU BUS slave error of ACEU1 during DTF transfer; */
extern void eiint60(void);
/* Compare error from duplex circuit of ACEU1; */
extern void eiint61(void);
/* DTS ch31-0 transfer end; */
extern void eiint62(void);
/* DTS ch63-32 transfer end; */
extern void eiint63(void);
/* DTS ch95-64 transfer end; */
extern void eiint64(void);
/* DTS ch127-96 transfer end; */
extern void eiint65(void);
/* DTS ch31-0 transfer count match; */
extern void eiint66(void);
/* DTS ch63-32 transfer count match; */
extern void eiint67(void);
/* DTS ch95-64 transfer count match; */
extern void eiint68(void);
/* DTS ch127-96 transfer count match; */
extern void eiint69(void);
/* sDMAC0 channel 0 transfer end or descriptor step end interrupt; */
extern void eiint70(void);
/* sDMAC0 channel 1 transfer end or descriptor step end interrupt; */
extern void eiint71(void);
/* sDMAC0 channel 2 transfer end or descriptor step end interrupt; */
extern void eiint72(void);
/* sDMAC0 channel 3 transfer end or descriptor step end interrupt; */
extern void eiint73(void);
/* sDMAC0 channel 4 transfer end or descriptor step end interrupt; */
extern void eiint74(void);
/* sDMAC0 channel 5 transfer end or descriptor step end interrupt; */
extern void eiint75(void);
/* sDMAC0 channel 6 transfer end or descriptor step end interrupt; */
extern void eiint76(void);
/* sDMAC0 channel 7 transfer end or descriptor step end interrupt; */
extern void eiint77(void);
/* sDMAC0 channel 8 transfer end or descriptor step end interrupt; */
extern void eiint78(void);
/* sDMAC0 channel 9 transfer end or descriptor step end interrupt; */
extern void eiint79(void);
/* sDMAC0 channel 10 transfer end or descriptor step end interrupt; */
extern void eiint80(void);
/* sDMAC0 channel 11 transfer end or descriptor step end interrupt; */
extern void eiint81(void);
/* sDMAC0 channel 12 transfer end or descriptor step end interrupt; */
extern void eiint82(void);
/* sDMAC0 channel 13 transfer end or descriptor step end interrupt; */
extern void eiint83(void);
/* sDMAC0 channel 14 transfer end or descriptor step end interrupt; */
extern void eiint84(void);
/* sDMAC0 channel 15 transfer end or descriptor step end interrupt; */
extern void eiint85(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 000 setting; */
extern void eiint86(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 001 setting; */
extern void eiint87(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 002 setting; */
extern void eiint88(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 003 setting; */
extern void eiint89(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 004 setting; */
extern void eiint90(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 005 setting; */
extern void eiint91(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 006 setting; */
extern void eiint92(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 007 setting; */
extern void eiint93(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 008 setting; */
extern void eiint94(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 009 setting; */
extern void eiint95(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 010 setting; */
extern void eiint96(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 011 setting; */
extern void eiint97(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 012 setting; */
extern void eiint98(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 013 setting; */
extern void eiint99(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 014 setting; */
extern void eiint100(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 015 setting; */
extern void eiint101(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 100 setting; */
extern void eiint102(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 101 setting; */
extern void eiint103(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 102 setting; */
extern void eiint104(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 103 setting; */
extern void eiint105(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 104 setting; */
extern void eiint106(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 105 setting; */
extern void eiint107(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 106 setting; */
extern void eiint108(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 107 setting; */
extern void eiint109(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 108 setting; */
extern void eiint110(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 109 setting; */
extern void eiint111(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 110 setting; */
extern void eiint112(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 111 setting; */
extern void eiint113(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 112 setting; */
extern void eiint114(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 113 setting; */
extern void eiint115(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 114 setting; */
extern void eiint116(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 115 setting; */
extern void eiint117(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 200 setting; */
extern void eiint118(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 201 setting; */
extern void eiint119(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 202 setting; */
extern void eiint120(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 203 setting; */
extern void eiint121(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 204 setting; */
extern void eiint122(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 205 setting; */
extern void eiint123(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 206 setting; */
extern void eiint124(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 207 setting; */
extern void eiint125(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 208 setting; */
extern void eiint126(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 209 setting; */
extern void eiint127(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 210 setting; */
extern void eiint128(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 211 setting; */
extern void eiint129(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 212 setting; */
extern void eiint130(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 213 setting; */
extern void eiint131(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 214 setting; */
extern void eiint132(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 215 setting; */
extern void eiint133(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 300 setting; */
extern void eiint134(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 301 setting; */
extern void eiint135(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 302 setting; */
extern void eiint136(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 303 setting; */
extern void eiint137(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 304 setting; */
extern void eiint138(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 305 setting; */
extern void eiint139(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 306 setting; */
extern void eiint140(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 307 setting; */
extern void eiint141(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 308 setting; */
extern void eiint142(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 309 setting; */
extern void eiint143(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 310 setting; */
extern void eiint144(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 311 setting; */
extern void eiint145(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 312 setting; */
extern void eiint146(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 313 setting; */
extern void eiint147(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 314 setting; */
extern void eiint148(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 315 setting; */
extern void eiint149(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 400 setting; */
extern void eiint150(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 401 setting; */
extern void eiint151(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 402 setting; */
extern void eiint152(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 403 setting; */
extern void eiint153(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 404 setting; */
extern void eiint154(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 405 setting; */
extern void eiint155(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 406 setting; */
extern void eiint156(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 407 setting; */
extern void eiint157(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 408 setting; */
extern void eiint158(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 409 setting; */
extern void eiint159(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 410 setting; */
extern void eiint160(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 411 setting; */
extern void eiint161(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 412 setting; */
extern void eiint162(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 413 setting; */
extern void eiint163(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 414 setting; */
extern void eiint164(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 415 setting; */
extern void eiint165(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 500 setting; */
extern void eiint166(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 501 setting; */
extern void eiint167(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 502 setting; */
extern void eiint168(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 503 setting; */
extern void eiint169(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 504 setting; */
extern void eiint170(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 505 setting; */
extern void eiint171(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 506 setting; */
extern void eiint172(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 507 setting; */
extern void eiint173(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 508 setting; */
extern void eiint174(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 509 setting; */
extern void eiint175(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 510 setting; */
extern void eiint176(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 511 setting; */
extern void eiint177(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 512 setting; */
extern void eiint178(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 513 setting; */
extern void eiint179(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 514 setting; */
extern void eiint180(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 515 setting; */
extern void eiint181(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 600 setting; */
extern void eiint182(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 601 setting; */
extern void eiint183(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 602 setting; */
extern void eiint184(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 603 setting; */
extern void eiint185(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 604 setting; */
extern void eiint186(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 605 setting; */
extern void eiint187(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 606 setting; */
extern void eiint188(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 607 setting; */
extern void eiint189(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 608 setting; */
extern void eiint190(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 609 setting; */
extern void eiint191(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 610 setting; */
extern void eiint192(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 611 setting; */
extern void eiint193(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 612 setting; */
extern void eiint194(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 613 setting; */
extern void eiint195(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 614 setting; */
extern void eiint196(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 615 setting; */
extern void eiint197(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 700 setting; */
extern void eiint198(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 701 setting; */
extern void eiint199(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 702 setting; */
extern void eiint200(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 703 setting; */
extern void eiint201(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 704 setting; */
extern void eiint202(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 705 setting; */
extern void eiint203(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 706 setting; */
extern void eiint204(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 707 setting; */
extern void eiint205(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 708 setting; */
extern void eiint206(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 709 setting; */
extern void eiint207(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 710 setting; */
extern void eiint208(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 711 setting; */
extern void eiint209(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 712 setting; */
extern void eiint210(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 713 setting; */
extern void eiint211(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 714 setting; */
extern void eiint212(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 715 setting; */
extern void eiint213(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 800 setting; */
extern void eiint214(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 801 setting; */
extern void eiint215(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 802 setting; */
extern void eiint216(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 803 setting; */
extern void eiint217(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 804 setting; */
extern void eiint218(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 805 setting; */
extern void eiint219(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 806 setting; */
extern void eiint220(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 807 setting; */
extern void eiint221(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 808 setting; */
extern void eiint222(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 809 setting; */
extern void eiint223(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 810 setting; */
extern void eiint224(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 811 setting; */
extern void eiint225(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 812 setting; */
extern void eiint226(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 813 setting; */
extern void eiint227(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 814 setting; */
extern void eiint228(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 815 setting; */
extern void eiint229(void);
/* AEI Shared interrupt; */
extern void eiint230(void);
/* ARU_NEW_DATA0 interrupt; */
extern void eiint231(void);
/* ARU_NEW_DATA1 interrupt; */
extern void eiint232(void);
/* ARU_ACC_ACK interrupt; */
extern void eiint233(void);
/* BRC Shared interrupt; */
extern void eiint234(void);
/* CMP Shared interrupt; */
extern void eiint235(void);
/* GTM Error interrupt; */
extern void eiint236(void);
/* Shared interrupt by GTM Interrupt DPLL Selection Register 0 setting; */
extern void eiint237(void);
/* Shared interrupt by GTM Interrupt DPLL Selection Register 1 setting; */
extern void eiint238(void);
/* Shared interrupt by GTM Interrupt DPLL Selection Register 2 setting; */
extern void eiint239(void);
/* Shared interrupt by GTM Interrupt DPLL Selection Register 3 setting; */
extern void eiint240(void);
/* Shared interrupt by GTM Interrupt DPLL Selection Register 4 setting; */
extern void eiint241(void);
/* Shared interrupt by GTM Interrupt DPLL Selection Register 5 setting; */
extern void eiint242(void);
/* Shared interrupt by GTM Interrupt DPLL Selection Register 6 setting; */
extern void eiint243(void);
/* Shared interrupt by GTM Interrupt DPLL Selection Register 7 setting; */
extern void eiint244(void);
/* Shared interrupt by GTM Interrupt DPLL Selection Register 8 setting; */
extern void eiint245(void);
/* Shared interrupt by GTM Interrupt DPLL Selection Register 9 setting; */
extern void eiint246(void);
/* Shared interrupt by GTM Interrupt DPLL Selection Register 10 setting; */
extern void eiint247(void);
/* Shared interrupt by GTM Interrupt DPLL Selection Register 11 setting; */
extern void eiint248(void);
/* Shared interrupt by GTM Interrupt DPLL Selection Register 12 setting; */
extern void eiint249(void);
/* Shared interrupt by GTM Interrupt DPLL Selection Register 13 setting; */
extern void eiint250(void);
/* Shared interrupt by GTM Interrupt DPLL Selection Register 14 setting; */
extern void eiint251(void);
/* Shared interrupt by GTM Interrupt DPLL Selection Register 15 setting; */
extern void eiint252(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 900 setting; */
extern void eiint253(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 901 setting; */
extern void eiint254(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 902 setting; */
extern void eiint255(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 903 setting; */
extern void eiint256(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 904 setting; */
extern void eiint257(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 905 setting; */
extern void eiint258(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 906 setting; */
extern void eiint259(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 907 setting; */
extern void eiint260(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 908 setting; */
extern void eiint261(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 909 setting; */
extern void eiint262(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 910 setting; */
extern void eiint263(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 911 setting; */
extern void eiint264(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 912 setting; */
extern void eiint265(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 913 setting; */
extern void eiint266(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 914 setting; */
extern void eiint267(void);
/* Shared interrupt by GTM Interrupt Selection Control Register 915 setting; */
extern void eiint268(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 000 setting; */
extern void eiint269(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 001 setting; */
extern void eiint270(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 002 setting; */
extern void eiint271(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 003 setting; */
extern void eiint272(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 100 setting; */
extern void eiint273(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 101 setting; */
extern void eiint274(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 102 setting; */
extern void eiint275(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 103 setting; */
extern void eiint276(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 200 setting; */
extern void eiint277(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 201 setting; */
extern void eiint278(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 202 setting; */
extern void eiint279(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 203 setting; */
extern void eiint280(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 300 setting; */
extern void eiint281(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 301 setting; */
extern void eiint282(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 302 setting; */
extern void eiint283(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 303 setting; */
extern void eiint284(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 400 setting; */
extern void eiint285(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 401 setting; */
extern void eiint286(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 402 setting; */
extern void eiint287(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 403 setting; */
extern void eiint288(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 500 setting; */
extern void eiint289(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 501 setting; */
extern void eiint290(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 502 setting; */
extern void eiint291(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 503 setting; */
extern void eiint292(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 600 setting; */
extern void eiint293(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 601 setting; */
extern void eiint294(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 602 setting; */
extern void eiint295(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 603 setting; */
extern void eiint296(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 700 setting; */
extern void eiint297(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 701 setting; */
extern void eiint298(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 702 setting; */
extern void eiint299(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 703 setting; */
extern void eiint300(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 800 setting; */
extern void eiint301(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 801 setting; */
extern void eiint302(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 802 setting; */
extern void eiint303(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 803 setting; */
extern void eiint304(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 900 setting; */
extern void eiint305(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 901 setting; */
extern void eiint306(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 902 setting; */
extern void eiint307(void);
/* Shared interrupt by GTM Interrupt 2 Selection Control Register 903 setting; */
extern void eiint308(void);
/* ENCA0 overflow interrupt; */
extern void eiint309(void);
/* ENCA0 capture/compare match interrupt 0; */
extern void eiint310(void);
/* ENCA0 capture/compare match interrupt 1; */
extern void eiint311(void);
/* ENCA0 underflow interrupt; */
extern void eiint312(void);
/* ENCA0 encoder clear interrupt (phase Z); */
extern void eiint313(void);
/* TAPA0 peak interrupt 0; */
extern void eiint314(void);
/* TAPA0 valley interrupt 0; */
extern void eiint315(void);
/* TAPA1 Peak interrupt 0; */
extern void eiint316(void);
/* TAPA1 Valley interrupt 0; */
extern void eiint317(void);
/* TAPA2 Peak interrupt 0; */
extern void eiint318(void);
/* TAPA2 Valley interrupt 0; */
extern void eiint319(void);
/* TAUD0 Channel 1 interrupt; */
extern void eiint320(void);
/* TAUD0 Channel 3 interrupt; */
extern void eiint321(void);
/* TAUD0 Channel 5 interrupt; */
extern void eiint322(void);
/* TAUD0 Channel 7 interrupt; */
extern void eiint323(void);
/* TAUD0 Channel 9 interrupt; */
extern void eiint324(void);
/* TAUD0 Channel 11 interrupt; */
extern void eiint325(void);
/* TAUD0 Channel 13 interrupt; */
extern void eiint326(void);
/* TAUD0 Channel 15 interrupt; */
extern void eiint327(void);
/* TAUD1 Channel 0 interrupt; */
extern void eiint328(void);
/* TAUD1 Channel 1 interrupt; */
extern void eiint329(void);
/* TAUD1 Channel 2 interrupt; */
extern void eiint330(void);
/* TAUD1 Channel 3 interrupt; */
extern void eiint331(void);
/* TAUD1 Channel 4 interrupt; */
extern void eiint332(void);
/* TAUD1 Channel 5 interrupt; */
extern void eiint333(void);
/* TAUD1 Channel 6 interrupt; */
extern void eiint334(void);
/* TAUD1 Channel 7 interrupt; */
extern void eiint335(void);
/* TAUD1 Channel 8 interrupt; */
extern void eiint336(void);
/* TAUD1 Channel 9 interrupt; */
extern void eiint337(void);
/* TAUD1 Channel 10 interrupt; */
extern void eiint338(void);
/* TAUD1 Channel 11 interrupt; */
extern void eiint339(void);
/* TAUD1 Channel 12 interrupt; */
extern void eiint340(void);
/* TAUD1 Channel 13 interrupt; */
extern void eiint341(void);
/* TAUD1 Channel 14 interrupt; */
extern void eiint342(void);
/* TAUD1 Channel 15 interrupt; */
extern void eiint343(void);
/* TAUD2 Channel 0 interrupt; */
extern void eiint344(void);
/* TAUD2 Channel 1 interrupt; */
extern void eiint345(void);
/* TAUD2 Channel 2 interrupt; */
extern void eiint346(void);
/* TAUD2 Channel 3 interrupt; */
extern void eiint347(void);
/* TAUD2 Channel 4 interrupt; */
extern void eiint348(void);
/* TAUD2 Channel 5 interrupt; */
extern void eiint349(void);
/* TAUD2 Channel 6 interrupt; */
extern void eiint350(void);
/* TAUD2 Channel 7 interrupt; */
extern void eiint351(void);
/* TAUD2 Channel 8 interrupt; */
extern void eiint352(void);
/* TAUD2 Channel 9 interrupt; */
extern void eiint353(void);
/* TAUD2 Channel 10 interrupt; */
extern void eiint354(void);
/* TAUD2 Channel 11 interrupt; */
extern void eiint355(void);
/* TAUD2 Channel 12 interrupt; */
extern void eiint356(void);
/* TAUD2 Channel 13 interrupt; */
extern void eiint357(void);
/* TAUD2 Channel 14 interrupt; */
extern void eiint358(void);
/* TAUD2 Channel 15 interrupt; */
extern void eiint359(void);
/* OSTM0 interrupt; */
extern void eiint360(void);
/* OSTM1 interrupt; */
extern void eiint361(void);
/* TSG30 compare match interrupt 0 or TSG30 period interrupt (in HTPWM mode only); */
extern void eiint362(void);
/* TSG30 compare match interrupt 1; */
extern void eiint363(void);
/* TSG30 compare match interrupt 2; */
extern void eiint364(void);
/* TSG30 compare match interrupt 3; */
extern void eiint365(void);
/* TSG30 compare match interrupt 4; */
extern void eiint366(void);
/* TSG30 compare match interrupt 5; */
extern void eiint367(void);
/* TSG30 compare match interrupt 6; */
extern void eiint368(void);
/* TSG30 compare match interrupt 7; */
extern void eiint369(void);
/* TSG30 compare match interrupt 8; */
extern void eiint370(void);
/* TSG30 compare match interrupt 9; */
extern void eiint371(void);
/* TSG30 compare match interrupt 10; */
extern void eiint372(void);
/* TSG30 compare match interrupt 11; */
extern void eiint373(void);
/* TSG30 compare match interrupt 12; */
extern void eiint374(void);
/* TSG30 peak interrupt; */
extern void eiint375(void);
/* TSG30 valley interrupt; */
extern void eiint376(void);
/* TSG30 error interrupt; */
extern void eiint377(void);
/* TSG30 warning interrupt; */
extern void eiint378(void);
/* TSG31 compare match interrupt 0 or TSG31 period interrupt (in HTPWM mode only); */
extern void eiint379(void);
/* TSG31 compare match interrupt 1; */
extern void eiint380(void);
/* TSG31 compare match interrupt 2; */
extern void eiint381(void);
/* TSG31 compare match interrupt 3; */
extern void eiint382(void);
/* TSG31 compare match interrupt 4; */
extern void eiint383(void);
/* TSG31 compare match interrupt 5; */
extern void eiint384(void);
/* TSG31 compare match interrupt 6; */
extern void eiint385(void);
/* TSG31 compare match interrupt 7; */
extern void eiint386(void);
/* TSG31 compare match interrupt 8; */
extern void eiint387(void);
/* TSG31 compare match interrupt 9; */
extern void eiint388(void);
/* TSG31 compare match interrupt 10; */
extern void eiint389(void);
/* TSG31 compare match interrupt 11; */
extern void eiint390(void);
/* TSG31 compare match interrupt 12; */
extern void eiint391(void);
/* TSG31 peak interrupt; */
extern void eiint392(void);
/* TSG31 valley interrupt; */
extern void eiint393(void);
/* TSG31 error interrupt; */
extern void eiint394(void);
/* TSG31 warning interrupt; */
extern void eiint395(void);
/* TSG32 compare match interrupt 0 or TSG32 period interrupt (in HTPWM mode only); */
extern void eiint396(void);
/* TSG32 compare match interrupt 1; */
extern void eiint397(void);
/* TSG32 compare match interrupt 2; */
extern void eiint398(void);
/* TSG32 compare match interrupt 3; */
extern void eiint399(void);
/* TSG32 compare match interrupt 4; */
extern void eiint400(void);
/* TSG32 compare match interrupt 5; */
extern void eiint401(void);
/* TSG32 compare match interrupt 6; */
extern void eiint402(void);
/* TSG32 compare match interrupt 7; */
extern void eiint403(void);
/* TSG32 compare match interrupt 8; */
extern void eiint404(void);
/* TSG32 compare match interrupt 9; */
extern void eiint405(void);
/* TSG32 compare match interrupt 10; */
extern void eiint406(void);
/* TSG32 compare match interrupt 11; */
extern void eiint407(void);
/* TSG32 compare match interrupt 12; */
extern void eiint408(void);
/* TSG32 peak interrupt; */
extern void eiint409(void);
/* TSG32 valley interrupt; */
extern void eiint410(void);
/* TSG32 error interrupt; */
extern void eiint411(void);
/* TSG32 warning interrupt; */
extern void eiint412(void);
/* TPTM up timer interrupt for PE0 with comparison value 0; */
extern void eiint413(void);
/* TPTM up timer interrupt for PE0 with comparison value 1; */
extern void eiint414(void);
/* TPTM up timer interrupt for PE0 with comparison value 2; */
extern void eiint415(void);
/* TPTM up timer interrupt for PE0 with comparison value 3; */
extern void eiint416(void);
/* TPTM up timer interrupt for PE1 with comparison value 0; */
extern void eiint417(void);
/* TPTM up timer interrupt for PE1 with comparison value 1; */
extern void eiint418(void);
/* TPTM up timer interrupt for PE1 with comparison value 2; */
extern void eiint419(void);
/* TPTM up timer interrupt for PE1 with comparison value 3; */
extern void eiint420(void);
/* Phi comparison interrupt output 2 ( RDC3AS0); */
extern void eiint421(void);
/* Phi comparison interrupt output 1 ( RDC3AS0); */
extern void eiint422(void);
/* Phi comparison interrupt output 0 ( RDC3AS0); */
extern void eiint423(void);
/* Fault detection interrupt output ( RDC3AS0); */
extern void eiint424(void);
/* Z signal interrupt output ( RDC3AS0); */
extern void eiint425(void);
/* Excitation zero-crossing interrupt output ( RDC3AS0); */
extern void eiint426(void);
/* Excitation timer interrupt output ( RDC3AS0); */
extern void eiint427(void);
/* BIST end interrupt output ( RDC3AS0); */
extern void eiint428(void);
/* Phi comparison interrupt output 2 ( RDC3AS1); */
extern void eiint429(void);
/* Phi comparison interrupt output 1 ( RDC3AS1); */
extern void eiint430(void);
/* Phi comparison interrupt output 0 ( RDC3AS1); */
extern void eiint431(void);
/* Fault detection interrupt output ( RDC3AS1); */
extern void eiint432(void);
/* Z signal interrupt output ( RDC3AS1); */
extern void eiint433(void);
/* Excitation zero-crossing interrupt output ( RDC3AS1); */
extern void eiint434(void);
/* Excitation timer interrupt output ( RDC3AS1); */
extern void eiint435(void);
/* BIST end interrupt output ( RDC3AS1); */
extern void eiint436(void);
/* Interrupt request signal from AIR; */
extern void eiint437(void);
/* Interrupt request signal from AIR; */
extern void eiint438(void);
/* Interrupt request signal from AIR; */
extern void eiint439(void);
/* Interrupt request signal from AIR; */
extern void eiint440(void);
/* Interrupt request signal from AIR; */
extern void eiint441(void);
/* Interrupt request signal from AIR; */
extern void eiint442(void);
/* Interrupt request signal from AIR; */
extern void eiint443(void);
/* Interrupt request signal from AIR; */
extern void eiint444(void);
/* Interrupt request signal from AIR; */
extern void eiint445(void);
/* Interrupt request signal from AIR; */
extern void eiint446(void);
/* Interrupt request signal from AIR; */
extern void eiint447(void);
/* Interrupt request signal from AIR; */
extern void eiint448(void);
/* Interrupt request signal from AIR; */
extern void eiint449(void);
/* Interrupt request signal from AIR; */
extern void eiint450(void);
/* Interrupt request signal from AIR; */
extern void eiint451(void);
/* Interrupt request signal from AIR; */
extern void eiint452(void);
/* Interrupt request signal from AIR; */
extern void eiint453(void);
/* Interrupt request signal from AIR; */
extern void eiint454(void);
/* Interrupt request signal from AIR; */
extern void eiint455(void);
/* Interrupt request signal from AIR; */
extern void eiint456(void);
/* Interrupt request signal from AIR; */
extern void eiint457(void);
/* Interrupt request signal from AIR; */
extern void eiint458(void);
/* Interrupt request signal from AIR; */
extern void eiint459(void);
/* Interrupt request signal from AIR; */
extern void eiint460(void);
/* Interrupt request signal from AIR; */
extern void eiint461(void);
/* Interrupt request signal from AIR; */
extern void eiint462(void);
/* Interrupt request signal from AIR; */
extern void eiint463(void);
/* Interrupt request signal from AIR; */
extern void eiint464(void);
/* Interrupt request signal from AIR; */
extern void eiint465(void);
/* Interrupt request signal from AIR; */
extern void eiint466(void);
/* Interrupt request signal from AIR; */
extern void eiint467(void);
/* Interrupt request signal from AIR; */
extern void eiint468(void);
/* Interrupt request signal from AIR; */
extern void eiint469(void);
/* Interrupt request signal from AIR; */
extern void eiint470(void);
/* Interrupt request signal from AIR; */
extern void eiint471(void);
/* Interrupt request signal from AIR; */
extern void eiint472(void);
/* Interrupt request signal from AIR; */
extern void eiint473(void);
/* Interrupt request signal from AIR; */
extern void eiint474(void);
/* Interrupt request signal from AIR; */
extern void eiint475(void);
/* Interrupt request signal from AIR; */
extern void eiint476(void);
/* Interrupt request signal from AIR; */
extern void eiint477(void);
/* Interrupt request signal from AIR; */
extern void eiint478(void);
/* Interrupt request signal from AIR; */
extern void eiint479(void);
/* Interrupt request signal from AIR; */
extern void eiint480(void);
/* Interrupt request signal from AIR; */
extern void eiint481(void);
/* Interrupt request signal from AIR; */
extern void eiint482(void);
/* Interrupt request signal from AIR; */
extern void eiint483(void);
/* Interrupt request signal from AIR; */
extern void eiint484(void);
/* Interrupt request signal from AIR; */
extern void eiint485(void);
/* Interrupt request signal from AIR; */
extern void eiint486(void);
/* Interrupt request signal from AIR; */
extern void eiint487(void);
/* Interrupt request signal from AIR; */
extern void eiint488(void);
/* Interrupt request signal from AIR; */
extern void eiint489(void);
/* Interrupt request signal from AIR; */
extern void eiint490(void);
/* Interrupt request signal from AIR; */
extern void eiint491(void);
/* Interrupt request signal from AIR; */
extern void eiint492(void);
/* Interrupt request signal from AIR; */
extern void eiint493(void);
/* Interrupt request signal from AIR; */
extern void eiint494(void);
/* Interrupt request signal from AIR; */
extern void eiint495(void);
/* Interrupt request signal from AIR; */
extern void eiint496(void);
/* Interrupt request signal from AIR; */
extern void eiint497(void);
/* Interrupt request signal from AIR; */
extern void eiint498(void);
/* Interrupt request signal from AIR; */
extern void eiint499(void);
/* Interrupt request signal from AIR; */
extern void eiint500(void);
/* Comparator result interrupt for channel 0; */
extern void eiint501(void);
/* Comparator result interrupt for channel 1; */
extern void eiint502(void);
/* Comparator result interrupt for channel 2; */
extern void eiint503(void);
/* Comparator result interrupt for channel 3; */
extern void eiint504(void);
/* CH0 output data interrupt/CH0 condition match interrupt 0; */
extern void eiint505(void);
/* CH1 output data interrupt/CH1 condition match interrupt 0; */
extern void eiint506(void);
/* CH2 output data interrupt/CH2 condition match interrupt 0; */
extern void eiint507(void);
/* CH3 output data interrupt/CH3 condition match interrupt 0; */
extern void eiint508(void);
/* CH4 output data interrupt/CH4 condition match interrupt 0; */
extern void eiint509(void);
/* CH5 output data interrupt/CH5 condition match interrupt 0; */
extern void eiint510(void);
/* CH6 output data interrupt/CH6 condition match interrupt 0; */
extern void eiint511(void);
/* CH7 output data interrupt/CH7 condition match interrupt 0; */
extern void eiint512(void);
/* CH8 output data interrupt/CH8 condition match interrupt 0; */
extern void eiint513(void);
/* CH9 output data interrupt/CH9 condition match interrupt 0; */
extern void eiint514(void);
/* CH10 output data interrupt/CH10 condition match interrupt 0; */
extern void eiint515(void);
/* CH11 output data interrupt/CH11 condition match interrupt 0; */
extern void eiint516(void);
/* CH12 output data interrupt/CH12 condition match interrupt 0; */
extern void eiint517(void);
/* CH13 output data interrupt/CH13 condition match interrupt 0; */
extern void eiint518(void);
/* CH14 output data interrupt/CH14 condition match interrupt 0; */
extern void eiint519(void);
/* CH15 output data interrupt/CH15 condition match interrupt 0; */
extern void eiint520(void);
/* Error interrupt; */
extern void eiint521(void);
/* CH0 condition match interrupt 1; */
extern void eiint522(void);
/* CH1 condition match interrupt 1; */
extern void eiint523(void);
/* CH2 condition match interrupt 1; */
extern void eiint524(void);
/* CH3 condition match interrupt 1; */
extern void eiint525(void);
/* Subtraction data interrupt 0; */
extern void eiint526(void);
/* Subtraction data interrupt 1; */
extern void eiint527(void);
/* Subtraction data interrupt 2; */
extern void eiint528(void);
/* CH0 Filter Processing End Interrupt Request; */
extern void eiint529(void);
/* CH1 Filter Processing End Interrupt Request; */
extern void eiint530(void);
/* CH2 Filter Processing End Interrupt Request; */
extern void eiint531(void);
/* CH3 Filter Processing End Interrupt Request; */
extern void eiint532(void);
/* CH4 Filter Processing End Interrupt Request; */
extern void eiint533(void);
/* CH5 Filter Processing End Interrupt Request; */
extern void eiint534(void);
/* CH6 Filter Processing End Interrupt Request; */
extern void eiint535(void);
/* CH7 Filter Processing End Interrupt Request; */
extern void eiint536(void);
/* CH8 Filter Processing End Interrupt Request; */
extern void eiint537(void);
/* CH9 Filter Processing End Interrupt Request; */
extern void eiint538(void);
/* CH10 Filter Processing End Interrupt Request; */
extern void eiint539(void);
/* CH11 Filter Processing End Interrupt Request; */
extern void eiint540(void);
/* CH12 Filter Processing End Interrupt Request; */
extern void eiint541(void);
/* CH13 Filter Processing End Interrupt Request; */
extern void eiint542(void);
/* CH14 Filter Processing End Interrupt Request; */
extern void eiint543(void);
/* CH15 Filter Processing End Interrupt Request; */
extern void eiint544(void);
/* CH0 output data interrupt/CH0 condition match interrupt 0; */
extern void eiint545(void);
/* CH1 output data interrupt/CH1 condition match interrupt 0; */
extern void eiint546(void);
/* CH2 output data interrupt/CH2 condition match interrupt 0; */
extern void eiint547(void);
/* CH3 output data interrupt/CH3 condition match interrupt 0; */
extern void eiint548(void);
/* Error interrupt; */
extern void eiint549(void);
/* CH0 condition match interrupt 1; */
extern void eiint550(void);
/* CH1 condition match interrupt 1; */
extern void eiint551(void);
/* CH2 condition match interrupt 1; */
extern void eiint552(void);
/* CH3 condition match interrupt 1; */
extern void eiint553(void);
/* Subtraction data interrupt 0; */
extern void eiint554(void);
/* Subtraction data interrupt 1; */
extern void eiint555(void);
/* Subtraction data interrupt 2; */
extern void eiint556(void);
/* CH0 Filter Processing End Interrupt Request; */
extern void eiint557(void);
/* CH1 Filter Processing End Interrupt Request; */
extern void eiint558(void);
/* CH2 Filter Processing End Interrupt Request; */
extern void eiint559(void);
/* CH3 Filter Processing End Interrupt Request; */
extern void eiint560(void);
/* Buffer-A capture finished interrupt; */
extern void eiint561(void);
/* Buffer-B capture finished interrupt; */
extern void eiint562(void);
/* Error interrupt; */
extern void eiint563(void);
/* MSPI0 Transmit status interrupt for channel 0; */
extern void eiint564(void);
/* MSPI0 Transmit status interrupt for channel 1; */
extern void eiint565(void);
/* MSPI0 Transmit status interrupt for channel 2; */
extern void eiint566(void);
/* MSPI0 Receive status interrupt for channel 0; */
extern void eiint567(void);
/* MSPI0 Receive status interrupt for channel 1; */
extern void eiint568(void);
/* MSPI0 Receive status interrupt for channel 2; */
extern void eiint569(void);
/* MSPI1 Transmit status interrupt for channel 0; */
extern void eiint570(void);
/* MSPI1 Transmit status interrupt for channel 1; */
extern void eiint571(void);
/* MSPI1 Transmit status interrupt for channel 2; */
extern void eiint572(void);
/* MSPI1 Receive status interrupt for channel 0; */
extern void eiint573(void);
/* MSPI1 Receive status interrupt for channel 1; */
extern void eiint574(void);
/* MSPI1 Receive status interrupt for channel 2; */
extern void eiint575(void);
/* MSPI0 Channel selectable Transmit status interrupt; */
extern void eiint576(void);
/* MSPI0 Channel selectable Receive status interrupt; */
extern void eiint577(void);
/* MSPI0 Channel selectable Frame count end interrupt; */
extern void eiint578(void);
/* MSPI0 Channel selectable Error interrupt; */
extern void eiint579(void);
/* MSPI1 Channel selectable Transmit status interrupt; */
extern void eiint580(void);
/* MSPI1 Channel selectable Receive status interrupt; */
extern void eiint581(void);
/* MSPI1 Channel selectable Frame count end interrupt; */
extern void eiint582(void);
/* MSPI1 Channel selectable Error interrupt; */
extern void eiint583(void);
/* MSPI2 Channel selectable Transmit status interrupt; */
extern void eiint584(void);
/* MSPI2 Channel selectable Receive status interrupt; */
extern void eiint585(void);
/* MSPI2 Channel selectable Frame count end interrupt; */
extern void eiint586(void);
/* MSPI2 Channel selectable Error interrupt; */
extern void eiint587(void);
/* MSPI3 Channel selectable Transmit status interrupt; */
extern void eiint588(void);
/* MSPI3 Channel selectable Receive status interrupt; */
extern void eiint589(void);
/* MSPI3 Channel selectable Frame count end interrupt; */
extern void eiint590(void);
/* MSPI3 Channel selectable Error interrupt; */
extern void eiint591(void);
/* MSPI4 Channel selectable Transmit status interrupt; */
extern void eiint592(void);
/* MSPI4 Channel selectable Receive status interrupt; */
extern void eiint593(void);
/* MSPI4 Channel selectable Frame count end interrupt; */
extern void eiint594(void);
/* MSPI4 Channel selectable Error interrupt; */
extern void eiint595(void);
/* MSPI5 Channel selectable Transmit status interrupt; */
extern void eiint596(void);
/* MSPI5 Channel selectable Receive status interrupt; */
extern void eiint597(void);
/* MSPI5 Channel selectable Frame count end interrupt; */
extern void eiint598(void);
/* MSPI5 Channel selectable Error interrupt; */
extern void eiint599(void);
/* MSPI6 Channel selectable Transmit status interrupt; */
extern void eiint600(void);
/* MSPI6 Channel selectable Receive status interrupt; */
extern void eiint601(void);
/* MSPI6 Channel selectable Frame count end interrupt; */
extern void eiint602(void);
/* MSPI6 Channel selectable Error interrupt; */
extern void eiint603(void);
/* Data transmission started/complete; */
extern void eiint604(void);
/* Command frame transmission complete/started; */
extern void eiint605(void);
/* Emergency frame transmission complete; */
extern void eiint606(void);
/* Data receive; */
extern void eiint607(void);
/* Upstream error/ Timeout detected/ Data lost; */
extern void eiint608(void);
/* Upstream frame received; */
extern void eiint609(void);
/* Upstream external interrupt 0; */
extern void eiint610(void);
/* Upstream external interrupt 1; */
extern void eiint611(void);
/* Data transmission started/complete; */
extern void eiint612(void);
/* Command frame transmission complete/started; */
extern void eiint613(void);
/* Emergency frame transmission complete; */
extern void eiint614(void);
/* Data receive; */
extern void eiint615(void);
/* Upstream error/ Timeout detected/ Data lost; */
extern void eiint616(void);
/* Upstream frame received; */
extern void eiint617(void);
/* Upstream external interrupt 0; */
extern void eiint618(void);
/* Upstream external interrupt 1; */
extern void eiint619(void);
/* RLIN30 interrupt; */
extern void eiint620(void);
/* RLIN30 transmit interrupt; */
extern void eiint621(void);
/* RLIN30 receive completion interrupt; */
extern void eiint622(void);
/* RLIN30 status interrupt; */
extern void eiint623(void);
/* Reserved; */
extern void eiint624(void);
/* RLIN31 interrupt; */
extern void eiint625(void);
/* RLIN31 transmit interrupt; */
extern void eiint626(void);
/* RLIN31 receive completion interrupt; */
extern void eiint627(void);
/* RLIN31 status interrupt; */
extern void eiint628(void);
/* Reserved; */
extern void eiint629(void);
/* RLIN32 interrupt; */
extern void eiint630(void);
/* RLIN32 transmit interrupt; */
extern void eiint631(void);
/* RLIN32 receive completion interrupt; */
extern void eiint632(void);
/* RLIN32 status interrupt; */
extern void eiint633(void);
/* Reserved; */
extern void eiint634(void);
/* RLIN33 interrupt; */
extern void eiint635(void);
/* RLIN33 transmit interrupt; */
extern void eiint636(void);
/* RLIN33 receive completion interrupt; */
extern void eiint637(void);
/* RLIN33 status interrupt; */
extern void eiint638(void);
/* Reserved; */
extern void eiint639(void);
/* RLIN34 interrupt; */
extern void eiint640(void);
/* RLIN34 transmit interrupt; */
extern void eiint641(void);
/* RLIN34 receive completion interrupt; */
extern void eiint642(void);
/* RLIN34 status interrupt; */
extern void eiint643(void);
/* RLIN35 interrupt; */
extern void eiint644(void);
/* RLIN35 transmit interrupt; */
extern void eiint645(void);
/* RLIN35 receive completion interrupt; */
extern void eiint646(void);
/* RLIN35 status interrupt; */
extern void eiint647(void);
/* RLIN323 interrupt; */
extern void eiint648(void);
/* RLIN323 transmit interrupt; */
extern void eiint649(void);
/* RLIN323 receive completion interrupt; */
extern void eiint650(void);
/* RLIN323 status interrupt; */
extern void eiint651(void);
/* RSCAN0 CAN global error interrupt; */
extern void eiint652(void);
/* RSCAN0 CAN receive FIFO interrupt; */
extern void eiint653(void);
/* RSCAN1 CAN global error interrupt; */
extern void eiint654(void);
/* RSCAN1 CAN receive FIFO interrupt; */
extern void eiint655(void);
/* RSCAN2 CAN global error interrupt; */
extern void eiint656(void);
/* RSCAN2 CAN receive FIFO interrupt; */
extern void eiint657(void);
/* CAN0 error interrupt; */
extern void eiint658(void);
/* CAN0 transmit/receive FIFO receive completion interrupt; */
extern void eiint659(void);
/* CAN0 transmit interrupt; */
extern void eiint660(void);
/* CAN0 virtual machine TX interrupt; */
extern void eiint661(void);
/* CAN0 virtual machine RX interrupt; */
extern void eiint662(void);
/* CAN0 virtual machine error interrupt; */
extern void eiint663(void);
/* CAN1 error interrupt; */
extern void eiint664(void);
/* CAN1 transmit/receive FIFO receive completion interrupt; */
extern void eiint665(void);
/* CAN1 transmit interrupt; */
extern void eiint666(void);
/* CAN1 virtual machine TX interrupt; */
extern void eiint667(void);
/* CAN1 virtual machine RX interrupt; */
extern void eiint668(void);
/* CAN1 virtual machine error interrupt; */
extern void eiint669(void);
/* CAN2 error interrupt; */
extern void eiint670(void);
/* CAN2 transmit/receive FIFO receive completion interrupt; */
extern void eiint671(void);
/* CAN2 transmit interrupt; */
extern void eiint672(void);
/* CAN2 virtual machine TX interrupt; */
extern void eiint673(void);
/* CAN2 virtual machine RX interrupt; */
extern void eiint674(void);
/* CAN2 virtual machine error interrupt; */
extern void eiint675(void);
/* CAN3 error interrupt; */
extern void eiint676(void);
/* CAN3 transmit/receive FIFO receive completion interrupt; */
extern void eiint677(void);
/* CAN3 transmit interrupt; */
extern void eiint678(void);
/* CAN3 virtual machine TX interrupt; */
extern void eiint679(void);
/* CAN3 virtual machine RX interrupt; */
extern void eiint680(void);
/* CAN3 virtual machine error interrupt; */
extern void eiint681(void);
/* CAN4 error interrupt; */
extern void eiint682(void);
/* CAN4 transmit/receive FIFO receive completion interrupt; */
extern void eiint683(void);
/* CAN4 transmit interrupt; */
extern void eiint684(void);
/* CAN4 virtual machine TX interrupt; */
extern void eiint685(void);
/* CAN4 virtual machine RX interrupt; */
extern void eiint686(void);
/* CAN4 virtual machine error interrupt; */
extern void eiint687(void);
/* CAN5 error interrupt; */
extern void eiint688(void);
/* CAN5 transmit/receive FIFO receive completion interrupt; */
extern void eiint689(void);
/* CAN5 transmit interrupt; */
extern void eiint690(void);
/* CAN5 virtual machine TX interrupt; */
extern void eiint691(void);
/* CAN5 virtual machine RX interrupt; */
extern void eiint692(void);
/* CAN5 virtual machine error interrupt; */
extern void eiint693(void);
/* CAN6 error interrupt; */
extern void eiint694(void);
/* CAN6 transmit/receive FIFO receive completion interrupt; */
extern void eiint695(void);
/* CAN6 transmit interrupt; */
extern void eiint696(void);
/* CAN6 virtual machine TX interrupt; */
extern void eiint697(void);
/* CAN6 virtual machine RX interrupt; */
extern void eiint698(void);
/* CAN6 virtual machine error interrupt; */
extern void eiint699(void);
/* CAN7 error interrupt; */
extern void eiint700(void);
/* CAN7 transmit/receive FIFO receive completion interrupt; */
extern void eiint701(void);
/* CAN7 transmit interrupt; */
extern void eiint702(void);
/* CAN7 virtual machine TX interrupt; */
extern void eiint703(void);
/* CAN7 virtual machine RX interrupt; */
extern void eiint704(void);
/* CAN7 virtual machine error interrupt; */
extern void eiint705(void);
/* Completion of ACEU2 encryption or decryption with CPU transfer; */
extern void eiint706(void);
/* Completion of ACEU3 encryption or decryption with CPU transfer; */
extern void eiint707(void);
/* ETNE0 (Ether L2 Switch) interrupt 0; */
extern void eiint708(void);
/* ETNE0 (Ether L2 Switch) interrupt 1; */
extern void eiint709(void);
/* ETNE0 (Ether L2 Switch) interrupt 2; */
extern void eiint710(void);
/* ETNE0 (Ether L2 Switch) interrupt 3; */
extern void eiint711(void);
/* ETNE0 (Ether L2 Switch) interrupt 4; */
extern void eiint712(void);
/* ETNE0 (Ether L2 Switch) interrupt 5; */
extern void eiint713(void);
/* ETNE0 (Ether L2 Switch) interrupt 6; */
extern void eiint714(void);
/* ETNE0 (Ether L2 Switch) interrupt 7; */
extern void eiint715(void);
/* ETNE0 (Ether L2 Switch) interrupt 8; */
extern void eiint716(void);
/* CPU0 Code Flash bus port (Ch3); */
extern void eiint717(void);
/* CPU0 Code Flash bus port (Ch4); */
extern void eiint718(void);
/* CPU0 Code Flash bus port (Ch5); */
extern void eiint719(void);
/* CPU0 Code Flash bus port (Ch6); */
extern void eiint720(void);
/* CPU0 Code Flash bus port (Ch7); */
extern void eiint721(void);
/* FLXA0 line 0 interrupt; */
extern void eiint722(void);
/* FLXA0 line 1 interrupt; */
extern void eiint723(void);
/* FLXA0 Timer 0 interrupt; */
extern void eiint724(void);
/* FLXA0 Timer 1 interrupt; */
extern void eiint725(void);
/* FLXA0 Timer 2 interrupt; */
extern void eiint726(void);
/* FLXA0 FIFO data available (FIFO is not empty) interrupt; */
extern void eiint727(void);
/* FLXA0 FIFO transfer warning interrupt; */
extern void eiint728(void);
/* FLXA0 Output transfer warning interrupt; */
extern void eiint729(void);
/* FLXA0 Output transfer done interrupt; */
extern void eiint730(void);
/* FLXA0 Input queue full interrupt; */
extern void eiint731(void);
/* FLXA0 Input queue empty interrupt; */
extern void eiint732(void);
/* RSENT0 receive interrupt; */
extern void eiint733(void);
/* RSENT1 receive interrupt; */
extern void eiint734(void);
/* RSENT2 receive interrupt; */
extern void eiint735(void);
/* RSENT3 receive interrupt; */
extern void eiint736(void);
/* RSENT4 receive interrupt; */
extern void eiint737(void);
/* RSENT5 receive interrupt; */
extern void eiint738(void);
/* RSENT6 receive interrupt; */
extern void eiint739(void);
/* RSENT7 receive interrupt; */
extern void eiint740(void);
/* RSENT8 receive interrupt; */
extern void eiint741(void);
/* RSENT9 receive interrupt; */
extern void eiint742(void);
/* RSENT0 status interrupt; */
extern void eiint743(void);
/* RSENT1 status interrupt; */
extern void eiint744(void);
/* RSENT2 status interrupt; */
extern void eiint745(void);
/* RSENT3 status interrupt; */
extern void eiint746(void);
/* RSENT4 status interrupt; */
extern void eiint747(void);
/* RSENT5 status interrupt; */
extern void eiint748(void);
/* RSENT6 status interrupt; */
extern void eiint749(void);
/* RSENT7 status interrupt; */
extern void eiint750(void);
/* RSENT8 status interrupt; */
extern void eiint751(void);
/* RSENT9 status interrupt; */
extern void eiint752(void);
/* Inter-PE interrupt from ICUMHB to INTC2(Interrupt request from ICUP to CPU (PE)); */
extern void eiint753(void);
/* Inter-PE interrupt from ICUMHB to INTC2(Interrupt request from ICUP to CPU (PE)); */
extern void eiint754(void);
/* Inter-PE interrupt from ICUMHB to INTC2(Interrupt request from ICUP to CPU (PE)); */
extern void eiint755(void);
/* Inter-PE interrupt from ICUMHB to INTC2(Interrupt request from ICUP to CPU (PE)); */
extern void eiint756(void);
/* Inter-PE interrupt from ICUMHB to INTC2(Interrupt request from ICUP to CPU (PE)); */
extern void eiint757(void);
/* Inter-PE interrupt from ICUMHB to INTC2(Interrupt request from ICUP to CPU (PE)); */
extern void eiint758(void);
/* Inter-PE interrupt from ICUMHB to INTC2(Interrupt request from ICUP to CPU (PE)); */
extern void eiint759(void);
/* Inter-PE interrupt from ICUMHB to INTC2(Interrupt request from ICUP to CPU (PE)); */
extern void eiint760(void);
/* ICUMHB fatal error notification; */
extern void eiint761(void);
/* OTS0 Error interrupt; */
extern void eiint762(void);
/* OTS0 Temperature measurement end interrupt; */
extern void eiint763(void);
/* OTS0 Temperature rise/drop interrupt; */
extern void eiint764(void);
/* External interrupt 0; */
extern void eiint765(void);
/* External interrupt 1; */
extern void eiint766(void);
/* External interrupt 2; */
extern void eiint767(void);
/* External interrupt 3; */
extern void eiint768(void);
/* External interrupt 4; */
extern void eiint769(void);
/* External interrupt 5; */
extern void eiint770(void);
/* External interrupt 6; */
extern void eiint771(void);
/* External interrupt 7; */
extern void eiint772(void);
/* External interrupt 8; */
extern void eiint773(void);
/* External interrupt 9; */
extern void eiint774(void);
/* External interrupt 10; */
extern void eiint775(void);
/* External interrupt 11; */
extern void eiint776(void);
/* External interrupt 12; */
extern void eiint777(void);
/* External interrupt 13; */
extern void eiint778(void);
/* External interrupt 14; */
extern void eiint779(void);
/* External interrupt 15; */
extern void eiint780(void);
/* External interrupt 16; */
extern void eiint781(void);
/* External interrupt 17; */
extern void eiint782(void);
/* External interrupt 18; */
extern void eiint783(void);
/* External interrupt 19; */
extern void eiint784(void);
/* External interrupt 20; */
extern void eiint785(void);
/* External interrupt 21; */
extern void eiint786(void);
/* External interrupt 22; */
extern void eiint787(void);
/* External interrupt 23; */
extern void eiint788(void);
/* External interrupt 24; */
extern void eiint789(void);
/* External interrupt 25; */
extern void eiint790(void);
/* External interrupt 26; */
extern void eiint791(void);
/* External interrupt 27; */
extern void eiint792(void);
/* External interrupt 28; */
extern void eiint793(void);
/* External interrupt 29; */
extern void eiint794(void);
/* External interrupt 30; */
extern void eiint795(void);
/* External interrupt 31; */
extern void eiint796(void);
/* External interrupt 32; */
extern void eiint797(void);
/* External interrupt 33; */
extern void eiint798(void);
/* External interrupt 34; */
extern void eiint799(void);
/* External interrupt 35; */
extern void eiint800(void);
/* External interrupt 36; */
extern void eiint801(void);
/* External interrupt 37; */
extern void eiint802(void);
/* External interrupt 38; */
extern void eiint803(void);
/* External interrupt 39; */
extern void eiint804(void);
/* Edge detection of RLIN30 received data; */
extern void eiint805(void);
/* Edge detection of RLIN31 received data; */
extern void eiint806(void);
/* Edge detection of RSCFD0 received data; */
extern void eiint807(void);
/* Edge detection of RSCFD1 received data; */
extern void eiint808(void);
/* Edge detection of FLXA0 ch A received data; */
extern void eiint809(void);
/* Dedicated interrupt for on-chip debug function; */
extern void eiint810(void);
/* Emergency Hi-Z input 0; */
extern void eiint811(void);
/* Emergency Hi-Z input 1; */
extern void eiint812(void);
/* Emergency Hi-Z input 2; */
extern void eiint813(void);
/* Emergency Hi-Z input 3; */
extern void eiint814(void);
/* Emergency Hi-Z input 4; */
extern void eiint815(void);
/* Emergency Hi-Z input 5; */
extern void eiint816(void);
/* External interrupt 40; */
extern void eiint817(void);
/* External interrupt 41; */
extern void eiint818(void);
/* External interrupt 42; */
extern void eiint819(void);
/* External interrupt 43; */
extern void eiint820(void);
/* Reserved; */
extern void eiint821(void);
/* CPU0 Code Flash bus port (Ch0); */
extern void eiint822(void);
/* CPU0 Code Flash bus port (Ch1); */
extern void eiint823(void);
/* CPU0 Code Flash bus port (Ch2); */
extern void eiint824(void);
/* sDMAC1 channel 0 transfer end or descriptor step end interrupt; */
extern void eiint825(void);
/* sDMAC1 channel 1 transfer end or descriptor step end interrupt; */
extern void eiint826(void);
/* sDMAC1 channel 2 transfer end or descriptor step end interrupt; */
extern void eiint827(void);
/* sDMAC1 channel 3 transfer end or descriptor step end interrupt; */
extern void eiint828(void);
/* sDMAC1 channel 4 transfer end or descriptor step end interrupt; */
extern void eiint829(void);
/* sDMAC1 channel 5 transfer end or descriptor step end interrupt; */
extern void eiint830(void);
/* sDMAC1 channel 6 transfer end or descriptor step end interrupt; */
extern void eiint831(void);
/* sDMAC1 channel 7 transfer end or descriptor step end interrupt; */
extern void eiint832(void);
/* sDMAC1 channel 8 transfer end or descriptor step end interrupt; */
extern void eiint833(void);
/* sDMAC1 channel 9 transfer end or descriptor step end interrupt; */
extern void eiint834(void);
/* sDMAC1 channel 10 transfer end or descriptor step end interrupt; */
extern void eiint835(void);
/* sDMAC1 channel 11 transfer end or descriptor step end interrupt; */
extern void eiint836(void);
/* sDMAC1 channel 12 transfer end or descriptor step end interrupt; */
extern void eiint837(void);
/* sDMAC1 channel 13 transfer end or descriptor step end interrupt; */
extern void eiint838(void);
/* sDMAC1 channel 14 transfer end or descriptor step end interrupt; */
extern void eiint839(void);
/* sDMAC1 channel 15 transfer end or descriptor step end interrupt; */
extern void eiint840(void);
/* OSTM2 interrupt; */
extern void eiint841(void);
/* OSTM3 interrupt; */
extern void eiint842(void);
/* TPTM up timer interrupt for PE2 with comparison value 0; */
extern void eiint843(void);
/* TPTM up timer interrupt for PE2 with comparison value 1; */
extern void eiint844(void);
/* TPTM up timer interrupt for PE2 with comparison value 2; */
extern void eiint845(void);
/* TPTM up timer interrupt for PE2 with comparison value 3; */
extern void eiint846(void);
/* TPTM up timer interrupt for PE3 with comparison value 0; */
extern void eiint847(void);
/* TPTM up timer interrupt for PE3 with comparison value 1; */
extern void eiint848(void);
/* TPTM up timer interrupt for PE3 with comparison value 2; */
extern void eiint849(void);
/* TPTM up timer interrupt for PE3 with comparison value 3; */
extern void eiint850(void);
/* MSPI7 Channel selectable Transmit status interrupt; */
extern void eiint851(void);
/* MSPI7 Channel selectable Receive status interrupt; */
extern void eiint852(void);
/* MSPI7 Channel selectable Frame count end interrupt; */
extern void eiint853(void);
/* MSPI7 Channel selectable Error interrupt; */
extern void eiint854(void);
/* MSPI8 Channel selectable Transmit status interrupt; */
extern void eiint855(void);
/* MSPI8 Channel selectable Receive status interrupt; */
extern void eiint856(void);
/* MSPI8 Channel selectable Frame count end interrupt; */
extern void eiint857(void);
/* MSPI8 Channel selectable Error interrupt; */
extern void eiint858(void);
/* MSPI9 Channel selectable Transmit status interrupt; */
extern void eiint859(void);
/* MSPI9 Channel selectable Receive status interrupt; */
extern void eiint860(void);
/* MSPI9 Channel selectable Frame count end interrupt; */
extern void eiint861(void);
/* MSPI9 Channel selectable Error interrupt; */
extern void eiint862(void);
/* Data transmission started/complete; */
extern void eiint863(void);
/* Command frame transmission complete/started; */
extern void eiint864(void);
/* Emergency frame transmission complete; */
extern void eiint865(void);
/* Data receive; */
extern void eiint866(void);
/* Upstream error/ Timeout detected/ Data lost; */
extern void eiint867(void);
/* Upstream frame received; */
extern void eiint868(void);
/* Upstream external interrupt 0; */
extern void eiint869(void);
/* Upstream external interrupt 1; */
extern void eiint870(void);
/* RHSIF0 Transmit complete interrupt; */
extern void eiint871(void);
/* RHSIF0 Transmit exception interrupt; */
extern void eiint872(void);
/* RHSIF0 Receive complete interrupt; */
extern void eiint873(void);
/* RHSIF0 Receive exception interrupt; */
extern void eiint874(void);
/* RHSIF0 ICLC receive interrupt; */
extern void eiint875(void);
/* RHSIF0 Channel 0 interrupt; */
extern void eiint876(void);
/* RHSIF0 Channel 1 interrupt; */
extern void eiint877(void);
/* RHSIF0 Channel 2 interrupt; */
extern void eiint878(void);
/* RHSIF0 Channel 3 interrupt; */
extern void eiint879(void);
/* RHSIF0 Stream interrupt; */
extern void eiint880(void);
/* RHSIF0 Error interrupt/Security interrupt; */
extern void eiint881(void);
/* RIIC0 receive end interrupt; */
extern void eiint882(void);
/* RIIC0 transmit data empty interrupt; */
extern void eiint883(void);
/* RIIC1 receive end interrupt; */
extern void eiint884(void);
/* RIIC1 transmit data empty interrupt; */
extern void eiint885(void);
/* RIIC0 communication error or event generation interrupt; */
extern void eiint886(void);
/* RIIC0 transmit end interrupt; */
extern void eiint887(void);
/* RIIC1 communication error or event generation interrupt; */
extern void eiint888(void);
/* RIIC1 transmit end interrupt; */
extern void eiint889(void);
/* RSENT10 receive interrupt; */
extern void eiint890(void);
/* RSENT11 receive interrupt; */
extern void eiint891(void);
/* RSENT12 receive interrupt; */
extern void eiint892(void);
/* RSENT13 receive interrupt; */
extern void eiint893(void);
/* RSENT14 receive interrupt; */
extern void eiint894(void);
/* RSENT15 receive interrupt; */
extern void eiint895(void);
/* RSENT16 receive interrupt; */
extern void eiint896(void);
/* RSENT17 receive interrupt; */
extern void eiint897(void);
/* RSENT18 receive interrupt; */
extern void eiint898(void);
/* RSENT19 receive interrupt; */
extern void eiint899(void);
/* RSENT20 receive interrupt; */
extern void eiint900(void);
/* RSENT21 receive interrupt; */
extern void eiint901(void);
/* RSENT22 receive interrupt; */
extern void eiint902(void);
/* RSENT23 receive interrupt; */
extern void eiint903(void);
/* RSENT24 receive interrupt; */
extern void eiint904(void);
/* RSENT25 receive interrupt; */
extern void eiint905(void);
/* RSENT26 receive interrupt; */
extern void eiint906(void);
/* RSENT27 receive interrupt; */
extern void eiint907(void);
/* RSENT28 receive interrupt; */
extern void eiint908(void);
/* RSENT29 receive interrupt; */
extern void eiint909(void);
/* RSENT10 status interrupt; */
extern void eiint910(void);
/* RSENT11 status interrupt; */
extern void eiint911(void);
/* RSENT12 status interrupt; */
extern void eiint912(void);
/* RSENT13 status interrupt; */
extern void eiint913(void);
/* RSENT14 status interrupt; */
extern void eiint914(void);
/* RSENT15 status interrupt; */
extern void eiint915(void);
/* RSENT16 status interrupt; */
extern void eiint916(void);
/* RSENT17 status interrupt; */
extern void eiint917(void);
/* RSENT18 status interrupt; */
extern void eiint918(void);
/* RSENT19 status interrupt; */
extern void eiint919(void);
/* RSENT20 status interrupt; */
extern void eiint920(void);
/* RSENT21 status interrupt; */
extern void eiint921(void);
/* RSENT22 status interrupt; */
extern void eiint922(void);
/* RSENT23 status interrupt; */
extern void eiint923(void);
/* RSENT24 status interrupt; */
extern void eiint924(void);
/* RSENT25 status interrupt; */
extern void eiint925(void);
/* RSENT26 status interrupt; */
extern void eiint926(void);
/* RSENT27 status interrupt; */
extern void eiint927(void);
/* RSENT28 status interrupt; */
extern void eiint928(void);
/* RSENT29 status interrupt; */
extern void eiint929(void);
/* PSI50 status interrupt; */
extern void eiint930(void);
/* PSI50 receive interrupt; */
extern void eiint931(void);
/* PSI50 transfer interrupt; */
extern void eiint932(void);
/* PSI51 status interrupt; */
extern void eiint933(void);
/* PSI51 receive interrupt; */
extern void eiint934(void);
/* PSI51 transfer interrupt; */
extern void eiint935(void);
/* PSI52 status interrupt; */
extern void eiint936(void);
/* PSI52 receive interrupt; */
extern void eiint937(void);
/* PSI52 transfer interrupt; */
extern void eiint938(void);
/* PSI53 status interrupt; */
extern void eiint939(void);
/* PSI53 receive interrupt; */
extern void eiint940(void);
/* PSI53 transfer interrupt; */
extern void eiint941(void);
/* Interruption reports the end of all channel enable; */
extern void eiint942(void);
/* PSI5S0 Communication interrupt for CH0; */
extern void eiint943(void);
/* PSI5S0 Communication interrupt for CH1; */
extern void eiint944(void);
/* PSI5S0 Communication interrupt for CH2; */
extern void eiint945(void);
/* PSI5S0 Communication interrupt for CH3; */
extern void eiint946(void);
/* PSI5S0 Communication interrupt for CH4; */
extern void eiint947(void);
/* PSI5S0 Communication interrupt for CH5; */
extern void eiint948(void);
/* PSI5S0 Communication interrupt for CH6; */
extern void eiint949(void);
/* PSI5S0 Communication interrupt for CH7; */
extern void eiint950(void);
/* PSI5S1 Communication interrupt for CH0; */
extern void eiint951(void);
/* PSI5S1 Communication interrupt for CH1; */
extern void eiint952(void);
/* PSI5S1 Communication interrupt for CH2; */
extern void eiint953(void);
/* PSI5S1 Communication interrupt for CH3; */
extern void eiint954(void);
/* PSI5S1 Communication interrupt for CH4; */
extern void eiint955(void);
/* PSI5S1 Communication interrupt for CH5; */
extern void eiint956(void);
/* PSI5S1 Communication interrupt for CH6; */
extern void eiint957(void);
/* PSI5S1 Communication interrupt for CH7; */
extern void eiint958(void);
/* MMCA interrupt; */
extern void eiint959(void);
/* TAUJ2 Channel 0 interrupt; */
extern void eiint960(void);
/* TAUJ2 Channel 1 interrupt; */
extern void eiint961(void);
/* TAUJ2 Channel 2 interrupt; */
extern void eiint962(void);
/* TAUJ2 Channel 3 interrupt; */
extern void eiint963(void);
/* ETNF0 Data related interrupt; */
extern void eiint964(void);
/* ETNF0 Error related interrupt; */
extern void eiint965(void);
/* ETNF0 Management related interrupt; */
extern void eiint966(void);
/* ETNF0 MAC interrupt; */
extern void eiint967(void);
/* OSTM4 interrupt; */
extern void eiint968(void);
/* OSTM5 interrupt; */
extern void eiint969(void);
/* RTCA0 1-second interval interrupt; */
extern void eiint970(void);
/* RTCA0 Alarm interrupt; */
extern void eiint971(void);
/* RTCA0 Fixed interval interrupt; */
extern void eiint972(void);
/* TPTM up timer interrupt for PE4 with comparison value 0; */
extern void eiint973(void);
/* TPTM up timer interrupt for PE4 with comparison value 1; */
extern void eiint974(void);
/* TPTM up timer interrupt for PE4 with comparison value 2; */
extern void eiint975(void);
/* TPTM up timer interrupt for PE4 with comparison value 3; */
extern void eiint976(void);
/* TPTM up timer interrupt for PE5 with comparison value 0; */
extern void eiint977(void);
/* TPTM up timer interrupt for PE5 with comparison value 1; */
extern void eiint978(void);
/* TPTM up timer interrupt for PE5 with comparison value 2; */
extern void eiint979(void);
/* TPTM up timer interrupt for PE5 with comparison value 3; */
extern void eiint980(void);
/* WDTBA interrupt; */
extern void eiint981(void);
/* Completion of ACEU2 encryption or decryption with DTF transfer; */
extern void eiint982(void);
/* ACEU BUS slave error of ACEU2 during DTF transfer; */
extern void eiint983(void);
/* Compare error from duplex circuit of ACEU2; */
extern void eiint984(void);
/* Completion of ACEU3 encryption or decryption with DTF transfer; */
extern void eiint985(void);
/* ACEU BUS slave error of ACEU3 during DTF transfer; */
extern void eiint986(void);
/* Compare error from duplex circuit of ACEU3; */
extern void eiint987(void);
/* Comparator result interrupt for channel 4; */
extern void eiint988(void);
/* Comparator result interrupt for channel 5; */
extern void eiint989(void);
/* Comparator result interrupt for channel 6; */
extern void eiint990(void);
/* Comparator result interrupt for channel 7; */
extern void eiint991(void);
/* RLIN36 interrupt; */
extern void eiint992(void);
/* RLIN36 transmit interrupt; */
extern void eiint993(void);
/* RLIN36 receive completion interrupt; */
extern void eiint994(void);
/* RLIN36 status interrupt; */
extern void eiint995(void);
/* RLIN37 interrupt; */
extern void eiint996(void);
/* RLIN37 transmit interrupt; */
extern void eiint997(void);
/* RLIN37 receive completion interrupt; */
extern void eiint998(void);
/* RLIN37 status interrupt; */
extern void eiint999(void);
/* LPS0 Port polling end interrupt; */
extern void eiint1000(void);
/* LPS0 Digital port error interrupt; */
extern void eiint1001(void);
/* Reserved; */
extern void eiint1002(void);
/* Comparator result interrupt for channel 8; */
extern void eiint1003(void);
/* Comparator result interrupt for channel 9; */
extern void eiint1004(void);
/* CAN8 error interrupt; */
extern void eiint1005(void);
/* CAN8 transmit/receive FIFO receive completion interrupt; */
extern void eiint1006(void);
/* CAN8 transmit interrupt; */
extern void eiint1007(void);
/* CAN8 virtual machine TX interrupt; */
extern void eiint1008(void);
/* CAN8 virtual machine RX interrupt; */
extern void eiint1009(void);
/* CAN8 virtual machine error interrupt; */
extern void eiint1010(void);
/* CAN9 error interrupt; */
extern void eiint1011(void);
/* CAN9 transmit/receive FIFO receive completion interrupt; */
extern void eiint1012(void);
/* CAN9 transmit interrupt; */
extern void eiint1013(void);
/* CAN9 virtual machine TX interrupt; */
extern void eiint1014(void);
/* CAN9 virtual machine RX interrupt; */
extern void eiint1015(void);
/* CAN9 virtual machine error interrupt; */
extern void eiint1016(void);
/* XCAN0 functional relevant; */
extern void eiint1017(void);
/* XCAN0 functional error relevant; */
extern void eiint1018(void);
/* XCAN0 safety relevant; */
extern void eiint1019(void);
/* XCAN1 functional relevant; */
extern void eiint1020(void);
/* XCAN1 functional error relevant; */
extern void eiint1021(void);
/* XCAN1 safety relevant; */
extern void eiint1022(void);
/* External interrupt 45; */
extern void eiint1023(void);

#pragma ghs startdata
#pragma ghs section rodata="EIINTTBL_PE0"

void * const INT_Vectors_PE0[] = {
    /* IPIR CH0 interrupt; */
    (void *)eiint0,
    /* IPIR CH1 interrupt; */
    (void *)eiint1,
    /* IPIR CH2 interrupt; */
    (void *)eiint2,
    /* IPIR CH3 interrupt; */
    (void *)eiint3,
    /* Broadcast notification 0; */
    (void *)eiint4,
    /* Broadcast notification 1; */
    (void *)eiint5,
    /* Broadcast notification 2; */
    (void *)eiint6,
    /* Broadcast notification 3; */
    (void *)eiint7,
    /* ECM maskable interrupt (EI level); */
    (void *)eiint8,
    /* DCLS error interrupt (EI level); */
    (void *)eiint9,
    /* TAUD0 Channel 0 interrupt; */
    (void *)eiint10,
    /* TAUD0 Channel 2 interrupt; */
    (void *)eiint11,
    /* TAUD0 Channel 4 interrupt; */
    (void *)eiint12,
    /* TAUD0 Channel 6 interrupt; */
    (void *)eiint13,
    /* Software interrupt 0; */
    (void *)eiint14,
    /* Software interrupt 1; */
    (void *)eiint15,
    /* Software interrupt 2; */
    (void *)eiint16,
    /* Software interrupt 3; */
    (void *)eiint17,
    /* Reserved; */
    (void *)eiint18,
    /* Reserved; */
    (void *)eiint19,
    /* Reserved; */
    (void *)eiint20,
    /* Inter-PE interrupt from ICUMHB to PE0(Single interrupt request from ICUP to CPU (PE)); */
    (void *)eiint21,
    /* WDTB0 interrupt; */
    (void *)eiint22,
    /* TAUD0 Channel 8 interrupt; */
    (void *)eiint23,
    /* TAUD0 Channel 10 interrupt; */
    (void *)eiint24,
    /* TAUD0 Channel 12 interrupt; */
    (void *)eiint25,
    /* TAUD0 Channel 14 interrupt; */
    (void *)eiint26,
    /* Reserved; */
    (void *)eiint27,
    /* Reserved; */
    (void *)eiint28,
    /* sDMAC0 address error or sDMAC1 address error interrupt; */
    (void *)eiint29,
    /* DTS transfer error; */
    (void *)eiint30,
    /* TPTM Interval timer Interrupt for PE0; */
    (void *)eiint31,
    /* interrupt for degradation; */
    (void *)eiint32,
    /* Unimplemented area access detected in a request to instrumentation RAM; */
    (void *)eiint33,
    /* Mask generation notification interrupt signal for execution / access hold request; */
    (void *)eiint34,
    /* FPSYS0 Flash sequencer processing end interrupt; */
    (void *)eiint35,
    /* External interrupt 44; */
    (void *)eiint36,
    /* FPSYS2 Flash sequencer processing end interrupt; */
    (void *)eiint37,
    /* iso_dfa_int_swc[0]; */
    (void *)eiint38,
    /* iso_dfa_int_swc[1]; */
    (void *)eiint39,
    /* iso_dfa_int_swc[2]; */
    (void *)eiint40,
    /* iso_dfa_int_swc[3]; */
    (void *)eiint41,
    /* iso_dfa_int_dfa[0]; */
    (void *)eiint42,
    /* iso_dfa_int_dfa[1]; */
    (void *)eiint43,
    /* iso_dfa_int_dfa[2]; */
    (void *)eiint44,
    /* iso_dfa_int_dfa[3]; */
    (void *)eiint45,
    /* iso_dfa_int_dfa[4]; */
    (void *)eiint46,
    /* TPBA0 Period match detection interrupt; */
    (void *)eiint47,
    /* TPBA0 Duty match detection interrupt; */
    (void *)eiint48,
    /* TPBA0 Pattern number matching detection interrupt; */
    (void *)eiint49,
    /* TPBA1 Period match detection interrupt; */
    (void *)eiint50,
    /* TPBA1 Duty match detection interrupt; */
    (void *)eiint51,
    /* TPBA1 Pattern number matching detection interrupt; */
    (void *)eiint52,
    /* OSPI0 Interrupt pulse signal by factors excluding errors; */
    (void *)eiint53,
    /* Completion of ACEU0 encryption or decryption with CPU transfer; */
    (void *)eiint54,
    /* Completion of ACEU0 encryption or decryption with DTF transfer; */
    (void *)eiint55,
    /* ACEU BUS slave error of ACEU0 during DTF transfer; */
    (void *)eiint56,
    /* Compare error from duplex circuit of ACEU0; */
    (void *)eiint57,
    /* Completion of ACEU1 encryption or decryption with CPU transfer; */
    (void *)eiint58,
    /* Completion of ACEU1 encryption or decryption with DTF transfer; */
    (void *)eiint59,
    /* ACEU BUS slave error of ACEU1 during DTF transfer; */
    (void *)eiint60,
    /* Compare error from duplex circuit of ACEU1; */
    (void *)eiint61,
    /* DTS ch31-0 transfer end; */
    (void *)eiint62,
    /* DTS ch63-32 transfer end; */
    (void *)eiint63,
    /* DTS ch95-64 transfer end; */
    (void *)eiint64,
    /* DTS ch127-96 transfer end; */
    (void *)eiint65,
    /* DTS ch31-0 transfer count match; */
    (void *)eiint66,
    /* DTS ch63-32 transfer count match; */
    (void *)eiint67,
    /* DTS ch95-64 transfer count match; */
    (void *)eiint68,
    /* DTS ch127-96 transfer count match; */
    (void *)eiint69,
    /* sDMAC0 channel 0 transfer end or descriptor step end interrupt; */
    (void *)eiint70,
    /* sDMAC0 channel 1 transfer end or descriptor step end interrupt; */
    (void *)eiint71,
    /* sDMAC0 channel 2 transfer end or descriptor step end interrupt; */
    (void *)eiint72,
    /* sDMAC0 channel 3 transfer end or descriptor step end interrupt; */
    (void *)eiint73,
    /* sDMAC0 channel 4 transfer end or descriptor step end interrupt; */
    (void *)eiint74,
    /* sDMAC0 channel 5 transfer end or descriptor step end interrupt; */
    (void *)eiint75,
    /* sDMAC0 channel 6 transfer end or descriptor step end interrupt; */
    (void *)eiint76,
    /* sDMAC0 channel 7 transfer end or descriptor step end interrupt; */
    (void *)eiint77,
    /* sDMAC0 channel 8 transfer end or descriptor step end interrupt; */
    (void *)eiint78,
    /* sDMAC0 channel 9 transfer end or descriptor step end interrupt; */
    (void *)eiint79,
    /* sDMAC0 channel 10 transfer end or descriptor step end interrupt; */
    (void *)eiint80,
    /* sDMAC0 channel 11 transfer end or descriptor step end interrupt; */
    (void *)eiint81,
    /* sDMAC0 channel 12 transfer end or descriptor step end interrupt; */
    (void *)eiint82,
    /* sDMAC0 channel 13 transfer end or descriptor step end interrupt; */
    (void *)eiint83,
    /* sDMAC0 channel 14 transfer end or descriptor step end interrupt; */
    (void *)eiint84,
    /* sDMAC0 channel 15 transfer end or descriptor step end interrupt; */
    (void *)eiint85,
    /* Shared interrupt by GTM Interrupt Selection Control Register 000 setting; */
    (void *)eiint86,
    /* Shared interrupt by GTM Interrupt Selection Control Register 001 setting; */
    (void *)eiint87,
    /* Shared interrupt by GTM Interrupt Selection Control Register 002 setting; */
    (void *)eiint88,
    /* Shared interrupt by GTM Interrupt Selection Control Register 003 setting; */
    (void *)eiint89,
    /* Shared interrupt by GTM Interrupt Selection Control Register 004 setting; */
    (void *)eiint90,
    /* Shared interrupt by GTM Interrupt Selection Control Register 005 setting; */
    (void *)eiint91,
    /* Shared interrupt by GTM Interrupt Selection Control Register 006 setting; */
    (void *)eiint92,
    /* Shared interrupt by GTM Interrupt Selection Control Register 007 setting; */
    (void *)eiint93,
    /* Shared interrupt by GTM Interrupt Selection Control Register 008 setting; */
    (void *)eiint94,
    /* Shared interrupt by GTM Interrupt Selection Control Register 009 setting; */
    (void *)eiint95,
    /* Shared interrupt by GTM Interrupt Selection Control Register 010 setting; */
    (void *)eiint96,
    /* Shared interrupt by GTM Interrupt Selection Control Register 011 setting; */
    (void *)eiint97,
    /* Shared interrupt by GTM Interrupt Selection Control Register 012 setting; */
    (void *)eiint98,
    /* Shared interrupt by GTM Interrupt Selection Control Register 013 setting; */
    (void *)eiint99,
    /* Shared interrupt by GTM Interrupt Selection Control Register 014 setting; */
    (void *)eiint100,
    /* Shared interrupt by GTM Interrupt Selection Control Register 015 setting; */
    (void *)eiint101,
    /* Shared interrupt by GTM Interrupt Selection Control Register 100 setting; */
    (void *)eiint102,
    /* Shared interrupt by GTM Interrupt Selection Control Register 101 setting; */
    (void *)eiint103,
    /* Shared interrupt by GTM Interrupt Selection Control Register 102 setting; */
    (void *)eiint104,
    /* Shared interrupt by GTM Interrupt Selection Control Register 103 setting; */
    (void *)eiint105,
    /* Shared interrupt by GTM Interrupt Selection Control Register 104 setting; */
    (void *)eiint106,
    /* Shared interrupt by GTM Interrupt Selection Control Register 105 setting; */
    (void *)eiint107,
    /* Shared interrupt by GTM Interrupt Selection Control Register 106 setting; */
    (void *)eiint108,
    /* Shared interrupt by GTM Interrupt Selection Control Register 107 setting; */
    (void *)eiint109,
    /* Shared interrupt by GTM Interrupt Selection Control Register 108 setting; */
    (void *)eiint110,
    /* Shared interrupt by GTM Interrupt Selection Control Register 109 setting; */
    (void *)eiint111,
    /* Shared interrupt by GTM Interrupt Selection Control Register 110 setting; */
    (void *)eiint112,
    /* Shared interrupt by GTM Interrupt Selection Control Register 111 setting; */
    (void *)eiint113,
    /* Shared interrupt by GTM Interrupt Selection Control Register 112 setting; */
    (void *)eiint114,
    /* Shared interrupt by GTM Interrupt Selection Control Register 113 setting; */
    (void *)eiint115,
    /* Shared interrupt by GTM Interrupt Selection Control Register 114 setting; */
    (void *)eiint116,
    /* Shared interrupt by GTM Interrupt Selection Control Register 115 setting; */
    (void *)eiint117,
    /* Shared interrupt by GTM Interrupt Selection Control Register 200 setting; */
    (void *)eiint118,
    /* Shared interrupt by GTM Interrupt Selection Control Register 201 setting; */
    (void *)eiint119,
    /* Shared interrupt by GTM Interrupt Selection Control Register 202 setting; */
    (void *)eiint120,
    /* Shared interrupt by GTM Interrupt Selection Control Register 203 setting; */
    (void *)eiint121,
    /* Shared interrupt by GTM Interrupt Selection Control Register 204 setting; */
    (void *)eiint122,
    /* Shared interrupt by GTM Interrupt Selection Control Register 205 setting; */
    (void *)eiint123,
    /* Shared interrupt by GTM Interrupt Selection Control Register 206 setting; */
    (void *)eiint124,
    /* Shared interrupt by GTM Interrupt Selection Control Register 207 setting; */
    (void *)eiint125,
    /* Shared interrupt by GTM Interrupt Selection Control Register 208 setting; */
    (void *)eiint126,
    /* Shared interrupt by GTM Interrupt Selection Control Register 209 setting; */
    (void *)eiint127,
    /* Shared interrupt by GTM Interrupt Selection Control Register 210 setting; */
    (void *)eiint128,
    /* Shared interrupt by GTM Interrupt Selection Control Register 211 setting; */
    (void *)eiint129,
    /* Shared interrupt by GTM Interrupt Selection Control Register 212 setting; */
    (void *)eiint130,
    /* Shared interrupt by GTM Interrupt Selection Control Register 213 setting; */
    (void *)eiint131,
    /* Shared interrupt by GTM Interrupt Selection Control Register 214 setting; */
    (void *)eiint132,
    /* Shared interrupt by GTM Interrupt Selection Control Register 215 setting; */
    (void *)eiint133,
    /* Shared interrupt by GTM Interrupt Selection Control Register 300 setting; */
    (void *)eiint134,
    /* Shared interrupt by GTM Interrupt Selection Control Register 301 setting; */
    (void *)eiint135,
    /* Shared interrupt by GTM Interrupt Selection Control Register 302 setting; */
    (void *)eiint136,
    /* Shared interrupt by GTM Interrupt Selection Control Register 303 setting; */
    (void *)eiint137,
    /* Shared interrupt by GTM Interrupt Selection Control Register 304 setting; */
    (void *)eiint138,
    /* Shared interrupt by GTM Interrupt Selection Control Register 305 setting; */
    (void *)eiint139,
    /* Shared interrupt by GTM Interrupt Selection Control Register 306 setting; */
    (void *)eiint140,
    /* Shared interrupt by GTM Interrupt Selection Control Register 307 setting; */
    (void *)eiint141,
    /* Shared interrupt by GTM Interrupt Selection Control Register 308 setting; */
    (void *)eiint142,
    /* Shared interrupt by GTM Interrupt Selection Control Register 309 setting; */
    (void *)eiint143,
    /* Shared interrupt by GTM Interrupt Selection Control Register 310 setting; */
    (void *)eiint144,
    /* Shared interrupt by GTM Interrupt Selection Control Register 311 setting; */
    (void *)eiint145,
    /* Shared interrupt by GTM Interrupt Selection Control Register 312 setting; */
    (void *)eiint146,
    /* Shared interrupt by GTM Interrupt Selection Control Register 313 setting; */
    (void *)eiint147,
    /* Shared interrupt by GTM Interrupt Selection Control Register 314 setting; */
    (void *)eiint148,
    /* Shared interrupt by GTM Interrupt Selection Control Register 315 setting; */
    (void *)eiint149,
    /* Shared interrupt by GTM Interrupt Selection Control Register 400 setting; */
    (void *)eiint150,
    /* Shared interrupt by GTM Interrupt Selection Control Register 401 setting; */
    (void *)eiint151,
    /* Shared interrupt by GTM Interrupt Selection Control Register 402 setting; */
    (void *)eiint152,
    /* Shared interrupt by GTM Interrupt Selection Control Register 403 setting; */
    (void *)eiint153,
    /* Shared interrupt by GTM Interrupt Selection Control Register 404 setting; */
    (void *)eiint154,
    /* Shared interrupt by GTM Interrupt Selection Control Register 405 setting; */
    (void *)eiint155,
    /* Shared interrupt by GTM Interrupt Selection Control Register 406 setting; */
    (void *)eiint156,
    /* Shared interrupt by GTM Interrupt Selection Control Register 407 setting; */
    (void *)eiint157,
    /* Shared interrupt by GTM Interrupt Selection Control Register 408 setting; */
    (void *)eiint158,
    /* Shared interrupt by GTM Interrupt Selection Control Register 409 setting; */
    (void *)eiint159,
    /* Shared interrupt by GTM Interrupt Selection Control Register 410 setting; */
    (void *)eiint160,
    /* Shared interrupt by GTM Interrupt Selection Control Register 411 setting; */
    (void *)eiint161,
    /* Shared interrupt by GTM Interrupt Selection Control Register 412 setting; */
    (void *)eiint162,
    /* Shared interrupt by GTM Interrupt Selection Control Register 413 setting; */
    (void *)eiint163,
    /* Shared interrupt by GTM Interrupt Selection Control Register 414 setting; */
    (void *)eiint164,
    /* Shared interrupt by GTM Interrupt Selection Control Register 415 setting; */
    (void *)eiint165,
    /* Shared interrupt by GTM Interrupt Selection Control Register 500 setting; */
    (void *)eiint166,
    /* Shared interrupt by GTM Interrupt Selection Control Register 501 setting; */
    (void *)eiint167,
    /* Shared interrupt by GTM Interrupt Selection Control Register 502 setting; */
    (void *)eiint168,
    /* Shared interrupt by GTM Interrupt Selection Control Register 503 setting; */
    (void *)eiint169,
    /* Shared interrupt by GTM Interrupt Selection Control Register 504 setting; */
    (void *)eiint170,
    /* Shared interrupt by GTM Interrupt Selection Control Register 505 setting; */
    (void *)eiint171,
    /* Shared interrupt by GTM Interrupt Selection Control Register 506 setting; */
    (void *)eiint172,
    /* Shared interrupt by GTM Interrupt Selection Control Register 507 setting; */
    (void *)eiint173,
    /* Shared interrupt by GTM Interrupt Selection Control Register 508 setting; */
    (void *)eiint174,
    /* Shared interrupt by GTM Interrupt Selection Control Register 509 setting; */
    (void *)eiint175,
    /* Shared interrupt by GTM Interrupt Selection Control Register 510 setting; */
    (void *)eiint176,
    /* Shared interrupt by GTM Interrupt Selection Control Register 511 setting; */
    (void *)eiint177,
    /* Shared interrupt by GTM Interrupt Selection Control Register 512 setting; */
    (void *)eiint178,
    /* Shared interrupt by GTM Interrupt Selection Control Register 513 setting; */
    (void *)eiint179,
    /* Shared interrupt by GTM Interrupt Selection Control Register 514 setting; */
    (void *)eiint180,
    /* Shared interrupt by GTM Interrupt Selection Control Register 515 setting; */
    (void *)eiint181,
    /* Shared interrupt by GTM Interrupt Selection Control Register 600 setting; */
    (void *)eiint182,
    /* Shared interrupt by GTM Interrupt Selection Control Register 601 setting; */
    (void *)eiint183,
    /* Shared interrupt by GTM Interrupt Selection Control Register 602 setting; */
    (void *)eiint184,
    /* Shared interrupt by GTM Interrupt Selection Control Register 603 setting; */
    (void *)eiint185,
    /* Shared interrupt by GTM Interrupt Selection Control Register 604 setting; */
    (void *)eiint186,
    /* Shared interrupt by GTM Interrupt Selection Control Register 605 setting; */
    (void *)eiint187,
    /* Shared interrupt by GTM Interrupt Selection Control Register 606 setting; */
    (void *)eiint188,
    /* Shared interrupt by GTM Interrupt Selection Control Register 607 setting; */
    (void *)eiint189,
    /* Shared interrupt by GTM Interrupt Selection Control Register 608 setting; */
    (void *)eiint190,
    /* Shared interrupt by GTM Interrupt Selection Control Register 609 setting; */
    (void *)eiint191,
    /* Shared interrupt by GTM Interrupt Selection Control Register 610 setting; */
    (void *)eiint192,
    /* Shared interrupt by GTM Interrupt Selection Control Register 611 setting; */
    (void *)eiint193,
    /* Shared interrupt by GTM Interrupt Selection Control Register 612 setting; */
    (void *)eiint194,
    /* Shared interrupt by GTM Interrupt Selection Control Register 613 setting; */
    (void *)eiint195,
    /* Shared interrupt by GTM Interrupt Selection Control Register 614 setting; */
    (void *)eiint196,
    /* Shared interrupt by GTM Interrupt Selection Control Register 615 setting; */
    (void *)eiint197,
    /* Shared interrupt by GTM Interrupt Selection Control Register 700 setting; */
    (void *)eiint198,
    /* Shared interrupt by GTM Interrupt Selection Control Register 701 setting; */
    (void *)eiint199,
    /* Shared interrupt by GTM Interrupt Selection Control Register 702 setting; */
    (void *)eiint200,
    /* Shared interrupt by GTM Interrupt Selection Control Register 703 setting; */
    (void *)eiint201,
    /* Shared interrupt by GTM Interrupt Selection Control Register 704 setting; */
    (void *)eiint202,
    /* Shared interrupt by GTM Interrupt Selection Control Register 705 setting; */
    (void *)eiint203,
    /* Shared interrupt by GTM Interrupt Selection Control Register 706 setting; */
    (void *)eiint204,
    /* Shared interrupt by GTM Interrupt Selection Control Register 707 setting; */
    (void *)eiint205,
    /* Shared interrupt by GTM Interrupt Selection Control Register 708 setting; */
    (void *)eiint206,
    /* Shared interrupt by GTM Interrupt Selection Control Register 709 setting; */
    (void *)eiint207,
    /* Shared interrupt by GTM Interrupt Selection Control Register 710 setting; */
    (void *)eiint208,
    /* Shared interrupt by GTM Interrupt Selection Control Register 711 setting; */
    (void *)eiint209,
    /* Shared interrupt by GTM Interrupt Selection Control Register 712 setting; */
    (void *)eiint210,
    /* Shared interrupt by GTM Interrupt Selection Control Register 713 setting; */
    (void *)eiint211,
    /* Shared interrupt by GTM Interrupt Selection Control Register 714 setting; */
    (void *)eiint212,
    /* Shared interrupt by GTM Interrupt Selection Control Register 715 setting; */
    (void *)eiint213,
    /* Shared interrupt by GTM Interrupt Selection Control Register 800 setting; */
    (void *)eiint214,
    /* Shared interrupt by GTM Interrupt Selection Control Register 801 setting; */
    (void *)eiint215,
    /* Shared interrupt by GTM Interrupt Selection Control Register 802 setting; */
    (void *)eiint216,
    /* Shared interrupt by GTM Interrupt Selection Control Register 803 setting; */
    (void *)eiint217,
    /* Shared interrupt by GTM Interrupt Selection Control Register 804 setting; */
    (void *)eiint218,
    /* Shared interrupt by GTM Interrupt Selection Control Register 805 setting; */
    (void *)eiint219,
    /* Shared interrupt by GTM Interrupt Selection Control Register 806 setting; */
    (void *)eiint220,
    /* Shared interrupt by GTM Interrupt Selection Control Register 807 setting; */
    (void *)eiint221,
    /* Shared interrupt by GTM Interrupt Selection Control Register 808 setting; */
    (void *)eiint222,
    /* Shared interrupt by GTM Interrupt Selection Control Register 809 setting; */
    (void *)eiint223,
    /* Shared interrupt by GTM Interrupt Selection Control Register 810 setting; */
    (void *)eiint224,
    /* Shared interrupt by GTM Interrupt Selection Control Register 811 setting; */
    (void *)eiint225,
    /* Shared interrupt by GTM Interrupt Selection Control Register 812 setting; */
    (void *)eiint226,
    /* Shared interrupt by GTM Interrupt Selection Control Register 813 setting; */
    (void *)eiint227,
    /* Shared interrupt by GTM Interrupt Selection Control Register 814 setting; */
    (void *)eiint228,
    /* Shared interrupt by GTM Interrupt Selection Control Register 815 setting; */
    (void *)eiint229,
    /* AEI Shared interrupt; */
    (void *)eiint230,
    /* ARU_NEW_DATA0 interrupt; */
    (void *)eiint231,
    /* ARU_NEW_DATA1 interrupt; */
    (void *)eiint232,
    /* ARU_ACC_ACK interrupt; */
    (void *)eiint233,
    /* BRC Shared interrupt; */
    (void *)eiint234,
    /* CMP Shared interrupt; */
    (void *)eiint235,
    /* GTM Error interrupt; */
    (void *)eiint236,
    /* Shared interrupt by GTM Interrupt DPLL Selection Register 0 setting; */
    (void *)eiint237,
    /* Shared interrupt by GTM Interrupt DPLL Selection Register 1 setting; */
    (void *)eiint238,
    /* Shared interrupt by GTM Interrupt DPLL Selection Register 2 setting; */
    (void *)eiint239,
    /* Shared interrupt by GTM Interrupt DPLL Selection Register 3 setting; */
    (void *)eiint240,
    /* Shared interrupt by GTM Interrupt DPLL Selection Register 4 setting; */
    (void *)eiint241,
    /* Shared interrupt by GTM Interrupt DPLL Selection Register 5 setting; */
    (void *)eiint242,
    /* Shared interrupt by GTM Interrupt DPLL Selection Register 6 setting; */
    (void *)eiint243,
    /* Shared interrupt by GTM Interrupt DPLL Selection Register 7 setting; */
    (void *)eiint244,
    /* Shared interrupt by GTM Interrupt DPLL Selection Register 8 setting; */
    (void *)eiint245,
    /* Shared interrupt by GTM Interrupt DPLL Selection Register 9 setting; */
    (void *)eiint246,
    /* Shared interrupt by GTM Interrupt DPLL Selection Register 10 setting; */
    (void *)eiint247,
    /* Shared interrupt by GTM Interrupt DPLL Selection Register 11 setting; */
    (void *)eiint248,
    /* Shared interrupt by GTM Interrupt DPLL Selection Register 12 setting; */
    (void *)eiint249,
    /* Shared interrupt by GTM Interrupt DPLL Selection Register 13 setting; */
    (void *)eiint250,
    /* Shared interrupt by GTM Interrupt DPLL Selection Register 14 setting; */
    (void *)eiint251,
    /* Shared interrupt by GTM Interrupt DPLL Selection Register 15 setting; */
    (void *)eiint252,
    /* Shared interrupt by GTM Interrupt Selection Control Register 900 setting; */
    (void *)eiint253,
    /* Shared interrupt by GTM Interrupt Selection Control Register 901 setting; */
    (void *)eiint254,
    /* Shared interrupt by GTM Interrupt Selection Control Register 902 setting; */
    (void *)eiint255,
    /* Shared interrupt by GTM Interrupt Selection Control Register 903 setting; */
    (void *)eiint256,
    /* Shared interrupt by GTM Interrupt Selection Control Register 904 setting; */
    (void *)eiint257,
    /* Shared interrupt by GTM Interrupt Selection Control Register 905 setting; */
    (void *)eiint258,
    /* Shared interrupt by GTM Interrupt Selection Control Register 906 setting; */
    (void *)eiint259,
    /* Shared interrupt by GTM Interrupt Selection Control Register 907 setting; */
    (void *)eiint260,
    /* Shared interrupt by GTM Interrupt Selection Control Register 908 setting; */
    (void *)eiint261,
    /* Shared interrupt by GTM Interrupt Selection Control Register 909 setting; */
    (void *)eiint262,
    /* Shared interrupt by GTM Interrupt Selection Control Register 910 setting; */
    (void *)eiint263,
    /* Shared interrupt by GTM Interrupt Selection Control Register 911 setting; */
    (void *)eiint264,
    /* Shared interrupt by GTM Interrupt Selection Control Register 912 setting; */
    (void *)eiint265,
    /* Shared interrupt by GTM Interrupt Selection Control Register 913 setting; */
    (void *)eiint266,
    /* Shared interrupt by GTM Interrupt Selection Control Register 914 setting; */
    (void *)eiint267,
    /* Shared interrupt by GTM Interrupt Selection Control Register 915 setting; */
    (void *)eiint268,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 000 setting; */
    (void *)eiint269,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 001 setting; */
    (void *)eiint270,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 002 setting; */
    (void *)eiint271,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 003 setting; */
    (void *)eiint272,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 100 setting; */
    (void *)eiint273,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 101 setting; */
    (void *)eiint274,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 102 setting; */
    (void *)eiint275,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 103 setting; */
    (void *)eiint276,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 200 setting; */
    (void *)eiint277,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 201 setting; */
    (void *)eiint278,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 202 setting; */
    (void *)eiint279,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 203 setting; */
    (void *)eiint280,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 300 setting; */
    (void *)eiint281,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 301 setting; */
    (void *)eiint282,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 302 setting; */
    (void *)eiint283,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 303 setting; */
    (void *)eiint284,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 400 setting; */
    (void *)eiint285,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 401 setting; */
    (void *)eiint286,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 402 setting; */
    (void *)eiint287,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 403 setting; */
    (void *)eiint288,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 500 setting; */
    (void *)eiint289,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 501 setting; */
    (void *)eiint290,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 502 setting; */
    (void *)eiint291,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 503 setting; */
    (void *)eiint292,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 600 setting; */
    (void *)eiint293,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 601 setting; */
    (void *)eiint294,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 602 setting; */
    (void *)eiint295,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 603 setting; */
    (void *)eiint296,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 700 setting; */
    (void *)eiint297,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 701 setting; */
    (void *)eiint298,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 702 setting; */
    (void *)eiint299,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 703 setting; */
    (void *)eiint300,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 800 setting; */
    (void *)eiint301,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 801 setting; */
    (void *)eiint302,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 802 setting; */
    (void *)eiint303,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 803 setting; */
    (void *)eiint304,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 900 setting; */
    (void *)eiint305,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 901 setting; */
    (void *)eiint306,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 902 setting; */
    (void *)eiint307,
    /* Shared interrupt by GTM Interrupt 2 Selection Control Register 903 setting; */
    (void *)eiint308,
    /* ENCA0 overflow interrupt; */
    (void *)eiint309,
    /* ENCA0 capture/compare match interrupt 0; */
    (void *)eiint310,
    /* ENCA0 capture/compare match interrupt 1; */
    (void *)eiint311,
    /* ENCA0 underflow interrupt; */
    (void *)eiint312,
    /* ENCA0 encoder clear interrupt (phase Z); */
    (void *)eiint313,
    /* TAPA0 peak interrupt 0; */
    (void *)eiint314,
    /* TAPA0 valley interrupt 0; */
    (void *)eiint315,
    /* TAPA1 Peak interrupt 0; */
    (void *)eiint316,
    /* TAPA1 Valley interrupt 0; */
    (void *)eiint317,
    /* TAPA2 Peak interrupt 0; */
    (void *)eiint318,
    /* TAPA2 Valley interrupt 0; */
    (void *)eiint319,
    /* TAUD0 Channel 1 interrupt; */
    (void *)eiint320,
    /* TAUD0 Channel 3 interrupt; */
    (void *)eiint321,
    /* TAUD0 Channel 5 interrupt; */
    (void *)eiint322,
    /* TAUD0 Channel 7 interrupt; */
    (void *)eiint323,
    /* TAUD0 Channel 9 interrupt; */
    (void *)eiint324,
    /* TAUD0 Channel 11 interrupt; */
    (void *)eiint325,
    /* TAUD0 Channel 13 interrupt; */
    (void *)eiint326,
    /* TAUD0 Channel 15 interrupt; */
    (void *)eiint327,
    /* TAUD1 Channel 0 interrupt; */
    (void *)eiint328,
    /* TAUD1 Channel 1 interrupt; */
    (void *)eiint329,
    /* TAUD1 Channel 2 interrupt; */
    (void *)eiint330,
    /* TAUD1 Channel 3 interrupt; */
    (void *)eiint331,
    /* TAUD1 Channel 4 interrupt; */
    (void *)eiint332,
    /* TAUD1 Channel 5 interrupt; */
    (void *)eiint333,
    /* TAUD1 Channel 6 interrupt; */
    (void *)eiint334,
    /* TAUD1 Channel 7 interrupt; */
    (void *)eiint335,
    /* TAUD1 Channel 8 interrupt; */
    (void *)eiint336,
    /* TAUD1 Channel 9 interrupt; */
    (void *)eiint337,
    /* TAUD1 Channel 10 interrupt; */
    (void *)eiint338,
    /* TAUD1 Channel 11 interrupt; */
    (void *)eiint339,
    /* TAUD1 Channel 12 interrupt; */
    (void *)eiint340,
    /* TAUD1 Channel 13 interrupt; */
    (void *)eiint341,
    /* TAUD1 Channel 14 interrupt; */
    (void *)eiint342,
    /* TAUD1 Channel 15 interrupt; */
    (void *)eiint343,
    /* TAUD2 Channel 0 interrupt; */
    (void *)eiint344,
    /* TAUD2 Channel 1 interrupt; */
    (void *)eiint345,
    /* TAUD2 Channel 2 interrupt; */
    (void *)eiint346,
    /* TAUD2 Channel 3 interrupt; */
    (void *)eiint347,
    /* TAUD2 Channel 4 interrupt; */
    (void *)eiint348,
    /* TAUD2 Channel 5 interrupt; */
    (void *)eiint349,
    /* TAUD2 Channel 6 interrupt; */
    (void *)eiint350,
    /* TAUD2 Channel 7 interrupt; */
    (void *)eiint351,
    /* TAUD2 Channel 8 interrupt; */
    (void *)eiint352,
    /* TAUD2 Channel 9 interrupt; */
    (void *)eiint353,
    /* TAUD2 Channel 10 interrupt; */
    (void *)eiint354,
    /* TAUD2 Channel 11 interrupt; */
    (void *)eiint355,
    /* TAUD2 Channel 12 interrupt; */
    (void *)eiint356,
    /* TAUD2 Channel 13 interrupt; */
    (void *)eiint357,
    /* TAUD2 Channel 14 interrupt; */
    (void *)eiint358,
    /* TAUD2 Channel 15 interrupt; */
    (void *)eiint359,
    /* OSTM0 interrupt; */
    (void *)eiint360,
    /* OSTM1 interrupt; */
    (void *)eiint361,
    /* TSG30 compare match interrupt 0 or TSG30 period interrupt (in HTPWM mode only); */
    (void *)eiint362,
    /* TSG30 compare match interrupt 1; */
    (void *)eiint363,
    /* TSG30 compare match interrupt 2; */
    (void *)eiint364,
    /* TSG30 compare match interrupt 3; */
    (void *)eiint365,
    /* TSG30 compare match interrupt 4; */
    (void *)eiint366,
    /* TSG30 compare match interrupt 5; */
    (void *)eiint367,
    /* TSG30 compare match interrupt 6; */
    (void *)eiint368,
    /* TSG30 compare match interrupt 7; */
    (void *)eiint369,
    /* TSG30 compare match interrupt 8; */
    (void *)eiint370,
    /* TSG30 compare match interrupt 9; */
    (void *)eiint371,
    /* TSG30 compare match interrupt 10; */
    (void *)eiint372,
    /* TSG30 compare match interrupt 11; */
    (void *)eiint373,
    /* TSG30 compare match interrupt 12; */
    (void *)eiint374,
    /* TSG30 peak interrupt; */
    (void *)eiint375,
    /* TSG30 valley interrupt; */
    (void *)eiint376,
    /* TSG30 error interrupt; */
    (void *)eiint377,
    /* TSG30 warning interrupt; */
    (void *)eiint378,
    /* TSG31 compare match interrupt 0 or TSG31 period interrupt (in HTPWM mode only); */
    (void *)eiint379,
    /* TSG31 compare match interrupt 1; */
    (void *)eiint380,
    /* TSG31 compare match interrupt 2; */
    (void *)eiint381,
    /* TSG31 compare match interrupt 3; */
    (void *)eiint382,
    /* TSG31 compare match interrupt 4; */
    (void *)eiint383,
    /* TSG31 compare match interrupt 5; */
    (void *)eiint384,
    /* TSG31 compare match interrupt 6; */
    (void *)eiint385,
    /* TSG31 compare match interrupt 7; */
    (void *)eiint386,
    /* TSG31 compare match interrupt 8; */
    (void *)eiint387,
    /* TSG31 compare match interrupt 9; */
    (void *)eiint388,
    /* TSG31 compare match interrupt 10; */
    (void *)eiint389,
    /* TSG31 compare match interrupt 11; */
    (void *)eiint390,
    /* TSG31 compare match interrupt 12; */
    (void *)eiint391,
    /* TSG31 peak interrupt; */
    (void *)eiint392,
    /* TSG31 valley interrupt; */
    (void *)eiint393,
    /* TSG31 error interrupt; */
    (void *)eiint394,
    /* TSG31 warning interrupt; */
    (void *)eiint395,
    /* TSG32 compare match interrupt 0 or TSG32 period interrupt (in HTPWM mode only); */
    (void *)eiint396,
    /* TSG32 compare match interrupt 1; */
    (void *)eiint397,
    /* TSG32 compare match interrupt 2; */
    (void *)eiint398,
    /* TSG32 compare match interrupt 3; */
    (void *)eiint399,
    /* TSG32 compare match interrupt 4; */
    (void *)eiint400,
    /* TSG32 compare match interrupt 5; */
    (void *)eiint401,
    /* TSG32 compare match interrupt 6; */
    (void *)eiint402,
    /* TSG32 compare match interrupt 7; */
    (void *)eiint403,
    /* TSG32 compare match interrupt 8; */
    (void *)eiint404,
    /* TSG32 compare match interrupt 9; */
    (void *)eiint405,
    /* TSG32 compare match interrupt 10; */
    (void *)eiint406,
    /* TSG32 compare match interrupt 11; */
    (void *)eiint407,
    /* TSG32 compare match interrupt 12; */
    (void *)eiint408,
    /* TSG32 peak interrupt; */
    (void *)eiint409,
    /* TSG32 valley interrupt; */
    (void *)eiint410,
    /* TSG32 error interrupt; */
    (void *)eiint411,
    /* TSG32 warning interrupt; */
    (void *)eiint412,
    /* TPTM up timer interrupt for PE0 with comparison value 0; */
    (void *)eiint413,
    /* TPTM up timer interrupt for PE0 with comparison value 1; */
    (void *)eiint414,
    /* TPTM up timer interrupt for PE0 with comparison value 2; */
    (void *)eiint415,
    /* TPTM up timer interrupt for PE0 with comparison value 3; */
    (void *)eiint416,
    /* TPTM up timer interrupt for PE1 with comparison value 0; */
    (void *)eiint417,
    /* TPTM up timer interrupt for PE1 with comparison value 1; */
    (void *)eiint418,
    /* TPTM up timer interrupt for PE1 with comparison value 2; */
    (void *)eiint419,
    /* TPTM up timer interrupt for PE1 with comparison value 3; */
    (void *)eiint420,
    /* Phi comparison interrupt output 2 ( RDC3AS0); */
    (void *)eiint421,
    /* Phi comparison interrupt output 1 ( RDC3AS0); */
    (void *)eiint422,
    /* Phi comparison interrupt output 0 ( RDC3AS0); */
    (void *)eiint423,
    /* Fault detection interrupt output ( RDC3AS0); */
    (void *)eiint424,
    /* Z signal interrupt output ( RDC3AS0); */
    (void *)eiint425,
    /* Excitation zero-crossing interrupt output ( RDC3AS0); */
    (void *)eiint426,
    /* Excitation timer interrupt output ( RDC3AS0); */
    (void *)eiint427,
    /* BIST end interrupt output ( RDC3AS0); */
    (void *)eiint428,
    /* Phi comparison interrupt output 2 ( RDC3AS1); */
    (void *)eiint429,
    /* Phi comparison interrupt output 1 ( RDC3AS1); */
    (void *)eiint430,
    /* Phi comparison interrupt output 0 ( RDC3AS1); */
    (void *)eiint431,
    /* Fault detection interrupt output ( RDC3AS1); */
    (void *)eiint432,
    /* Z signal interrupt output ( RDC3AS1); */
    (void *)eiint433,
    /* Excitation zero-crossing interrupt output ( RDC3AS1); */
    (void *)eiint434,
    /* Excitation timer interrupt output ( RDC3AS1); */
    (void *)eiint435,
    /* BIST end interrupt output ( RDC3AS1); */
    (void *)eiint436,
    /* Interrupt request signal from AIR; */
    (void *)eiint437,
    /* Interrupt request signal from AIR; */
    (void *)eiint438,
    /* Interrupt request signal from AIR; */
    (void *)eiint439,
    /* Interrupt request signal from AIR; */
    (void *)eiint440,
    /* Interrupt request signal from AIR; */
    (void *)eiint441,
    /* Interrupt request signal from AIR; */
    (void *)eiint442,
    /* Interrupt request signal from AIR; */
    (void *)eiint443,
    /* Interrupt request signal from AIR; */
    (void *)eiint444,
    /* Interrupt request signal from AIR; */
    (void *)eiint445,
    /* Interrupt request signal from AIR; */
    (void *)eiint446,
    /* Interrupt request signal from AIR; */
    (void *)eiint447,
    /* Interrupt request signal from AIR; */
    (void *)eiint448,
    /* Interrupt request signal from AIR; */
    (void *)eiint449,
    /* Interrupt request signal from AIR; */
    (void *)eiint450,
    /* Interrupt request signal from AIR; */
    (void *)eiint451,
    /* Interrupt request signal from AIR; */
    (void *)eiint452,
    /* Interrupt request signal from AIR; */
    (void *)eiint453,
    /* Interrupt request signal from AIR; */
    (void *)eiint454,
    /* Interrupt request signal from AIR; */
    (void *)eiint455,
    /* Interrupt request signal from AIR; */
    (void *)eiint456,
    /* Interrupt request signal from AIR; */
    (void *)eiint457,
    /* Interrupt request signal from AIR; */
    (void *)eiint458,
    /* Interrupt request signal from AIR; */
    (void *)eiint459,
    /* Interrupt request signal from AIR; */
    (void *)eiint460,
    /* Interrupt request signal from AIR; */
    (void *)eiint461,
    /* Interrupt request signal from AIR; */
    (void *)eiint462,
    /* Interrupt request signal from AIR; */
    (void *)eiint463,
    /* Interrupt request signal from AIR; */
    (void *)eiint464,
    /* Interrupt request signal from AIR; */
    (void *)eiint465,
    /* Interrupt request signal from AIR; */
    (void *)eiint466,
    /* Interrupt request signal from AIR; */
    (void *)eiint467,
    /* Interrupt request signal from AIR; */
    (void *)eiint468,
    /* Interrupt request signal from AIR; */
    (void *)eiint469,
    /* Interrupt request signal from AIR; */
    (void *)eiint470,
    /* Interrupt request signal from AIR; */
    (void *)eiint471,
    /* Interrupt request signal from AIR; */
    (void *)eiint472,
    /* Interrupt request signal from AIR; */
    (void *)eiint473,
    /* Interrupt request signal from AIR; */
    (void *)eiint474,
    /* Interrupt request signal from AIR; */
    (void *)eiint475,
    /* Interrupt request signal from AIR; */
    (void *)eiint476,
    /* Interrupt request signal from AIR; */
    (void *)eiint477,
    /* Interrupt request signal from AIR; */
    (void *)eiint478,
    /* Interrupt request signal from AIR; */
    (void *)eiint479,
    /* Interrupt request signal from AIR; */
    (void *)eiint480,
    /* Interrupt request signal from AIR; */
    (void *)eiint481,
    /* Interrupt request signal from AIR; */
    (void *)eiint482,
    /* Interrupt request signal from AIR; */
    (void *)eiint483,
    /* Interrupt request signal from AIR; */
    (void *)eiint484,
    /* Interrupt request signal from AIR; */
    (void *)eiint485,
    /* Interrupt request signal from AIR; */
    (void *)eiint486,
    /* Interrupt request signal from AIR; */
    (void *)eiint487,
    /* Interrupt request signal from AIR; */
    (void *)eiint488,
    /* Interrupt request signal from AIR; */
    (void *)eiint489,
    /* Interrupt request signal from AIR; */
    (void *)eiint490,
    /* Interrupt request signal from AIR; */
    (void *)eiint491,
    /* Interrupt request signal from AIR; */
    (void *)eiint492,
    /* Interrupt request signal from AIR; */
    (void *)eiint493,
    /* Interrupt request signal from AIR; */
    (void *)eiint494,
    /* Interrupt request signal from AIR; */
    (void *)eiint495,
    /* Interrupt request signal from AIR; */
    (void *)eiint496,
    /* Interrupt request signal from AIR; */
    (void *)eiint497,
    /* Interrupt request signal from AIR; */
    (void *)eiint498,
    /* Interrupt request signal from AIR; */
    (void *)eiint499,
    /* Interrupt request signal from AIR; */
    (void *)eiint500,
    /* Comparator result interrupt for channel 0; */
    (void *)eiint501,
    /* Comparator result interrupt for channel 1; */
    (void *)eiint502,
    /* Comparator result interrupt for channel 2; */
    (void *)eiint503,
    /* Comparator result interrupt for channel 3; */
    (void *)eiint504,
    /* CH0 output data interrupt/CH0 condition match interrupt 0; */
    (void *)eiint505,
    /* CH1 output data interrupt/CH1 condition match interrupt 0; */
    (void *)eiint506,
    /* CH2 output data interrupt/CH2 condition match interrupt 0; */
    (void *)eiint507,
    /* CH3 output data interrupt/CH3 condition match interrupt 0; */
    (void *)eiint508,
    /* CH4 output data interrupt/CH4 condition match interrupt 0; */
    (void *)eiint509,
    /* CH5 output data interrupt/CH5 condition match interrupt 0; */
    (void *)eiint510,
    /* CH6 output data interrupt/CH6 condition match interrupt 0; */
    (void *)eiint511,
    /* CH7 output data interrupt/CH7 condition match interrupt 0; */
    (void *)eiint512,
    /* CH8 output data interrupt/CH8 condition match interrupt 0; */
    (void *)eiint513,
    /* CH9 output data interrupt/CH9 condition match interrupt 0; */
    (void *)eiint514,
    /* CH10 output data interrupt/CH10 condition match interrupt 0; */
    (void *)eiint515,
    /* CH11 output data interrupt/CH11 condition match interrupt 0; */
    (void *)eiint516,
    /* CH12 output data interrupt/CH12 condition match interrupt 0; */
    (void *)eiint517,
    /* CH13 output data interrupt/CH13 condition match interrupt 0; */
    (void *)eiint518,
    /* CH14 output data interrupt/CH14 condition match interrupt 0; */
    (void *)eiint519,
    /* CH15 output data interrupt/CH15 condition match interrupt 0; */
    (void *)eiint520,
    /* Error interrupt; */
    (void *)eiint521,
    /* CH0 condition match interrupt 1; */
    (void *)eiint522,
    /* CH1 condition match interrupt 1; */
    (void *)eiint523,
    /* CH2 condition match interrupt 1; */
    (void *)eiint524,
    /* CH3 condition match interrupt 1; */
    (void *)eiint525,
    /* Subtraction data interrupt 0; */
    (void *)eiint526,
    /* Subtraction data interrupt 1; */
    (void *)eiint527,
    /* Subtraction data interrupt 2; */
    (void *)eiint528,
    /* CH0 Filter Processing End Interrupt Request; */
    (void *)eiint529,
    /* CH1 Filter Processing End Interrupt Request; */
    (void *)eiint530,
    /* CH2 Filter Processing End Interrupt Request; */
    (void *)eiint531,
    /* CH3 Filter Processing End Interrupt Request; */
    (void *)eiint532,
    /* CH4 Filter Processing End Interrupt Request; */
    (void *)eiint533,
    /* CH5 Filter Processing End Interrupt Request; */
    (void *)eiint534,
    /* CH6 Filter Processing End Interrupt Request; */
    (void *)eiint535,
    /* CH7 Filter Processing End Interrupt Request; */
    (void *)eiint536,
    /* CH8 Filter Processing End Interrupt Request; */
    (void *)eiint537,
    /* CH9 Filter Processing End Interrupt Request; */
    (void *)eiint538,
    /* CH10 Filter Processing End Interrupt Request; */
    (void *)eiint539,
    /* CH11 Filter Processing End Interrupt Request; */
    (void *)eiint540,
    /* CH12 Filter Processing End Interrupt Request; */
    (void *)eiint541,
    /* CH13 Filter Processing End Interrupt Request; */
    (void *)eiint542,
    /* CH14 Filter Processing End Interrupt Request; */
    (void *)eiint543,
    /* CH15 Filter Processing End Interrupt Request; */
    (void *)eiint544,
    /* CH0 output data interrupt/CH0 condition match interrupt 0; */
    (void *)eiint545,
    /* CH1 output data interrupt/CH1 condition match interrupt 0; */
    (void *)eiint546,
    /* CH2 output data interrupt/CH2 condition match interrupt 0; */
    (void *)eiint547,
    /* CH3 output data interrupt/CH3 condition match interrupt 0; */
    (void *)eiint548,
    /* Error interrupt; */
    (void *)eiint549,
    /* CH0 condition match interrupt 1; */
    (void *)eiint550,
    /* CH1 condition match interrupt 1; */
    (void *)eiint551,
    /* CH2 condition match interrupt 1; */
    (void *)eiint552,
    /* CH3 condition match interrupt 1; */
    (void *)eiint553,
    /* Subtraction data interrupt 0; */
    (void *)eiint554,
    /* Subtraction data interrupt 1; */
    (void *)eiint555,
    /* Subtraction data interrupt 2; */
    (void *)eiint556,
    /* CH0 Filter Processing End Interrupt Request; */
    (void *)eiint557,
    /* CH1 Filter Processing End Interrupt Request; */
    (void *)eiint558,
    /* CH2 Filter Processing End Interrupt Request; */
    (void *)eiint559,
    /* CH3 Filter Processing End Interrupt Request; */
    (void *)eiint560,
    /* Buffer-A capture finished interrupt; */
    (void *)eiint561,
    /* Buffer-B capture finished interrupt; */
    (void *)eiint562,
    /* Error interrupt; */
    (void *)eiint563,
    /* MSPI0 Transmit status interrupt for channel 0; */
    (void *)eiint564,
    /* MSPI0 Transmit status interrupt for channel 1; */
    (void *)eiint565,
    /* MSPI0 Transmit status interrupt for channel 2; */
    (void *)eiint566,
    /* MSPI0 Receive status interrupt for channel 0; */
    (void *)eiint567,
    /* MSPI0 Receive status interrupt for channel 1; */
    (void *)eiint568,
    /* MSPI0 Receive status interrupt for channel 2; */
    (void *)eiint569,
    /* MSPI1 Transmit status interrupt for channel 0; */
    (void *)eiint570,
    /* MSPI1 Transmit status interrupt for channel 1; */
    (void *)eiint571,
    /* MSPI1 Transmit status interrupt for channel 2; */
    (void *)eiint572,
    /* MSPI1 Receive status interrupt for channel 0; */
    (void *)eiint573,
    /* MSPI1 Receive status interrupt for channel 1; */
    (void *)eiint574,
    /* MSPI1 Receive status interrupt for channel 2; */
    (void *)eiint575,
    /* MSPI0 Channel selectable Transmit status interrupt; */
    (void *)eiint576,
    /* MSPI0 Channel selectable Receive status interrupt; */
    (void *)eiint577,
    /* MSPI0 Channel selectable Frame count end interrupt; */
    (void *)eiint578,
    /* MSPI0 Channel selectable Error interrupt; */
    (void *)eiint579,
    /* MSPI1 Channel selectable Transmit status interrupt; */
    (void *)eiint580,
    /* MSPI1 Channel selectable Receive status interrupt; */
    (void *)eiint581,
    /* MSPI1 Channel selectable Frame count end interrupt; */
    (void *)eiint582,
    /* MSPI1 Channel selectable Error interrupt; */
    (void *)eiint583,
    /* MSPI2 Channel selectable Transmit status interrupt; */
    (void *)eiint584,
    /* MSPI2 Channel selectable Receive status interrupt; */
    (void *)eiint585,
    /* MSPI2 Channel selectable Frame count end interrupt; */
    (void *)eiint586,
    /* MSPI2 Channel selectable Error interrupt; */
    (void *)eiint587,
    /* MSPI3 Channel selectable Transmit status interrupt; */
    (void *)eiint588,
    /* MSPI3 Channel selectable Receive status interrupt; */
    (void *)eiint589,
    /* MSPI3 Channel selectable Frame count end interrupt; */
    (void *)eiint590,
    /* MSPI3 Channel selectable Error interrupt; */
    (void *)eiint591,
    /* MSPI4 Channel selectable Transmit status interrupt; */
    (void *)eiint592,
    /* MSPI4 Channel selectable Receive status interrupt; */
    (void *)eiint593,
    /* MSPI4 Channel selectable Frame count end interrupt; */
    (void *)eiint594,
    /* MSPI4 Channel selectable Error interrupt; */
    (void *)eiint595,
    /* MSPI5 Channel selectable Transmit status interrupt; */
    (void *)eiint596,
    /* MSPI5 Channel selectable Receive status interrupt; */
    (void *)eiint597,
    /* MSPI5 Channel selectable Frame count end interrupt; */
    (void *)eiint598,
    /* MSPI5 Channel selectable Error interrupt; */
    (void *)eiint599,
    /* MSPI6 Channel selectable Transmit status interrupt; */
    (void *)eiint600,
    /* MSPI6 Channel selectable Receive status interrupt; */
    (void *)eiint601,
    /* MSPI6 Channel selectable Frame count end interrupt; */
    (void *)eiint602,
    /* MSPI6 Channel selectable Error interrupt; */
    (void *)eiint603,
    /* Data transmission started/complete; */
    (void *)eiint604,
    /* Command frame transmission complete/started; */
    (void *)eiint605,
    /* Emergency frame transmission complete; */
    (void *)eiint606,
    /* Data receive; */
    (void *)eiint607,
    /* Upstream error/ Timeout detected/ Data lost; */
    (void *)eiint608,
    /* Upstream frame received; */
    (void *)eiint609,
    /* Upstream external interrupt 0; */
    (void *)eiint610,
    /* Upstream external interrupt 1; */
    (void *)eiint611,
    /* Data transmission started/complete; */
    (void *)eiint612,
    /* Command frame transmission complete/started; */
    (void *)eiint613,
    /* Emergency frame transmission complete; */
    (void *)eiint614,
    /* Data receive; */
    (void *)eiint615,
    /* Upstream error/ Timeout detected/ Data lost; */
    (void *)eiint616,
    /* Upstream frame received; */
    (void *)eiint617,
    /* Upstream external interrupt 0; */
    (void *)eiint618,
    /* Upstream external interrupt 1; */
    (void *)eiint619,
    /* RLIN30 interrupt; */
    (void *)eiint620,
    /* RLIN30 transmit interrupt; */
    (void *)eiint621,
    /* RLIN30 receive completion interrupt; */
    (void *)eiint622,
    /* RLIN30 status interrupt; */
    (void *)eiint623,
    /* Reserved; */
    (void *)eiint624,
    /* RLIN31 interrupt; */
    (void *)eiint625,
    /* RLIN31 transmit interrupt; */
    (void *)eiint626,
    /* RLIN31 receive completion interrupt; */
    (void *)eiint627,
    /* RLIN31 status interrupt; */
    (void *)eiint628,
    /* Reserved; */
    (void *)eiint629,
    /* RLIN32 interrupt; */
    (void *)eiint630,
    /* RLIN32 transmit interrupt; */
    (void *)eiint631,
    /* RLIN32 receive completion interrupt; */
    (void *)eiint632,
    /* RLIN32 status interrupt; */
    (void *)eiint633,
    /* Reserved; */
    (void *)eiint634,
    /* RLIN33 interrupt; */
    (void *)eiint635,
    /* RLIN33 transmit interrupt; */
    (void *)eiint636,
    /* RLIN33 receive completion interrupt; */
    (void *)eiint637,
    /* RLIN33 status interrupt; */
    (void *)eiint638,
    /* Reserved; */
    (void *)eiint639,
    /* RLIN34 interrupt; */
    (void *)eiint640,
    /* RLIN34 transmit interrupt; */
    (void *)eiint641,
    /* RLIN34 receive completion interrupt; */
    (void *)eiint642,
    /* RLIN34 status interrupt; */
    (void *)eiint643,
    /* RLIN35 interrupt; */
    (void *)eiint644,
    /* RLIN35 transmit interrupt; */
    (void *)eiint645,
    /* RLIN35 receive completion interrupt; */
    (void *)eiint646,
    /* RLIN35 status interrupt; */
    (void *)eiint647,
    /* RLIN323 interrupt; */
    (void *)eiint648,
    /* RLIN323 transmit interrupt; */
    (void *)eiint649,
    /* RLIN323 receive completion interrupt; */
    (void *)eiint650,
    /* RLIN323 status interrupt; */
    (void *)eiint651,
    /* RSCAN0 CAN global error interrupt; */
    (void *)eiint652,
    /* RSCAN0 CAN receive FIFO interrupt; */
    (void *)eiint653,
    /* RSCAN1 CAN global error interrupt; */
    (void *)eiint654,
    /* RSCAN1 CAN receive FIFO interrupt; */
    (void *)eiint655,
    /* RSCAN2 CAN global error interrupt; */
    (void *)eiint656,
    /* RSCAN2 CAN receive FIFO interrupt; */
    (void *)eiint657,
    /* CAN0 error interrupt; */
    (void *)eiint658,
    /* CAN0 transmit/receive FIFO receive completion interrupt; */
    (void *)eiint659,
    /* CAN0 transmit interrupt; */
    (void *)eiint660,
    /* CAN0 virtual machine TX interrupt; */
    (void *)eiint661,
    /* CAN0 virtual machine RX interrupt; */
    (void *)eiint662,
    /* CAN0 virtual machine error interrupt; */
    (void *)eiint663,
    /* CAN1 error interrupt; */
    (void *)eiint664,
    /* CAN1 transmit/receive FIFO receive completion interrupt; */
    (void *)eiint665,
    /* CAN1 transmit interrupt; */
    (void *)eiint666,
    /* CAN1 virtual machine TX interrupt; */
    (void *)eiint667,
    /* CAN1 virtual machine RX interrupt; */
    (void *)eiint668,
    /* CAN1 virtual machine error interrupt; */
    (void *)eiint669,
    /* CAN2 error interrupt; */
    (void *)eiint670,
    /* CAN2 transmit/receive FIFO receive completion interrupt; */
    (void *)eiint671,
    /* CAN2 transmit interrupt; */
    (void *)eiint672,
    /* CAN2 virtual machine TX interrupt; */
    (void *)eiint673,
    /* CAN2 virtual machine RX interrupt; */
    (void *)eiint674,
    /* CAN2 virtual machine error interrupt; */
    (void *)eiint675,
    /* CAN3 error interrupt; */
    (void *)eiint676,
    /* CAN3 transmit/receive FIFO receive completion interrupt; */
    (void *)eiint677,
    /* CAN3 transmit interrupt; */
    (void *)eiint678,
    /* CAN3 virtual machine TX interrupt; */
    (void *)eiint679,
    /* CAN3 virtual machine RX interrupt; */
    (void *)eiint680,
    /* CAN3 virtual machine error interrupt; */
    (void *)eiint681,
    /* CAN4 error interrupt; */
    (void *)eiint682,
    /* CAN4 transmit/receive FIFO receive completion interrupt; */
    (void *)eiint683,
    /* CAN4 transmit interrupt; */
    (void *)eiint684,
    /* CAN4 virtual machine TX interrupt; */
    (void *)eiint685,
    /* CAN4 virtual machine RX interrupt; */
    (void *)eiint686,
    /* CAN4 virtual machine error interrupt; */
    (void *)eiint687,
    /* CAN5 error interrupt; */
    (void *)eiint688,
    /* CAN5 transmit/receive FIFO receive completion interrupt; */
    (void *)eiint689,
    /* CAN5 transmit interrupt; */
    (void *)eiint690,
    /* CAN5 virtual machine TX interrupt; */
    (void *)eiint691,
    /* CAN5 virtual machine RX interrupt; */
    (void *)eiint692,
    /* CAN5 virtual machine error interrupt; */
    (void *)eiint693,
    /* CAN6 error interrupt; */
    (void *)eiint694,
    /* CAN6 transmit/receive FIFO receive completion interrupt; */
    (void *)eiint695,
    /* CAN6 transmit interrupt; */
    (void *)eiint696,
    /* CAN6 virtual machine TX interrupt; */
    (void *)eiint697,
    /* CAN6 virtual machine RX interrupt; */
    (void *)eiint698,
    /* CAN6 virtual machine error interrupt; */
    (void *)eiint699,
    /* CAN7 error interrupt; */
    (void *)eiint700,
    /* CAN7 transmit/receive FIFO receive completion interrupt; */
    (void *)eiint701,
    /* CAN7 transmit interrupt; */
    (void *)eiint702,
    /* CAN7 virtual machine TX interrupt; */
    (void *)eiint703,
    /* CAN7 virtual machine RX interrupt; */
    (void *)eiint704,
    /* CAN7 virtual machine error interrupt; */
    (void *)eiint705,
    /* Completion of ACEU2 encryption or decryption with CPU transfer; */
    (void *)eiint706,
    /* Completion of ACEU3 encryption or decryption with CPU transfer; */
    (void *)eiint707,
    /* ETNE0 (Ether L2 Switch) interrupt 0; */
    (void *)eiint708,
    /* ETNE0 (Ether L2 Switch) interrupt 1; */
    (void *)eiint709,
    /* ETNE0 (Ether L2 Switch) interrupt 2; */
    (void *)eiint710,
    /* ETNE0 (Ether L2 Switch) interrupt 3; */
    (void *)eiint711,
    /* ETNE0 (Ether L2 Switch) interrupt 4; */
    (void *)eiint712,
    /* ETNE0 (Ether L2 Switch) interrupt 5; */
    (void *)eiint713,
    /* ETNE0 (Ether L2 Switch) interrupt 6; */
    (void *)eiint714,
    /* ETNE0 (Ether L2 Switch) interrupt 7; */
    (void *)eiint715,
    /* ETNE0 (Ether L2 Switch) interrupt 8; */
    (void *)eiint716,
    /* CPU0 Code Flash bus port (Ch3); */
    (void *)eiint717,
    /* CPU0 Code Flash bus port (Ch4); */
    (void *)eiint718,
    /* CPU0 Code Flash bus port (Ch5); */
    (void *)eiint719,
    /* CPU0 Code Flash bus port (Ch6); */
    (void *)eiint720,
    /* CPU0 Code Flash bus port (Ch7); */
    (void *)eiint721,
    /* FLXA0 line 0 interrupt; */
    (void *)eiint722,
    /* FLXA0 line 1 interrupt; */
    (void *)eiint723,
    /* FLXA0 Timer 0 interrupt; */
    (void *)eiint724,
    /* FLXA0 Timer 1 interrupt; */
    (void *)eiint725,
    /* FLXA0 Timer 2 interrupt; */
    (void *)eiint726,
    /* FLXA0 FIFO data available (FIFO is not empty) interrupt; */
    (void *)eiint727,
    /* FLXA0 FIFO transfer warning interrupt; */
    (void *)eiint728,
    /* FLXA0 Output transfer warning interrupt; */
    (void *)eiint729,
    /* FLXA0 Output transfer done interrupt; */
    (void *)eiint730,
    /* FLXA0 Input queue full interrupt; */
    (void *)eiint731,
    /* FLXA0 Input queue empty interrupt; */
    (void *)eiint732,
    /* RSENT0 receive interrupt; */
    (void *)eiint733,
    /* RSENT1 receive interrupt; */
    (void *)eiint734,
    /* RSENT2 receive interrupt; */
    (void *)eiint735,
    /* RSENT3 receive interrupt; */
    (void *)eiint736,
    /* RSENT4 receive interrupt; */
    (void *)eiint737,
    /* RSENT5 receive interrupt; */
    (void *)eiint738,
    /* RSENT6 receive interrupt; */
    (void *)eiint739,
    /* RSENT7 receive interrupt; */
    (void *)eiint740,
    /* RSENT8 receive interrupt; */
    (void *)eiint741,
    /* RSENT9 receive interrupt; */
    (void *)eiint742,
    /* RSENT0 status interrupt; */
    (void *)eiint743,
    /* RSENT1 status interrupt; */
    (void *)eiint744,
    /* RSENT2 status interrupt; */
    (void *)eiint745,
    /* RSENT3 status interrupt; */
    (void *)eiint746,
    /* RSENT4 status interrupt; */
    (void *)eiint747,
    /* RSENT5 status interrupt; */
    (void *)eiint748,
    /* RSENT6 status interrupt; */
    (void *)eiint749,
    /* RSENT7 status interrupt; */
    (void *)eiint750,
    /* RSENT8 status interrupt; */
    (void *)eiint751,
    /* RSENT9 status interrupt; */
    (void *)eiint752,
    /* Inter-PE interrupt from ICUMHB to INTC2(Interrupt request from ICUP to CPU (PE)); */
    (void *)eiint753,
    /* Inter-PE interrupt from ICUMHB to INTC2(Interrupt request from ICUP to CPU (PE)); */
    (void *)eiint754,
    /* Inter-PE interrupt from ICUMHB to INTC2(Interrupt request from ICUP to CPU (PE)); */
    (void *)eiint755,
    /* Inter-PE interrupt from ICUMHB to INTC2(Interrupt request from ICUP to CPU (PE)); */
    (void *)eiint756,
    /* Inter-PE interrupt from ICUMHB to INTC2(Interrupt request from ICUP to CPU (PE)); */
    (void *)eiint757,
    /* Inter-PE interrupt from ICUMHB to INTC2(Interrupt request from ICUP to CPU (PE)); */
    (void *)eiint758,
    /* Inter-PE interrupt from ICUMHB to INTC2(Interrupt request from ICUP to CPU (PE)); */
    (void *)eiint759,
    /* Inter-PE interrupt from ICUMHB to INTC2(Interrupt request from ICUP to CPU (PE)); */
    (void *)eiint760,
    /* ICUMHB fatal error notification; */
    (void *)eiint761,
    /* OTS0 Error interrupt; */
    (void *)eiint762,
    /* OTS0 Temperature measurement end interrupt; */
    (void *)eiint763,
    /* OTS0 Temperature rise/drop interrupt; */
    (void *)eiint764,
    /* External interrupt 0; */
    (void *)eiint765,
    /* External interrupt 1; */
    (void *)eiint766,
    /* External interrupt 2; */
    (void *)eiint767,
    /* External interrupt 3; */
    (void *)eiint768,
    /* External interrupt 4; */
    (void *)eiint769,
    /* External interrupt 5; */
    (void *)eiint770,
    /* External interrupt 6; */
    (void *)eiint771,
    /* External interrupt 7; */
    (void *)eiint772,
    /* External interrupt 8; */
    (void *)eiint773,
    /* External interrupt 9; */
    (void *)eiint774,
    /* External interrupt 10; */
    (void *)eiint775,
    /* External interrupt 11; */
    (void *)eiint776,
    /* External interrupt 12; */
    (void *)eiint777,
    /* External interrupt 13; */
    (void *)eiint778,
    /* External interrupt 14; */
    (void *)eiint779,
    /* External interrupt 15; */
    (void *)eiint780,
    /* External interrupt 16; */
    (void *)eiint781,
    /* External interrupt 17; */
    (void *)eiint782,
    /* External interrupt 18; */
    (void *)eiint783,
    /* External interrupt 19; */
    (void *)eiint784,
    /* External interrupt 20; */
    (void *)eiint785,
    /* External interrupt 21; */
    (void *)eiint786,
    /* External interrupt 22; */
    (void *)eiint787,
    /* External interrupt 23; */
    (void *)eiint788,
    /* External interrupt 24; */
    (void *)eiint789,
    /* External interrupt 25; */
    (void *)eiint790,
    /* External interrupt 26; */
    (void *)eiint791,
    /* External interrupt 27; */
    (void *)eiint792,
    /* External interrupt 28; */
    (void *)eiint793,
    /* External interrupt 29; */
    (void *)eiint794,
    /* External interrupt 30; */
    (void *)eiint795,
    /* External interrupt 31; */
    (void *)eiint796,
    /* External interrupt 32; */
    (void *)eiint797,
    /* External interrupt 33; */
    (void *)eiint798,
    /* External interrupt 34; */
    (void *)eiint799,
    /* External interrupt 35; */
    (void *)eiint800,
    /* External interrupt 36; */
    (void *)eiint801,
    /* External interrupt 37; */
    (void *)eiint802,
    /* External interrupt 38; */
    (void *)eiint803,
    /* External interrupt 39; */
    (void *)eiint804,
    /* Edge detection of RLIN30 received data; */
    (void *)eiint805,
    /* Edge detection of RLIN31 received data; */
    (void *)eiint806,
    /* Edge detection of RSCFD0 received data; */
    (void *)eiint807,
    /* Edge detection of RSCFD1 received data; */
    (void *)eiint808,
    /* Edge detection of FLXA0 ch A received data; */
    (void *)eiint809,
    /* Dedicated interrupt for on-chip debug function; */
    (void *)eiint810,
    /* Emergency Hi-Z input 0; */
    (void *)eiint811,
    /* Emergency Hi-Z input 1; */
    (void *)eiint812,
    /* Emergency Hi-Z input 2; */
    (void *)eiint813,
    /* Emergency Hi-Z input 3; */
    (void *)eiint814,
    /* Emergency Hi-Z input 4; */
    (void *)eiint815,
    /* Emergency Hi-Z input 5; */
    (void *)eiint816,
    /* External interrupt 40; */
    (void *)eiint817,
    /* External interrupt 41; */
    (void *)eiint818,
    /* External interrupt 42; */
    (void *)eiint819,
    /* External interrupt 43; */
    (void *)eiint820,
    /* Reserved; */
    (void *)eiint821,
    /* CPU0 Code Flash bus port (Ch0); */
    (void *)eiint822,
    /* CPU0 Code Flash bus port (Ch1); */
    (void *)eiint823,
    /* CPU0 Code Flash bus port (Ch2); */
    (void *)eiint824,
    /* sDMAC1 channel 0 transfer end or descriptor step end interrupt; */
    (void *)eiint825,
    /* sDMAC1 channel 1 transfer end or descriptor step end interrupt; */
    (void *)eiint826,
    /* sDMAC1 channel 2 transfer end or descriptor step end interrupt; */
    (void *)eiint827,
    /* sDMAC1 channel 3 transfer end or descriptor step end interrupt; */
    (void *)eiint828,
    /* sDMAC1 channel 4 transfer end or descriptor step end interrupt; */
    (void *)eiint829,
    /* sDMAC1 channel 5 transfer end or descriptor step end interrupt; */
    (void *)eiint830,
    /* sDMAC1 channel 6 transfer end or descriptor step end interrupt; */
    (void *)eiint831,
    /* sDMAC1 channel 7 transfer end or descriptor step end interrupt; */
    (void *)eiint832,
    /* sDMAC1 channel 8 transfer end or descriptor step end interrupt; */
    (void *)eiint833,
    /* sDMAC1 channel 9 transfer end or descriptor step end interrupt; */
    (void *)eiint834,
    /* sDMAC1 channel 10 transfer end or descriptor step end interrupt; */
    (void *)eiint835,
    /* sDMAC1 channel 11 transfer end or descriptor step end interrupt; */
    (void *)eiint836,
    /* sDMAC1 channel 12 transfer end or descriptor step end interrupt; */
    (void *)eiint837,
    /* sDMAC1 channel 13 transfer end or descriptor step end interrupt; */
    (void *)eiint838,
    /* sDMAC1 channel 14 transfer end or descriptor step end interrupt; */
    (void *)eiint839,
    /* sDMAC1 channel 15 transfer end or descriptor step end interrupt; */
    (void *)eiint840,
    /* OSTM2 interrupt; */
    (void *)eiint841,
    /* OSTM3 interrupt; */
    (void *)eiint842,
    /* TPTM up timer interrupt for PE2 with comparison value 0; */
    (void *)eiint843,
    /* TPTM up timer interrupt for PE2 with comparison value 1; */
    (void *)eiint844,
    /* TPTM up timer interrupt for PE2 with comparison value 2; */
    (void *)eiint845,
    /* TPTM up timer interrupt for PE2 with comparison value 3; */
    (void *)eiint846,
    /* TPTM up timer interrupt for PE3 with comparison value 0; */
    (void *)eiint847,
    /* TPTM up timer interrupt for PE3 with comparison value 1; */
    (void *)eiint848,
    /* TPTM up timer interrupt for PE3 with comparison value 2; */
    (void *)eiint849,
    /* TPTM up timer interrupt for PE3 with comparison value 3; */
    (void *)eiint850,
    /* MSPI7 Channel selectable Transmit status interrupt; */
    (void *)eiint851,
    /* MSPI7 Channel selectable Receive status interrupt; */
    (void *)eiint852,
    /* MSPI7 Channel selectable Frame count end interrupt; */
    (void *)eiint853,
    /* MSPI7 Channel selectable Error interrupt; */
    (void *)eiint854,
    /* MSPI8 Channel selectable Transmit status interrupt; */
    (void *)eiint855,
    /* MSPI8 Channel selectable Receive status interrupt; */
    (void *)eiint856,
    /* MSPI8 Channel selectable Frame count end interrupt; */
    (void *)eiint857,
    /* MSPI8 Channel selectable Error interrupt; */
    (void *)eiint858,
    /* MSPI9 Channel selectable Transmit status interrupt; */
    (void *)eiint859,
    /* MSPI9 Channel selectable Receive status interrupt; */
    (void *)eiint860,
    /* MSPI9 Channel selectable Frame count end interrupt; */
    (void *)eiint861,
    /* MSPI9 Channel selectable Error interrupt; */
    (void *)eiint862,
    /* Data transmission started/complete; */
    (void *)eiint863,
    /* Command frame transmission complete/started; */
    (void *)eiint864,
    /* Emergency frame transmission complete; */
    (void *)eiint865,
    /* Data receive; */
    (void *)eiint866,
    /* Upstream error/ Timeout detected/ Data lost; */
    (void *)eiint867,
    /* Upstream frame received; */
    (void *)eiint868,
    /* Upstream external interrupt 0; */
    (void *)eiint869,
    /* Upstream external interrupt 1; */
    (void *)eiint870,
    /* RHSIF0 Transmit complete interrupt; */
    (void *)eiint871,
    /* RHSIF0 Transmit exception interrupt; */
    (void *)eiint872,
    /* RHSIF0 Receive complete interrupt; */
    (void *)eiint873,
    /* RHSIF0 Receive exception interrupt; */
    (void *)eiint874,
    /* RHSIF0 ICLC receive interrupt; */
    (void *)eiint875,
    /* RHSIF0 Channel 0 interrupt; */
    (void *)eiint876,
    /* RHSIF0 Channel 1 interrupt; */
    (void *)eiint877,
    /* RHSIF0 Channel 2 interrupt; */
    (void *)eiint878,
    /* RHSIF0 Channel 3 interrupt; */
    (void *)eiint879,
    /* RHSIF0 Stream interrupt; */
    (void *)eiint880,
    /* RHSIF0 Error interrupt/Security interrupt; */
    (void *)eiint881,
    /* RIIC0 receive end interrupt; */
    (void *)eiint882,
    /* RIIC0 transmit data empty interrupt; */
    (void *)eiint883,
    /* RIIC1 receive end interrupt; */
    (void *)eiint884,
    /* RIIC1 transmit data empty interrupt; */
    (void *)eiint885,
    /* RIIC0 communication error or event generation interrupt; */
    (void *)eiint886,
    /* RIIC0 transmit end interrupt; */
    (void *)eiint887,
    /* RIIC1 communication error or event generation interrupt; */
    (void *)eiint888,
    /* RIIC1 transmit end interrupt; */
    (void *)eiint889,
    /* RSENT10 receive interrupt; */
    (void *)eiint890,
    /* RSENT11 receive interrupt; */
    (void *)eiint891,
    /* RSENT12 receive interrupt; */
    (void *)eiint892,
    /* RSENT13 receive interrupt; */
    (void *)eiint893,
    /* RSENT14 receive interrupt; */
    (void *)eiint894,
    /* RSENT15 receive interrupt; */
    (void *)eiint895,
    /* RSENT16 receive interrupt; */
    (void *)eiint896,
    /* RSENT17 receive interrupt; */
    (void *)eiint897,
    /* RSENT18 receive interrupt; */
    (void *)eiint898,
    /* RSENT19 receive interrupt; */
    (void *)eiint899,
    /* RSENT20 receive interrupt; */
    (void *)eiint900,
    /* RSENT21 receive interrupt; */
    (void *)eiint901,
    /* RSENT22 receive interrupt; */
    (void *)eiint902,
    /* RSENT23 receive interrupt; */
    (void *)eiint903,
    /* RSENT24 receive interrupt; */
    (void *)eiint904,
    /* RSENT25 receive interrupt; */
    (void *)eiint905,
    /* RSENT26 receive interrupt; */
    (void *)eiint906,
    /* RSENT27 receive interrupt; */
    (void *)eiint907,
    /* RSENT28 receive interrupt; */
    (void *)eiint908,
    /* RSENT29 receive interrupt; */
    (void *)eiint909,
    /* RSENT10 status interrupt; */
    (void *)eiint910,
    /* RSENT11 status interrupt; */
    (void *)eiint911,
    /* RSENT12 status interrupt; */
    (void *)eiint912,
    /* RSENT13 status interrupt; */
    (void *)eiint913,
    /* RSENT14 status interrupt; */
    (void *)eiint914,
    /* RSENT15 status interrupt; */
    (void *)eiint915,
    /* RSENT16 status interrupt; */
    (void *)eiint916,
    /* RSENT17 status interrupt; */
    (void *)eiint917,
    /* RSENT18 status interrupt; */
    (void *)eiint918,
    /* RSENT19 status interrupt; */
    (void *)eiint919,
    /* RSENT20 status interrupt; */
    (void *)eiint920,
    /* RSENT21 status interrupt; */
    (void *)eiint921,
    /* RSENT22 status interrupt; */
    (void *)eiint922,
    /* RSENT23 status interrupt; */
    (void *)eiint923,
    /* RSENT24 status interrupt; */
    (void *)eiint924,
    /* RSENT25 status interrupt; */
    (void *)eiint925,
    /* RSENT26 status interrupt; */
    (void *)eiint926,
    /* RSENT27 status interrupt; */
    (void *)eiint927,
    /* RSENT28 status interrupt; */
    (void *)eiint928,
    /* RSENT29 status interrupt; */
    (void *)eiint929,
    /* PSI50 status interrupt; */
    (void *)eiint930,
    /* PSI50 receive interrupt; */
    (void *)eiint931,
    /* PSI50 transfer interrupt; */
    (void *)eiint932,
    /* PSI51 status interrupt; */
    (void *)eiint933,
    /* PSI51 receive interrupt; */
    (void *)eiint934,
    /* PSI51 transfer interrupt; */
    (void *)eiint935,
    /* PSI52 status interrupt; */
    (void *)eiint936,
    /* PSI52 receive interrupt; */
    (void *)eiint937,
    /* PSI52 transfer interrupt; */
    (void *)eiint938,
    /* PSI53 status interrupt; */
    (void *)eiint939,
    /* PSI53 receive interrupt; */
    (void *)eiint940,
    /* PSI53 transfer interrupt; */
    (void *)eiint941,
    /* Interruption reports the end of all channel enable; */
    (void *)eiint942,
    /* PSI5S0 Communication interrupt for CH0; */
    (void *)eiint943,
    /* PSI5S0 Communication interrupt for CH1; */
    (void *)eiint944,
    /* PSI5S0 Communication interrupt for CH2; */
    (void *)eiint945,
    /* PSI5S0 Communication interrupt for CH3; */
    (void *)eiint946,
    /* PSI5S0 Communication interrupt for CH4; */
    (void *)eiint947,
    /* PSI5S0 Communication interrupt for CH5; */
    (void *)eiint948,
    /* PSI5S0 Communication interrupt for CH6; */
    (void *)eiint949,
    /* PSI5S0 Communication interrupt for CH7; */
    (void *)eiint950,
    /* PSI5S1 Communication interrupt for CH0; */
    (void *)eiint951,
    /* PSI5S1 Communication interrupt for CH1; */
    (void *)eiint952,
    /* PSI5S1 Communication interrupt for CH2; */
    (void *)eiint953,
    /* PSI5S1 Communication interrupt for CH3; */
    (void *)eiint954,
    /* PSI5S1 Communication interrupt for CH4; */
    (void *)eiint955,
    /* PSI5S1 Communication interrupt for CH5; */
    (void *)eiint956,
    /* PSI5S1 Communication interrupt for CH6; */
    (void *)eiint957,
    /* PSI5S1 Communication interrupt for CH7; */
    (void *)eiint958,
    /* MMCA interrupt; */
    (void *)eiint959,
    /* TAUJ2 Channel 0 interrupt; */
    (void *)eiint960,
    /* TAUJ2 Channel 1 interrupt; */
    (void *)eiint961,
    /* TAUJ2 Channel 2 interrupt; */
    (void *)eiint962,
    /* TAUJ2 Channel 3 interrupt; */
    (void *)eiint963,
    /* ETNF0 Data related interrupt; */
    (void *)eiint964,
    /* ETNF0 Error related interrupt; */
    (void *)eiint965,
    /* ETNF0 Management related interrupt; */
    (void *)eiint966,
    /* ETNF0 MAC interrupt; */
    (void *)eiint967,
    /* OSTM4 interrupt; */
    (void *)eiint968,
    /* OSTM5 interrupt; */
    (void *)eiint969,
    /* RTCA0 1-second interval interrupt; */
    (void *)eiint970,
    /* RTCA0 Alarm interrupt; */
    (void *)eiint971,
    /* RTCA0 Fixed interval interrupt; */
    (void *)eiint972,
    /* TPTM up timer interrupt for PE4 with comparison value 0; */
    (void *)eiint973,
    /* TPTM up timer interrupt for PE4 with comparison value 1; */
    (void *)eiint974,
    /* TPTM up timer interrupt for PE4 with comparison value 2; */
    (void *)eiint975,
    /* TPTM up timer interrupt for PE4 with comparison value 3; */
    (void *)eiint976,
    /* TPTM up timer interrupt for PE5 with comparison value 0; */
    (void *)eiint977,
    /* TPTM up timer interrupt for PE5 with comparison value 1; */
    (void *)eiint978,
    /* TPTM up timer interrupt for PE5 with comparison value 2; */
    (void *)eiint979,
    /* TPTM up timer interrupt for PE5 with comparison value 3; */
    (void *)eiint980,
    /* WDTBA interrupt; */
    (void *)eiint981,
    /* Completion of ACEU2 encryption or decryption with DTF transfer; */
    (void *)eiint982,
    /* ACEU BUS slave error of ACEU2 during DTF transfer; */
    (void *)eiint983,
    /* Compare error from duplex circuit of ACEU2; */
    (void *)eiint984,
    /* Completion of ACEU3 encryption or decryption with DTF transfer; */
    (void *)eiint985,
    /* ACEU BUS slave error of ACEU3 during DTF transfer; */
    (void *)eiint986,
    /* Compare error from duplex circuit of ACEU3; */
    (void *)eiint987,
    /* Comparator result interrupt for channel 4; */
    (void *)eiint988,
    /* Comparator result interrupt for channel 5; */
    (void *)eiint989,
    /* Comparator result interrupt for channel 6; */
    (void *)eiint990,
    /* Comparator result interrupt for channel 7; */
    (void *)eiint991,
    /* RLIN36 interrupt; */
    (void *)eiint992,
    /* RLIN36 transmit interrupt; */
    (void *)eiint993,
    /* RLIN36 receive completion interrupt; */
    (void *)eiint994,
    /* RLIN36 status interrupt; */
    (void *)eiint995,
    /* RLIN37 interrupt; */
    (void *)eiint996,
    /* RLIN37 transmit interrupt; */
    (void *)eiint997,
    /* RLIN37 receive completion interrupt; */
    (void *)eiint998,
    /* RLIN37 status interrupt; */
    (void *)eiint999,
    /* LPS0 Port polling end interrupt; */
    (void *)eiint1000,
    /* LPS0 Digital port error interrupt; */
    (void *)eiint1001,
    /* Reserved; */
    (void *)eiint1002,
    /* Comparator result interrupt for channel 8; */
    (void *)eiint1003,
    /* Comparator result interrupt for channel 9; */
    (void *)eiint1004,
    /* CAN8 error interrupt; */
    (void *)eiint1005,
    /* CAN8 transmit/receive FIFO receive completion interrupt; */
    (void *)eiint1006,
    /* CAN8 transmit interrupt; */
    (void *)eiint1007,
    /* CAN8 virtual machine TX interrupt; */
    (void *)eiint1008,
    /* CAN8 virtual machine RX interrupt; */
    (void *)eiint1009,
    /* CAN8 virtual machine error interrupt; */
    (void *)eiint1010,
    /* CAN9 error interrupt; */
    (void *)eiint1011,
    /* CAN9 transmit/receive FIFO receive completion interrupt; */
    (void *)eiint1012,
    /* CAN9 transmit interrupt; */
    (void *)eiint1013,
    /* CAN9 virtual machine TX interrupt; */
    (void *)eiint1014,
    /* CAN9 virtual machine RX interrupt; */
    (void *)eiint1015,
    /* CAN9 virtual machine error interrupt; */
    (void *)eiint1016,
    /* XCAN0 functional relevant; */
    (void *)eiint1017,
    /* XCAN0 functional error relevant; */
    (void *)eiint1018,
    /* XCAN0 safety relevant; */
    (void *)eiint1019,
    /* XCAN1 functional relevant; */
    (void *)eiint1020,
    /* XCAN1 functional error relevant; */
    (void *)eiint1021,
    /* XCAN1 safety relevant; */
    (void *)eiint1022,
    /* External interrupt 45; */
    (void *)eiint1023,
};

#pragma ghs section
