<xsl:stylesheet>
<xsl:template match="/">
  <html>
  	<body bgcolor="#EBC137" text="#DB4C2C">
  		<xsl:apply-templates/>
  	</body>
  </html>
</xsl:template>

<xsl:template match="client">
   <xsl:apply-templates/>
</xsl:template>

<xsl:template match="prenom">
   <font size="22" color="#771E10"><xsl:apply-templates/></font>
</xsl:template>

<xsl:template match="nom">
   <font size="22" color="#771E10"><xsl:apply-templates/></font>
</xsl:template>

<xsl:template match="telephone">
   <p>
   <b><font color="#771E10">Tel:</font></b>
   <xsl:apply-templates/>
   </p>
</xsl:template>

<xsl:template match="produit">
    <h2><font color="#771E10">Liste des Produits</font></h2>
    <xsl:apply-templates/>
</xsl:template>

<xsl:template match="id">
    <h3><font color="#771E10">ID Produit</font></h3>
    <xsl:apply-templates/>
</xsl:template>

<xsl:template match="description">
    <h3><font color="#771E10">Description Produit</font></h3>
    <p><xsl:apply-templates/></p>
</xsl:template>

</xsl:stylesheet>
