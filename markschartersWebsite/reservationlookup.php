<?php 
include 'header.php';
include 'dbconnect.php';
?>

<!DOCTYPE html>
<html>



<div class="row">
  <div class="col-sm-12 wowload spacer">
    <center>
      <h3>
        Look up your reservation
      </h3>
      <h4> Please enter your last name and reservation number</h4>
      <br>
    </center>

    <form method="post" action="<?php $_PHP_SELF ?>">
      <center>
        <div class="form-group">
          <label class="inline"> Last Name:
            <input name="lastName" type="text" placeholder="Last Name" id="lastName" class="form-control"></label>
        </div>

        <div class="form-group">
          <label class="inline">Reservation Number:
            <input name="resNumber" type="number" placeholder="Reservation Number" min="1" id="resNumber" class="form-control"></label>
        </div>

        <button class='button btn btn-info form-control' name="look" type="submit" id="look" value="Lookup Reservation">Look
          Up Reservation</button>

      </center>

    </form>
  </div>
</div>

<div class="row rating">
  <div class="col-sm-12 wowload ">

    <body>

      <?php
if(isset($_POST['look']))
{         
  $lastName = $_POST['lastName'];
  $resNumber = $_POST['resNumber'];
  $sql1 = "SELECT resNumber, boat, package, resDate, totalPrice, firstName, lastName FROM reservations WHERE lastName = '$lastName' AND resNumber = $resNumber";
  $result1 = mysql_query($sql1, $conn);
  $num_rows1 = mysql_num_rows($result1);
  
  if ($num_rows1 > 0) 
  {
    $row = mysql_fetch_assoc($result1);
      echo "<center><br><h3>Greetings "; echo $row["firstName"]; echo " "; echo $row["lastName"];
      echo "!<br></h3>Your Reservation Number is: "; echo $row["resNumber"];
      echo "<br>Your reserved boat is: "; echo $row["boat"];
      echo "<br>Your selected package is: "; echo $row["package"];  
      echo "<br>Your reservation date is: "; echo $row["resDate"];
      echo "<br>Your estimated total is: $"; echo $row["totalPrice"];
      echo "<br><br>Please make your payment when you arrive at Mark's!";
      echo "<br><br>Thank You, we look forward to serving you!<br><br>"; 
      echo "<button type='button' onClick='window.print()' class='button btn btn-info'>Print This Page</button><br><br></center>";
  }
  else {
    echo "<center>Reservation not found <br> Please verify your reservation number, and try again<br><br></center>";
  }
}


  

mysql_close($conn);
?>

    </body>
  </div>
</div>

</html>
<?php include 'footer.php';?>