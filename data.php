<?php
/*header("Refresh:3");*/
?>
<html>
<head><link href="styles/style.css" rel="stylesheet" type="text/css"></head>
<body>

<?php 
	$weather = file('weather.txt');
	echo"<div><table class=tweather>";
	foreach($weather as $line_num => $weather_data){
		echo " <tr><td>$weather_data</td></tr>";
	}
	echo"</table></div>"
?>
</body>
</html>
