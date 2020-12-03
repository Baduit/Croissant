function(addTest test_name test_files)
	set(test_target ${test_name}_test)

	add_executable(${test_target} ${test_files})
	target_compile_features(${test_target} PRIVATE cxx_std_20)
	target_compile_options(${test_target}
						PRIVATE
						$<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
						$<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wextra -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -g>)
	target_link_libraries(${test_target} Croissant)
	add_test(${test_name} ${test_target})
endfunction()