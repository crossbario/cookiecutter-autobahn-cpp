# multi-stage dockerfile that:
#
# (1) first builds a statically linked client program using
#     the autobahn-cpp toolchain docker image, and then
# (2) builds a run-time image containing the executable (and
#     only that), based on the null based image

FROM {{ cookiecutter.image }}

COPY CMakeLists.txt /autobahn/
COPY client.cpp /autobahn/

RUN cd build \
    && cmake .. \
    && make -j4 \
    && find .

CMD ["bash"]
