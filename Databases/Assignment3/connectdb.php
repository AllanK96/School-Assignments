<?php
$dbhost = "dbserver";
$dbuser = "akhan655";
$dbpass = "2NX6CDRA3x";
$dbname = "akhan655assign2db";
$connection = pg_connect("host=$dbhost dbname=$dbname user=$dbuser 

password=$dbpass");

if(!$connection){
	echo "Database Connection Failed";
 }
?>
