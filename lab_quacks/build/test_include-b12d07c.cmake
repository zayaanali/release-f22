if(EXISTS "/workspaces/CS 225 Code/release-f22/lab_quacks/build/test_tests-b12d07c.cmake")
  include("/workspaces/CS 225 Code/release-f22/lab_quacks/build/test_tests-b12d07c.cmake")
else()
  add_test(test_NOT_BUILT-b12d07c test_NOT_BUILT-b12d07c)
endif()
