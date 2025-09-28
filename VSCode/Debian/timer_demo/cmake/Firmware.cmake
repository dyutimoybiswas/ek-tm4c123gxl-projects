macro(add_raw_binary output input)
  add_custom_command(
    OUTPUT ${output}
    COMMAND arm-none-eabi-objcopy -O binary ${input} ${output}
    DEPENDS ${input}
    COMMENT "Creating raw binary ${output}")
  add_custom_target(${output}-target ALL DEPENDS ${output})
endmacro(add_raw_binary)