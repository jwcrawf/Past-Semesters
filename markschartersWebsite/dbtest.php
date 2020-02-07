<?php 
include 'header.php';
include 'dbconnect.php';
?>
<!DOCTYPE html>

<html>

<head>
  <title>Query Test</title>
</head>

<body>
  <pre>
<?php  
   
   echo "All Boats\n";
   $boats = mysql_query ("SELECT * FROM boats", $conn);
   while ($row = mysql_fetch_row($boats))
   {
     for ($i = 0; $i < mysql_num_fields($boats); ++$i)
        echo $row[$i] . " ";      
      echo "\n";
   }   

   echo "\nReservations\n";
   $reservations = mysql_query ("SELECT * FROM reservations", $conn);
   while ($row = mysql_fetch_row($reservations))
   {
     for ($i = 0; $i < mysql_num_fields($reservations); ++$i)
        echo $row[$i] . " ";      
      echo "\n";
   }  
    
   mysql_close($conn);
?>
</pre>
</body>

</html>
<?php include 'footer.php';?>