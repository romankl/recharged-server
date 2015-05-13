CC ?= $(which clang)

BUILDTYPE ?= Release
BUILDFILE ?= src/recharged.cc src/parser.cc src/ast.cc src/astnode.cc \
             src/node.cc src/error.cc
OUTFILE ?= reCharged

UV_DIR ?= deps/uv
UV_BUILD_DIR = $(UV_DIR)/build/$(BUILDTYPE)
UV_CC_FLAGS = -fno-omit-frame-pointer

UV_INCLUDE_DIR = $(UV_DIR)/include


JS_DIR ?= deps/js
JS_BUILD_DIR = $(JS_DIR)/src/build_OPT.OBJ/libjs_static.a
JS_CC_FLAGS = -fno-omit-frame-pointer

JS_INCLUDE_DIR = $(JS_DIR)/src/*.h
CFLAGS = -pthread -fno-omit-frame-pointer -Wall -g

all:
	g++ $(CFLAGS) -o $(OUTFILE) $(BUILDFILE) $(UV_BUILD_DIR)/libuv.a -I$(UV_INCLUDE_DIR) 

test:
	./node_modules/mocha/bin/mocha --reporter spec test/*-test.js

.PHONY: uv test

uv:
	@cd $(UV_DIR); \
		./gyp_uv.py -f make > /dev/null; \
		BUILDTYPE=$(BUILDTYPE) CFLAGS=$(UV_CC_FLAGS) make -C out -j4
