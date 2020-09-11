templatesdir=$(datadir)/git-extra/templates

AM_CPPFLAGS = \
	-I$(top_builddir)/include/ \
	-I$(top_srcdir)/include/ \
	-DTEMPLATE_DIR='"$(templatesdir)"'

bin_PROGRAMS = git-ex
git_ex_SOURCES = \
	src/add.c \
	src/branch.c \
	src/cat.c \
	src/commit.c \
	src/default.c \
	src/edit.c \
	src/editor.c \
	src/exec.c \
	src/git.c \
	src/hash.c \
	src/log.c \
	src/ls.c \
	src/main.c \
	src/prepend.c \
	src/templ.c
git_ex_SOURCES += \
	include/add.h \
	include/branch.h \
	include/cat.h \
	include/commit.h \
	include/default.h \
	include/edit.h \
	include/editor.h \
	include/exec.h \
	include/git.h \
	include/hash.h \
	include/log.h \
	include/ls.h \
	include/main.h \
	include/opt.h \
	include/prepend.h \
	include/templ.h

dist_doc_DATA = $(top_srcdir)/README.md
dist_templates_DATA = \
	$(top_srcdir)/templates/bug.template

SUBDIRS = test/integration test/unit

if HAVE_DOCKER
IMAGE_NAME=git-extra
CONTAINER_NAME=git-extra-test
build:
	docker build -t $(IMAGE_NAME) .

run: build
	docker run -d \
		--name $(CONTAINER_NAME) \
		--cap-add=SYS_PTRACE --security-opt seccomp=unconfined \
	 	$(IMAGE_NAME)

start: build
	-docker run -it --rm \
		--cap-add=SYS_PTRACE --security-opt seccomp=unconfined \
		$(IMAGE_NAME)

stop:
	docker stop $(CONTAINER_NAME)
	docker rm $(CONTAINER_NAME);
else
build: missing-local
run: missing-local
start: missing-local
stop: missing-local
missing-local:
	@echo "docker not found"
endif