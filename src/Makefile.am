bin_PROGRAMS = cppwss
cppwss_CXXFLAGS = -DBOOST_REGEX_DYN_LINK
cppwss_LDFLAGS = -lboost_system-mt -lboost_regex-mt -lcryptopp
cppwss_SOURCES = \
				 main.cpp \
				 server.cpp \
				 connection_manager.cpp \
				 connection.cpp \
				 packet_parser.cpp \
				 http_header_packet_parser.cpp \
				 web_socket_parser.cpp \
				 websocket_frame.cpp \
				 dummy_packet_parser.cpp
