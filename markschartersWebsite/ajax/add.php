<?php
	if(isset($_POST['firstName']) && isset($_POST['lastName']) && isset($_POST['email']) && isset($_POST['boat']) && isset($_POST['package']) && isset($_POST['resDate']) && isset($_POST['totalPrice']) && isset($_POST['phone']))
	{
		// include Database connection file 
    include("../../rating/rdb_connect.php");
		

		// get values 
		$firstName = $_POST['firstName'];
		$lastName = $_POST['lastName'];
    $boat = $_POST['boat'];
    $package = $_POST['package'];
    $phone = $_POST['phone'];
    $resDate = $_POST['resDate'];
    $totalPrice = $_POST['totalPrice'];
    $email = $_POST['email'];
    

		$query = "INSERT INTO reservations(boat, package, firstName, lastName, email, phone, resDate, totalPrice) VALUES('$boat', '$package', '$firstName', '$lastName', '$email', '$phone', CAST('". $resDate ."' AS DATE), '$total')";
		if (!$result = mysqli_query($con, $query)) {
	        exit(mysqli_error($con));
	    }
	    echo "1 Record Added!";
	}
?>