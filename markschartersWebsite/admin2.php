<?php 
include 'header.php';
include 'dbconnect.php';
;?>

<div class="container">
   <div class="row">
      <h4><br>Admin Page:<h4>
   </div>
   <div class="row">
      <?php
session_start();
if(!isset($_SESSION['login'])) {
  header('LOCATION:login.php'); die();
}
?>
      <html>

      <head>
         <title>Admin Page</title>
      </head>

      <body>
         <script src="pack2.js"></script>

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
              "VALUES($boat, $package, '$firstName', '$lastName', '$email', '$phone', CAST('". $resDate ."' AS DATE), $pax, $total)";
               
            
            $retRes = mysql_query( $sqlRes, $conn );
            
            if(! $retRes ) 
            {
              die('Could not enter data: ' . mysql_error());
            }
            
            echo "Entered data successfully\n";
            
            $mailBody="\nName:$firstName $lastName \nEmail:$email \nPhone:$phone \nBoat:$boat \nPackage:$package \nPeople:$pax \nReserved Date:$resDate \nTotal Price: $$total \nThank you for your reservation please contact us if anything is incorrect.";
            mail("markscharter@gmail.com", "Confirmed Reservation", $mailBody, "For: $email");
            mail("$email", "Email Confirmation From Mark's Charters", $mailBody, "From: markscharter@gmail.com");

            
         }
         else 
         {           
            ?>
         <br />
         <h3><center>This is your reservation console Mark</center></h3>
         <br>
         <br />

         <form method="post" action="<?php $_PHP_SELF ?>">
         <center>
            <table width="400" border="0" cellspacing="1" cellpadding="2">

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
                        <option value="Half Day">Half-day</option>
                        <option value="Full Day">Full-day</option>
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
                  <td width="100">Reservation Cost: </td>
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
         }
      ?>
         <br />


      </html>
      <form align="right" name="form1" method="post" action="logout.php">
         <label class="logoutLblPos">
            <button type='submit' name="submit2" class='button btn btn-info form-control'>Logout</button><BR><BR>
         </label>
      </form>


   </div>
</div>
</div>
</form>
</body>

</html>

<?php 
mysql_close($conn);
include 'footer.php';

?>