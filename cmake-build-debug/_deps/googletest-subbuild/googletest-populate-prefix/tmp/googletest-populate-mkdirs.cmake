# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/raulm/labwork-5-rurkk/cmake-build-debug/_deps/googletest-src"
  "C:/Users/raulm/labwork-5-rurkk/cmake-build-debug/_deps/googletest-build"
  "C:/Users/raulm/labwork-5-rurkk/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix"
  "C:/Users/raulm/labwork-5-rurkk/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "C:/Users/raulm/labwork-5-rurkk/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "C:/Users/raulm/labwork-5-rurkk/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "C:/Users/raulm/labwork-5-rurkk/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/raulm/labwork-5-rurkk/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
