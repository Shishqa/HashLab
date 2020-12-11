file(REMOVE_RECURSE
  "libOpenAddressing.a"
  "libOpenAddressing.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/OpenAddressing.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
