# Makefile for JsonBenchmarkCpp
# A small program to compare perfomance of different json libs available
# 
# Copyright Lijo Antony 2011
# Distributed under Apache License, Version 2.0
# see accompanying file LICENSE.txt

CC=g++
CFLAGS=-c -Wall
LDFLAGS=libs/libjson/libjson/libjson.a -lrt libs/json_spirit/json_spirit_v4.05/build/json_spirit/libjson_spirit.a
OBJECTS=$(SOURCES:.cpp=.o)
INCLUDE=\
		-Ilibs/cajun/cajun\
		-Ilibs/json_spirit/json_spirit_v4.05/json_spirit\
		-Ilibs/libjson/libjson\
		-Ilibs/json-parser

EXECUTABLE=JsonBenchmarkCpp

SOURCES=main.cpp libs/json-parser/json.c

all: cajun json_spirit libjson $(SOURCES) $(EXECUTABLE)
		
cajun: 
	if [ ! -d "libs/cajun/cajun" ]; then\
		unzip libs/cajun/cajun.zip -d libs/cajun;\
	fi

json_spirit:
	if [ ! -d "libs/json_spirit/json_spirit_v4.05" ]; then\
		unzip libs/json_spirit/json_spirit_v4_05.zip -d libs/json_spirit;\
	fi

libjson:
	if [ ! -d "libs/libjson/libjson" ]; then\
		unzip libs/libjson/libjson_7.4.0.zip -d libs/libjson;\
		make -w -Clibs/libjson/libjson;\
	fi

$(EXECUTABLE): $(OBJECTS) 
		$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
		$(CC) $(CFLAGS) $(INCLUDE) $< -o $@
clean:
	    \rm *.o $(EXECUTABLE)
