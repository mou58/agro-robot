<?php
include("connect.php");
if(isset($_POST["finish"]))
{
	$fruitr = $_POST["fruitr"];
$sql="INSERT INTO fruit_color (id,fruitr,fruitb)
VALUES
('NULL','$fruitr','$_POST[fruitb]')";

if (!mysql_query($sql,$con))
  {
  die('Error: ' . mysql_error());
  }
  else
  {
$res =  "User Registered Successfully...";
  }
}
?>
<?php
include("connect2.php");
if(isset($_POST["finish"]))
{
	$leafgr = $_POST["leafgr"];
$sql="INSERT INTO leafc (id,leafgr,leafyl)
VALUES
('NULL','$leafgr','$_POST[leafyl]')";

if (!mysql_query($sql,$con))
  {
  die('Error: ' . mysql_error());
  }
  else
  {
$res1 =  "User Registered Successfully...";
  }
}
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
	<title>Agri Doctor</title>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<meta name="description" content="" />
	<meta name="keywords" content="" />
	<meta name="robots" content="index,follow" />
	<link rel="stylesheet" type="text/css" href="styles.css" />
</head>

<body>
<center>
<h1>Fruit Color</h1>
<form action="localhost1.php" method = "POST"  >
<?php echo $res ?> 
<input type="text" name="fruitr" value="" placeholder= "Red" />
<input type="text" name="fruitb" value="" placeholder= "Black"/>
<input type="submit" value="Submit" name = "finish" />
</form>
<h1>Leaf Color</h1>
<form action="localhost1.php" method = "POST"  >
<?php echo $res1 ?> 
<input type="text" name="leafgr" value="" placeholder= "Green" />
<input type="text" name="leafyl" value="" placeholder= "Yellow"/>
<input type="submit" value="Submit" name = "finish" />
</form>
</center>
</body>
</html>
