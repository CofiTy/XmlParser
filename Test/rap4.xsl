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
   <font size="22"><xsl:apply-templates/></font>
</xsl:template>

<xsl:template match="nom">
   <font size="22"><xsl:apply-templates/></font>
</xsl:template>

<xsl:template match="telephone">
   <p><i><xsl:apply-templates/></i></p>
</xsl:template>

<xsl:template match="produit">
    <h2>Liste des Produits</h2>
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
