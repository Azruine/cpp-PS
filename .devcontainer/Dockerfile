FROM gcc:16.2.0-trixie

ARG LLVM_VERSION=24

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
       ca-certificates \
       cmake \
       cppcheck \
       cpplint \
       gdb \
       git \
       ninja-build \
       sudo \
       time \
       wget \
    && wget -qO /etc/apt/trusted.gpg.d/apt.llvm.org.asc \
       https://apt.llvm.org/llvm-snapshot.gpg.key \
    && echo "deb https://apt.llvm.org/trixie/ llvm-toolchain-trixie main" \
       > /etc/apt/sources.list.d/llvm.list \
    && apt-get update \
    && apt-get install -y --no-install-recommends \
       clang-${LLVM_VERSION} \
       clangd-${LLVM_VERSION} \
       clang-format-${LLVM_VERSION} \
       libc++-${LLVM_VERSION}-dev \
       libc++abi-${LLVM_VERSION}-dev \
    && ln -sf /usr/bin/clang-${LLVM_VERSION} /usr/local/bin/clang \
    && ln -sf /usr/bin/clang++-${LLVM_VERSION} /usr/local/bin/clang++ \
    && ln -sf /usr/bin/clangd-${LLVM_VERSION} /usr/local/bin/clangd \
    && ln -sf /usr/bin/clang-format-${LLVM_VERSION} /usr/local/bin/clang-format \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Install GCC's matching pretty-printer in GDB's default trusted directory.
RUN set -eu; \
    libstdcpp="$(readlink -f "$(g++ -print-file-name=libstdc++.so.6)")"; \
    printer="${libstdcpp}-gdb.py"; \
    destination="/usr/share/gdb/auto-load${printer}"; \
    mkdir -p "$(dirname "$destination")"; \
    mv "$printer" "$destination"

ARG USERNAME=azruine
ARG USER_UID=1000
ARG USER_GID=${USER_UID}

RUN groupadd --gid ${USER_GID} ${USERNAME} \
    && useradd --uid ${USER_UID} --gid ${USER_GID} -m ${USERNAME} -s /bin/bash \
    && echo "${USERNAME} ALL=(root) NOPASSWD:ALL" > /etc/sudoers.d/${USERNAME} \
    && chmod 0440 /etc/sudoers.d/${USERNAME}

USER ${USERNAME}
