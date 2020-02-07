<?php include 'header.php';


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
  

  $subject = "Request for new reservation";
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
  $marksBody .= "<p>Message: $message</p>";

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
  $guestBody .= "<p>Message: $message</p>";
  $guestBody .= "<p>We will get back to you ASAP</p>";

  mail("markscharter@gmail.com", $subject, $marksBody, $headers);
  mail("$senderEmail", $subject, $guestBody, $headers);
}


?>

<div class="container">

  <h1 class="title">
    <center>Request a Reservation</center>
  </h1>
  <div class="row">
    <div class="col-sm-4">
      <p>here's a container for you Jon, no tables here please, thanks</p>

    </div>
    <div class="col-sm-4">
      <p>maybe a gallery here?</p>

    </div>
    <div class="col-sm-4">
      <p>maybe another gallery here?</p>

    </div>
    <div id="information" class="spacer reserve-info ">
      <div class="container">
        <div class="row">
          <div class="col-sm-6" style="margin-bottom=60px">

            <body onload='hideTotal()'>
              <script src="pack2.js"></script>
              <form method="post" action="<?php echo htmlspecialchars($_SERVER[" PHP_SELF"]);?>" role="fo\
                rm" class="wowload fadeInRight" >
                <h4>
                  <center>Fill out this form, and we'll get back to you within 1 business day.</center>
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
                      <div id="totalPrice" name="total"  class="content"></div>
                    </div>
                    <center>
                      <input type="submit" class='button btn btn-info form-control' style="margin-top: 10px; margin-bottom: 50px" name="submit">
                    </center>
              </form>
          </div>
          <div class="col-sm-6 wowload fadeInLeft">
            <h4>
              <center>
                <iframe src="https://calendar.google.com/calendar/embed?height=600&amp;wkst=1&amp;bgcolor=%23FFFFFF&amp;src=markscharter%40gmail.com&amp;color=%231B887A&amp;src=en.usa%23holiday%40group.v.calendar.google.com&amp;color=%23711616&amp;ctz=America%2FWinnipeg"
                  style="border-width:0" width="100%" height="500" frameborder="0" scrolling="no"></iframe>
              </center>
            </h4>

          </div>
          <div class="row wowload">
        
            <div class="col-sm-12" style="margin-top: 30px;">
              <center>
                <table style="height: 139px; width: 90%; border-collapse: collapse; border-color: #000000;" border="1"
                  ;>
                  <tbody>
                    <tr style="height: 25px;">
                      <td style="width: 33.3333%; height: 25px; text-align: center; "><span style="font-size: 12pt;  font-family: arial, helvetica, sans-serif; font-weight: bold;">Fish</span></td>
                      <td style="width: 33.3333%; height: 25px; text-align: center; "><span style="font-size: 12pt;  font-family: arial, helvetica, sans-serif; font-weight: bold;">Description</span></td>
                      <td style="width: 33.3333%; height: 25px; text-align: center; "><span style="font-size: 12pt;  font-family: arial, helvetica, sans-serif; font-weight: bold;">Season</span></td>
                    </tr>
                    <tr style="height: 25px;">
                      <td style="width: 33.3333%; height: 25px;"><span style="font-weight: bold;">Snapper</span></td>
                      <td style="width: 33.3333%; height: 25px;">Pinkish in color, found offshore bottom fishing</td>
                      <td style="width: 33.3333%; height: 25px;">Typically available, call Mark to confirm</td>
                    </tr>
                    <tr style="height: 25px;">
                      <td style="width: 33.3333%; height: 25px;"><span style="font-weight: bold;">Amberjack</span></td>
                      <td style="width: 33.3333%; height: 25px;">Offshore bottom fish found on wrecks and rocky reefs</td>
                      <td style="width: 33.3333%; height: 25px;">Closes June 1st to July 31st</td>
                    </tr>
                    <tr style="height: 25px;">
                      <td style="width: 33.3333%; height: 25px;"><span style="font-weight: bold;">Grouper</span></td>
                      <td style="width: 33.3333%; height: 25px;">Offshore species, lives on rocky bottom</td>
                      <td style="width: 33.3333%; height: 25px;">Closed February through March</td>
                    </tr>
                    <tr style="height: 25px;">
                      <td style="width: 33.3333%; height: 25px;"><span style="font-weight: bold;">Mackerel</span></td>
                      <td style="width: 33.3333%; height: 25px;">Schooling migratory fish, King and Spanish varieties</td>
                      <td style="width: 33.3333%; height: 25px;">May through September, depeding on variety</td>
                    </tr>
                    <tr style="height: 25px;">
                      <td style="width: 33.3333%; height: 25px;"><span style="font-weight: bold;">Marlin</span></td>
                      <td style="width: 33.3333%; height: 25px;">Large impressive game fish, up to 8 feet long</td>
                      <td style="width: 33.3333%; height: 25px;">June through October</td>
                    </tr>
                    <tr style="height: 25px;">
                      <td style="width: 33.3333%; height: 25px;"><span style="font-weight: bold;">Tuna</span></td>
                      <td style="width: 33.3333%; height: 25px;">Large schooling fish found offshore.</td>
                      <td style="width: 33.3333%; height: 25px;">June through October, great for sushi</td>
                    </tr>
                    <tr style="height: 25px;">
                      <td style="width: 33.3333%; height: 25px;"><span style="font-weight: bold;">Wahoo</span></td>
                      <td style="width: 33.3333%; height: 25px;">Largest of mackerel family, fastest fish in the sea</td>
                      <td style="width: 33.3333%; height: 25px;">June through October</td>
                    </tr>
                  </tbody>
                </table>
              </center>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>

  </body>


</div>
<!-- proposed image carousel -->
<!-- services -->
<div class="spacer services wowload fadeInUp">
  <div class="container">
    <div class="row">
      <div class="col-sm-4">
        <!-- RoomCarousel -->
        <div id="RoomCarousel" class="carousel slide" data-ride="carousel">
          <div class="carousel-inner">
            <div class="item active"><img src="images/boats/jameis1.jpg" class="img-responsive" alt="slide"></div>
            <div class="item  height-full"><img src="images/boats/gillum1.jpg" class="img-responsive" alt="slide"></div>
            <div class="item  height-full"><img src="images/boats/bowden1.jpg" class="img-responsive" alt="slide"></div>
            <div class="item  height-full"><img src="images/boats/cstring1.jpg" class="img-responsive" alt="slide"></div>
            <div class="item  height-full"><img src="images/boats/renegade1.jpg" class="img-responsive" alt="slide"></div>
            <div class="item  height-full"><img src="images/boats/raven1.jpg" class="img-responsive" alt="slide"></div>
          </div>
          <!-- Controls -->
          <a class="left carousel-control" href="#RoomCarousel" role="button" data-slide="prev"><i class="fa fa-angle-left"></i></a>
          <a class="right carousel-control" href="#RoomCarousel" role="button" data-slide="next"><i class="fa fa-angle-right"></i></a>
        </div>
        <!-- RoomCarousel-->
        <div class="caption">Boats<a href="boats.php" class="pull-right"><i class="fa fa-edit"></i></a></div>
      </div>


      <div class="col-sm-4">
        <!-- RoomCarousel -->
        <div id="TourCarousel" class="carousel slide" data-ride="carousel">
          <div class="carousel-inner">
            <div class="item active"><img src="images/packages/halfday1.jpg" class="img-responsive" alt="slide"></div>
            <div class="item  height-full"><img src="images/packages/fullday1.jpg" class="img-responsive" alt="slide"></div>
            <div class="item  height-full"><img src="images/packages/deepsea1.jpg" class="img-responsive" alt="slide"></div>
            <div class="item  height-full"><img src="images/packages/spear1.jpg" class="img-responsive" alt="slide"></div>
            <div class="item  height-full"><img src="images/packages/dinner1.jpg" class="img-responsive" alt="slide"></div>
            <div class="item  height-full"><img src="images/packages/night1.jpg" class="img-responsive" alt="slide"></div>
          </div>
          <!-- Controls -->
          <a class="left carousel-control" href="#TourCarousel" role="button" data-slide="prev"><i class="fa fa-angle-left"></i></a>
          <a class="right carousel-control" href="#TourCarousel" role="button" data-slide="next"><i class="fa fa-angle-right"></i></a>
        </div>
        <!-- RoomCarousel-->
        <div class="caption">Packages<a href="packages.php" class="pull-right"><i class="fa fa-edit"></i></a></div>
      </div>


      <div class="col-sm-4">
        <!-- RoomCarousel -->
        <div id="FoodCarousel" class="carousel slide" data-ride="carousel">
          <div class="carousel-inner">
            <div class="item active"><img src="images/seasons/snapper1.jpg" class="img-responsive" alt="slide"></div>
            <div class="item  height-full"><img src="images/seasons/amberjack1.jpg" class="img-responsive" alt="slide"></div>
            <div class="item  height-full"><img src="images/seasons/wahoo1.jpg" class="img-responsive" alt="slide"></div>
            <div class="item  height-full"><img src="images/seasons/grouper1.jpg" class="img-responsive" alt="slide"></div>
            <div class="item  height-full"><img src="images/seasons/tuna1.jpg" class="img-responsive" alt="slide"></div>
            <div class="item  height-full"><img src="images/seasons/marlin1.jpg" class="img-responsive" alt="slide"></div>
          </div>
          <!-- Controls -->
          <a class="left carousel-control" href="#FoodCarousel" role="button" data-slide="prev"><i class="fa fa-angle-left"></i></a>
          <a class="right carousel-control" href="#FoodCarousel" role="button" data-slide="next"><i class="fa fa-angle-right"></i></a>
        </div>
        <!-- RoomCarousel-->
        <div class="caption">Seasons<a href="reservation.php" class="pull-right"><i class="fa fa-edit"></i></a></div>
      </div>
    </div>
  </div>
</div>


<!--- end of proposed image carousels  -->

<?php include 'footer.php';?>