FROM debian:trixie-slim

# Install base packages + LLVM 23 tools from apt.llvm.org.
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
       gcc gdb g++ cmake git \
       libc++-dev libc++abi-dev \
       cppcheck cpplint \
       time \
       wget ca-certificates \
       ninja-build \
    && wget -qO /etc/apt/trusted.gpg.d/apt.llvm.org.asc \
       https://apt.llvm.org/llvm-snapshot.gpg.key \
    && echo "deb http://apt.llvm.org/trixie/ llvm-toolchain-trixie main" \
       > /etc/apt/sources.list.d/llvm-23.list \
    && apt-get update \
    && apt-get install -y --no-install-recommends clangd-23 clang-format-23 \
    && ln -sf /usr/bin/clangd-23 /usr/bin/clangd \
    && ln -sf /usr/bin/clang-format-23 /usr/bin/clang-format \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Create non-root user
ARG USERNAME=azruine
ARG USER_UID=1000
ARG USER_GID=$USER_UID
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME -s /bin/bash \
    && apt-get update \
    && apt-get install -y --no-install-recommends sudo \
    && echo "$USERNAME ALL=(root) NOPASSWD:ALL" > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

USER $USERNAME
# RUN mkdir -p /home/$USERNAME/.config/clangd \
#     && cp /workspaces/${localWorkspaceFolderBasename}/.clangd /home/$USERNAME/.config/clangd/config.yaml