# Copyright (c) 2023 ivfzhou
# data-structure-algorithm is licensed under Mulan PSL v2.
# You can use this software according to the terms and conditions of the Mulan PSL v2.
# You may obtain a copy of Mulan PSL v2 at:
#          http://license.coscl.org.cn/MulanPSL2
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
# EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
# MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
# See the Mulan PSL v2 for more details.

CC = gcc
AR = ar
SHELL = sh

PREFIX ?= /usr/local/
ALL_SOURCES := $(wildcard *.c)
ALL_HEADERS := $(wildcard *.h)
SOURCES := $(filter-out %_test.c,$(ALL_SOURCES))
TEST_TARGETS := $(sort $(patsubst %.c,%,$(wildcard *_test.c)))
HEADERS := $(filter-out common.h,$(ALL_HEADERS))
STATIC_DEBUG_OBJECTS := $(addprefix build/objects/static-debug/,$(patsubst %.c,%.o,$(SOURCES)))
STATIC_RELEASE_OBJECTS := $(addprefix build/objects/static-release/,$(patsubst %.c,%.o,$(SOURCES)))
SHARED_DEBUG_OBJECTS := $(addprefix build/objects/shared-debug/,$(patsubst %.c,%.o,$(SOURCES)))
SHARED_RELEASE_OBJECTS := $(addprefix build/objects/shared-release/,$(patsubst %.c,%.o,$(SOURCES)))
STATIC_DEBUG_OBJECTS_DIRECTORIES := $(sort $(dir $(STATIC_DEBUG_OBJECTS)))
STATIC_RELEASE_OBJECTS_DIRECTORIES := $(sort $(dir $(STATIC_RELEASE_OBJECTS)))
SHARED_DEBUG_OBJECTS_DIRECTORIES := $(sort $(dir $(SHARED_DEBUG_OBJECTS)))
SHARED_RELEASE_OBJECTS_DIRECTORIES := $(sort $(dir $(SHARED_RELEASE_OBJECTS)))

.PHONY: all clean build test install uninstall docs $(TEST_TARGETS)

all: clean build docs test install

%/:
	@mkdir -p $@

build/objects/static-debug/%.o: %.c | $(STATIC_DEBUG_OBJECTS_DIRECTORIES)
	@$(CC) -std=c17 -finput-charset=UTF-8 -fexec-charset=UTF-8 -Wpedantic -Winline -Wall -Wextra -Wno-unused-variable \
	       -Wno-unused-function -Wno-unused-local-typedefs -Wno-unused-parameter -O0 -g3 -c -o $@ $<

build/objects/static-release/%.o: %.c | $(STATIC_RELEASE_OBJECTS_DIRECTORIES)
	@$(CC) -std=c17 -finput-charset=UTF-8 -fexec-charset=UTF-8 -Wpedantic -Winline -Wall -Wextra -Wno-unused-variable \
	       -Wno-unused-function -Wno-unused-local-typedefs -Wno-unused-parameter -O3 -flto -fPIC -c -o $@ $<

build/objects/shared-debug/%.o: %.c | $(SHARED_DEBUG_OBJECTS_DIRECTORIES)
	@$(CC) -std=c17 -finput-charset=UTF-8 -fexec-charset=UTF-8 -Wpedantic -Winline -Wall -Wextra -Wno-unused-variable \
	       -Wno-unused-function -Wno-unused-local-typedefs -Wno-unused-parameter -O0 -g3 -c -o $@ $<

build/objects/shared-release/%.o: %.c | $(SHARED_RELEASE_OBJECTS_DIRECTORIES)
	@$(CC) -std=c17 -finput-charset=UTF-8 -fexec-charset=UTF-8 -Wpedantic -Winline -Wall -Wextra -Wno-unused-variable \
	       -Wno-unused-function -Wno-unused-local-typedefs -Wno-unused-parameter -O3 -DNDEBUG -flto -fPIC -c -o $@ $<

build/libdata-structure-algorithm-static-debug.a: $(STATIC_DEBUG_OBJECTS)
	@$(AR) rcs $@ $^

define make_debug_target
build/debug/$(1): build/objects/static-debug/$(1).o build/libdata-structure-algorithm-static-debug.a | build/debug/
	@$$(CC) -o $$@ $$^

$(1): build/debug/$(1)
endef

$(foreach v,$(TEST_TARGETS),$(eval $(call make_debug_target,$(v))))

build/libdata-structure-algorithm.so: $(SHARED_RELEASE_OBJECTS)
	@$(CC) -shared -flto -Wl,-soname,libdata-structure-algorithm.so -Wl,-rpath,'$$ORIGIN' -o $@ $^

build/libdata-structure-algorithm.a: $(STATIC_RELEASE_OBJECTS)
	@$(AR) rcs $@ $^

build: build/libdata-structure-algorithm.so build/libdata-structure-algorithm.a
	@echo 'build done'

build/libdata-structure-algorithm-static-release.a: $(STATIC_RELEASE_OBJECTS)
	@$(AR) rcs $@ $^

define make_test_target
build/test/$(1): build/objects/static-release/$(1).o build/libdata-structure-algorithm-static-release.a | build/test/
	@$$(CC) -o $$@ $$^
	@echo 'start $(1) test'
	@build/test/$(1)
	@echo 'end $(1) test'
endef

$(foreach v,$(TEST_TARGETS),$(eval $(call make_test_target,$(v))))

test: $(addprefix build/test/,$(TEST_TARGETS))
	@echo 'test done'

clean:
	@rm -rf build
	@rm -rf docs
	@echo 'clean done'

install: build
	@mkdir -p $(PREFIX)/lib/ivfzhou/data-structure-algorithm/
	@cp -f build/libdata-structure-algorithm.so build/libdata-structure-algorithm.a $(PREFIX)/lib/ivfzhou/data-structure-algorithm/
	@mkdir -p  $(PREFIX)/include/ivfzhou/data-structure-algorithm/
	@cp -f $(HEADERS) $(PREFIX)/include/ivfzhou/data-structure-algorithm/
	@echo 'install done'

uninstall:
	@rm -rf $(PREFIX)/lib/ivfzhou/data-structure-algorithm/
	@rm -rf $(PREFIX)/include/ivfzhou/data-structure-algorithm/

docs:
	@doxygen ./Doxyfile
	@echo docs done
