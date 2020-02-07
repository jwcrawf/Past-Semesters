<?php
// check request
if(isset($_POST['resNumber']) && isset($_POST['resNumber']) != "")
{
    // include Database connection file
    include("dbconnect.php");
 
    // get user id
    $res_id = $_POST['resNumber'];
 
    // delete User
    $query = "DELETE FROM reservations WHERE resNumber = '$res_id'";
    if (!$result = mysql_query($query, $conn)) {
        exit(mysql_error($conn));
    }
}
?>
<!--- old modal I wish worked
<div class="modal fade" id="delete_modal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
            <div class="modal-dialog" style="width: 300px" role="document">
              <div class="modal-content">
                <div class="modal-header">
                  <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">×</span></button>
                  <h4 class="modal-title" id="myModalLabel">Delete Reservation</h4>
                </div>
                <div class="modal-body">
                <form method="post" name="create" input autocomplete="off" action="<?php $_PHP_SELF ?>">


                    <div class="alert alert-danger fade in">
                    <div class="form-group">
                      <input name="resNumber" id="resNumber" class="form-control" value="<?php echo trim($_GET["delres"]); ?>" />
      </div>
                      <center>
                        <p>Are you sure you want <br>to delete this record?</p>
                      </center><br>
      
                      <p>
      
                        <div class="modal-footer">
                          <center>
                            <button type="button" class="btn btn-default" data-dismiss="modal">Cancel</button>
                            <button class="btn btn-danger" name="delete" type="submit" id="delete" value="Delete">Delete</button></center>
                        </div>
                      </p>
                    </div>
                </div>
              </div>
            </div>
          </div>

          -->