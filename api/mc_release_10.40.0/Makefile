# Copyright 2022 NXP
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# * Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
# * Redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution.
# * Neither the name of the above-listed copyright holders nor the
# names of any contributors may be used to endorse or promote products
# derived from this software without specific prior written permission.
#
#
# ALTERNATIVELY, this software may be distributed under the terms of the
# GNU General Public License ("GPL") as published by the Free Software
# Foundation, either version 2 of that License or (at your option) any
# later version.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

INCLUDE_HEADER_PATH ?= ./include
DPLIB_HEADER_PATH ?= ./include/dplib
ARCH_HEADER_PATH ?= ./include/arch
NET_HEADER_PATH ?= ./include/net

PKG_NAME = dplib
PKG_RELEASE = 1

ARFLAGS = -rvU

ifdef M64BIT
  CFLAGS += -m64
  LDFLAGS += -m64
endif

CFLAGS += -D_HOST_DPLIB_ -O2 -D__STDC_LIMIT_MACROS\
          -I. \
          -I$(INCLUDE_HEADER_PATH) \
          -I$(DPLIB_HEADER_PATH) \
          -I$(ARCH_HEADER_PATH) \
          -I$(NET_HEADER_PATH)

LDFLAGS += -L.

CXXFLAGS = $(CFLAGS)

.PHONY: default
default: dplib

objects = ./dpaiop.o ./dpbp.o ./dpci.o ./dpcon.o \
          ./dpdbg.o ./dpdcei.o ./dpdmai.o ./dpdmux.o \
          ./dpio.o ./dpkg.o ./dpmac.o ./dpmcp.o \
          ./dpmng.o ./dpni.o ./dprc.o ./dprtc.o \
          ./dpseci.o ./dpsparser.o ./dpsw.o ./mc_sys.o

others = ./dplib ./dplib.o

all: dplib
dplib : ./dplib.o $(objects)
	$(CXX) $(LDFLAGS) -o $@ $^ 

.PHONY: clean
clean:
	rm -f $(others) $(objects)
