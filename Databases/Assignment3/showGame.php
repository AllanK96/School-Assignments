<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Game Info</title>
</head>
<body>
<?php
include 'connectdb.php';
?>
<?php

$gameID = $_POST["gameID"];

$query2 = 'SELECT tmp.game_ID, location, city, game_date, tmp.team_name, score, head_official  FROM (SELECT games.game_ID, location, game_date, team_name, score, head_official FROM games, games_played 
WHERE games.game_ID = games_played.game_ID ORDER BY games.game_ID) as tmp, team WHERE team.team_name=tmp.team_name AND game_ID= \''.$gameID.'\'';

$query1 = 'SELECT first_name, last_name FROM officials, games_refd WHERE games_refd.game_ID = \''.$gameID.'\' AND games_refd.official_id = officials.official_id';

$result = pg_query($query2);
if (!$result) {
   die("error on select ID query");
}
if (pg_num_rows($result)>0){
     echo "<ol>";
     $i = pg_num_fields($result);
     for ($j = 1; $j < $i-1; $j++){
        $fieldname = pg_field_name($result,$j);
	echo ($fieldname." | ");
     }
     
     while ($row = pg_fetch_row($result)) {
        echo("<br>");
	$head = $row[6];
        echo $row[1]." | ".$row[2]." | ".$row[3]." | ".$row[4]." | ".$row[5]." | ";
     }
     echo ("<br>");
     $query = 'SELECT first_name, last_name FROM officials WHERE official_ID = \''.$head.'\'';
     $result = pg_query($query);
     $row = pg_fetch_row($result);
     echo "<br> <font color=\"red\">The Head Official Was: ".$row[0]." ".$row[1]."</font>";

     $result = pg_query($query1);
     if (!$result) {
        die("error on select ID query");
     }
     echo ("<br> <br> Referees: <br> ");
     echo(pg_field_name($result,0)." | ".pg_field_name($result,1));
     while ($row = pg_fetch_row($result)) {
        echo("<br>");
        echo $row[0]." | ".$row[1];
     }     
     echo "</ol>";
}
else{
   echo ("That ID does not exist.");
}
?>
</ol>
<?php
   pg_close($connection);
?>
</body>
</html>
