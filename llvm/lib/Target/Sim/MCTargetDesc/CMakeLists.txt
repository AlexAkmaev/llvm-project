add_llvm_component_library(LLVMSimDesc
    SimInstPrinter.cpp
    SimMCTargetDesc.cpp
    SimMCAsmInfo.cpp

    LINK_COMPONENTS
    MC
    SimInfo
    Support

    ADD_TO_COMPONENT
    Sim
)
