# The following variables contains the files used by the different stages of the build process.
set(ECE_312_lab2_complete_default_default_AVR_GCC_FILE_TYPE_assemble)
set_source_files_properties(${ECE_312_lab2_complete_default_default_AVR_GCC_FILE_TYPE_assemble} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${ECE_312_lab2_complete_default_default_AVR_GCC_FILE_TYPE_assemble})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(ECE_312_lab2_complete_default_default_AVR_GCC_FILE_TYPE_assembleWithPreprocess)
set_source_files_properties(${ECE_312_lab2_complete_default_default_AVR_GCC_FILE_TYPE_assembleWithPreprocess} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${ECE_312_lab2_complete_default_default_AVR_GCC_FILE_TYPE_assembleWithPreprocess})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(ECE_312_lab2_complete_default_default_AVR_GCC_FILE_TYPE_compile
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../buzzer.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../songs.c")
set_source_files_properties(${ECE_312_lab2_complete_default_default_AVR_GCC_FILE_TYPE_compile} PROPERTIES LANGUAGE C)
set(ECE_312_lab2_complete_default_default_AVR_GCC_FILE_TYPE_compile_cpp)
set_source_files_properties(${ECE_312_lab2_complete_default_default_AVR_GCC_FILE_TYPE_compile_cpp} PROPERTIES LANGUAGE CXX)
set(ECE_312_lab2_complete_default_default_AVR_GCC_FILE_TYPE_link)
set(ECE_312_lab2_complete_default_default_AVR_GCC_FILE_TYPE_objcopy_ihex)
set(ECE_312_lab2_complete_default_default_AVR_GCC_FILE_TYPE_objcopy_eep)
set(ECE_312_lab2_complete_default_default_AVR_GCC_FILE_TYPE_objcopy_lss)
set(ECE_312_lab2_complete_default_default_AVR_GCC_FILE_TYPE_objcopy_srec)
set(ECE_312_lab2_complete_default_default_AVR_GCC_FILE_TYPE_objcopy_sig)
set(ECE_312_lab2_complete_default_default_AVR_GCC_FILE_TYPE_objcopy_memusage)
set(ECE_312_lab2_complete_default_image_name "default.elf")
set(ECE_312_lab2_complete_default_image_base_name "default")

# The output directory of the final image.
set(ECE_312_lab2_complete_default_output_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../out/ECE_312_lab2_complete")

# The full path to the final image.
set(ECE_312_lab2_complete_default_full_path_to_image ${ECE_312_lab2_complete_default_output_dir}/${ECE_312_lab2_complete_default_image_name})

# Potential output file extensions
set(output_extensions
    .hex
    .lss
    .eep
    .srec
    .usersignatures)
list(TRANSFORM output_extensions PREPEND "${ECE_312_lab2_complete_default_output_dir}/${ECE_312_lab2_complete_default_image_base_name}")
