FROM debian:trixie-slim

# Install base packages + clangd 22.1.0 from GitHub release
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
       gcc gdb g++ cmake git \
       libc++-dev libc++abi-dev \
       cppcheck cpplint \
       wget ca-certificates unzip \
       ninja-build \
    && wget -qO /tmp/clangd.zip \
       https://github.com/clangd/clangd/releases/download/22.1.0/clangd-linux-22.1.0.zip \
    && unzip -q /tmp/clangd.zip -d /tmp/clangd \
    && mv /tmp/clangd/clangd_22.1.0/bin/clangd /usr/local/bin/ \
    && mv /tmp/clangd/clangd_22.1.0/lib/clang /usr/local/lib/ \
    && ln -s /usr/local/bin/clangd /usr/bin/clangd \
    && rm -rf /tmp/clangd /tmp/clangd.zip \
    && apt-get purge -y unzip \
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