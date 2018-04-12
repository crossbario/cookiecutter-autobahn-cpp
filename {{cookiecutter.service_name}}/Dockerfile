# Multi-stage dockerfile for autobahn-cpp based programs:
#
# (1) first builds a statically linked client program using
#     the autobahn-cpp toolchain docker image, and then
# (2) builds a run-time image containing the executable (and
#     only that), based on the null based image
#
# The actual, final Docker image for the user program
# created is around 3MB in size!
#
# This is possible, because the user program is completely
# statically linked, and because we base the 2nd image (the
# user application run-time image) from "scratch" - a container
# that comes without anything, zero, nada.
#
# In fact, it is like containerizing a single-file executable.

#
# Stage 1
#
FROM {{ cookiecutter.image }}

COPY CMakeLists.txt /autobahn/
COPY client.cpp /autobahn/

RUN    rm -rf build \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make -j4 \
    && strip client \
    && wc -c client \
    && file client


#
# Stage 2
#
FROM scratch

WORKDIR /
COPY --from=0 /autobahn/build/client .

CMD ["/client", "127.0.0.1", "8080"]
