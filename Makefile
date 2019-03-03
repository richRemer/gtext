app = gtext
src = src
inc = inc
bin = bin
build = build
deps = gtk+-3.0

objects = $(build)/$(app)_css.o $(patsubst $(src)/%.c, $(build)/%.o, $(shell find $(src) -type f -name "*".c))

cc = gcc
ld = gcc

cflags = $(shell pkg-config --cflags $(deps)) -I$(inc)
ldflags = $(shell pkg-config --libs $(deps))

default: build

debug: build
	GTK_DEBUG=interactive $(bin)/$(app)

build: $(bin)/$(app)

install: $(bin)/$(app)
	cp $< /usr/local/bin/$(app)
	cp share/$(app).desktop /usr/share/applications/

clean:
	rm -fr $(build)/* $(bin)/*

$(bin)/$(app): $(objects)
	$(ld) $^ -o $@ $(ldflags)

$(build)/%_css.o: $(build)/%_css.c
	$(cc) -c $< -o $@

$(build)/%_css.c: $(build)/%.css
	cd $(build); xxd -i $(notdir $<) > $(notdir $@)

$(build)/%.css: $(src)/%.css
	cp $< $@
	truncate -s +1 $@

$(build)/%.o: $(src)/%.c
	$(cc) $(cflags) -c $< -o $@

.PHONY: default build install clean debug
