<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Assignment 3 NHL</title>
</head>
<body>
<?php
include 'connectdb.php';
?>
<?php
$updateID = $_POST["gameID"];
$query1 = 'SELECT game_ID FROM Games WHERE game_ID = \''.$updateID.'\'';
$result = pg_query($query1);
if (!$result) {
   die("error on select ID query");
}
if (pg_num_rows($result)>0){
   $query2 = 'SELECT Location FROM games WHERE game_ID = \''.$updateID.'\'';
   $result2 = pg_query($query2);
   if (!$result2) {
      die("error on delete ID query");
   }
   echo ("Game with ID of ".$updateID." is played in: ");
   $row = pg_fetch_row($result2);
   echo $row[0];
   ?>
   <h1>Update Game City</h1>
   <form action="updateCity.php" method="POST">
   New name of City: <input type="text" name="cityName"><br>
   ID of Game to Update: <input type="text" name="gameID" value="<?php echo $updateID?>" readonly><br>
   <input type="submit" value="Update City">
   </form>
   <?php   
}
else{
   echo ("That ID does not exist, therefor cannot be updated.");
}
?>
</ol>
</body>
</html>
