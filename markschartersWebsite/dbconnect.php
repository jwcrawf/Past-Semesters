<?php

$dbhost = 'dbsrv2.cs.fsu.edu';
$dbuser = 'crawford';
$dbpass = 'Tedy143!';
$conn = mysql_connect($dbhost, $dbuser, $dbpass);
            
if(! $conn ) 
{
  die('Could not connect: ' . mysql_error());
}
          
mysql_select_db('crawforddb');

?>