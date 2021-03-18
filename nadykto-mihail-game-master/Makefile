ifeq ($(OS),Windows_NT)
	FLAGS = -DCMAKE_SH="CMAKE_SH-NOTFOUND" -G "MinGW Makefiles"
else
	FLAGS = ""
endif

all: clean reload build exec

mkdir_build:
	[ -d ./cmake-build-debug ] | mkdir -p cmake-build-debug

build:
	cd cmake-build-debug;make

exec:
	./cmake-build-debug/hike

clean:
	rm -rf cmake-build-debug

reload: mkdir_build
	cd cmake-build-debug;cmake ..

fast_build:
	cd cmake-build-debug;make

run: fast_build exec
