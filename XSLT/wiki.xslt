<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet>
  <xsl:template match="/persons">
    <root>
      <xsl:apply-templates />
    </root>
  </xsl:template>
 
  <xsl:template match="person">
    <name username="{@username}">
    </name>
  </xsl:template>
</xsl:stylesheet>
