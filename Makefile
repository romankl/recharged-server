BUILDTYPE ?= Release


.PHONY: gyp clean distclean debug run-debug


debug:
	-cd out/ && make BUILDTYPE=Debug V=1

run-debug:
	-lldb out/Debug/recharged

gyp:
	./gyp_recharged -f make


distclean:
	-rm -rf out/


clean:
	-rm -rf out/$(BUILDTYPE)/
	-rm -f out/Makefile
