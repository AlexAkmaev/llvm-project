//===-- SimTargetMachine.h - Define TargetMachine for Sim ---*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the Sim specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_SIM_SIMTARGETMACHINE_H
#define LLVM_LIB_TARGET_SIM_SIMTARGETMACHINE_H

#include "SimInstrInfo.h"
#include "SimSubtarget.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class SimTargetMachine : public LLVMTargetMachine {
public:
  SimTargetMachine(const Target &T, const Triple &TT, StringRef CPU, StringRef FS, const TargetOptions &Options,
                   Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM, CodeGenOpt::Level OL, bool JIT);
  ~SimTargetMachine() override = default;

  const SimSubtarget *getSubtargetImpl() const { return &subtarget_;  }
  const SimSubtarget *getSubtargetImpl(const Function &) const override { return &subtarget_; }

  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
  TargetLoweringObjectFile *getObjFileLowering() const override { return tlof_.get(); }

private:
  std::unique_ptr<TargetLoweringObjectFile> tlof_;
  SimSubtarget subtarget_;
};
}   // llvm

#endif  // LLVM_LIB_TARGET_SIM_SIMTARGETMACHINE_H
