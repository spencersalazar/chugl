
CHUGL_SRC_ROOT=../

PKG_VERSION=$(shell date '+%Y%m%d')-$(shell git rev-parse --short --verify HEAD)

CHUGIN_NAMES=chugl MAUI
CHUGINS=$(addsuffix .chug,$(CHUGIN_NAMES))
CHUGINS_ORIGINAL=$(foreach CHUG,$(CHUGIN_NAMES),$(CHUGL_SRC_ROOT)/$(CHUG).chug)

CHUGIN_PKGS=$(addsuffix .pkg,$(CHUGINS))
PKGS=$(APP_PKGS) $(BIN_PKGS) $(CHUGIN_PKGS)

INSTALLER=chugl-$(PKG_VERSION).pkg

CHUG_DIR=/usr/lib/chuck

IDENTIFIER_BASE=edu.stanford.chuck
CERT=Developer ID Installer: Spencer Salazar (9GU9FHJ3JC)

.PHONY: all
all: $(INSTALLER)

upload: $(INSTALLER)
	scp $(INSTALLER) ccrma-gate.stanford.edu:Library/Web/chuck
	@echo "\033[32;1muploaded to URL: \033[0m"
	@echo "\033[32;1mhttps://ccrma.stanford.edu/~spencer/chuck/$(INSTALLER)\033[0m"

$(INSTALLER): $(PKGS) $(CHUGINS) Distribution.xml
	@echo "Creating installer"
	@echo "\033[32;1m    chugl path:" $(realpath $(CHUGL_SRC_ROOT)) "\033[0m"
	productbuild --distribution Distribution.xml --version $(PKG_VERSION) --package-path . --sign "$(CERT)" --resources resources $@

$(CHUGIN_PKGS): %.pkg: %
	rm -rf $<.tmp/$(CHUG_DIR)
	mkdir -p $<.tmp/$(CHUG_DIR)
	cp -af $< $<.tmp/$(CHUG_DIR)
	pkgbuild --root $<.tmp --identifier $(IDENTIFIER_BASE).$(basename $<) $@
	rm -rf $<.tmp

$(CHUGINS): $(CHUGINS_ORIGINAL)
	cp -af $(CHUGL_SRC_ROOT)/$@  .
	touch $@
$(CHUGINS_ORIGINAL): 
	make -C $(dir $@) osx

clean: 
	rm -rf $(CHUGINS) *.pkg *.tmp
clean-all: clean
	rm -rf $(CHUGINS) *.pkg
	make -C $(CHUGL_SRC_ROOT) clean

