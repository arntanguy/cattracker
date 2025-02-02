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

RUN apt install sudo
RUN echo "ubuntu:ubuntu" | chpasswd && adduser ubuntu sudo
# Ensure sudo group users are not 
# asked for a password when using 
# sudo command by ammending sudoers file
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> \
/etc/sudoers

WORKDIR /home/ubuntu
USER ubuntu
RUN mkdir apps
WORKDIR /home/ubuntu/apps
RUN git clone https://github.com:/gilarus/util-jc.git && cd util-jc/tud && make && make install

WORKDIR /home/ubuntu
RUN echo "source /opt/esp/idf/export.sh" >> /home/ubuntu/.bashrc
RUN echo "alias cmake='cmake -DCMAKE_TOOLCHAIN_FILE=/opt/esp/idf/tools/cmake/toolchain-clang-esp32.cmake -GNinja'" >> /home/ubuntu/.bashrc
ENTRYPOINT ["/bin/bash", "-c"]
