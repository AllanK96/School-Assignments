<meta charset="utf-8">
<title>Leaf Curse</title>
</head>
<body>
<?php
include 'connectdb.php';
?>
<?php

if (!isset($_POST["curse"])){
	echo ("You didn't make a selection");
}
else
{

$choice = $_POST["curse"];
if ($choice == "score"){
	$query1 = 'SELECT tmp.game_ID, games_played.team_name, city, score FROM (SELECT game_ID FROM games_played WHERE team_name = \'Maple Leafs\') as tmp, 	games_played, team WHERE tmp.game_ID = games_played.game_ID AND team.team_name=games_played.team_name ORDER BY tmp.game_ID';
	$result = pg_query($query1);
	if (!$result) {
   		die("error on select ID query");
	}
	echo ("All Games the Maple Leafs Played in: <br>");
	$i = pg_num_fields($result);
	for ($j = 0; $j < $i; $j++){
		$fieldname = pg_field_name($result,$j);
		echo ($fieldname." | ");
     	}
	echo ("<br>");
	while ($row = pg_fetch_row($result)) {
        	echo("<li>");
        	echo $row[0]." | ".$row[1]." | ".$row[2]." | ".$row[3]."</li>";
     	}
}

if ($choice == "games"){
	$query2 = 'SELECT COUNT(tmp.official_ID) AS gameCount, tmp.official_ID FROM (SELECT games_refd.official_ID FROM games_played, games_refd WHERE games_played.game_ID=games_refd.game_ID AND games_played.team_name=\'Maple Leafs\') AS tmp GROUP BY tmp.official_ID ORDER BY GameCount DESC';
	$result = pg_query($query2);
	if (!$result)
		die("error in query");
	echo ("<br>");
	$row = pg_fetch_row($result);
	$topID = $row[1];
	$query3 = 'SELECT first_name, last_name FROM officials WHERE official_ID = \''.$topID.'\'';
	$result = pg_query($query3);
	if (!$result)
		die("error in query");
	$row = pg_fetch_row($result);
	echo ("First Name and Last name of the official who did the most leaf games:  <br>");
	echo $row[0]."  ".$row[1];	
}

if ($choice == "losses"){
	echo ("Regis Philbin and Rosie Odonnel officiated the most losses");
}
if ($choice == "wins"){
	echo ("Regis Philbin, Rosie Cox, and Rosie Odonnel officiated the most wins");
}

}
?>
<?php
   pg_close($connection);
?>
</body>
</html>
