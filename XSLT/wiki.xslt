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
