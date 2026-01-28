// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.1 (64-bit)
// Tool Version Limit: 2025.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xtop_ntt.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XTop_ntt_CfgInitialize(XTop_ntt *InstancePtr, XTop_ntt_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XTop_ntt_Start(XTop_ntt *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ntt_ReadReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_AP_CTRL) & 0x80;
    XTop_ntt_WriteReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XTop_ntt_IsDone(XTop_ntt *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ntt_ReadReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XTop_ntt_IsIdle(XTop_ntt *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ntt_ReadReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XTop_ntt_IsReady(XTop_ntt *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ntt_ReadReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XTop_ntt_EnableAutoRestart(XTop_ntt *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_ntt_WriteReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XTop_ntt_DisableAutoRestart(XTop_ntt *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_ntt_WriteReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_AP_CTRL, 0);
}

void XTop_ntt_Set_in_r(XTop_ntt *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_ntt_WriteReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_IN_R_DATA, (u32)(Data));
    XTop_ntt_WriteReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_IN_R_DATA + 4, (u32)(Data >> 32));
}

u64 XTop_ntt_Get_in_r(XTop_ntt *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ntt_ReadReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_IN_R_DATA);
    Data += (u64)XTop_ntt_ReadReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_IN_R_DATA + 4) << 32;
    return Data;
}

void XTop_ntt_Set_out_r(XTop_ntt *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_ntt_WriteReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_OUT_R_DATA, (u32)(Data));
    XTop_ntt_WriteReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_OUT_R_DATA + 4, (u32)(Data >> 32));
}

u64 XTop_ntt_Get_out_r(XTop_ntt *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ntt_ReadReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_OUT_R_DATA);
    Data += (u64)XTop_ntt_ReadReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_OUT_R_DATA + 4) << 32;
    return Data;
}

void XTop_ntt_Set_zetas_forward(XTop_ntt *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_ntt_WriteReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_ZETAS_FORWARD_DATA, (u32)(Data));
    XTop_ntt_WriteReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_ZETAS_FORWARD_DATA + 4, (u32)(Data >> 32));
}

u64 XTop_ntt_Get_zetas_forward(XTop_ntt *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ntt_ReadReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_ZETAS_FORWARD_DATA);
    Data += (u64)XTop_ntt_ReadReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_ZETAS_FORWARD_DATA + 4) << 32;
    return Data;
}

void XTop_ntt_InterruptGlobalEnable(XTop_ntt *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_ntt_WriteReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_GIE, 1);
}

void XTop_ntt_InterruptGlobalDisable(XTop_ntt *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_ntt_WriteReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_GIE, 0);
}

void XTop_ntt_InterruptEnable(XTop_ntt *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XTop_ntt_ReadReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_IER);
    XTop_ntt_WriteReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_IER, Register | Mask);
}

void XTop_ntt_InterruptDisable(XTop_ntt *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XTop_ntt_ReadReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_IER);
    XTop_ntt_WriteReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_IER, Register & (~Mask));
}

void XTop_ntt_InterruptClear(XTop_ntt *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_ntt_WriteReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_ISR, Mask);
}

u32 XTop_ntt_InterruptGetEnabled(XTop_ntt *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XTop_ntt_ReadReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_IER);
}

u32 XTop_ntt_InterruptGetStatus(XTop_ntt *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XTop_ntt_ReadReg(InstancePtr->Control_BaseAddress, XTOP_NTT_CONTROL_ADDR_ISR);
}

