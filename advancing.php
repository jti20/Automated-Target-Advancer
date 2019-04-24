
<html>
<body>
<head><link href = "styles/style.css" rel ="stylesheet" type = "text/css">
</head>
<?php
header("Refresh:5; url=advance2.php");
 /*$output= shell_exec('python target_advance.py');*/
 $output = shell_exec('echo "1" > /dev/ttyS0');
?>
<img  class = "imgbutton" src="advancing_button.jpg" />
</body>
</html>
