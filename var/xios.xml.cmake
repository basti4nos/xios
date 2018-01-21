<?xml version="1.0" encoding="UTF-8"?>
<xios version="@XIOS_VERSION@">
  <!-- General configuration section -->
  <general>
    <instance>
      <path>.</path>
      <!--
      <user>xios</user>
      <group>xios</group>
        -->
    </instance>
  </general>
  <!-- Servers configuration section -->
  <servers>
    <enable>s1</enable>
    <s1>
      <type>http</type>
      <port>8190</port>
      <path>${general.instance.path}/ROOT</path>
    </s1>
  </servers>
  <!-- Workers configuration section -->
  <workers/>
  <!-- Logging configuration section -->
  <logging>
    <loggers>
      <root>
        <channel>c1</channel>
        <level>trace</level>
      </root>
    </loggers>
    <channels>
      <c1>
        <class>ConsoleChannel</class>
        <formatter>f1</formatter>
      </c1>
      <c2>
        <class>FileChannel</class>
        <formatter>f1</formatter>
        <path>${general.instance.path}/logs/message.log</path>
        <rotation>daily</rotation>
        <archive>timestamp</archive>
        <times>local</times>
        <compress>true</compress>
        <purgeCount>7</purgeCount>
      </c2>
    </channels>
    <formatters>
      <f1>
        <class>PatternFormatter</class>
        <pattern>%Y-%m-%d %H:%M:%S.%i: %p: %t</pattern>
        <times>local</times>
      </f1>
    </formatters>
  </logging>
</xios>
