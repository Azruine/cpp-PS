FROM debian:trixie-slim

RUN apt update && apt install -y gcc gdb g++ cmake git libc++-dev libc++abi-dev clangd cppcheck cpplint

ARG USERNAME=azruine
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME -s /bin/bash \
    && apt-get update \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

USER $USERNAME

# RUN mkdir -p /home/$USERNAME/.config/clangd \
#     && cp /workspaces/${localWorkspaceFolderBasename}/.clangd /home/$USERNAME/.config/clangd/config.yaml