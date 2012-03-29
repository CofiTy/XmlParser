<xsl:stylesheet>
<xsl:template match="/">
  <html>
  	<body bgcolor="Silver">
  		<xsl:apply-templates/>
  	</body>
  </html>
</xsl:template>

<xsl:template match="client">
   <xsl:apply-templates/>
</xsl:template>

<xsl:template match="prenom">
   <h2><xsl:apply-templates/></h2>
</xsl:template>

<xsl:template match="nom">
   <xsl:apply-templates/>
</xsl:template>

<xsl:template match="produit">
  <xsl:apply-templates/>
</xsl:template>

<xsl:template match="id">
    <h3>ID Produit</h3>
    <xsl:apply-templates/>
</xsl:template>

<xsl:template match="description">
    <h3>Description Produit</h3>
    <p><xsl:apply-templates/></p>
</xsl:template>

</xsl:stylesheet>
