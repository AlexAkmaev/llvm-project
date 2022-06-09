//===-- SimMCTargetDesc.cpp - Sim Target Descriptions -------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides Sim specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "SimInfo.h"
#include "SimMCTargetDesc.h"
#include "SimInstPrinter.h"
#include "SimMCAsmInfo.h"
#include "../TargetInfo/SimTargetInfo.h"
#include "llvm/MC/MachineLocation.h"
#include "llvm/MC/MCELFStreamer.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "SimGenInstrInfo.inc"

#define GET_REGINFO_MC_DESC
#include "SimGenRegisterInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "SimGenSubtargetInfo.inc"

static MCInstPrinter *createSimMCInstPrinter(const Triple &T, unsigned SyntaxVariant,
                                             const MCAsmInfo &MAI, const MCInstrInfo &MII, const MCRegisterInfo &MRI) {
  return new SimInstPrinter(MAI, MII, MRI);
}

static MCAsmInfo *createSimMCAsmInfo(const MCRegisterInfo &MRI,
                                     const Triple &T,
                                     const MCTargetOptions &Options) {
  MCAsmInfo *MAI = new SimMCAsmInfo(T);
  MCRegister SP = MRI.getDwarfRegNum(SIM::R2, true);
  MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, SP, 0);
  MAI->addInitialFrameState(Inst);
  return MAI;
}

static MCSubtargetInfo *createSimMCSubtargetInfo(const Triple &T, StringRef CPU, StringRef FS) {
  return createSimMCSubtargetInfoImpl(T, CPU, /*TuneCPU*/ CPU, FS);
}

static MCRegisterInfo *createSimMCRegisterInfo(const Triple &TT) {
  auto *X = new MCRegisterInfo();
  InitSimMCRegisterInfo(X, SIM::R1);
  return X;
}

static MCInstrInfo *createSimMCInstrInfo() {
  auto *II = new MCInstrInfo();
  InitSimMCInstrInfo(II);
  return II;
}

extern "C" void LLVMInitializeSimTargetMC() {
  Target &target = getTheSimTarget();

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(target, createSimMCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(target, createSimMCSubtargetInfo);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(target, createSimMCInstrInfo);

  TargetRegistry::RegisterMCAsmInfo(target, createSimMCAsmInfo);

  // Register the MCInstPrinter
  TargetRegistry::RegisterMCInstPrinter(target, createSimMCInstPrinter);

  // Register the MC Code Emitter.
  // TargetRegistry::RegisterMCCodeEmitter(*target, createSimMCCodeEmitter);
}
