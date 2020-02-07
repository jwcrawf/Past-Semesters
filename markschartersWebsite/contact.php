<?php include 'header.php';

//if statement checks for correct and input in the form to 
//send the emails to the clients for a contact request.
//The statements extracts the data from the HTML form and saves
//them in variables which are read by the php script. PHP script
//then uses the $headers to send the confirmation email using a HTML
//page. It also uses the variables with the contact information to both
//the client and the email for mark's charters: markscharter@gmail.com     
//once the form is currectly submitted the confirmation message for sending
//the email will be displayed on the page.
if(isset($_POST["submit"])) {
  $sender=$_POST["sender"];
  $senderEmail=$_POST["senderEmail"];
  $message=$_POST["message"];
  $phone=$_POST["phone"];
  $subject="Contact request for Mark's Charters"; 
  $subject2="Contact request from $senderEmail";

  $headers  = 'MIME-Version: 1.0' . "\r\n";
  $headers .= 'Content-type: text/html; charset=UTF-8' . "\r\n";
  $headers .= "From: Customer <$senderEmail>" . "\r\n";

//  $headers .= "From: Mark's Charters <markscharter@gmail.com>" . "\r\n";
  
  $bodyCust = "<img src='http://ww2.cs.fsu.edu/~crawford/marks/images/logo.png'>";
  $bodyCust .= "<h2>Your message has been recieved</h2>";
  $bodyCust .= "<p>Message: $message </p>";
  $bodyCust .= "<p>We will get back to you ASAP</p>";
  $bodyCust .= '<a href="http://ww2.cs.fsu.edu/~crawford/marks/index.php">Marks Charters</a></p>';
  
  $bodyMarks = "<img src='http://ww2.cs.fsu.edu/~crawford/marks/images/logo.png'>";
  $bodyMarks .= "<h2>Contact request from guest: </h2>";
  $bodyMarks .= "<p>Name: $sender </p>";
  $bodyMarks .= "<p>Email: $senderEmail </p>";
  $bodyMarks .= "<p>Phone: $phone </p>";
  $bodyMarks .= "<p>Message: $message </p>";

  $message ="Your message has been sent!";
   
  mail("markscharter@gmail.com", $subject2, $bodyMarks, $headers);
  mail("$senderEmail", $subject, $bodyCust, $headers );
  
  //header("Location: http://www.google.com"); /* Redirect browser */
  //exit();
}

?>
<!DOCTYPE html>


<div class="container">
  <h1 class="title">
    <center>Contact Us</center>
  </h1>
  <!-- form -->
  <div class="contact">
    <div class="row">
      <div class="col-sm-12">
        <div class="col-sm-6">
          <div class="map">
            <iframe src="https://www.google.com/maps/embed?pb=!1m18!1m12!1m3!1d3976.6216911200963!2d-85.72564009746915!3d30.189080182050954!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x8893842cfea6b60b%3A0xffcc0ac9729595a7!2sFlorida+State+University+Panama+City!5e0!3m2!1sen!2sus!4v1543071426977"
              width="100%" height="500" frameborder="2"></iframe>
          </div>
        </div>

        <html>

        <head>
          <meta charset="utf-8">
        </head>

        <body>
          <?=$thankYou ?>

          <div class="row">
            <div class="col-sm-3"></div>
            <div class="col-sm-6">

              <form method="post" action="">
  <?php echo $message; ?>
                 <fieldset>
                  <br><br>

                  <h3>Drop us a Line!</h3>
                  <input type="text" class="form-control" name="sender" placeholder="Name" required>
                  <br><br>
                  <input type="email" class="form-control" name="senderEmail" placeholder="Enter email" required>
                  <br><br>
                  <input type="tel" class="form-control" name="phone" placeholder="Phone" required>
                  <br><br>
                  <textarea rows="5" cols="20" class="form-control" name="message" placeholder="Message" required></textarea>
                  <br><br>
                </fieldset>
                <center>
                <input type="submit" class='button btn btn-info form-control' name="submit">
                </center>
            </div>
          </div>
          <br><br>

          </form>
        </body>
      </div>
    </div>
  </div>
</div>
<?php include 'footer.php';?>