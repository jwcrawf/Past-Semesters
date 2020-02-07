<?php 
include 'header.php';
?>

<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
  <title>Admin Console</title>

  <!-- Bootstrap CSS File  -->
  <link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u"
    crossorigin="anonymous">
</head>

<body>

  <!-- Content Section -->
  <div class="container">
    <div class="row">
      <div class="col-md-12">
        <h1>Admin Console</h1>
      </div>
    </div>
    <div class="row">
      <div class="col-md-12">
        <div class="pull-right">
          <button class="btn btn-success" data-toggle="modal" data-target="#add_new_record_modal">Add New Record</button>
        </div>
      </div>
    </div>
    <div class="row">
      <div class="col-md-12">
        <h3>Records:</h3>
        <div class="row">
          <div class="col-sm-11 " style="width: 300px;">
            <?php
    // include Database connection file 
    include("../rating/rdb_connect.php");
 
    // Design initial table header 
    $data = '<table class="table table-bordered table-striped">
                        <tr>
                            <th>Reservation No.</th>
                            <th>Date</th>
                            <th>Last Name</th>
                            <th>Boat</th>
                            <th>Package</th>
                            <th>Price</th>
                            <th>Update</th>
                            <th>Delete</th>
                        </tr>';
 
    $query = "SELECT * FROM reservations";
 
    if (!$result = mysqli_query($con, $query)) {
        exit(mysqli_error($con));
    }
 
    // if query results contains rows then featch those rows 
    if(mysqli_num_rows($result) > 0)
    {
        $number = 1;
        while($row = mysqli_fetch_assoc($result))
        {
            $data .= '<tr>
                <td>'.$row['resNumber'].'</td>
                <td>'.$row['resDate'].'</td>
                <td>'.$row['lastName'].'</td>
                <td>'.$row['boat'].'</td>
                <td>'.$row['package'].'</td>
                <td>'.$row['totalPrice'].'</td>

                <td>
                    <button onclick="GetUserDetails('.$row['resNumber'].')" class="btn btn-warning">Update</button>
                </td>
                <td>
                    <button onclick="DeleteUser('.$row['resNumber'].')" class="btn btn-danger">Delete</button>
                </td>
            </tr>';
            $number++;
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
          </div>
        </div>
      </div>
    </div>
  </div>
  <!-- /Content Section -->


  <!-- Bootstrap Modals -->
  <!-- Modal - Add New Record/User -->
  <div class="modal fade" id="add_new_record_modal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
    <div class="modal-dialog" role="document">
      <div class="modal-content">
        <div class="modal-header">
          <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">×</span></button>
          <h4 class="modal-title" id="myModalLabel">Add New Reservation</h4>
        </div>
        <div class="modal-body">
        <form method="post" name="create" input autocomplete="off">
          <div class="form-group">
            <label for="boat">Boat</label>
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
            <label for="package">Package</label>
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
            <label for="firstName">First Name</label>
            <input type="text" id="firsName" placeholder="First Name" class="form-control" />
          </div>

          <div class="form-group">
            <label for="lastName">Last Name</label>
            <input type="text" id="lastName" placeholder="Last Name" class="form-control" />
          </div>

          <div class="form-group">
            <label for="email">Email Address</label>
            <input type="text" id="email" placeholder="Email Address" class="form-control" />
          </div>

          <div class="form-group">
            <label for="phone">Phone</label>
            <input name="phone" type="tel" id="phone">
          </div>

          <div class="form-group">
            <label for="resDate">Date</label>
            <input name="resDate" type="date" id="resDate" min=<?php echo date('Y-m-d');?>>
          </div>

          <div class="form-group">
            <label for="totalPrice">Est. Total</label>
            <input name="totalPrice" type="text" id="totalPrice" readonly="true" value="<?php echo $total; ?>" />
          </div>

        </div>
        <div class="modal-footer">
          <button type="button" class="btn btn-default" data-dismiss="modal">Cancel</button>
          <button type="submit" name="add" id="add" class="btn btn-primary" onclick="addRecord()">Add Record</button>
        </div>
      </form>
      </div>
    </div>
  </div>
  <!-- // Modal -->

  <!-- Modal - Update User details -->
  <div class="modal fade" id="update_user_modal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
    <div class="modal-dialog" role="document">
      <div class="modal-content">
        <div class="modal-header">
          <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">×</span></button>
          <h4 class="modal-title" id="myModalLabel">Update</h4>
        </div>
        <div class="modal-body">

          <div class="form-group">
            <label for="update_firstName">First Name</label>
            <input type="text" id="update_firstName" placeholder="First Name" class="form-control" />
          </div>

          <div class="form-group">
            <label for="update_lastName">Last Name</label>
            <input type="text" id="update_lastName" placeholder="Last Name" class="form-control" />
          </div>

          <div class="form-group">
            <label for="update_email">Email Address</label>
            <input type="text" id="update_email" placeholder="Email Address" class="form-control" />
          </div>

          <div class="form-group">
            <label for="update_email">Email Address</label>
            <input type="text" id="update_email" placeholder="Email Address" class="form-control" />
          </div>

          <div class="form-group">
            <label for="update_bpat">Boat</label>
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
            <label for="update_package">Package</label>
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
            <label for="update_resDate">Date</label>
            <input name="resDate" type="date" id="resDate" min=<?php echo date('Y-m-d');?>>
          </div>

          <div class="form-group">
            <label for="update_email">Est. Total</label>
            <input name="totalPrice" type="text" id="totalPrice" readonly="true" value="<?php echo $total; ?>" />
          </div>

        </div>
        <div class="modal-footer">
          <button type="button" class="btn btn-default" data-dismiss="modal">Cancel</button>
          <button type="button" class="btn btn-primary" onclick="UpdateUserDetails()">Save Changes</button>
          <input type="hidden" id="hidden_user_id">
        </div>
      </div>
    </div>
  </div>
  <!-- // Modal -->

  <!-- Jquery JS file -->
  <script src="https://code.jquery.com/jquery-2.2.4.min.js"></script>

  <!-- Bootstrap JS file -->
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js" integrity="sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa"
    crossorigin="anonymous"></script>

  <!-- Custom JS file -->
  <script type="text/javascript" src="crud.js"></script>
  <script src="pack2.js"></script>

</body>

</html>

<?php 
include 'footer.php'
;?>