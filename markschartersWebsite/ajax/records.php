<?php
    // include Database connection file 
    include("../../rating/rdb_connect.php");
 
    // Design initial table header 
    $data = '<table class="table table-bordered table-striped">
                        <tr>
                            <th>Reservation No.</th>
                            <th>Date</th>
                            <th>First Name</th>
                            <th>Last Name</th>
                            <th>Email Address</th>
                            <th>Boat</th>
                            <th>Package</th>
                            <th>Price</th>
                            <th>Phone</th>
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
                <td>'.$row['firstName'].'</td>
                <td>'.$row['lastName'].'</td>
                <td>'.$row['email'].'</td>
                <td>'.$row['boat'].'</td>
                <td>'.$row['package'].'</td>
                <td>'.$row['totalPrice'].'</td>
                <td>'.$row['phone'].'</td>

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