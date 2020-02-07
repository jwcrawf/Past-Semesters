<?php include 'header.php';
?>
	<div class="login wowload fadeInUp">
		<center>
			<?php session_start();
$errorMsg="";
$validUser=$_SESSION["login"]===true;

if(isset($_POST["submit"])) {
	$validUser=$_POST["username"]=="admin"&& $_POST["password"]=="password";
	if( !$validUser) $errorMsg="Invalid username or password.";
	else $_SESSION["login"]=true;
}

if($validUser) {
	header("Location: http://ww2.cs.fsu.edu/~crawford/marks/admincrud.php");
	die();
}

?>

			<body>
				<h3>Admin Login</h3>
				<form name="input" action="" method="post"><label for="username">
						Username:
					</label><input class='input text-center form-control' placeholder='Username' type="text" id="username" name="username" /><br><br><label
					 for="password">
						Password:
					</label><input class='input text-center form-control' placeholder='Password' type="password" value="" id="password"
					 name="password" />
					<div class="error">
						<?=$errorMsg ?>
					</div>
					<br>
					<button type='submit' name="submit" class='button btn btn-info form-control'>Login</button><BR><BR>
		</center>
	</div>
</div>
</form>
</body>

</html>
<?php include 'footer.php';
?>