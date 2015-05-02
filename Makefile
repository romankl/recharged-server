CC ?= $(which clang)

BUILDTYPE ?= Release
BUILDFILE ?= src/recharged.c src/error.c src/queue.c
OUTFILE ?= reCharged

UV_DIR ?= deps/uv
UV_BUILD_DIR = $(UV_DIR)/build/$(BUILDTYPE)
UV_CC_FLAGS = -fno-omit-frame-pointer

UV_INCLUDE_DIR = $(UV_DIR)/include
CFLAGS = -pthread -fno-omit-frame-pointer -Wall -g

all:
	$(CC) $(CFLAGS) -o $(OUTFILE) $(BUILDFILE) $(UV_BUILD_DIR)/libuv.a -I$(UV_INCLUDE_DIR)


.PHONY: uv

uv:
	@cd $(UV_DIR); \
		./gyp_uv.py -f make > /dev/null; \
		BUILDTYPE=$(BUILDTYPE) CFLAGS=$(UV_CC_FLAGS) make -C out -j4
