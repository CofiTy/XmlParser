<xsl:stylesheet>
<xsl:template match="/">
  <html>
  	<body bgcolor="Silver">
  		<xsl:apply-templates/>
  	</body>
  </html>
</xsl:template>

<xsl:template match="rapport/titre">
  <h2>
  <font color="Brown">
    <xsl:apply-templates/> 
  </font>
  </h2>
</xsl:template>

<xsl:template match="auteur">
  <h3>
  <font color="Purple">
  Auteur
  </font>
  </h3>
  <xsl:apply-templates/>
</xsl:template>

<xsl:template match="resume">
  <h3>Abstract</h3>
  <p>
  	<xsl:apply-templates/>
  </p>
</xsl:template>

<xsl:template match="chapitre">
  <xsl:apply-templates/>
</xsl:template>

<xsl:template match="chapitre/titre">
  <h3>
  	<xsl:apply-templates/>
  </h3>
</xsl:template>

<xsl:template match="section">
  <xsl:apply-templates/>
</xsl:template>

<xsl:template match="section/titre">
  <h4>
     <xsl:apply-templates/>
  </h4>
</xsl:template>

<xsl:template match="p">
   <p>
      <xsl:apply-templates/>
   </p>
</xsl:template>
</xsl:stylesheet>
