XML_DIR=AnalyseurXML
EXEC=$(XML_DIR)/analyseXML

all: $(EXEC)
	 
$(EXEC):
		@(cd $(XML_DIR) && $(MAKE))

clean:
		@(cd $(XML_DIR) && $(MAKE) $@)
