<?php
session_start();
unset($_SESSION);
session_destroy();
session_write_close();
header('Location: http://ww2.cs.fsu.edu/~crawford/marks/login.php');
die;
?>