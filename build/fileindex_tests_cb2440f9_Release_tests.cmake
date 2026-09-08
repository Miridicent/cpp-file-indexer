add_test([=[toLowerTest.ConvertsUppercaseToLowercase]=]  C:/Users/conor/OneDrive/Documents/cpp-file-indexer/build/Release/fileindex_tests.exe [==[--gtest_filter=toLowerTest.ConvertsUppercaseToLowercase]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[toLowerTest.ConvertsUppercaseToLowercase]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[C:\Users\conor\OneDrive\Documents\cpp-file-indexer\tests\file_indexer_tests.cpp:6]==]
    WORKING_DIRECTORY [==[C:/Users/conor/OneDrive/Documents/cpp-file-indexer/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[searchByExtensionTest.FindsMatchingExtension]=]  C:/Users/conor/OneDrive/Documents/cpp-file-indexer/build/Release/fileindex_tests.exe [==[--gtest_filter=searchByExtensionTest.FindsMatchingExtension]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[searchByExtensionTest.FindsMatchingExtension]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[C:\Users\conor\OneDrive\Documents\cpp-file-indexer\tests\file_indexer_tests.cpp:11]==]
    WORKING_DIRECTORY [==[C:/Users/conor/OneDrive/Documents/cpp-file-indexer/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[searchByFilenameTest.FindsMatchingFilename]=]  C:/Users/conor/OneDrive/Documents/cpp-file-indexer/build/Release/fileindex_tests.exe [==[--gtest_filter=searchByFilenameTest.FindsMatchingFilename]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[searchByFilenameTest.FindsMatchingFilename]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[C:\Users\conor\OneDrive\Documents\cpp-file-indexer\tests\file_indexer_tests.cpp:24]==]
    WORKING_DIRECTORY [==[C:/Users/conor/OneDrive/Documents/cpp-file-indexer/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
set(fileindex_tests_TESTS [==[toLowerTest.ConvertsUppercaseToLowercase]==] [==[searchByExtensionTest.FindsMatchingExtension]==] [==[searchByFilenameTest.FindsMatchingFilename]==])
