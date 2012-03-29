<!--<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">-->
<xsl:stylesheet>
<xsl:template match="/">
  <html>
  <body>
  <h2>My CD Collection</h2>
  <xsl:apply-templates/>
  </body>
  </html>
</xsl:template>

<xsl:template match="catalog/cd">
  <p>
    <xsl:apply-templates/> 
  </p>
</xsl:template>

<xsl:template match="cd/title">
  Title: <span style="color:#ff0000">
  <xsl:apply-templates/></span>
  <br />
</xsl:template>

<xsl:template match="cd/artist">
  Artist: <span style="color:#00ff00">
  <xsl:apply-templates/></span>
  <br />
</xsl:template>

</xsl:stylesheet>
