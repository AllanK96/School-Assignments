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

<h1>Deleting Team...</h1>
<?php
$delID = $_POST["teamID"];
$query1 = 'SELECT team_ID FROM team WHERE team_ID = \''.$delID.'\'';
$result = pg_query($query1);
if (!$result) {
   die("error on select ID query");
}
if (pg_num_rows($result)>0){
   $query2 = 'DELETE FROM team WHERE team_ID = \''.$delID.'\'';
   $result2 = pg_query($query2);
   if (!$result) {
      die("error on delete ID query");
   }
   echo ("Team with ID ".$delID." was deleted");
}
else{
   echo ("That ID does not exist, therefor cannot be deleted.");
}
pg_close($connection);
?>
</ol>
</body>
</html>
