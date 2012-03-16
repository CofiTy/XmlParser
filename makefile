XML_DIR=AnalyseurXML
EXEC_XML=$(XML_DIR)/analyseXML
DTD_DIR=AnalyseurDTD
EXEC_DTD=$(DTD_DIR)/analyseDTD

all: $(EXEC_XML) $(EXEC_DTD)
	 
$(EXEC_XML):
		@(cd $(XML_DIR) && $(MAKE))

$(EXEC_DTD):
		@(cd $(DTD_DIR) && $(MAKE))

clean:
		@(cd $(XML_DIR) && $(MAKE) $@)
		@(cd $(DTD_DIR) && $(MAKE) $@)
