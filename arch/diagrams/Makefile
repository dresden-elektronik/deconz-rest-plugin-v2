
# Helper for editing PlantUML diagrams and generate images of them
#
# Dependencies:
#   - watchexec
#   - plantuml
#
# Editing Diagrams:
#
#   Use the `make watch` target. When a .puml file is
#   changed and saved, the PNG is generated automatically.
#
#   In a editor/IDE open a 2 column layout, one side for .puml
#   the other side showing the generated image.

PLANTUML= plantuml

PUML_FILES = $(patsubst %.puml,%.png,$(wildcard *.puml))

all: $(PUML_FILES)

%.png : %.puml
	$(PLANTUML) $<

watch:
	watchexec make

clean:
	rm -f $(PUML_FILES)
