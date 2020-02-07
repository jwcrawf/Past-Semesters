<?php 
include 'header.php';
include 'dbconnect.php';
session_start();
if(!isset($_SESSION['login'])) {
  header('LOCATION:login.php'); die();
}
?>

<!DOCTYPE html>
<html>

<head>
   <style>
      table,
        th,
        td {
            border: 1px solid black;
        }
    </style>
</head>

<body onload="document.create.reset()" onload="document.lookupDate.reset()" onload="document.lookupRes.reset()" >

   <script src="pack2.js"></script>
   
      
   <div class="container">

      <h1 class="title">
         <center>Mark's Admin Console</center>
      </h1>
      <div class="row">
         <div class="col-sm-4">

            <br>

            <h3>
               <center>Look up a Reservation</center>
            </h3>

            <form method="post" name="lookupRes" action="<?php $_PHP_SELF ?>">
               <center>
                  <table width="350" border="0" cellspacing="1" cellpadding="2">
                     <tr>
                        <td width="100">Last Name</td>
                        <td><input name="lastName" type="text" id="lastName"></td>

                     </tr>
                     <tr>
                        <td width="100">Reservation Number</td>
                        <td><input name="resNumber" type="number" min="1" id="resNumber"></td>

                     </tr>
                     <tr>
                        <td width="100"> </td>
                        <td>
                           <input name="look" type="submit" id="look" value="Lookup Reservation">
                        </td>
                     </tr>
                  </table>
               </center>

            </form>
            <?php

if(isset($_POST['look']))
{         
  $lastName = $_POST['lastName'];
  $resNumber = $_POST['resNumber'];
  $sql1 = "SELECT resNumber, lastName, boat, package, resDate, totalPrice FROM reservations WHERE lastName = '$lastName' AND resNumber = $resNumber";
  $result1 = mysql_query($sql1, $conn);
  $num_rows1 = mysql_num_rows($result1);
  
  if (!$result1)
   echo "<center>0 results</center>";
  
  if ($num_rows1 > 0) 
  {
    $row = mysql_fetch_assoc($result1);
      echo "<center>";
      echo "<br>Reservation Number is: "; echo $row["resNumber"];
      echo "<br>Last Name is: "; echo $row["lastName"];
      echo "<br>Boat reserved is: "; echo $row["boat"];
      echo "<br>Package is: "; echo $row["package"];  
      echo "<br>Reservation Date is: "; echo $row["resDate"];
      echo "<br>Estimated Total is: $"; echo $row["totalPrice"];
      echo "</center>";    
  }
} 

?>
         </div>
         <div class="col-sm-4">
            <br>
            <h3>
               <center>Schedule by Date</center>
            </h3>

            <form method="post" name="lookupDate"  action="<?php $_PHP_SELF ?>">

               <center>
                  <table width="350" border="0" cellspacing="1" cellpadding="2">
                     <tr>
                        <td width="100">Date</td>
                        <td><input name="resDate" type="date" id="resDate"></td>

                     </tr>
                     <tr>
                        <td width="100"> </td>
                        <td>
                           <input name="que" type="submit" id="que" value="Lookup Schedule">
                        </td>
                     </tr>
                  </table>
               </center>

            </form>
            <?php

if(isset($_POST['que']))
{         
  $resDate = $_POST['resDate'];
  $sql = "SELECT resNumber, boat, package, lastName, resDate, totalPrice FROM reservations WHERE resDate = CAST('". $resDate ."' AS DATE)";
  $result = mysql_query($sql, $conn);
  $num_rows = mysql_num_rows($result);
  if (!$result)
   echo "<br><center>0 results</center>";
  
  if ($num_rows > 0) 
  {
    
    echo "<br><center><table><tr><th>Reservation</th><th>Boat</th><th>Package</th><th>Last Name</th><th>Date</th><th>Price</th></tr>";
      // output data of each row
    while($row = mysql_fetch_assoc($result)) 
    {
      echo "<tr><td>".$row["resNumber"]."</td><td>".$row["boat"]."</td><td>".$row["package"]."</td><td>".$row["lastName"]."</td><td>".$row["resDate"]."</td><td>".$row["totalPrice"]."</td></tr>";
    }
    echo "</table></center>";
    
  } 
   
}
?>
         </div>
         <div class="col-sm-4">
            <br>
            <h3>
               <center>Create a New Reservation</center>
            </h3>

            <form method="post" name="create" input autocomplete="off" action="<?php $_PHP_SELF ?>">
               <center>
                  <table width="350" border="0" cellspacing="1" cellpadding="2">

                     <tr>
                        <td width="100">Boat</td>
                        <td width="80">
                           <select name=boat id="boat" onchange="adminTotal()">
                              <option value="0">Select the boat</option>
                              <option value="Jameis">Jameis</option>
                              <option value="Gillum">Gillum</option>
                              <option value="Bowden">Bowden</option>
                              <option value="CString">CString</option>
                              <option value="Renegade">Renegade</option>
                              <option value="Raven">Raven</option>
                           </select>
                        </td>
                     </tr>

                     <tr>
                        <td width="100">Package</td>
                        <td width="80">
                           <select name='package' id="package" onchange="adminTotal()">
                              <option value="None">Select package</option>
                              <option value="Half Day">Half Day</option>
                              <option value="Full Day">Full Day</option>
                              <option value="Deep Sea">Deep Sea</option>
                              <option value="Dinner">Dinner</option>
                              <option value="Night">Night</option>
                              <option value="Spearfishing">Spearfishing</option>
                           </select>
                        </td>
                     </tr>

                     <tr>
                        <td width="100">First Name</td>
                        <td><input name="firstName" type="text" id="firstName"></td>
                     </tr>

                     <tr>
                        <td width="100">Last Name</td>
                        <td><input name="lastName" type="text" id="lastName"></td>
                     </tr>

                     <tr>
                        <td width="100">Email</td>
                        <td><input name="email" type="email" id="email"></td>
                     </tr>
                     <tr>
                        <td width="100">Phone</td>
                        <td><input name="phone" type="tel" id="phone"></td>
                     </tr>

                     <tr>
                        <td width="100">Passengers</td>
                        <td><input name="pax" type="number" id="pax" min="1" max="120"></td>
                     </tr>

                     <tr>
                        <td width="100">Date</td>
                        <td><input name="resDate" type="date" id="resDate" min=<?php echo date('Y-m-d');?>></td>

                     </tr>

                     <tr>
                        <td width="100">Est. Total: </td>
                        <td><input name="totalPrice" type="text" id="totalPrice" readonly="true" value="<?php echo $total; ?>" /></td>
                     </tr>

                     <tr>
                        <td width="100"> </td>
                        <td> </td>
                     </tr>

                     <tr>
                        <td width="100"> </td>
                        <td>
                           <input name="add" type="submit" id="add" value="Add Reservation">
                        </td>
                     </tr>

                  </table>
               </center>

            </form>

            <?php 
   
   if(isset($_POST['add']))
   {            
    if(! get_magic_quotes_gpc() )
    {
      $firstName = addslashes ($_POST['firstName']);
      $lastName = addslashes ($_POST['lastName']);
      $email = addslashes ($_POST['email']);
      $phone = addslashes ($_POST['phone']);
    }
    else
    {
      $firstName = $_POST['firstName'];
      $lastName = $_POST['lastName'];
      $email = $_POST['email'];
      $phone = $_POST['phone'];
    }
    
    $boat = $_POST['boat'];
    $package = $_POST['package'];         
    $resDate = $_POST['resDate'];
    $pax = $_POST['pax'];
    
    $total = $_POST['totalPrice'];
    
    $sqlRes = "INSERT INTO reservations ". "(boat, package, firstName, lastName, email, phone, resDate, pax, totalPrice) ". 
      "VALUES('$boat', '$package', '$firstName', '$lastName', '$email', '$phone', CAST('". $resDate ."' AS DATE), $pax, $total)";
              
    $retRes = mysql_query( $sqlRes, $conn );       
        
    if(!$retRes)     
      echo "<br><center>Could not enter data Please check format</center>";     
        
    $res = mysql_result(mysql_query("SELECT resNumber FROM reservations ORDER BY resNumber DESC LIMIT 1"),0);
    
    if ($retRes)
      echo "<br><center>Entered data successfully<br>Created reservation number is $res</center>";
    


   $subjectCust="Reservation confirmation from Mark's Charter";
   $subjectMark="Reservation confirmation for $email";

   $headers  = 'MIME-Version: 1.0' . "\r\n";
   $headers .= 'Content-type: text/html; charset=UTF-8' . "\r\n";
   $headers .= "From: Mark's Charters <markscharter@gmail.com>" . "\r\n";

   $bodyCust = "<img src='http://ww2.cs.fsu.edu/~crawford/marks/images/logo.png'>";
   $bodyCust .= "<h2>Reservation confirmation</h2>";
   $bodyCust .= "<p>Thank you for your reservation, please contact us if anything is incorrect</p>";
   $bodyCust .= "<p>Name: $firstName $lastName</p>";					   
   $bodyCust .= "<p>Reservation Number: $res</p>";
   $bodyCust .= "<p>Email: $email</p>";
   $bodyCust .= "<p>Phone: $phone</p>";
   $bodyCust .= "<p>Boat: $boat</p>";
   $bodyCust .= "<p>Package: $package</p>";
   $bodyCust .= "<p>People: $pax</p>";
   $bodyCust .= "<p>Reserved Date: $resDate</p>";
   $bodyCust .= "<p>Estimated Total: $$total</p>";


    $thankYou="Thank you for your reservation, please contact us if anything is incorrect.";
    mail("markscharter@gmail.com", $subjectMark, $bodyCust, $headers);
    mail("$email", $subjectCust, $bodyCust, $headers);
   }  
   ?>
         </div>

      </div>

      <br>

      <form align="center" name="form1" method="post" action="logout.php">
         <center>
            <label class="logoutLblPos">

               <button type='submit' name="submit2" class='button btn btn-info form-control'>Logout of Console</button><BR><BR>
            </label>
         </center>
      </form>
      <br/>
   </div>
</body>
</html>

<?php 
mysql_close($conn);
include 'footer.php'
;?>