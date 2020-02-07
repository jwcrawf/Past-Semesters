<?php include 'header.php';

?>
<!DOCTYPE html>
<html>

<head>
  <meta charset="utf-8">


  <!-- banner -->
  <div class="banner">
    <img src="images/darkfront.jpg" class="img-responsive" alt="slide">
    <div class="welcome-message">
      <div class="wrap-info">
        <div class="information">
          <h1 class="animated fadeInDown">Mark's Charter Service</h1>
          <p class="animated fadeInUp">The most experienced captains in the Gulf.</p>
        </div>
      </div>
    </div>
  </div>
  <!-- banner-->


  <!-- reservation-information -->
  <div id="information" class="spacer reserve-info ">
    <div class="container">
      <div class="row">
        <div class="col-sm-12">
          <div class="embed-responsive embed-responsive-16by9 wowload fadeInLeft"><center><iframe class="embed-responsive-item"
              src="https://www.youtube.com/embed/saTMZ6A_AH8" width="100%" height="400" frameborder="0"
              webkitallowfullscreen mozallowfullscreen allowfullscreen></iframe></center></div>
        </div>
      </div>
    </div>
  </div>



  <!-- reviews-information -->
  <div class=" rating wowload fadeInUp">

    <?php include '../rating/rating.php';?>
  </div>

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
  <!-- services -->

  <?php include 'footer.php';?>