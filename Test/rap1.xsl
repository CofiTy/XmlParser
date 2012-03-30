<xsl:stylesheet>
<xsl:template match="/">
  <html>
  	<body bgcolor="#F2F39E" text="#71C42B">
  		<xsl:apply-templates/>
  	</body>
  </html>
</xsl:template>

<xsl:template match="rapport/titre">
  <h2>
  <font color="#01243B">
    <xsl:apply-templates/> 
  </font>
  </h2>
</xsl:template>

<xsl:template match="/auteur">
  <h3>
    <font color="#5288DB">
    Auteur
  </font>
  </h3>
  <xsl:apply-templates/>
</xsl:template>

<xsl:template match="resume">
  <h3><font color="#5288DB">Abstract</font></h3>
  <p>
  	<xsl:apply-templates/>
  </p>
</xsl:template>

<xsl:template match="chapitre">
  <xsl:apply-templates/>
</xsl:template>

<xsl:template match="chapitre/titre">
  <h3>
  <font color="#5288DB">
  	<xsl:apply-templates/>
  </font>
  </h3>
</xsl:template>

<xsl:template match="section">
  <xsl:apply-templates/>
</xsl:template>

<xsl:template match="section/titre">
  <h4>
  <font color="#9DA7B2">
     <xsl:apply-templates/>
  </font>
  </h4>
</xsl:template>

<xsl:template match="p">
   <p>
      <xsl:apply-templates/>
   </p>
</xsl:template>
</xsl:stylesheet>
