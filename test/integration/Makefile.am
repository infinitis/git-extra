EXTRA_DIST = \
	index.js \
	package.json \
	package-lock.json \
	test/utils.js \
	test/ls.integration.tests.js \
	test/cat.integration.tests.js \
	test/edit.integration.tests.js \
	test/add.integration.tests.js \
	test/branch.pattern.integration.test.js

if HAVE_DOCKER
PACKAGE_CONTAINER_NAME=git_extra_package_init

package_init:
	docker run -d --name $(PACKAGE_CONTAINER_NAME) node:latest tail -f /dev/null
	docker cp package.json $(PACKAGE_CONTAINER_NAME):/home/node/
	docker cp package-lock.json $(PACKAGE_CONTAINER_NAME):/home/node/

package_extract:
	docker cp $(PACKAGE_CONTAINER_NAME):/home/node/package.json ./package.json
	docker cp $(PACKAGE_CONTAINER_NAME):/home/node/package-lock.json ./package-lock.json
	$(MAKE) -s package_stop

package_stop:
	docker stop $(PACKAGE_CONTAINER_NAME)
	docker rm $(PACKAGE_CONTAINER_NAME)

outdated: package_init
	-docker exec -it -w /home/node $$(docker container ls -q -f name=$(PACKAGE_CONTAINER_NAME)) npm outdated
	$(MAKE) -s package_stop

update: package_init
	-docker exec -it -w /home/node $$(docker container ls -q -f name=$(PACKAGE_CONTAINER_NAME)) /bin/bash
	$(MAKE) -s package_extract

inspect: package_init
	docker exec -it $$(docker container ls -q -f name=$(PACKAGE_CONTAINER_NAME)) /bin/bash

else
build: missing-local
run: missing-local
extract: missing-local
start: missing-local
stop: missing-local
package_init: missing-local
package_extract: missing-local
package_stop: missing-local
outdated: missing-local
update: missing-local
inspect: missing-local
missing-local:
	@echo "docker not found"
endif

if HAVE_NODE
all-local:
	npm install

check-local:
	npm run test
else
all-local: missing-local
check-local: missing-local
missing-local:
	@echo "node not found"
endif