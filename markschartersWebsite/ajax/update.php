<?php
// include Database connection file
include("../../rating/rdb_connect.php");

 
// check request
if(isset($_POST))
{
    // get values
    $res_id = $_POST['resNumber'];
    $firstName = $_POST['firstName'];
    $lastName = $_POST['lastName'];
    $email = $_POST['email'];
    $boat = $_POST['boat'];
    $package = $_POST['package'];
    $totalPrice = $_POST['totalPrice'];
    $phone = $_POST['phone'];
    $resDate = $_POST['resDate'];


 
    // Updaste User details
    $query = "UPDATE reservations SET firstName = '$firstName', lastName = '$lastName', email = '$email', boat = '$boat', package = '$package', resDate = '$resDate', totalPrice = '$totalPrice', phone = '$phone',  WHERE resNumber = '$res_id'";
    if (!$result = mysqli_query($con, $query)) {
        exit(mysqli_error($con));
    }
}