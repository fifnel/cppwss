TESTS = cppwss_test
check_PROGRAMS = cppwss_test
cppwss_test_CXXFLAGS = -DBOOST_REGEX_DYN_LINK -DENABLE_UNIT_TEST -I../src
cppwss_test_LDFLAGS = -lboost_system-mt -lboost_regex-mt -lboost_unit_test_framework-mt
cppwss_test_SOURCES = \
				 ../src/server.cpp \
				 ../src/connection_manager.cpp \
				 ../src/connection.cpp \
				 ../src/packet_parser.cpp \
				 ../src/http_header_packet_parser.cpp \
				 ../src/dummy_packet_parser.cpp \
				 http_header_packet_parser_test.cpp \
				 initialize_unit_test.cpp

