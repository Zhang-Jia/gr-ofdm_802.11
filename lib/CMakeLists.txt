# Copyright 2011,2012 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
list(APPEND ofdm_80211_sources
    short_match_filter_impl.cc
    ofdm_sync_short_impl.cc
    bor_impl.cc
    )

set(ofdm_80211_sources "${ofdm_80211_sources}" PARENT_SCOPE)
if(NOT ofdm_80211_sources)
	MESSAGE(STATUS "No C++ sources... skipping lib/")
	return()
endif(NOT ofdm_80211_sources)

add_library(gnuradio-ofdm_80211 SHARED ${ofdm_80211_sources})
target_link_libraries(gnuradio-ofdm_80211 ${Boost_LIBRARIES} ${GNURADIO_ALL_LIBRARIES})
set_target_properties(gnuradio-ofdm_80211 PROPERTIES DEFINE_SYMBOL "gnuradio_ofdm_80211_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-ofdm_80211 PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
install(TARGETS gnuradio-ofdm_80211
    LIBRARY DESTINATION lib${LIB_SUFFIX} # .so/.dylib file
    ARCHIVE DESTINATION lib${LIB_SUFFIX} # .lib file
    RUNTIME DESTINATION bin              # .dll file
)

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})
list(APPEND test_ofdm_80211_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_ofdm_80211.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_ofdm_80211.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_ofdm_sync_short.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_short_match_filter.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/)

add_executable(test-ofdm_80211 ${test_ofdm_80211_sources})

target_link_libraries(
  test-ofdm_80211
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-ofdm_80211
)

GR_ADD_TEST(test_ofdm_80211 test-ofdm_80211)
