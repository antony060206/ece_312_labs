# The following functions contains all the flags passed to the different build stages.

set(PACK_REPO_PATH "C:/Users/antho/.mchp_packs" CACHE PATH "Path to the root of a pack repository.")

function(ECE_312_lab2_complete_default_default_AVR_GCC_assemble_rule target)
    set(options
        "-x"
        "assembler-with-cpp"
        "${MP_EXTRA_AS_PRE}"
        "-mmcu=attiny2313a"
        "-B${PACK_REPO_PATH}/Microchip/ATtiny_DFP/3.4.278/gcc/dev/attiny2313a"
        "-c"
        "-Wa,--defsym=__MPLAB_BUILD=1${MP_EXTRA_AS_POST},--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--gdwarf-2,-g")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "DEBUG"
        PRIVATE "__ATtiny2313A__"
        PRIVATE "default=default")
    target_include_directories(${target} PRIVATE "${PACK_REPO_PATH}/Microchip/ATtiny_DFP/3.4.278/include")
endfunction()
function(ECE_312_lab2_complete_default_default_AVR_GCC_assembleWithPreprocess_rule target)
    set(options
        "-x"
        "assembler-with-cpp"
        "${MP_EXTRA_AS_PRE}"
        "-mmcu=attiny2313a"
        "-B${PACK_REPO_PATH}/Microchip/ATtiny_DFP/3.4.278/gcc/dev/attiny2313a"
        "-c"
        "-Wa,--defsym=__MPLAB_BUILD=1${MP_EXTRA_AS_POST},--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--gdwarf-2,-g")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "DEBUG"
        PRIVATE "__ATtiny2313A__"
        PRIVATE "default=default")
    target_include_directories(${target} PRIVATE "${PACK_REPO_PATH}/Microchip/ATtiny_DFP/3.4.278/include")
endfunction()
function(ECE_312_lab2_complete_default_default_AVR_GCC_compile_rule target)
    set(options
        "-g"
        "-gdwarf-2"
        "${MP_EXTRA_CC_PRE}"
        "-mmcu=attiny2313a"
        "-B${PACK_REPO_PATH}/Microchip/ATtiny_DFP/3.4.278/gcc/dev/attiny2313a"
        "-x"
        "c"
        "-c"
        "-funsigned-char"
        "-funsigned-bitfields"
        "-O1"
        "-ffunction-sections"
        "-fdata-sections"
        "-fpack-struct"
        "-fshort-enums"
        "-Wall")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "DEBUG"
        PRIVATE "__ATtiny2313A__"
        PRIVATE "default=default")
    target_include_directories(${target}
        PRIVATE "${PACK_REPO_PATH}/Microchip/ATtiny_DFP/3.4.278/include"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../..")
endfunction()
function(ECE_312_lab2_complete_default_default_AVR_GCC_compile_cpp_rule target)
    set(options
        "-g"
        "-gdwarf-2"
        "${MP_EXTRA_CC_PRE}"
        "-mmcu=attiny2313a"
        "-B${PACK_REPO_PATH}/Microchip/ATtiny_DFP/3.4.278/gcc/dev/attiny2313a"
        "-x"
        "c++"
        "-c"
        "-funsigned-char"
        "-funsigned-bitfields"
        "-O1"
        "-ffunction-sections"
        "-fdata-sections"
        "-fpack-struct"
        "-fshort-enums"
        "-Wall")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "DEBUG"
        PRIVATE "__ATtiny2313A__"
        PRIVATE "default=default")
    target_include_directories(${target}
        PRIVATE "${PACK_REPO_PATH}/Microchip/ATtiny_DFP/3.4.278/include"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../..")
endfunction()
function(ECE_312_lab2_complete_default_link_rule target)
    set(options
        "-gdwarf-2"
        "${MP_EXTRA_LD_PRE}"
        "-mmcu=attiny2313a"
        "-B${PACK_REPO_PATH}/Microchip/ATtiny_DFP/3.4.278/gcc/dev/attiny2313a"
        "-Wl,-Map=mem.map"
        "-Wl,--defsym=__MPLAB_BUILD=1${MP_EXTRA_LD_POST},--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1"
        "-L${CMAKE_CURRENT_SOURCE_DIR}/../../.."
        "-Wl,--gc-sections")
    list(REMOVE_ITEM options "")
    target_link_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__ATtiny2313A__"
        PRIVATE "default=default")
    target_link_libraries(${target} PRIVATE "m")
endfunction()
function(ECE_312_lab2_complete_default_objcopy_ihex_rule target)
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${OBJCOPY}
        ARGS --output-target=ihex ${ECE_312_lab2_complete_default_image_name} ${ECE_312_lab2_complete_default_image_base_name}.hex
        WORKING_DIRECTORY ${ECE_312_lab2_complete_default_output_dir})
endfunction()
function(ECE_312_lab2_complete_default_objcopy_eep_rule target)
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${OBJCOPY}
        ARGS --only-section=.eeprom --change-section-lma .eeprom=0 --no-change-warnings --output-target=ihex ${ECE_312_lab2_complete_default_image_name} ${ECE_312_lab2_complete_default_image_base_name}.eep
        WORKING_DIRECTORY ${ECE_312_lab2_complete_default_output_dir})
endfunction()
function(ECE_312_lab2_complete_default_objcopy_lss_rule target)
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${OBJDUMP}
        ARGS --disassemble --wide --demangle --line-numbers --section-headers --source ${ECE_312_lab2_complete_default_image_name} > ${ECE_312_lab2_complete_default_image_base_name}.lss
        WORKING_DIRECTORY ${ECE_312_lab2_complete_default_output_dir})
endfunction()
function(ECE_312_lab2_complete_default_objcopy_srec_rule target)
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${OBJCOPY}
        ARGS --output-target=srec --remove-section=.eeprom --remove-section=.fuse --remove-section=.lock --remove-section=.signature ${ECE_312_lab2_complete_default_image_name} ${ECE_312_lab2_complete_default_image_base_name}.srec
        WORKING_DIRECTORY ${ECE_312_lab2_complete_default_output_dir})
endfunction()
function(ECE_312_lab2_complete_default_objcopy_sig_rule target)
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${OBJCOPY}
        ARGS --only-section=.user_signatures --change-section-lma .user_signatures=0 --no-change-warnings --output-target=ihex ${ECE_312_lab2_complete_default_image_name} ${ECE_312_lab2_complete_default_image_base_name}.usersignatures
        WORKING_DIRECTORY ${ECE_312_lab2_complete_default_output_dir})
endfunction()
function(ECE_312_lab2_complete_default_objcopy_memusage_rule target)
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${OBJDUMP}
        ARGS -Pmem-usage ${ECE_312_lab2_complete_default_image_name}
        WORKING_DIRECTORY ${ECE_312_lab2_complete_default_output_dir})
endfunction()
