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
<h1>Teams</h1>
<form action="getTeams.php" method="POST">
Team Name: <input type="radio" name="order" value="Team_Name"><br>
City Name: <input type="radio" name="order" value="City"><br>
<input type="submit" value="Order Teams">
</form>

<h1>Insert New Team</h1>
<form action="insertTeam.php" method="POST">
New Team's Name: <input type="text" name="teamname"><br>
New Team's City: <input type="text" name="teamcity"><br>
<input type="submit" value="Add New Team">
</form>

<h1>Delete Team</h1>
<form action="deleteTeam.php" method="POST">
ID of Team to Delete: <input type="text" name="teamID"><br>
<input type="submit" value="Delete Team">
</form>

<h1>Update Game City</h1>
<form action="updateGame.php" method="POST">
ID of Game to Update: <input type="text" name="gameID"><br>
<input type="submit" value="Update Game">
</form>

<h1>Game Info</h1>
<form action="showGame.php" method="POST">
ID of Game to Show: <input type="text" name="gameID"><br>
<input type="submit" value="Game Info">
</form>

<h1> List Officials </h1>
<?php
$query = 'SELECT * FROM officials ORDER BY last_name';
$result = pg_query($query);
if (!$result){
	die("DB query failed");
}
$i = pg_num_fields($result);
for ($j=0; $j<$i; $j++){
	$fieldname = pg_field_name($result,$j);
	echo ($fieldname." | ");
}
echo ("<br>");
while ($row = pg_fetch_row($result)){
	echo ("<li>");
	echo $row[0]." | ".$row[1]." | ".$row[2]." | ".$row[3];
}
?>

<h4> Maple Leafs Curse </h4>
<form action="leafCurse.php" method="POST">
Score of games Leafs played in: <input type="radio" name="curse" value="score"><br>
Name of official who has did most Leafs games: <input type="radio" name="curse" value="games"><br>
Name of official who has did most Leafs losses: <input type="radio" name="curse" value="losses"><br>
Name of official who has did most Leafs wins: <input type="radio" name="curse" value="wins"><br>
<input type="submit" value= "Submit Curse ;^)">
</form>

</php
	pg_close($connection);
?>
</body>
</html>
