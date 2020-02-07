

// READ records
function readRecords() {
  $.get("ajax/records.php", {}, function (data, status) {
      $(".records_content").html(data);
  });
}


function DeleteUser(res_id) {
  var conf = confirm("Are you sure, do you really want to delete Reservation?");
  if (conf == true) {
      $.post("ajax/delete.php", {
              res_id: res_id
          },
          function (data, status) {
              // reload Users by using readRecords();
              readRecords();
          }
      );
  }
}

function GetUserDetails(res_id) {
  // Add User ID to the hidden field for future usage
  $("#hidden_user_id").val(res_id);
  $.post("ajax/read.php", {
          res_id: res_id
      },
      function (data, status) {
          // PARSE json data
          var user = JSON.parse(data);
          // Assing existing values to the modal popup fields
          $("#update_firstName").val(user.firstName);
          $("#update_lastName").val(user.lastName);
          $("#update_email").val(user.email);
          $("#update_boat").val(user.boat);
          $("#update_package").val(user.package);
          $("#update_phone").val(user.phone);
          $("#update_resDate").val(user.resDate);
          $("#update_totalPrice").val(user.totalPrice);

      }
  );
  // Open modal popup
  $("#update_user_modal").modal("show");
}

function UpdateUserDetails() {
  // get values
  var firstName = $("#update_firstName").val();
  var lastName = $("#update_lastName").val();
  var email = $("#update_email").val();
  var boat = $("#update_boat").val();
  var package = $("#update_package").val();
  var totalPrice = $("#update_totalPrice").val();
  var phone = $("#update_phone").val();
  var resDate = $("#update_resDate").val();


  // get hidden field value
  var res_id = $("#hidden_user_id").val();

  // Update the details by requesting to the server using ajax
  $.post("ajax/update.php", {
          res_id: res_id
          firstName: firstName,
          lastName: lastName,
          email: email,
          boat: boat,
          package: package,
          totalPrice: totalPrice,
          phone: phone,
          resDate: resDate
      },
      function (data, status) {
          // hide modal popup
          $("#update_user_modal").modal("hide");
          // reload Users by using readRecords();
          readRecords();
      }
  );
}

$(document).ready(function () {
  // READ recods on page load
  readRecords(); // calling function
});