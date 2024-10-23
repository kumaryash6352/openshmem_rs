#FROM --platform=linux/amd64 archlinux:base-devel
FROM ljmf00/archlinux

RUN uname -m

WORKDIR /scratch

RUN pacman -Sy
RUN yes | pacman -S     \
    base-devel          \
    cmake               \
    flex                \
    openpmix            \
    gcc                 \
    git                 \
    libev               \
    make

# Build libfabric
RUN git clone https://github.com/ofiwg/libfabric.git libfabric
WORKDIR /scratch/libfabric
RUN git checkout 159219639b7fd69d140892120121bbb4d694e295
# From arch's libfabric PKGBUILD
RUN ./autogen.sh
RUN autoreconf -fvi
RUN ./configure --prefix=/scratch/libfabric-bin \
                --enable-tcp=yes
RUN make -j$(nproc)
RUN make install

# Build SOS
WORKDIR /scratch
RUN git clone https://github.com/Sandia-OpenSHMEM/SOS.git sos
WORKDIR /scratch/sos
#RUN git submodule update --init # for trunk
RUN git checkout e616ba00c21fe7983840527ec3abea0672fdf003 # for shmem 1.5
#RUN git checkout 1f89a0f04f1e303c09b3f482d1476adab1c21691 # for shmem 1.4
RUN ./autogen.sh
RUN ./configure --prefix=/scratch/sos-bin         \
                --with-ofi=/scratch/libfabric-bin \
                --enable-pmi-simple
RUN make -j$(nproc)
RUN make install
ENV PATH=$PATH:/scratch/sos-bin/bin
ENV SHMEM_INSTALL_DIR=/scratch/sos-bin

# Build Hydra
WORKDIR /scratch
RUN yes | pacman -S wget
RUN wget https://www.mpich.org/static/downloads/4.2.2/hydra-4.2.2.tar.gz
RUN tar -xzvf hydra-4.2.2.tar.gz
WORKDIR /scratch/hydra-4.2.2
RUN ./configure
RUN make
RUN make install

# Setup a Rust toolchain.
RUN yes | pacman -S rustup
# TODO: msrv
RUN rustup default nightly
# We need clang for libbindgen.
RUN yes | pacman -S llvm clang
RUN yes | pacman -S gdb icu
ENV LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/scratch/sos-bin/lib

# Copy the entire damn worktree.
WORKDIR /scratch/openshmem-rs
COPY . .

WORKDIR /scratch/openshmem-rs/openshmem
RUN cargo build --example mandlebrot

# WORKDIR /scratch/shmemvv
# RUN oshcc test.c

#ENTRYPOINT ["/scratch/sosbin/bin/oshrun", "--allow-run-as-root", "-n", "2", "--", "./a.out"]
ENTRYPOINT ["mpiexec.hydra", "-l", "-n", "1", "gdb", "--args", "./target/debug/examples/mandlebrot", ":", "-n", "1", "./target/debug/examples/mandlebrot"]
#ENTRYPOINT "bash"
