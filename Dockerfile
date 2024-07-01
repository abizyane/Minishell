FROM debian:bullseye-slim

RUN apt-get update && apt-get upgrade -y &&\
    apt-get install -y \
    build-essential \
    libreadline-dev

COPY . ./minishell

RUN cd /minishell &&\
    make && make clean &&\
    mv minishell /usr/local/bin &&\
    cd / && rm -rf minishell \
    cd /home

CMD ["minishell"]