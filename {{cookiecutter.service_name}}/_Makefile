.PHONY: run build

HOSTIP=$(shell ip route get 1 | awk '{print $$NF;exit}')

qemu_deps:
	mkdir -p ./.qemu
	cp /usr/bin/qemu-arm-static ./.qemu/
	cp /usr/bin/qemu-aarch64-static ./.qemu/


# build all architectures
build_all: build build_armhf build_aarch64 file

# build for x86-64
build:
	time docker run -it --rm \
		--net=host \
		-v ${PWD}/app:/usr/local/app/examples \
		-v ${PWD}/.build_x86-64:/build \
		crossbario/autobahn-cpp:gcc \
		/usr/local/app/examples/build

# build for ARM v7
build_armhf:
	time docker run -it --rm \
		--net=host \
		-v ${PWD}/app:/usr/local/app/examples \
		-v ${PWD}/.build_armhf:/build \
		crossbario/autobahn-cpp-armhf:gcc \
		/usr/local/app/examples/build

# build for ARM v8
build_aarch64:
	time docker run -it --rm \
		--net=host \
		-v ${PWD}/app:/usr/local/app/examples \
		-v ${PWD}/.build_aarch64:/build \
		crossbario/autobahn-cpp-aarch64:gcc \
		/usr/local/app/examples/build


# test all architectures
start_all: start start_armhf start_aarch64

# test for x86-64
start:
	docker run -it --rm \
		--net=host \
		-v ${PWD}/.build_x86-64:/build \
		debian:stretch \
		/build/client ${HOSTIP} 8080

# test for ARM v7
start_armhf:
	docker run -it --rm \
		--net=host \
        -v ${PWD}/.qemu/qemu-arm-static:/usr/bin/qemu-arm-static \
		-v ${PWD}/.build_armhf:/build \
		armhf/debian:stretch \
		/build/client ${HOSTIP} 8080

# test for ARM v8
start_aarch64:
	docker run -it --rm \
		--net=host \
        -v ${PWD}/.qemu/qemu-aarch64-static:/usr/bin/qemu-aarch64-static \
		-v ${PWD}/.build_aarch64:/build \
		aarch64/debian:stretch \
		/build/client ${HOSTIP} 8080


file:
	ls -la .build_*
	file .build_x86-64/client
	file .build_armhf/client
	file .build_aarch64/client

clean:
	-sudo rm -rf .build_x86-64
	-sudo rm -rf .build_armhf
	-sudo rm -rf .build_aarch64
