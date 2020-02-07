<?php include 'header.php';

if($_POST["submit"]) {
  $sender=$_POST["sender"];
  $senderEmail=$_POST["senderEmail"];
  $message=$_POST["message"];
  $phone=$_POST["phone"];
  $replyBody1 = "We have recieved your email:";
  $replyBody2 = "We will contact you as soon as possible";
  $mailBody="Name: $sender \nEmail: $senderEmail \nPhone:$phone \nMessage:$message ";
  mail("princessbpn@gmail.com", "Form to email message", $mailBody, "From: $senderEmail");
  mail("$senderEmail", "Email confirmation", "$replyBody1 \n $message \n $replyBody2", "From: princessbpn@gmail.com");
  $thankYou="<p>Thank you! Your message has been sent.</p>";
}

?>
<!DOCTYPE html>


<div class="container">
  <h1 class="title">Contact</h1>
  <!-- form -->
  <div class="contact">
    <div class="row">
      <div class="col-sm-12">

        <div class="map">
          <iframe src="https://www.google.com/maps/embed?pb=!1m18!1m12!1m3!1d3450.002297749885!2d-85.66804618496319!3d30.151350320469486!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x8893813ded5d1701%3A0x8b344996fa8ef365!2sPanama+City+Marina!5e0!3m2!1sen!2sus!4v1542399675519"
            width="100%" height="600" frameborder="0"></iframe>
        </div>



        <html>

        <head>
          <meta charset="utf-8">
        </head>

        <body>
          <?=$thankYou ?>




          <form method="post" action="<?php echo htmlspecialchars($_SERVER[" PHP_SELF"]);?>">
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
            <input type="submit" name="submit">
            <br><br>
          </form>
        </body>

        <?php include 'footer.php';?>