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


<body onload="document.create.reset()" onload="document.lookupDate.reset()" onload="document.lookupRes.reset()">

  <script src="pack2.js"></script>


  <div class="container">

    <h1 class="title">
      <center>Mark's Admin Console</center>
    </h1>
    <!-- Top Modal Buttons -->
    <!-- Lookup Reservation -->

    <div class="row">

      <div class="col-sm-3">
        <div class="center">
          <center>
            <button class="btn btn-info" data-toggle="modal" data-target="#lookup_reservation_modal"> <i class="fa fa-search"></i>
              Lookup Reservation</button></center>
        </div>
        <br>

        <div class="modal fade" id="lookup_reservation_modal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
          <div class="modal-dialog" role="document">
            <div class="modal-content">
              <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">×</span></button>
                <h4 class="modal-title" id="myModalLabel">Lookup Reservation</h4>
              </div>
              <div class="modal-body">

                <form method="post" name="lookupRes" action="<?php $_PHP_SELF ?>">
                  <div class="form-group">
                    <label>Last Name</label>
                    <input name="lastName" type="text" id="lastName" placeholder="Last Name" class="form-control">
                  </div>

                  <div class="form-group">
                    <label>Reservation Number</label>
                    <input name="resNumber" type="number" min="1" id="resNumber" class="form-control" placeholder="Reservation Number">
                  </div>
                  <div class="modal-footer">
                    <button type="button" class="btn btn-danger" data-dismiss="modal">Cancel</button>
                    <button class="btn btn-info" name="look" type="submit" id="look" value="Lookup Reservation">Search</button>
                  </div>

                </form>
              </div>
            </div>
          </div>
        </div>
      </div>

      <!-- Get Schedule By Date -->

      <div class="col-sm-3">
        <div class="center">
          <center>
            <button class="btn btn-info" data-toggle="modal" data-target="#date_schedule_modal"> <i class="fa fa-search"></i>
              Schedule by Date</button></center>
        </div>
        <br>

        <div class="modal fade" id="date_schedule_modal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
          <div class="modal-dialog" role="document">
            <div class="modal-content">
              <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">×</span></button>
                <h4 class="modal-title" id="myModalLabel">Schedule by Date</h4>
              </div>
              <div class="modal-body">

                <form method="post" name="lookupDate" action="<?php $_PHP_SELF ?>">

                  <div class="form-group">
                    <label for="resDate">Date</label>
                    <input name="resDate" type="date" id="resDate" class="form-control">
                  </div>

                  <div class="modal-footer">
                    <button type="button" class="btn btn-danger" data-dismiss="modal">Cancel</button>
                    <button class="btn btn-info" name="que" type="submit" id="que" value="Lookup Schedule">Search</button>
                  </div>

                </form>
              </div>
            </div>
          </div>
        </div>
      </div>

      <!-- Edit Reservation -->

      <div class="col-sm-3">
        <div class="center">
          <center>
            <button data-toggle="modal" data-target="#update_modal" class="btn btn-warning"> <i class="fa fa-pencil"></i>
              Reservation</button></center>
        </div>
        <br>

        <div class="modal fade" id="update_modal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
          <div class="modal-dialog" role="document">
            <div class="modal-content">
              <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">×</span></button>
                <h4 class="modal-title" id="myModalLabel">Update Reservation</h4>
              </div>
              <div class="modal-body">


                <form method="post" name="update" input autocomplete="off" action="<?php $_PHP_SELF ?>">

                  <div class="form-group">
                    <label> What reservation do you want to update?</label>
                    <input name="resNumber" type="number" id="resNumber" placeholder="Reservation Number" class="form-control">
                  </div>

                  <div class="form-group">
                    <label>Boat</label>
                    <select name="boatedit" id="boatedit">
                      <option value="0">Select the boat</option>
                      <option value="Jameis">Jameis</option>
                      <option value="Gillum">Gillum</option>
                      <option value="Bowden">Bowden</option>
                      <option value="CString">CString</option>
                      <option value="Renegade">Renegade</option>
                      <option value="Raven">Raven</option>
                    </select>
                  </div>
                  <div class="form-group">
                    <label>Package</label>
                    <select name='packageedit' id="packageedit">
                      <option value="None">Select package</option>
                      <option value="Half Day">Half Day</option>
                      <option value="Full">Full Day</option>
                      <option value="Deep Sea">Deep Sea</option>
                      <option value="Dinner">Dinner</option>
                      <option value="Night">Night</option>
                      <option value="Spearfishing">Spearfishing</option>
                    </select>
                  </div>

                  <div class="form-group">
                    <label>First Name</label>
                    <input name="firstName" type="text" id="firstName" placeholder="First Name" class="form-control">
                  </div>

                  <div class="form-group">
                    <label>Last Name</label>
                    <input name="lastName" type="text" id="lastName" placeholder="Last Name" class="form-control">
                  </div>

                  <div class="form-group">
                    <label>Email</label>
                    <input name="email" type="email" id="email" placeholder="Email" class="form-control">
                  </div>

                  <div class="form-group">
                    <label>Phone</label>
                    <input name="phone" type="tel" id="phone" placeholder="Phone" class="form-control">
                  </div>

                  <div class="form-group">
                    <label>Date</label>
                    <input name="resDate" class="form-control" type="date" id="resDate" min=<?php echo date('Y-m-d');?>>

                  </div>



                  <div class="modal-footer">
                    <button type="button" class="btn btn-default" data-dismiss="modal">Cancel</button>
                    <button class="btn btn-warning" name="update" id="update" type="submit"> <i class="fa fa-pencil"></i>
                      Save Changes</button>
                  </div>
                </form>
              </div>
            </div>
          </div>
        </div>
      </div>

      <!-- /Edit Reservation -->


      <!-- Create Reservation -->

      <div class="col-sm-3">
        <div class="center">
          <center>
            <button class="btn btn-success" data-toggle="modal" data-target="#add_new_record_modal"> <i class="fa fa-plus"></i>
              Reservation</button></center>
        </div>
        <br>

        <div class="modal fade" id="add_new_record_modal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
          <div class="modal-dialog" role="document">
            <div class="modal-content">
              <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">×</span></button>
                <h4 class="modal-title" id="myModalLabel">Add New Reservation</h4>
              </div>
              <div class="modal-body">
                <form method="post" name="create" input autocomplete="off" action="<?php $_PHP_SELF ?>">

                  <div class="form-group">
                    <label>Boat</label>
                    <select name=boat id="boat" onchange="adminTotal()">
                      <option value="0">Select the boat</option>
                      <option value="Jameis">Jameis</option>
                      <option value="Gillum">Gillum</option>
                      <option value="Bowden">Bowden</option>
                      <option value="CString">CString</option>
                      <option value="Renegade">Renegade</option>
                      <option value="Raven">Raven</option>
                    </select>
                  </div>
                  <div class="form-group">
                    <label>Package</label>
                    <select name='package' id="package" onchange="adminTotal()">
                      <option value="None">Select package</option>
                      <option value="Half Day">Half Day</option>
                      <option value="Full Day">Full Day</option>
                      <option value="Deep Sea">Deep Sea</option>
                      <option value="Dinner">Dinner</option>
                      <option value="Night">Night</option>
                      <option value="Spearfishing">Spearfishing</option>
                    </select>
                  </div>

                  <div class="form-group">
                    <label>First Name</label>
                    <input name="firstName" type="text" id="firstName" placeholder="First Name" class="form-control">
                  </div>

                  <div class="form-group">
                    <label>Last Name</label>
                    <input name="lastName" type="text" id="lastName" placeholder="Last Name" class="form-control">
                  </div>

                  <div class="form-group">
                    <label>Email</label>
                    <input name="email" type="email" id="email" placeholder="Email" class="form-control">
                  </div>

                  <div class="form-group">
                    <label>Phone</label>
                    <input name="phone" type="tel" id="phone" placeholder="Phone" class="form-control">
                  </div>



                  <div class="form-group">
                    <label>Date</label>
                    <input name="resDate" class="form-control" type="date" id="resDate" min=<?php echo date('Y-m-d');?>>

                  </div>

                  <div class="form-group">
                    <label>Est. Total</label>
                    <input name="totalPrice" class="form-control" type="text" id="totalPrice" readonly="true" value="<?php echo $total; ?>">
                  </div>


                  <div class="modal-footer">
                    <button type="button" class="btn btn-danger" data-dismiss="modal">Cancel</button>
                    <button class="btn btn-info" name="add" type="submit" id="add" value="Add Reservation">Submit</button>
                  </div>

                </form>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>


    <!-- /Create Reservation -->

    <!-- /Top Modal Buttons -->

    <!-- Results from Buttons -->


    <div class="row">
      <center>
        <?php
if (isset($_POST['look']))
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
      echo "";
      echo "<br>Reservation Number is: "; echo $row["resNumber"];
      echo "<br>Last Name is: "; echo $row["lastName"];
      echo "<br>Boat reserved is: "; echo $row["boat"];
      echo "<br>Package is: "; echo $row["package"];  
      echo "<br>Reservation Date is: "; echo $row["resDate"];
      echo "<br>Estimated Total is: $"; echo $row["totalPrice"];
      echo "";    
  }
} 



if(isset($_POST['que']))
{         
  $resDate = $_POST['resDate'];
  $sql2 = "SELECT resNumber, boat, package, lastName, resDate, totalPrice FROM reservations WHERE resDate = CAST('". $resDate ."' AS DATE)";
  $result = mysql_query($sql2, $conn);
  $num_rows = mysql_num_rows($result);
  if (!$result)
   echo "<br><center>0 results</center>";
  
  if ($num_rows > 0) 
  {
    
    echo '<br><center><table class="table table-bordered table-striped">
    <tr><th>Reservation</th><th>Boat</th><th>Package</th><th>Last Name</th><th>Date</th><th>Price</th></tr>';
      // output data of each row
    while($row = mysql_fetch_assoc($result)) 
    {
      echo "<tr><td>".$row["resNumber"]."</td><td>".$row["boat"]."</td><td>".$row["package"]."</td><td>".$row["lastName"]."</td><td>".$row["resDate"]."</td><td>".$row["totalPrice"]."</td></tr>";
    }
    echo "</table></center>";
    
  } 
   
}

if(isset($_POST['update']))
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
    $resNom = $_POST['resNumber'];
    $boat = $_POST['boatedit'];
    $package = $_POST['packageedit'];         
    $resDate = $_POST['resDate'];

    $query3 = "UPDATE reservations SET firstName = '$firstName', lastName = '$lastName', 
    email = '$email', boat = '$boat', package = '$package', phone = '$phone', 
    resDate = '$resDate' WHERE resNumber = '$resNom'";
    if (!$result = mysql_query($query3, $conn)) {
        exit(mysql_error($conn));
    }
}

if(isset($_POST['delete']))
{

      $resNumber= $_POST['delres'];
 
  // delete User
  $query2 = "DELETE FROM reservations WHERE resNumber = '$resNumber'";
  if (!$result = mysql_query($query2, $conn)) {
    exit(mysql_error($conn));
}

}




   
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
   
    
    $total = $_POST['totalPrice'];
    
    $sqlRes = "INSERT INTO reservations ". "(boat, package, firstName, lastName, email, phone, resDate, totalPrice) ". 
      "VALUES('$boat', '$package', '$firstName', '$lastName', '$email', '$phone', CAST('". $resDate ."' AS DATE), $total)";
              
    $retRes = mysql_query( $sqlRes, $conn );       
        
    if(!$retRes)     
      echo "<br><center>Could not enter data Please check format</center>";     
        
    $res = mysql_result(mysql_query("SELECT resNumber FROM reservations ORDER BY resNumber DESC LIMIT 1"),0);
    
    if ($retRes)
      echo "<br><center>Entered data successfully<br>Created reservation number is $res</center><br>";
    


   $subject="Reservation confirmation from Mark's Charter";
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
   $bodyCust .= "<p>Reserved Date: $resDate</p>";
   $bodyCust .= "<p>Estimated Total: $$total</p>";


    $thankYou="Thank you for your reservation, please contact us if anything is incorrect.";
    mail("markscharter@gmail.com", $subject, $bodyCust, $headers);
    mail("$email", $subject, $bodyCust, $headers);
   
  }


   
   ?>
      </center><br>

    </div>
    <!-- /Results from buttons -->



    <!-- Reservations -->

    <div class="row">
      <div class="col-md-12">
        <h3>
          <center>Reservations:</center>
        </h3>
        <div class="row">
          <center>
            <div class="col-sm-11 addScroll" style="width: 90%;">

              <?php

// find out how many rows are in the table 
$sql = "SELECT COUNT(*) FROM reservations";
$result = mysql_query($sql, $conn) or trigger_error("SQL", E_USER_ERROR);
$r = mysql_fetch_row($result);
$numrows = $r[0];

// number of rows to show per page
$rowsperpage = 5;
// find out total pages
$totalpages = ceil($numrows / $rowsperpage);

// get the current page or set a default
if (isset($_GET['currentpage']) && is_numeric($_GET['currentpage'])) {
   // cast var as int
   $currentpage = (int) $_GET['currentpage'];
} else {
   // default page num
   $currentpage = 1;
} // end if

// if current page is greater than total pages...
if ($currentpage > $totalpages) {
   // set current page to last page
   $currentpage = $totalpages;
} // end if
// if current page is less than first page...
if ($currentpage < 1) {
   // set current page to first page
   $currentpage = 1;
} // end if

// the offset of the list, based on current page 
$offset = ($currentpage - 1) * $rowsperpage;


 
    // Design initial table header 
    $data = '<table class="table table-bordered table-striped">
                        <tr>
                            <th>Reservation No.</th>
                            <th>Date</th>
                            <th>Last Name</th>
                            <th>Boat</th>
                            <th>Package</th>
                            <th>Price</th>
                            <th>Capacity</th>
                            <th>Phone</th>
                            <th>Delete</th>
                        </tr>';
 
// get the info from the db 
    $query = "SELECT * FROM reservations r, boats b WHERE r.boat = b.nickName AND r.resDate >= NOW() ORDER BY resDate LIMIT $offset, $rowsperpage ";
 
    if (!$result = mysql_query($query, $conn)) {
        exit(mysql_error($conn));
    }
 
    // if query results contains rows then featch those rows 
    if(mysql_num_rows($result) > 0)
    {
        while($row = mysql_fetch_assoc($result))
        {
            $data .= '<tr>
                <td>'.$row['resNumber'].'</td>
                <td>'.$row['resDate'].'</td>
                <td>'.$row['lastName'].'</td>
                <td>'.$row['boat'].'</td>
                <td>'.$row['package'].'</td>
                <td>'.$row['totalPrice'].'</td>
                <td>'.$row['capacity'].'</td>
                <td>'.$row['phone'].'</td>

                <td>
                <form method="post" name="delete" input autocomplete="off" action="'.$_PHP_SELF.'">
                  <center>
                  <input name="delres" type="hidden" id="delres" readonly="true" value="'.$row['resNumber'].'">
                  <button class="btn btn-danger" name="delete" id="delete" type="submit" > <i class="fa fa-trash"></i>
                  </button></center>
                </form>
                </td>
            </tr>';
        }

        /******  build the pagination links ******/
// range of num links to show
$range = 3;

// if not on page 1, don't show back links
if ($currentpage > 1) {
   // show << link to go back to page 1
   echo " <a href='{$_SERVER['PHP_SELF']}?currentpage=1'><<</a> ";
   // get previous page num
   $prevpage = $currentpage - 1;
   // show < link to go back to 1 page
   echo " <a href='{$_SERVER['PHP_SELF']}?currentpage=$prevpage'><</a> ";
} // end if 

// loop to show links to range of pages around current page
for ($x = ($currentpage - $range); $x < (($currentpage + $range) + 1); $x++) {
   // if it's a valid page number...
   if (($x > 0) && ($x <= $totalpages)) {
      // if we're on current page...
      if ($x == $currentpage) {
         // 'highlight' it but don't make a link
         echo " [<b>$x</b>] ";
      // if not current page...
      } else {
         // make it a link
         echo " <a href='{$_SERVER['PHP_SELF']}?currentpage=$x'>$x</a> ";
      } // end else
   } // end if 
} // end for
                 
// if not on last page, show forward and last page links        
if ($currentpage != $totalpages) {
   // get next page
   $nextpage = $currentpage + 1;
    // echo forward link for next page 
   echo " <a href='{$_SERVER['PHP_SELF']}?currentpage=$nextpage'>></a> ";
   // echo forward link for lastpage
   echo " <a href='{$_SERVER['PHP_SELF']}?currentpage=$totalpages'>>></a> ";
} // end if
/****** end build pagination links ******/
    }
    else
    {
        // records now found 
        $data .= '<tr><td colspan="6">Records not found!</td></tr>';
    }
 
    $data .= '</table>';
 
    echo $data;
?>
          </center>
        </div>
      </div>
    </div>
    <!-- /Reservations -->




    <!-- Captain Schedule -->

    <div class="row">
      <div class="col-md-12">
        <h4>
          <br>
          <center>This week's captain schedule:</center>
        </h4>
        <div class="row">
          <center>
            <div class="col-sm-11 addScroll" style="width: 90%;">

              <?php

    // Design initial table header 
    $data = '<table class="table table-bordered table-striped">
                        <tr>
                            <th>Date</th>
                            <th>Captain</th>
                            <th>Sail Hours</th>
                            <th>Passenger Capacity</th>
                            <th>Reservation No.</th>
                        </tr>';
 
// get the info from the db 
    $query = "SELECT resDate, captain, time, package, capacity, resNumber FROM reservations r, boats b, packages p WHERE r.boat = b.nickName AND r.package = p.nickName AND WEEKOFYEAR(resDate)=WEEKOFYEAR(NOW()) ORDER BY resDate ";
 
    if (!$result = mysql_query($query, $conn)) {
        exit(mysql_error($conn));
    }
 
    // if query results contains rows then featch those rows 
    if(mysql_num_rows($result) > 0)
    {
        while($row = mysql_fetch_assoc($result))
        {
            $data .= '<tr>
            <td>'.$row['resDate'].'</td>
            <td>'.$row['captain'].'</td>
            <td>'.$row['time'].'</td>
            <td>'.$row['capacity'].'</td>
            <td>'.$row['resNumber'].'</td>
            </tr>';
        }

  
} 
    else
    {
        // records now found 
        $data .= '<tr><td colspan="6">Records not found!</td></tr>';
    }
 
    $data .= '</table>';
 
    echo $data;
?>
          </center>
        </div>
      </div>
    </div>
    <!-- /Captain Schedule -->



    <br>

    <!-- Logout Button -->

    <div class="col-sm-12">
      <form name="form1" method="post" action="logout.php">
        <center>
          <label class="logoutLblPos">

            <button type='submit' name="submit2" class='button btn btn-info form-control'>Logout of Console</button><BR><BR>
          </label>
        </center>
      </form>
      <br />
    </div>
  </div>
  </div>

  <!-- /Logout Button -->

</body>

</html>

<?php 
mysql_close($conn);
include 'footer.php'
;?>