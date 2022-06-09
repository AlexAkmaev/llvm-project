add_llvm_component_group(Sim HAS_JIT)

set(LLVM_TARGET_DEFINITIONS Sim.td)

tablegen(LLVM SimGenAsmMatcher.inc -gen-asm-matcher)
tablegen(LLVM SimGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM SimGenCallingConv.inc -gen-callingconv)
tablegen(LLVM SimGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM SimGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM SimGenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM SimGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM SimGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM SimGenMCPseudoLowering.inc -gen-pseudo-lowering)

add_public_tablegen_target(SimCommonTableGen)

add_llvm_target(SimCodeGen
    SimAsmPrinter.cpp
    SimInstrInfo.cpp
    SimISelDAGToDAG.cpp
    SimISelLowering.cpp
    SimFrameLowering.cpp
    SimMachineFunctionInfo.cpp
    SimRegisterInfo.cpp
    SimSubtarget.cpp
    SimTargetMachine.cpp
    SimTargetObjectFile.cpp
    Sim.cpp

    LINK_COMPONENTS
    AsmPrinter
    CodeGen
    Core
    MC
    SelectionDAG
    SimDesc
    SimInfo
    Support
    Target

    ADD_TO_COMPONENT
    Sim
)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
