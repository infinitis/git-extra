FROM debian:latest as base

RUN apt-get update
RUN apt-get install -y git autoconf automake gcc make vim

FROM base as unit-tester

RUN apt-get install -y gdb vim valgrind

FROM base as core

WORKDIR /build

COPY Makefile.am .
COPY configure.ac .

COPY README.md .
COPY templates templates/

COPY test test/

COPY include include/
RUN autoreconf -vif

COPY src src/
RUN ./configure

RUN make
RUN make distcheck
RUN make install

FROM unit-tester

WORKDIR /build
COPY --from=core /build /build

COPY --from=core /usr/local/share/git-extra/templates/ /usr/local/share/git-extra/templates/

RUN ./configure
RUN make check || cat test/unit/test-suite.log

FROM node:latest as integration-tester

COPY --from=core /usr/local/bin/git-ex /usr/local/bin/git-ex
COPY --from=core /usr/local/share/git-extra/templates/ /usr/local/share/git-extra/templates/

USER node
WORKDIR /home/node

COPY --from=core --chown=node:node /build/test/integration/index.js .
COPY --from=core --chown=node:node /build/test/integration/package.json .
COPY --from=core --chown=node:node /build/test/integration/package-lock.json .

RUN npm install

COPY --from=core --chown=node:node /build/test/integration/test/ test/

RUN npm test

FROM core as final

WORKDIR /root
RUN git init working

# setup test repository; Docker image meant to be a sandbox
WORKDIR /root/working

RUN echo "test" > test.txt
RUN git config --global core.editor vim

RUN git config --local user.name "test"
RUN git config --local user.email "test@email"

RUN git add -A
RUN git commit -a -m "..."

ENTRYPOINT bash