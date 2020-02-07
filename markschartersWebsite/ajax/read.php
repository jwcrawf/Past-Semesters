<?php
// include Database connection file
include("../../rating/rdb_connect.php");
 
// check request
if(isset($_POST['resNumber']) && isset($_POST['resNumber']) != "")
{
    // get User ID
    $res_id = $_POST['resNumber'];
 
    // Get User Details
    $query = "SELECT * FROM reservations WHERE resNumber = '$res_id'";
    if (!$result = mysqli_query($con, $query)) {
        exit(mysqli_error($con));
    }
    $response = array();
    if(mysqli_num_rows($result) > 0) {
        while ($row = mysqli_fetch_assoc($result)) {
            $response = $row;
        }
    }
    else
    {
        $response['status'] = 200;
        $response['message'] = "Data not found!";
    }
    // display JSON data
    echo json_encode($response);
}
else
{
    $response['status'] = 200;
    $response['message'] = "Invalid Request!";
}