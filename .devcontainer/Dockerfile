FROM espressif/idf:release-v5.4

RUN apt update && apt install -y --no-install-recommends \
    ripgrep clang clang-tidy


# Install clang tools specific to esp32
# TODO move with esp idf commands (but it will rebuild everything after)
# See https://github.com/espressif/esp-idf/issues/6868
WORKDIR /opt/esp/idf
RUN . ./export.sh  \
    && /opt/esp/idf/tools/idf_tools.py install esp-clang \
    && /opt/esp/idf/tools/idf_tools.py install xtensa-clang

USER ubuntu 

RUN echo "source /opt/esp/idf/export.sh" >> /home/ubuntu/.bashrc
RUN echo "alias cmake='cmake -DCMAKE_TOOLCHAIN_FILE=/opt/esp/idf/tools/cmake/toolchain-clang-esp32.cmake -GNinja'" >> /home/ubuntu/.bashrc
ENTRYPOINT ["/bin/bash", "-c"]
