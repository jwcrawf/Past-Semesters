<?php include 'header.php';
include 'dbconnect.php';


//This if statement is used to extract information from the reservation
//form once the form has been filled out currectly. This extracted 
//information is then saved in variables which are read by the PHP
//script and attached as an email, which is then sent to both the 
//client and mark's charters. Once Mark's charters recieves the email
//the manager will call the client and book the reservation. When the
//form is submitted currectly then a message to confirm the email will
//be displayed on the screen. 
//The email will be send as an HTML page with logo of mark's charter
//and the package, date, number of people selected by the client. 


if(isset($_POST["submit"])) 
{
  $senderEmail=$_POST["email"];
  $senderName=$_POST["name"];
  $senderPhone=$_POST["phone"];
  $packageSelected=$_POST["package"];
  $boatSelected=$_POST["boat"];
  $numPeople=$_POST["people"];
  $depDate=$_POST["departure"];
  $messageSent=$_POST["message"];
  

  $subject = "Request for new reservation for $senderEmail";
  $headers  = 'MIME-Version: 1.0' . "\r\n";
  $headers .= 'Content-type: text/html; charset=UTF-8' . "\r\n";
  $headers .= "From: Mark's Charters <markscharter@gmail.com>" . "\r\n";

  $marksBody = "<img src='http://ww2.cs.fsu.edu/~lovoi/logo.png'>";
  $marksBody .= "<h2>Request for reservation:</h2>";
  $marksBody .= "<p>Name: $senderName</p>";
  $marksBody .= "<p>Email: $senderEmail</p>";
  $marksBody .= "<p>Phone: $senderPhone</p>";
  $marksBody .= "<p>Package: $packageSelected</p>";
  $marksBody .= "<p>Boat: $boatSelected</p>";
  $marksBody .= "<p>Number of guests: $numPeople</p>";
  $marksBody .= "<p>Departure date: $depDate</p>";
  $marksBody .= "<p>Message: $messageSent</p>";

  $guestBody = "<img src='http://ww2.cs.fsu.edu/~lovoi/logo.png'>";
  $guestBody .= "<h2>Request for reservation</h2>";
  $guestBody .= "<p>We have recieved the following reservation:</p>";
  $guestBody .= "<p>Name: $senderName</p>";
  $guestBody .= "<p>Email: $senderEmail</p>";
  $guestBody .= "<p>Phone: $senderPhone</p>";
  $guestBody .= "<p>Package: $packageSelected</p>";
  $guestBody .= "<p>Boat: $boatSelected</p>";
  $guestBody .= "<p>Number of guests: $numPeople</p>";
  $guestBody .= "<p>Departure date: $depDate</p>";
  $guestBody .= "<p>Message: $messageSent</p>";
  $guestBody .= "<p>Your reservation request has been sent. We will get back to you for your payment details.</p>";

  $message ="Your reservation request has been sent! Mark will contact you for your payment details.";

  mail("markscharter@gmail.com", $subject, $marksBody, $headers);
  mail("$senderEmail", $subject, $guestBody, $headers);
}


?>

<!DOCTYPE html>
<html>

<div class="container">


  <br>
  <div id="information" class="reserve-info ">
    <div class="container">
      <div class="row">
        <div class="col-sm-7" style="margin-bottom=60px">

          <body onload='hideTotal()'>
            <script src="pack2.js"></script>
            <form method="post" action="<?php echo htmlspecialchars($_SERVER[" PHP_SELF"]);?>" role="fo\
              rm" class="wowload fadeInRight" >
              <h1 class="title">
               
                <center>Request a Reservation</center>

              </h1>
              <h4>
                <center>Fill out this form, and we'll get back to you within 1 business day.</center>
               
               <br><center><?php echo $message; ?></center> 
 <br><br>
              </h4>
              <div class="form-group">
                
              <input type="text" name="name" class="form-control" placeholder="Name" required>
              </div>
              <div class="form-group">
                <input type="email" name="email" class="form-control" placeholder="Email" required>
              </div>
              <div class="form-group">
                <input type="Phone" name="phone" class="form-control" placeholder="Phone" required>
              </div>
              <div class="form-group">
                <div class="row">
                  <div class="col-xs-6">
                    <select required id="package" name='package' onchange="calculateResTotal()" class="form-control">
                      <option disabled value="" selected hidden>Package</option>
                      <option value="None">Select Package</option>
                      <option value="Half Day">Half Day Soiree (+$450)</option>
                      <option value="Full Day">Full Day ($600)</option>
                      <option value="Deep Sea">Deep Sea ++ ($650)</option>
                      <option value="Dinner">Fish and Dinner ($550)</option>
                      <option value="Night">Night Excursion ($450)</option>
                      <option value="Spearfishing">Fear the Spearfishing ($600)</option>
                    </select>
                  </div>
                  <div class="col-xs-6">
                    <select required name='boat' id="boat" onchange="calculateResTotal()" class="form-control">
                      <option value="0">Select the boat</option>
                      <option value="Jameis">Jameis (max 8 people)</option>
                      <option value="Gillum">Gillum (max 10 people)</option>
                      <option value="Bowden">Bowden (max 14 people)</option>
                      <option value="CString">CString (max 18 people)</option>
                      <option value="Renegade">Renegade (max 24 people)</option>
                      <option value="Raven">Raven (max 120 people)</option>
                    </select>
                  </div>
                </div>
              </div>
              <div class="form-group">
                <div class="row">
                  <div class="col-xs-6">

                    <input type="date" name="departure" id="dep" min="<?php echo date('Y-m-d'); ?>" value="<?php echo date('Y-m-d'); ?>" />
                    <label for="arrival" class="label-date"><i class="fa fa-calendar">
                      </i>&nbsp;&nbsp;Trip Date</label></div>
                  <div class="col-xs-6">
                    <select required name="people" class="form-control">
                      <option disabled value="" selected hidden>No. of adults</option>
                      <option>0-8</option>
                      <option>
                        < 10</option> <option>
                          < 14 </option> <option>
                            < 18</option> <option>
                              < 24</option> <option>
                                < 120</option> </select> </div> </div> </div> <div class="form-group">
                                  <textarea name="message" class="form-control" placeholder="Message" rows="4"></textarea>
                  </div>
                  <div class="row">
                    <div id="totalPrice" name="total" class="content"></div>
                  </div>
                  <center>
                    <input type="submit" class='button btn btn-info form-control' style="margin-top: 10px; margin-bottom: 50px"
                      name="submit">
                  </center>
            </form>
        </div>
        
        <div class="col-sm-5 wowload  fadeInRight">
          <center>
            <h3>
              <br>
              Look up your reservation
            </h3>
            <h4> Please enter your last name <br>and reservation number</h4>
            <br>
          </center>

          <form method="post" action="<?php $_PHP_SELF ?>">
            <center>
              <div class="form-group">
                <label class="inline"> Last Name:<br>
                  <input name="lastName" type="text" placeholder="Last Name" id="lastName" class="form-control"></label>
              </div>
              <label class="inline">Reservation Number:<br>
                <div class="form-group">
                  <input name="resNumber" type="number" placeholder="Reservation Number" min="1" id="resNumber" class="form-control">
              </label>
        </div>

        <button class='button btn btn-info form-control' name="look" type="submit" id="look" value="Lookup Reservation">Look
          Up Reservation</button>

        </center>

        </form>
        
        <div class=" rating wowload fadeInLeft">
    
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


?>

            </body>
          </div>
      </div>
    </div>
  </div>
</div>


</body>


</div>
<!-- proposed image carousel -->
<!-- services -->
<div class="services wowload fadeInUp">
  <div class="container">
    <div class="row">
      <div class="col-sm-7 wowload fadeInLeft" style="margin-top: 30px">
        <h4>
          <center>
            <iframe src="https://calendar.google.com/calendar/embed?height=600&amp;wkst=1&amp;bgcolor=%23FFFFFF&amp;src=markscharter%40gmail.com&amp;color=%231B887A&amp;src=en.usa%23holiday%40group.v.calendar.google.com&amp;color=%23711616&amp;ctz=America%2FWinnipeg"
              style="border-width:0" width="100%" height="530" frameborder="0" scrolling="no"></iframe>
          </center>
        </h4>
      </div>


      <style>
        table.roundedCorners { 
  border: 1px solid DarkBlue;
  border-radius: 10px; 
  border-spacing: 0;
  }
table.roundedCorners td, 
table.roundedCorners th { 
  border-bottom: 1px solid DarkBlue;
  padding: 5px; 
  }
table.roundedCorners tr:last-child > td {
  border-bottom: none;
}
</style>
      <div class="col-sm-5" style="margin-top: 30px;">
        <center>
          <table class="roundedCorners" style=" width: 100%;" ;>
              <tr>
                <th style="text-align: center; "><span style="font-size: 12pt;  font-family: arial, helvetica, sans-serif; font-weight: bold;">Fish</span></th>
                <th style="text-align: center; "><span style="font-size: 12pt;  font-family: arial, helvetica, sans-serif; font-weight: bold;">Season</span></th>
              </tr>
              <tr>
                <td><span style="font-weight: bold;">Snapper<br><br></span>
                  Pinkish in color, found offshore bottom fishing<br></td>
                <td>Typically available, call Mark to confirm</td>
              </tr>
              <tr>
                <td><span style="font-weight: bold;">Amberjack<br><br></span>
                  Offshore bottom fish found on wrecks and rocky reefs<br></td>
                <td>Closes June 1st to July 31st</td>
              </tr>
              <tr>
                <td><span style="font-weight: bold;">Grouper<br><br></span>
                  Offshore species, lives on rocky bottom<br></td>
                <td>Closed February through March</td>
              </tr>
              <tr>
                <td><span style="font-weight: bold;">Mackerel<br><br></span>
                  Schooling migratory fish, King and Spanish varieties<br></td>
                <td>May through September, depeding on variety</td>
              </tr>
              <tr>
                <td><span style="font-weight: bold;">Marlin<br><br></span>
                  Large impressive game fish, up to 8 feet long<br></td>
                <td>June through October</td>
              </tr>
              <tr>
                <td><span style="font-weight: bold;">Tuna<br><br></span>
                  Large schooling fish found offshore<br> </td>
                <td>June through October, great for sushi</td>
              </tr>
              <tr>
                <td><span style="font-weight: bold;">Wahoo<br><br></span>
                  Largest of mackerel family, fastest fish in the sea<br></td>
                <td>June through October</td>
              </tr>
          </table>
          <br><br>
        </center>
      </div>
    </div>
  </div>
</div>



</html>

<?php 
mysql_close($conn);
include 'footer.php';?>