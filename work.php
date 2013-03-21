<html>

<?php
  require_once('include/base.inc');
  
  $mf = isset($_POST['MyFigure']) ? $_POST['MyFigure'] : 'x';
  $fh = isset($_POST['FirstHod']) ? $_POST['FirstHod'] : '0';
  if (isset($_POST['HodHistory'])) {
    $hh = $_POST['HodHistory'];
    for ($y = $i = 0; $y < 3; $y++)
      for ($x = 0; $x < 3; $x++, $i++)
        //if (isset($_POST['pole' . $y . $x]['x'])) {
        if (isset($_POST['pole' . $y . $x .'_x'])) {            
          $hh[$i] = $mf;
          break 2;
        }
  }
  else $hh = '';  // здесь можно выставить начальное состояние (для отладки)

  $ex = new cX0($hh, $mf, $fh);

  require_once('include/header.inc');
?>

<link rel=stylesheet type="text/css" href="stylex0.css">
<body>

<?php 
  echo $ex->PrepareForm($_SERVER['PHP_SELF']);
?>

<p>Copyright 2008, null</p>
</body>
</html>