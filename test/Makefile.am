TESTS = cppwss_test
check_PROGRAMS = cppwss_test
cppwss_test_CXXFLAGS = -DBOOST_REGEX_DYN_LINK -DENABLE_UNIT_TEST -I../src
cppwss_test_LDFLAGS = -lboost_system-mt -lboost_regex-mt -lcryptopp -lboost_unit_test_framework-mt
cppwss_test_SOURCES = \
				 ../src/server.cpp \
				 ../src/connection_manager.cpp \
				 ../src/connection.cpp \
				 ../src/packet_parser.cpp \
				 ../src/http_header_packet_parser.cpp \
				 ../src/websocket_parser.cpp \
				 ../src/websocket_frame.cpp \
				 ../src/dummy_packet_parser.cpp \
				 \
				 server_test.cpp \
				 connection_manager_test.cpp \
				 connection_test.cpp \
				 http_header_packet_parser_test.cpp \
				 websocket_parser_test.cpp \
				 websocket_frame_test.cpp \
				 dummy_packet_parser_test.cpp \
				 \
				 initialize_unit_test.cpp
